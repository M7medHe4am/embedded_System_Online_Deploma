/*
 * Stm32F103C6_I2C_Driver.h
 *
 *  Created on: Jan 15, 2024
 *      Author: m7med
 */

#ifndef INC_STM32F103C6_I2C_DRIVER_H_
#define INC_STM32F103C6_I2C_DRIVER_H_
//=======================================================================================
//									NOTES
//=======================================================================================
//I2C DRIVER >> STM32F103C6
//THIS DRIVER SUPPORTS ONLY I2C MODE
//THIS DRIVER SUPPORTS ONLY 7BIT SLAVE ADDRESSING MODE
//THIS DRIVER SUPPORTS ONLY SM MODE
//THIS DRIVER IS CONFIGURED FOR THE MASTER TO WORK IN POLLING MECHANISM , SLAVE IN INTERRUPT MECHANISM
//IN SM NOTE THAT THE INPUT CLOCK FREQUENCY MUST BE 4MHZ AT LEAST (SM IS SUPPORTED )
//IN FM NOTE THAT THE INPUT CLOCK FREQUENCY MUST BE 4MHZ AT LEAST ( FM NOT SUPPORTED )
//SLAVE STATES NOT SUPPORTED
//=======================================================================================
//=======================================================================================
//									INCLUDES
//=======================================================================================
#include"stm32f103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "Stm32F103C6_RCC_Driver.h"
//=======================================================================================
//=======================================================================================
//							INLINE FUNCTIONS PROTOTYPES
//=======================================================================================
uint32_t I2C_SM_CONFIG(uint32_t speed);
uint32_t I2C_FM_CONFIG(uint32_t speed);
//=======================================================================================
//									TYPED DEFINED ENUMS
//=======================================================================================

typedef enum
{
	I2C_EV_STOP,
	I2C_ERR_AF,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ,			//The APP layer should send the data (I2C_SlaveSendData) in this state
	I2C_EV_DATA_RCV				//The APP layer should read the data (I2C_SlaveReceiveData) in this state
}Slave_State;

typedef enum
{
	I2C_ENABLE,
	I2C_DISABLE


}I2C_CHOISE;


typedef enum
{
	EV,
	ER
}I2C_IRQ_CHOISE;


typedef enum
{
	START,
	REPEATED_START
}start_condition;

typedef enum
{
	WITH_STOP,
	WITHOUT_STOP


}stop_condition;

typedef enum
{
	BUSY,
	EV5,
	EV6,
	EV8_1,
	EV8,
	EV7


}flag_choise;

typedef enum
{
	TRANSMITER,
	RECEIVER


}Tx_condition;



//=======================================================================================
//=======================================================================================
//								CONFIGURATIONS STRUCTURES
//=======================================================================================

typedef struct
{
	uint16_t DUAL_addressing_ENABLE	;			//1 to enable / 0 to disable
	uint16_t primary_address		;			//MUST BE SET IN SLAVE MODE
	uint16_t secondary_address		;			//MUST BE SET ONLY WHEN DUAL_addressing_ENABLE = 1 ;

	uint16_t slave_addressing_mode  ;			//Specifies THE SLAVE ADDRESSING MODE (7BIT/10BIT)
	//This parameter must be set based on @ref I2C_SLAVE_ADDRESSING_DEFINE

}S_Addresing_Mode_t;


//==============================MAIN I2C CONFIGURATION STRUCTURE==============================//
typedef struct
{
	uint32_t CLK_Speed_Mode ;				//Specifies the CLOCK MODE (SM/FM)
	//This parameter must be set based on @ref I2C_CLK_SPEED_DEFINE

	uint16_t Device_Mode ;					//Specifies the DEVICE MODE (I2C/SMBus)
	//This parameter must be set based on @ref I2C_DEVICE_MODE_DEFINE

	uint16_t ENGC ;							//Specifies the GENERAL CALL (EN/DS)
	//This parameter must be set based on @ref I2C_ENGC_DEFINE

	uint16_t CLK_Stretching ;				//Specifies theCLOCK STRETCHING
	//This parameter must be set based on @ref I2C_STRETCH_DEFINE

	uint16_t ACK_EN ;						//Specifies ACKNOWLEDGE (EN/DS)
	//This parameter must be set based on @ref I2C_ACK_DEFINE

	S_Addresing_Mode_t Addressing_Mode ;				//Specifies THE SLAVE ADDRESSING MODE (7BIT/10BIT)


	void(* p_Slave_Event_CallBAck)(Slave_State state); //set the C function which will be Called once the SLAVE IRQ HAPPENS




}I2C_Config_t;


//=======================================================================================
//									@ref MACROS
//=======================================================================================

//@ref I2C_CLK_SPEED_DEFINE

//ADD YOUR DESIRED CLOCK SPEED VALUES in the function's parameter
//MAKE SURE THAT SM MAX VALUE = 100 KHZ , FM MAX VALUE = 400 KHZ

#define I2C_CLK_SPEED_SM				I2C_SM_CONFIG(100000U)
#define I2C_CLK_SPEED_FM				I2C_FM_CONFIG(400000U)


//@ref I2C_DEVICE_MODE_DEFINE

//I2C->CR1
#define I2C_DEVICE_MODE_I2C				(0)
#define I2C_DEVICE_MODE_SMBUS			(1<<1)

//@ref I2C_ENGC_DEFINE
//I2C->CR1
#define I2C_ENGC_DISABLE				(0)
#define I2C_ENGC_ENABLE					(1<<6)

//@ref I2C_NOSTRETCH_DEFINE
//I2C->CR1
#define I2C_STRETCH_ENABLE				(0)
#define I2C_STRETCH_DISABLE				(1<<7)


//@ref I2C_ACK_DEFINE
//I2C->CR1
#define I2C_ACK_DISABLE					(0)
#define I2C_ACK_ENABLE					(1<<10)


//@ref I2C_SLAVE_ADDRESSING_DEFINE
//I2C->OAR1
#define I2C_SLAVE_ADDRESSING_7BIT		(0)
#define I2C_SLAVE_ADDRESSING_10BIT		(1<<15)

//=======================================================================================
//=======================================================================================
//						APIs Supported by "MCAL I2C DRIVER "
//=======================================================================================

void MCAL_I2C_init(I2C_TypeDef* I2Cx , I2C_Config_t* I2CCNFG);
void MCAL_I2C_Deinit(I2C_TypeDef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);
void MCAL_I2C_MASTER_Tx(I2C_TypeDef* I2Cx , start_condition startCondition , uint8_t devAddress , uint8_t * data \
																			, uint8_t dataLength ,stop_condition stopCondition);
void MCAL_I2C_MASTER_Rx(I2C_TypeDef* I2Cx , start_condition startCondition, uint8_t devAddress , uint8_t * data \
		,uint8_t dataLength,stop_condition stopCondition);



















//=======================================================================================


#endif /* INC_STM32F103C6_I2C_DRIVER_H_ */
