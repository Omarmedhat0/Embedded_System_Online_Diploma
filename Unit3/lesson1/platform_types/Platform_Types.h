#include "stdint.h"
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


#include <stdbool.h>
#include <stdint.h>


#ifndef _Bool
#define _Bool 			unsigned int
#endif

#define CPU_TYPE			cpu_type_32
#define CPU_BIT_ORDER		MSB-FIRST
#define CPU_BYTE_ORDER		HIGH-BYTE-FIRST

#ifndef FALSE
#define FALSE 				(boolean)false
#endif

#ifndef TRUE
#define TRUE 				(boolean)true
#endif

typedef _Bool				boolean;
typedef uint8_t				uint8;
typedef uint16_t			uint16;
typedef uint32_t			uint32;
typedef int8_t				sint8;
typedef int16_t				sint16;
typedef int32_t				sint32;
typedef uint_least8_t		uint8_least;
typedef uint_least16_t		uint16_least;
typedef uint_least32_t		uint32_least;
typedef int_least8_t		sint8_least;
typedef int_least16_t		sint16_least;
typedef int_least32_t		sint32_least;
typedef int_least8_t		float32;
typedef int_least8_t		sint8_least;


typedef signed float  		float32;
typedef signed double  		float64;


typedef volatile int8_t		vint8_t;
typedef volatile uint8_t	viint8_t;


typedef volatile int16_t	vint16_t;
typedef volatile uint16_t	viint16_t;


typedef volatile int32_t	vint32_t;
typedef volatile uint32_t	viint32_t;


typedef volatile int64_t	vint64_t;
typedef volatile uint64_t	viint64_t;


#endif
