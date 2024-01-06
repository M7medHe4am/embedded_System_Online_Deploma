/*
 * Stm32F103C6_GPIO_Driver.c
 *
 *  Created on: Dec 9, 2023
 *      Author: m7med
 */
#include "Stm32F103C6_GPIO_Driver.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0 ;
		break ;
	case GPIO_PIN_1:
		return 4 ;
		break ;

	case GPIO_PIN_2:
		return 8 ;
		break ;

	case GPIO_PIN_3:
		return 12 ;
		break ;

	case GPIO_PIN_4:
		return 16 ;
		break ;


	case GPIO_PIN_5:
		return 20 ;
		break ;

	case GPIO_PIN_6:
		return 24 ;
		break ;

	case GPIO_PIN_7:
		return 28 ;
		break ;

	case GPIO_PIN_8:
		return 0 ;
		break ;
	case GPIO_PIN_9:
		return 4 ;
		break ;

	case GPIO_PIN_10:
		return 8 ;
		break ;

	case GPIO_PIN_11:
		return 12 ;
		break ;

	case GPIO_PIN_12:
		return 16 ;
		break ;


	case GPIO_PIN_13:
		return 20 ;
		break ;

	case GPIO_PIN_14:
		return 24 ;
		break ;

	case GPIO_PIN_15:
		return 28 ;
		break ;


	}
return 0 ;

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

	volatile uint32_t* configregister = NULL ;
	uint8_t	PIN_Config = 0 ;

	configregister = (pinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;

	//CNF0[1:0] MODE0[1:0=]   Clear the four Bits
	(*configregister) &= ~(0xf << Get_CRLH_Position(pinConfig->GPIO_PinNumber) );

	//if Pin is output
	if ( (pinConfig->GPIO_Mode == GPIO_MODE_OUT_PP ) ||  (pinConfig->GPIO_Mode == GPIO_MODE_OUT_OD ) || (pinConfig->GPIO_Mode == GPIO_MODE_AF_OUT_OD ) ||(pinConfig->GPIO_Mode == GPIO_MODE_AF_OUT_PP ))
	{
		PIN_Config  =  (  ( ( (pinConfig->GPIO_Mode - 4) <<2 ) |  pinConfig->GPIO_Output_Speed   ) & 0x0F );
		(*configregister) |= (  (  PIN_Config  ) << ( Get_CRLH_Position( pinConfig->GPIO_PinNumber) ) ) ;
	}
	//if pin is input
	else //MODE =  00: Input mode (reset state)
	{
		if (  (pinConfig->GPIO_Mode == GPIO_MODE_Analog ) || (pinConfig->GPIO_Mode == GPIO_MODE_FLO_IN ) )
		{
			PIN_Config  =  (  ( ( pinConfig->GPIO_Mode <<2 ) |  0x0   ) & 0x0F );
			(*configregister) |= (  (  PIN_Config  ) << ( Get_CRLH_Position( pinConfig->GPIO_PinNumber) ) ) ;
		}
		else if (pinConfig->GPIO_Mode == GPIO_MODE_AF_IN )
		{
			PIN_Config  =  (  ( ( GPIO_MODE_FLO_IN <<2 ) |  0x0   ) & 0x0F );
			(*configregister) |= (  (  PIN_Config  ) << ( Get_CRLH_Position( pinConfig->GPIO_PinNumber) ) ) ;
		}
		//Input with pull-up / pull-down
		else
		{
			PIN_Config  =  (  ( ( GPIO_MODE_IN_PU <<2 ) |  0x0   ) & 0x0F );
			(*configregister) |= (  (  PIN_Config  ) << ( Get_CRLH_Position( pinConfig->GPIO_PinNumber) ) ) ;

			if (pinConfig->GPIO_Mode == GPIO_MODE_IN_PU)
			{
				//PxODR = 1 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |= pinConfig->GPIO_PinNumber ;
			}else
			{
				//PxODR = 0 Input pull-down :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(pinConfig->GPIO_PinNumber) ;

			}

		}
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
	uint8_t bitstatus ;
		if ((GPIOx->IDR & pinNumber) != (uint32_t)GPIO_PIN_RESET)
		{
			bitstatus = GPIO_PIN_SET;
		}else
		{
			bitstatus = GPIO_PIN_RESET;
		}
		return bitstatus;

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
	uint16_t port_value ;
		port_value = (uint16_t)(GPIOx->IDR) ;
		return port_value ;

}
/**================================================================
 * @Fn				-MCAL_GPIO_WritePIN
 * @brief 			-Writes on specific PIN
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @param [in]		-value: Pin value
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_WritePIN(GPIO_TypeDef *GPIOx,uint16_t pinNumber,uint8_t value)
{

	if (value != GPIO_PIN_RESET)
		{
	//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	//		These bits are write-only and can be accessed in Word mode only.
	//		0: No action on the corresponding ODRx bit
	//		1: Set the corresponding ODRx bit
			GPIOx->BSRR = pinNumber;

	//		or
	//		GPIOx->ODR |= PinNumber ;
		}
		else
		{
	//		BRy: Port x Reset bit y (y= 0 .. 15)
	//		These bits are write-only and can be accessed in Word mode only.
	//		0: No action on the corresponding ODRx bit
	//		1: Reset the corresponding ODRx bit
			GPIOx->BRR = (uint32_t)pinNumber ;

	//		or
	//		GPIOx->ODR &= ~(PinNumber) ;
		}
}
/**================================================================
 * @Fn				-MCAL_GPIO_WritePORT
 * @brief 			-Writes on specific PORT
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-value: PORT value
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_WritePORT(GPIO_TypeDef *GPIOx,uint16_t value)
{
	GPIOx->ODR = (uint32_t)(value);

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
	GPIOx->ODR ^= (pinNumber);
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
	//	Bit 16 LCKK[16]: Lock key
	 volatile uint32_t tmp = 1<<16 ;

	 //	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	 tmp |= pinNumber ;

	 //	LOCK key writing sequence:
	 //	Write 1
	 GPIOx->LCKR =  tmp ;
	 //	Write 0
	 GPIOx->LCKR =  pinNumber ;

	 //	Write 1
	 GPIOx->LCKR =  tmp ;

	 //	Read 0
	 tmp = GPIOx->LCKR;

	 //	Read 1 (this read is optional but confirms that the lock is active)
	 if ((uint32_t)(GPIOx->LCKR & 1<<16))
	 {
	   return OK;
	 }
	 else
	 {
	   return ERROR;
	 }
}
