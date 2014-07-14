#ifndef __dht_h_included__
#define __dht_h_included__

#define DHT_PORT	PORTB
#define DHT_DDR		DDRB
#define DHT_PIN		PINB
#define DHT_BIT		PB0

typedef enum 
{
	DHT_ERROR_NONE 			= 0,
	DHT_ERROR_NOT_PRESENT	= 1,
	DHT_ERROR_ACK_TOO_LONG	= 2,
	DHT_ERROR_CHECKSUM		= 3

} DHT_ERROR_t;


DHT_ERROR_t readDHT(unsigned char *dht_data);

#endif



