#include "dht.h"
#include <avr/io.h>
#define F_CPU 12000000L
#include <util/delay.h>
#include "util.h"

DHT_ERROR_t readDHT(unsigned char *dht_data)
{
	unsigned char i, j;
	
	sbi(DHT_DDR, DHT_BIT);
	cbi(DHT_PORT, DHT_BIT);
		
	_delay_ms(18);

	sbi(DHT_PORT, DHT_BIT);
	cbi(DHT_DDR, DHT_BIT);
	
	_delay_us(50); 
	
	if (DHT_PIN&(1<<DHT_BIT)) return DHT_ERROR_NOT_PRESENT;
	
	_delay_us(80);
	
	if (!(DHT_PIN&(1<<DHT_BIT))) return DHT_ERROR_ACK_TOO_LONG;
	
	while (DHT_PIN&(1<<DHT_BIT));
	
	for (j=0; j<5; j++)
    {
		dht_data[j]=0;
		for(i=0; i<8; i++)
        {
			while (!(DHT_PIN&(1<<DHT_BIT)));
			_delay_us (30);
		
			if (DHT_PIN&(1<<DHT_BIT)) 
				dht_data[j]|=1<<(7-i);
			
			while (DHT_PIN&(1<<DHT_BIT));
        }
    }
    	
	if (dht_data[4] == dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3])
	{
        return DHT_ERROR_NONE;
	}
	return DHT_ERROR_CHECKSUM;
}
