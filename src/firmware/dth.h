#ifndef __dth_h_included__
#define __dth_h_included__

#define DTH_PORT	PORTB
#define DTH_DDR		DDRB
#define DTH_PIN		PINB
#define DTH_BIT		4

#define DTH_DATA_BIT_COUNT 40


typedef enum 
{
	DHT_ERROR_NONE = 0,
	DHT_BUS_HUNG,
	DHT_ERROR_NOT_PRESENT,
	DHT_ERROR_ACK_TOO_LONG,
	DHT_ERROR_SYNC_TIMEOUT,
	DHT_ERROR_DATA_TIMEOUT,
	DHT_ERROR_CHECKSUM,

} DTH_ERROR_t;

typedef struct
{
	int8_t temperature_integral;
	uint8_t temperature_decimal;
	uint8_t humidity_integral;
	uint8_t humidity_decimal; 
} DTH_DATA_t;

DTH_ERROR_t readDTH(DTH_DATA_t* data);



#endif



