#ifndef _UTIL_H_
#define _UTIL_H_

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef tbi
#define tbi(sfr, bit) (_SFR_BYTE(sfr) ^= _BV(bit))
#endif

#define NOP asm("nop");

#endif