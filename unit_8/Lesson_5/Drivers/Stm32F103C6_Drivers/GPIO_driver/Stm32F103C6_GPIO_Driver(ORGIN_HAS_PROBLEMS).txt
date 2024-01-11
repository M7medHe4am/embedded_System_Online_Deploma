/*
 * Stm32F103C6_GPIO_Driver.c
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */
#include "Stm32F103C6_GPIO_Driver.h"

uint8_t CHECK_Position(uint8_t pinNumber)
{
	switch (pinNumber)
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
	default :
		return 28;
		break;

	}

}

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in] 		-PinConfig: Ptr to a GPIO_PinConfig_t structure that contains the configuration information for
 * 								the specified GPIO pin.
 * @retval 			-none
 * Note				-stm32F103C6 MCU has GPIO A,B,C,D,E modules
 * 					 But LQFP48 package has only GPIO A,B,PART of C,D exported as external pins from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *pinConfig)
{

	uint8_t position = CHECK_Position(pinConfig->GPIO_PinNumber);
	volatile uint32_t *configReg = NULL;
	configReg = ((pinConfig->GPIO_PinNumber > GPIO_PIN_7)? (&GPIOx->CRH):(&GPIOx->CRL));
	*configReg &=~ (0xb1111<<position);
	if ( pinConfig->GPIO_Mode == GPIO_MODE_Analog )
	{
		(*configReg) |= 0b0000 << position;
	}
	else if (pinConfig->GPIO_Mode == GPIO_MODE_FLO_IN)
	{
		(*configReg) |= 0b0100 << position;
	}
	else if(pinConfig->GPIO_Mode == GPIO_MODE_IN_PU)
	{
		(*configReg) |= 0b1000 << position;
		GPIOx->ODR |= 1 << position;
	}
	else if (pinConfig->GPIO_Mode == GPIO_MODE_IN_PD)
	{
		(*configReg) |= 0b1000 << position;
		GPIOx->ODR &= ~(1 << position);
	}
	else if (pinConfig->GPIO_Mode == GPIO_MODE_AF_IN)
	{
		(*configReg) |= 0b0100 << position;
	}

	else if (pinConfig->GPIO_Mode == GPIO_MODE_OUT_PP || GPIO_MODE_OUT_OD || GPIO_MODE_AF_OUT_PP || GPIO_MODE_AF_OUT_OD)
	{
		(*configReg) |= pinConfig->GPIO_Output_Speed << position ;
		if (pinConfig->GPIO_Mode == GPIO_MODE_OUT_PP)
			(*configReg) |= 0b0011 << position;
		else if (pinConfig->GPIO_Mode == GPIO_MODE_OUT_OD)
		{
			(*configReg) |= 0b0111 << position;
		}
		else if (pinConfig->GPIO_Mode == GPIO_MODE_AF_OUT_PP)
		{
			(*configReg) |= 0b1011 << position;
		}
		else if (pinConfig->GPIO_Mode == GPIO_MODE_AF_OUT_OD)
		{
			(*configReg) |= 0b1111 << position;
		}
	}



}
/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief 			-Resets the GPIOx Registers
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @retval 			-none
 * Note				-none
 */

void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	/*
	GPIOx->CRL	= 0x44444444 ;
	GPIOx->CRH	= 0x44444444 ;
	//GPIOx->IDR = READONLY	 ;
	GPIOx->ODR	= 0x00000000 ;
	GPIOx->BSRR = 0x00000000 ;
	GPIOx->BRR	= 0x00000000 ;
	GPIOx->LCKR	= 0x00000000 ;
	*/

	if (GPIOx==GPIOA)
	{
		RCC->APB2RSTR |= 1<<2;
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (GPIOx==GPIOB)
	{
		RCC->APB2RSTR |= 1<<3;
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if (GPIOx==GPIOC)
		{
			RCC->APB2RSTR |= 1<<4;
			RCC->APB2RSTR &= ~(1<<4);
		}
	else if (GPIOx==GPIOD)
		{
			RCC->APB2RSTR |= 1<<5;
			RCC->APB2RSTR &= ~(1<<5);
		}
	else if (GPIOx==GPIOE)
		{
			RCC->APB2RSTR |= 1<<6;
			RCC->APB2RSTR &= ~(1<<6);
		}


}


/**================================================================
 * @Fn				-MCAL_GPIO_ReadPIN
 * @brief 			-Read specific pin
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @retval 			-the input pin value(two possible values based on @ref GPIO_PIN_state)
 * Note				-none
 */
uint8_t MCAL_GPIO_ReadPIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber)
{
	uint8_t bit_status;
	bit_status = (GPIOx->IDR & (1<<pinNumber)) >>pinNumber;
	return bit_status;

}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPORT
 * @brief 			-Read specific PORT
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @retval 			-the input port value
 * Note				-none
 */
uint16_t MCAL_GPIO_ReadPORT(GPIO_TypeDef *GPIOx)
{
	uint16_t port_value;
	port_value = (uint16_t)GPIOx->IDR;
	return port_value;

}
/**================================================================
 * @Fn				-MCAL_GPIO_WritePIN
 * @brief 			-Writes on specific PIN
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @param [in]		-value: Pin Value
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_WritePIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber,uint8_t value)
{
	if (value == 0)
	{
		GPIOx->ODR &= ~(1<<pinNumber);
	}
	else
	{
		GPIOx->ODR |= (1<<pinNumber);
	}

}
/**================================================================
 * @Fn				-MCAL_GPIO_WritePORT
 * @brief 			-Writes on specific PORT
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-value: PORT Value
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_WritePORT(GPIO_TypeDef *GPIOx,uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;

}
/**================================================================
 * @Fn				-MCAL_GPIO_TogglePIN
 * @brief 			-Toggles specific PIN
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_TogglePIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber)
{
	GPIOx->ODR ^= (1<<pinNumber);
}
/**================================================================
 * @Fn				-MCAL_GPIO_LockPIN
 * @brief 			-The locking mechanism allows the IO
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @retval 			-OK if the pin config is locked or ERROR if the pin config isn't locked based on @ref GPIO_RETURN_LOCK
 * Note				-none
 */
uint8_t MCAL_GPIO_LockPIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber)
{
	//The pin to be locked
	GPIOx->LCKR |= 1<<pinNumber;
	//the locking sequence
	GPIOx->LCKR |= 1<<16;
	GPIOx->LCKR &= ~(1<<16);
	GPIOx->LCKR |= 1<<16;
	if(((GPIOx->LCKR & (1<<16)) >> 16))
	{
		return GPIO_RETURN_LOCK_Enabled;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}
}
