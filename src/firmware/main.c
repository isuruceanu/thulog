#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "usbdrv.h"
#include "util.h"

#define F_CPU 12000000L
#include <util/delay.h>

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


void setup(void);



int main(void)
{
	wdt_enable(WDTO_1S); //enable 1s watchdog timer
	usbInit();
	
	usbDeviceDisconnect(); //enforce re-enumeration
		
	_delay_ms(500);

	usbDeviceConnect();
	sei();

	while(1)
	{
		wdt_reset(); //keep the watchdog happy
		usbPoll();
	}
}

void setup(void)
{
	sbi(DDR_LED, PIN_LED); //set led pin as ouput
	sbi(PORT_LED, PIN_LED); //swich on the led by default
}