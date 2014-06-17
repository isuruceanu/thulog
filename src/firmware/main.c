#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "usbdrv.h"

#define F_CPU 12000000L
//#include <util/delay.h>

#define USB_LED_OFF	0
#define USB_LED_ON	1
#define USB_READ	2

#define PORT_LED	PORTD
#define PIN_LED		PIND3
#define DRR_LED		DDRD


static uchar dataReceived = 0;
static uchar dataLength = 0;
static uchar replyBuf[16];

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void *)data; // custom command is in bRequest field
	unsigned int v, i;
	
	switch(rq->bRequest)
	{
		case USB_LED_ON:
			PORT_LED |= (1<<PIN_LED); //turn LED on
			return 0;
		
		case USB_LED_OFF:
			PORT_LED &= ~(1<<PIN_LED); //turn LED off
			return 0;
		
		case USB_READ:
			//read sensor and fill replayBuf with response
			usbMsgPtr = replyBuf;
			return sizeof(replyBuf);
	}
	return 0;
}

int main(void)
{
	while(1)
	{
		wdt_reset(); //keep the watchdog happy
		usbPoll();
	}
}