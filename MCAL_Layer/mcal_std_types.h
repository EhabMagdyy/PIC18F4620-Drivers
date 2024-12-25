/* 
 * File:   mcal_std_types.h
 * Author: Ehab
 *
 * Created on 15 ????, 2023, 05:18 ?
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section: Includes */
#include "std_libraries.h"
#include "compiler.h"

/* Section: Macro Declarations */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;

typedef uint8   Std_ReturnType;

/* Function Declarations */

#endif	/* MCAL_STD_TYPES_H */

