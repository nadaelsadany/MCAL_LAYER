/*
 * STM32.h
 *
 *  Created on: Jan 31, 2023
 *      Author: utd
 */

#ifndef INC_STM32_H_
#define INC_STM32_H_

//-----------------------------
//Includes

#include"stdlib.h"
#include<stdint.h>
//-----------------------------

// Bit math functions
#define SET_BIT(REG,PIN)      (REG |= (1<<PIN))
#define CLR_BIT(REG,PIN)      (REG &= ~(1<<PIN))
#define TOG_BIT(REG,PIN)      (REG ^= (1<<PIN))
#define GET_BIT(REG,PIN)      ((REG >>PIN)& 0x01)

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define SRAM_Memory_Base        			0x20000000UL
#define Flash_Memory_Base        			0x08000000UL
#define System_Memory_Base					0x1FFFF000UL
#define Peripherals_Base        			0x40000000UL
#define Cortex_M3_Peripherals_Base        	0xE0000000UL


//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
#define RCC_Base        			0x20000000UL


//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//GPIO
//-----------------------------

//GPIO A&B FULly include
#define GPIOA_Base   				0x40010800UL
#define GPIOB_Base   				0x40010C00UL

//GPIO C&D partial include
#define GPIOC_Base   				0x40011000UL
#define GPIOD_Base    				0x40011400UL

//GPIO E not include
#define GPIOE_Base   				0x40011800UL
//-------------------------------

//EXIT
#define EXIT_Base  					0x40010400UL

//-------------------------------
//AFIO
#define AFIO_Base  				 	0x40010000UL

//-------------------------------


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
 typedef struct{

	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR ;

}GPIO_Typedef;
//-------------------------------
//RCC
typedef struct{

	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;


}RCC_Typedef;

//-------------------------------
//EXIT
typedef struct{

	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR ;



}EXTI_Typedef;

//-------------------------------
//AFIO
typedef struct{

	volatile uint32_t EVCR ;
	volatile uint32_t MAPR ;
	volatile uint32_t EXTICR1 ;
	volatile uint32_t EXTICR2 ;
	volatile uint32_t EXTICR3 ;
	volatile uint32_t EXTICR4 ;
	uint32_t RESERVED0 ;
	volatile uint32_t MAPR2 ;



}AFIO_Typedef;

//-------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA 		 ((GPIO_Typedef*)(GPIOA_Base))
#define GPIOB 		 ((GPIO_Typedef*)(GPIOB_Base))
#define GPIOC 		 ((GPIO_Typedef*)(GPIOC_Base))
#define GPIOD 		 ((GPIO_Typedef*)(GPIOD_Base))
#define GPIOE 		 ((GPIO_Typedef*)(GPIOE_Base))

#define RCC 		 ((RCC_Typedef*)(RCC_Base))

#define EXTI 		 ((EXTI_Typedef*)(EXTI_Base))

#define AFIO 		 ((AFIO_Typedef*)(AFIO_Base))
//-*-*-*-*-*-*-*-*-*-*-*-


//clock enable Macros:
// SET_BIT(RCC->APB2ENR,2)      (REG |= (1<<PIN))
#define RCC_GPIOA_CLK_EN()   SET_BIT(RCC->APB2ENR,2)
#define RCC_GPIOB_CLK_EN()   SET_BIT(RCC->APB2ENR,3)
#define RCC_GPIOC_CLK_EN()   SET_BIT(RCC->APB2ENR,4)
#define RCC_GPIOD_CLK_EN()   SET_BIT(RCC->APB2ENR,5)
#define RCC_GPIOE_CLK_EN()   SET_BIT(RCC->APB2ENR,6)

#define AFIO_CLK_EN()      	SET_BIT(RCC->APB2ENR,0)


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32_H_ */
