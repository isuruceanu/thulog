#ifndef __dht_h_included__
#define __dht_h_included__

#define DHT_PORT	PORTB
#define DHT_DDR		DDRB
#define DHT_PIN		PINB
#define DHT_BIT		4

#define DHT_DATA_BIT_COUNT 40

#ifndef PUBLIC
#define PUBLIC
#endif

typedef enum 
{
	DHT_ERROR_NONE = 0,
	DHT_BUS_HUNG,
	DHT_ERROR_NOT_PRESENT,
	DHT_ERROR_ACK_TOO_LONG,
	DHT_ERROR_SYNC_TIMEOUT,
	DHT_ERROR_DATA_TIMEOUT,
	DHT_ERROR_CHECKSUM,

} DHT_ERROR_t;


PUBLIC DHT_ERROR_t readDHT(unsigned char *dht_data);

#endif



