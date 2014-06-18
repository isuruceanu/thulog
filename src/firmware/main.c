#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#include "usbdrv.h"
#include "util.h"

#include <util/delay.h>
#include "dht.h"

//USB command
#define USB_LED_OFF	0
#define USB_LED_ON	1
#define USB_READ	2

#define PORT_LED	PORTD
#define PIN_LED		PIND3
#define DDR_LED		DDRD


static uchar dataReceived = 0;
static uchar dataLength = 0;
static uchar replyBuf[16];


void setup(void);
void system_sleep(void);
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
			//read sensor and fill replayBuf with response
			usbMsgPtr = replyBuf;
			return sizeof(replyBuf);
	}
	return 0;
}

USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	uchar i;
	
	for(i=0; dataReceived < dataLength && i < len; i++, dataReceived++)
		replyBuf[dataReceived] = data[i];
	
	return (dataReceived == dataLength);
}


/*

1. from the start mcu is going to sleep. Each 4 seconds its wakeup and toggle the led
2. if usb request is comming it automaticale wakeups and serve the request 
*/

int main(void)
{
	setup();


	sbi(PORT_LED, PIN_LED);
	_delay_ms(500);
	cbi(PORT_LED, PIN_LED);
	_delay_ms(500);
	sbi(PORT_LED, PIN_LED);
	_delay_ms(500);
	cbi(PORT_LED, PIN_LED);
	_delay_ms(500);


	cli();
	
	usbInit();
	usbDeviceDisconnect(); //enforce re-enumeration
		
	_delay_ms(500);
	
	usbDeviceConnect();
	
	setup_watchdog(); 

	set_sleep_mode(SLEEP_MODE_IDLE);    // Set Sleep Mode: Power Down
	sleep_enable();
	
	sei();

	while(1)
	{
		wdt_reset();
		usbPoll();
		
		if (MCUCR & _BV(SE))
		{
			sleep_mode();
		}
	}
}

ISR(WDT_vect)
{
  sleep_disable();
  blink_led();
  sleep_enable();
}

void setup(void)
{
	sbi(DDR_LED, PIN_LED); //set led pin as ouput
	cbi(PORT_LED, PIN_LED); 
	
	ACSR = (1<<ACD); //Turn off Analog Comparator
}

void setup_watchdog()
{
	
	MCUSR &= ~(1<<WDRF); // clear the watchdog reset
	// set up watchdog timer
	WDTCSR |= (1 << WDCE ) | ( 1 << WDE );
	WDTCSR |= (1 << WDIE );
	WDTCSR |= (1 << WDP3) | (1 << WDP0); // timer goes off every 8 seconds

}

void blink_led(void)
{
	sbi(PORT_LED, PIN_LED);
	_delay_ms(100);
	cbi(PORT_LED, PIN_LED);
}