

/*---------------------Includes---------------------*/

#include "../INCS/stm32f103x6_GPIO.h"
/*--------------------------------------------------*/


//* ===============================================
//* APIs Supported by "MCAL GPIO DRIVER"
//* ===============================================



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
void MCAL_GPIO_init(GPIO_TypeDef_t* GPIOx ,GPIO_PinConfig_t* PinConfig)
{
	volatile uint32_t* CNFG_Reg = &GPIOx->CRL ;
	uint8_t pinNumber = PinConfig->GPIO_PinNumber ;

	//======MODE CONFIG======

	if(pinNumber > GPIO_PIN_7)
	{
		CNFG_Reg = &GPIOx->CRH;
		pinNumber -=32 ;

	}

	//Clearing the pin's 4 bits
	*CNFG_Reg &= ~(0xF << pinNumber) ;

	//SETTING MODE (IN/OUT)
	if(PinConfig->GPIO_Mode == GPIO_MODE_IN_PU)
	{
		GPIOx->ODR |= 1 << pinNumber ;
	}
	else if(PinConfig->GPIO_Mode == GPIO_MODE_IN_PD)
	{
		GPIOx->ODR &= ~ (1 << pinNumber) ;
	}

	*CNFG_Reg |= PinConfig->GPIO_Mode << pinNumber ;

	//Setting Speed if output

	*CNFG_Reg |=PinConfig->GPIO_Speed << pinNumber ;


}



/**================================================================
 * @Fn				-MCAL_GPIO_ReadPIN
 * @brief 			-Read specific pin
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @retval 			-the input pin value(two possible values based on @ref GPIO_PIN_state)
 * Note				-none
 */
uint8_t MCAL_GPIO_ReadPIN(GPIO_TypeDef_t* GPIOx , uint8_t PinNumber)
{

	PinNumber /= 4;

	return ((GPIOx->IDR & (1<<PinNumber)) >> PinNumber) ;

}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPORT
 * @brief 			-Read specific PORT
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @retval 			-the input port value
 * Note				-none
 */
uint16_t MCAL_GPIO_ReadPORT(GPIO_TypeDef_t* GPIOx)
{

	return (uint16_t)GPIOx->ODR ;

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

void MCAL_GPIO_WritePIN(GPIO_TypeDef_t* GPIOx ,uint8_t PinNumber , uint8_t value)
{

	PinNumber /= 4;
	if (value == 0 )
	{
		GPIOx->ODR &= ~(1<<PinNumber);
	}
	else
	{
		GPIOx->ODR |= 1<<PinNumber ;
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
void MCAL_GPIO_WritePORT(GPIO_TypeDef_t* GPIOx , uint16_t value)
{
	GPIOx->ODR = (uint32_t)value ;
}




/**================================================================
 * @Fn				-MCAL_GPIO_TogglePIN
 * @brief 			-Toggles specific PIN
 * @param [in]		-GPIOx: where x can be (A...E depending on the device used) to select the GPIO peripheral
 * @param [in]		-pinNumber: Set the pin number according to @ref GPIO_PINS_Define
 * @retval 			-none
 * Note				-none
 */
void MCAL_GPIO_TogglePIN(GPIO_TypeDef_t* GPIOx , uint8_t PinNumber)
{
	PinNumber /= 4;

	GPIOx->ODR ^= 1<<PinNumber ;

}
