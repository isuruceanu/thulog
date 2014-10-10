#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#include <avr/pgmspace.h>
#include <util/delay.h>


#include "usbdrv.h"
#include "util.h"
#include "dht.h"



//USB command
#define USB_LED_ON	1
#define USB_LED_OFF	2
#define USB_READ 	3
#define HIDSERIAL_INBUFFER_SIZE 32


#define PORT_LED	PORTD
#define PIN_LED		PIND5
#define DDR_LED		DDRD

//static uchar dataReceived = 0;
//static uchar dataLength = 0;

static uchar replyBuf[8];


void setup(void);
void setup_watchdog(void);
void blink_led(void);

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void *)data; // custom command is in bRequest field
	
	switch(rq->bRequest)
	{
	
		case USB_LED_ON:
			sbi(PORT_LED, PIN_LED); //turn LED on
			return 0;
		
		
		case USB_LED_OFF:
			cbi(PORT_LED, PIN_LED); //turn LED off
			return 0;
		
		case USB_READ:
			readDHT(replyBuf);
			//replyBuf[5] = 0x04;
			usbMsgPtr = replyBuf;
			return sizeof(replyBuf);
	}
	return 0;
}

USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len) {
	return 0;
}


int main(void)
{
	cli();
	setup();
	
	usbDeviceDisconnect(); //enforce re-enumeration
		
	_delay_ms(500);
		
	usbDeviceConnect();
	
	
	
	usbInit();
	setup_watchdog(); 
	set_sleep_mode(SLEEP_MODE_IDLE); 
	
		
	sei();
	
	cbi(PORT_LED, PIN_LED);
	sleep_enable();

	while(1)
	{
		usbPoll();
		sbi(WDTCSR, WDIE);
		sleep_enable();
	}
}

ISR(WDT_OVERFLOW_vect)
{
	sleep_disable();
	blink_led();
}

void setup(void)
{
	sbi(DDR_LED, PIN_LED); //set led pin as ouput
	sbi(PORT_LED, PIN_LED); 
	
	ACSR = (1<<ACD); //Turn off Analog Comparator
}

void setup_watchdog()
{
	MCUSR &= ~(1<<WDRF); // clear the watchdog reset
	// set up watchdog timer
	WDTCSR |= (1 << WDCE ) | ( 1 << WDE );
	WDTCSR |= (1 << WDIE );
	WDTCSR |= (1 << WDP3); // timer goes off every 4 seconds
}

void blink_led(void)
{
	sbi(PORT_LED, PIN_LED);
	_delay_ms(100);
	cbi(PORT_LED, PIN_LED);
}
