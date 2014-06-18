#include "dht.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "util.h"

unsigned char checkForError(unsigned char timeout);


DHT_ERROR_t readDHT(DHT_DATA_t* data)
{
	uint8_t retryCount = 0;
	uint8_t i;
	uint8_t checkSum = 0;
	uint16_t rawHumidity = 0;
    uint16_t rawTemperature = 0;

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
	 for(i =0; i < DHT_DATA_BIT_COUNT; i++)
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
			if (i < 16) //Humidity
			{
				rawHumidity |= (1 << (15 -i));
			}	
			if((i > 15) && (i < 32)) // temperature
			{
				rawTemperature |= (1 << (31 - i));
			}
			
			if((i > 31) && (i < 40)) //check sum
			{
				checkSum |= (1<< (39-i));
			}
		}
	 }
	 
	 //translate bitTimes
	 // 26~28us == logical 0
	 // 70us    == logical 1
	 // here threshold is 40 us
	 
	 //calculate checksum
	 if (checkSum == (((rawHumidity >> 8) + (rawHumidity & 0xFF) + 
			(rawTemperature >> 8) + (rawTemperature & 0xFF)) & 0xFF ))
	 {
		// raw data to sensor values
        data->humidity_integral = (uint8_t)(rawHumidity / 10);
        data->humidity_decimal = (uint8_t)(rawHumidity % 10);

        if(rawTemperature & 0x8000)     // Check if temperature is below zero, non standard way of encoding negative numbers!
        {
            rawTemperature &= 0x7FFF; // Remove signal bit
            data->temperature_integral = (int8_t)(rawTemperature / 10) * -1;
            data->temperature_decimal = (uint8_t)(rawTemperature % 10);
        } 
		else
        {
			data->temperature_integral = (int8_t)(rawTemperature / 10);
            data->temperature_decimal = (uint8_t)(rawTemperature % 10);                    
		}
        return DHT_ERROR_NONE;
	}
	return DHT_ERROR_CHECKSUM;
}
//sourse: https://code.google.com/p/moreto-nixie-clock/source/browse/trunk/FirmwareV1/DHT22.c?r=19


unsigned char checkForError(unsigned char timeout)
{
	uint8_t retryCount = 0;
	do
	{
		if(retryCount > timeout) return 1;
		retryCount++;
		_delay_us(2);
	} while (!(DHT_PIN & (1 << DHT_BIT)));
	
	return 0;
}