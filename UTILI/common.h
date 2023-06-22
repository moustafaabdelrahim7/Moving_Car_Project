/**
 ** @file                   common.h
 ** @brief                  This is header file for common usage macros and defintions
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */


#ifndef COMMON_H_
#define COMMON_H_


/*********************************************************************************/
/* Includes***********************************************************************/
/*********************************************************************************/
#include "stdint.h"

#define  SUCCESS                (0)
#define  ERROR                  (1)
#define  INVALID_INPUT          (2)
#define  NULLPTR                ((void*)0)
#define  NULL                   (0)
#ifndef  TRUE
 #define TRUE                   (1u)
#endif

#ifndef FALSE
 #define FALSE                  (0u)
#endif

/***********************************************************************************/
/* Typedef**************************************************************************/
/***********************************************************************************/

typedef signed      char    sint8_t;   /*(_) is appended to the typename in order to avoid conflicts with the windows types*/
typedef unsigned    char    uint8_t;   /*(_) is appended to the typename in order to avoid conflicts with the windows types*/
typedef signed      short   sint16_t;  /*(_) is appended to the typename in order to avoid conflicts with the windows types*/
typedef unsigned    short   uint16_t;  /*(_) is appended to the typename in order to avoid conflicts with the windows types*/
typedef signed      int     sint32_t;  /*(_) is appended to the typename in order to avoid conflicts with the windows types*/
typedef unsigned    int     uint32_t;  /*(_) is appended to the typename in order to avoid conflicts with the windows types*/

typedef unsigned char             boolean;
/***********************************************************************************/
/*Bit Operations********************************************************************/
/***********************************************************************************/

#define READ_BIT(reg,bit_idx)   (0UL!=((reg) & (1UL <<(bit_idx))))

#define SET_BIT(reg,bit_idx)    (reg|=(1 << bit_idx))

#define CLEAR_BIT(reg,bit_idx)  (reg&=(~(1 <<(bit_idx))))

#define TOGGEL_BIT(reg,bit_idx) (reg^=(1UL <<(bit_idx)))


#endif /* COMMON_H_ */