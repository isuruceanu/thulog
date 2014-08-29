#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <avr/pgmspace.h>
#include <util/delay.h>



#include "usbdrv.h"
#include "util.h"



//USB command
#define USB_LED_OFF	2
#define USB_LED_ON	1
#define HIDSERIAL_INBUFFER_SIZE 32


#define PORT_LED	PORTD
#define PIN_LED		PIND3
#define DDR_LED		DDRD

//static uchar dataReceived = 0;
//static uchar dataLength = 0;

static uchar replyBuf[8];

PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x09, 0x00,                    //   USAGE (Undefined)  
    0x82, 0x02, 0x01,              //   INPUT (Data,Var,Abs,Buf)
    0x95, HIDSERIAL_INBUFFER_SIZE, //   REPORT_COUNT (32)
    0x09, 0x00,                    //   USAGE (Undefined)        
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

void setup(void);

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
	}
	return 0;
}



int main(void)
{
	cli();
	setup();
	
	usbDeviceDisconnect(); //enforce re-enumeration
		
	_delay_ms(500);
		
	usbDeviceConnect();
	
	wdt_enable(WDTO_1S);
	
	usbInit();
		
	sei();

	while(1)
	{
		wdt_reset();
		usbPoll();
		if(usbInterruptIsReady()){ 
            
            usbSetInterrupt(replyBuf, sizeof(replyBuf));
            
        }
		
	}
}

void setup(void)
{
	sbi(DDR_LED, PIN_LED); //set led pin as ouput
	sbi(PORT_LED, PIN_LED); 
	
	ACSR = (1<<ACD); //Turn off Analog Comparator
}
