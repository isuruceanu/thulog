#include "dht.h"
#include <avr/interrupt.h>

#define F_CPU 12000000L
#include <util/delay.h>
#include "util.h"

unsigned char checkForError(unsigned char timeout);


PUBLIC DHT_ERROR_t readDHT(unsigned char *dht_data)
{
	unsigned char retryCount = 0;
	unsigned char i, j;
	

	cli(); //disable interrupts
	cbi(DHT_DDR, DHT_BIT); //set pin as input
	sei(); //enable interrupts
	
	//try to connect to bus
	if (checkForError(125))
	{
		return DHT_BUS_HUNG;
	}
		
	//Send the activate pulse
	cli();
	cbi(DHT_PORT, DHT_BIT);
	sbi(DHT_DDR, DHT_BIT);
	sei();
	
	_delay_ms(20);
	cli();
	cbi(DHT_DDR, DHT_BIT);
	sei();
	
	//Find the start of the ACK signal
	if (checkForError(25))
	{
		return DHT_ERROR_NOT_PRESENT;
	}
	
	//Sensor responded pulling the line down
	//Find the transition of the ACK signal
	if (checkForError(50)) // Spec is 80us 50*2 = 100us
	{
		return DHT_ERROR_ACK_TOO_LONG;
	}
	
    // Here sensor pulled up
    // Find the end of the ACK signal
    
	if(checkForError(50))
	{
		return DHT_ERROR_ACK_TOO_LONG;
	}
		
     // Here sensor pulled down to start transmitting bits.
	 // Read the 40 bit data stream
	 for(j =0; j < 5; j++)
	 {
		//Find the start of the sync pulse
		if(checkForError(35)) // Spec is 50 us, 35*2 = 70
		{
		    return DHT_ERROR_SYNC_TIMEOUT;
		}
		
		//Measure the width of the data pulse
		retryCount = 0;
		do
		{
			if (retryCount > 50)
			{
				return DHT_ERROR_DATA_TIMEOUT;
			}
			retryCount++;
			_delay_us(2);
		}while (!(DHT_PIN & (1 << DHT_BIT)));
		
		// Identify bit values
		if(retryCount > 20) //Bit is 1: 20*2 = 40us 
		{
			dht_data[j]=0;
			for(i=0; i < 8; i++)
			{
				dht_data[j] |= 1 << (7 -i);
			}
		}
	 }
	 
	 //translate bitTimes
	 // 26~28us == logical 0
	 // 70us    == logical 1
	 // here threshold is 40 us
	 
	 //calculate checksum
	if (dht_data[4] == dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3])
	{

        return DHT_ERROR_NONE;
	}
	return DHT_ERROR_CHECKSUM;
}
//sourse: https://code.google.com/p/moreto-nixie-clock/source/browse/trunk/FirmwareV1/DHT22.c?r=19


unsigned char checkForError(unsigned char timeout)
{
	unsigned char retryCount = 0;
	do
	{
		if(retryCount > timeout) return 1;
		retryCount++;
		_delay_us(2);
	} while (!(DHT_PIN & (1 << DHT_BIT)));
	
	return 0;
}