#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


#include "dht.h"
#include "usbdrv.h"
#include "util.h"



//USB command
#define USB_LED_OFF	0
#define USB_LED_ON	1
#define USB_READ	2

#define PORT_LED	PORTD
#define PIN_LED		PIND5
#define DDR_LED		DDRD

static uchar dataReceived = 0;
static uchar dataLength = 0;

static uchar replyBuf[6];

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = { /* USB report descriptor */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};

void setup(void);
void setup_watchdog(void);
void blink_led(void);

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void *)data; // custom command is in bRequest field
	DHT_ERROR_t errorCode = 0;
		
	switch(rq->bRequest)
	{
	
		case USB_LED_ON:
			sbi(PORT_LED, PIN_LED); //turn LED on
			return 0;
		
		/*
		case USB_LED_OFF:
			cbi(PORT_LED, PIN_LED); //turn LED off
			return 0;
		*/
		
		
		case USB_READ:
		{
			errorCode = readDHT(replyBuf);
			replyBuf[5] = errorCode;
			usbMsgPtr = replyBuf;
			return sizeof(replyBuf);
		}
	}
	return 0;
}

void    usbEventResetReady(void)
{
}

USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
	uchar i;
	
	for(i=0; dataReceived < dataLength && i < len; i++, dataReceived++)
		replyBuf[dataReceived] = data[i];
	
	return (dataReceived == dataLength);
}


int main(void)
{
	cli();
	setup();
	setup_watchdog(); 
	usbInit();
	usbDeviceDisconnect(); //enforce re-enumeration
		
	_delay_ms(500);
		
	usbDeviceConnect();
	
	set_sleep_mode(SLEEP_MODE_IDLE);    // Set Sleep Mode: Power Down
		
	sei();
	
	cbi(PORT_LED, PIN_LED);
	sleep_enable();

	while(1)
	{
		usbPoll();
		/*if(usbInterruptIsReady()){ 
            
            usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
            
        }*/
		
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
	DHT_PORT = 0x0;
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