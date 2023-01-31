/*
 * GPIO.c
 *
 *  Created on: Jan 31, 2023
 *      Author: utd
 */


#include"INC/GPIO.h"
//based on pin number get the position at the register (CRL || CRH ) to write its modes
uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	default:
		return 0;
		break;

	}
}



void MCAL_GPIO_Init (GPIO_Typedef* GPIOX ,GPIO_PIN_Configer_t* PinConfig)
{

	volatile uint32_t *ConfigureRegister = NULL;
	uint8_t   ConfigurePin=0;     //In This Variable We Store The Configure Pin

	ConfigureRegister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOX->CRL : &GPIOX->CRH ; // to take the address of CRL or CRH and store it in ConfigureRegister

	//Clear CNF & MODE for this pin only (0xf = 1111)
	*(ConfigureRegister) &= ~(0xf<< Get_CRLH_Position(PinConfig->GPIO_PinNumber) );  //CLR_BIT(REG,PIN)      (REG &= ~(1<<PIN))

	if (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP || PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_OD || PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_PP || PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_OD)
		{
			//I sure The User Want Make The Pin As Output & in Case Output Should Configure Mode(Speed) & CNF(State)
			ConfigurePin = ((( (PinConfig->GPIO_MODE - 4)<<2) |(PinConfig->GPIO_OUTPUT_SPEED)) & 0x0f); //Shift 2 to Set The CNF Bits
		}

	else  //I sure The User Want Make The Pin As Input & in Case input Should Configure Mode(Speed)=00 & CNF(State)
		{
			if (PinConfig->GPIO_MODE == GPIO_MODE_Analog ||PinConfig->GPIO_MODE ==GPIO_MODE_INPUT_FLO ||  PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT)
			{
				ConfigurePin= (( ((PinConfig->GPIO_MODE )<<2) | 0x0) & 0x0f);
			}
			else  //PullUp Or PullDown
			{
				ConfigurePin= (( ((GPIO_MODE_INPUT_PU)<<2) | 0x0) & 0x0f);
				if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
				{
					GPIOX->ODR |= PinConfig->GPIO_PinNumber;
				}
				else
				{
					GPIOX->ODR &= ~(PinConfig->GPIO_PinNumber);
				}
			}
		}

	*(ConfigureRegister) |=( ConfigurePin << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

}


void MCAL_GPIO_Deinit(GPIO_Typedef * GPIOx)
{
	if(GPIOx == GPIOA)
	{
		SET_BIT(RCC->APB2RSTR,2) ;
        CLR_BIT(RCC->APB2RSTR,2) ;

	}
	else if(GPIOx == GPIOB)
	{
		SET_BIT(RCC->APB2RSTR,3) ;
		CLR_BIT(RCC->APB2RSTR,3) ;
	}
	else if(GPIOx == GPIOC)
	{
		SET_BIT(RCC->APB2RSTR,4) ;
        CLR_BIT(RCC->APB2RSTR,4) ;
	}
	else if(GPIOx == GPIOD)
	{
		SET_BIT(RCC->APB2RSTR,5) ;
	    CLR_BIT(RCC->APB2RSTR,5) ;
	}
	else if(GPIOx == GPIOE)
	{
		SET_BIT(RCC->APB2RSTR,6) ;
	    CLR_BIT(RCC->APB2RSTR,6) ;
	}
}


uint8_t MCAL_GPIO_Read_Pin(GPIO_Typedef * GPIOx,uint16_t PinNumber)
{
	uint8_t PinState =0;
	if( (GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_FALSE )      //(GPIOx->IDR & PinNumber) :to get the value from IDR for this pin
	{
		PinState = GPIO_PIN_TRUE;
	}
	else
	{
		PinState = GPIO_PIN_FALSE;
	}
	return PinState;
}

uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef * GPIOx)
{
	uint16_t PortState =0 ;
	PortState = (uint16_t)GPIOx->IDR;
	return PortState;

}

void MCAL_GPIO_WritePin(GPIO_Typedef * GPIOx,uint16_t PinNumber,uint8_t Value)
{
	if (Value !=(uint32_t)GPIO_PIN_FALSE )
	{
		GPIOx->ODR |= (uint32_t)PinNumber ;

	}
	else
	{
		GPIOx->ODR &= ~(uint32_t)PinNumber;
	}

}

void MCAL_GPIO_WritePort(GPIO_Typedef * GPIOx,uint16_t Value)
{
	GPIOx->ODR = (uint32_t) Value ;

}

void MCAL_GPIO_Toggle_pin(GPIO_Typedef *GPIOx , uint16_t PinNumber)
{

	GPIOx->ODR ^= (PinNumber);
}


uint8_t MCAL_GPIO_LockPin(GPIO_Typedef * GPIOx,uint16_t PinNumber)
{

	GPIOx->LCKR |=(PinNumber);
    SET_BIT(GPIOx->LCKR,16);
	//Write 0
    CLR_BIT(GPIOx->LCKR,16);
	//Write 1
	SET_BIT(GPIOx->LCKR,16);
   //Read 0
    if((uint16_t)(GPIOx->LCKR & 1<<16 ))
    {
    	return GPIO_RETURN_LOCK_DONE;
    }
    else
    {
    	return GPIO_RETURN_LOCK_ERROR;
    }

}
