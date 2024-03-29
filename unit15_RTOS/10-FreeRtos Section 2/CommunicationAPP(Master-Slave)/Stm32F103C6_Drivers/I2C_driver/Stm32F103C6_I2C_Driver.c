/*
 * Stm32F103C6_I2C_Driver.c
 *
 *  Created on: Jan 15, 2024
 *      Author: m7med
 */



//=======================================================================================
//									INCLUDES
//=======================================================================================
#include "Stm32F103C6_I2C_Driver.h"
//=======================================================================================

//=======================================================================================
//							STATIC FUNCTIONS PROTOTYPES
//=======================================================================================
static void I2C_Generate_Start(I2C_TypeDef* I2Cx,start_condition condition ,I2C_CHOISE choise);
static void I2C_Generate_Stop(I2C_TypeDef* I2Cx , I2C_CHOISE choise);
static uint8_t I2C_Check_flag(I2C_TypeDef* I2Cx ,flag_choise flag );
static void I2C_Send_Address(I2C_TypeDef* I2Cx ,uint8_t devAddress ,Tx_condition condition);
static void I2C_ACK_Config(I2C_TypeDef* I2Cx ,I2C_CHOISE choise  );

static uint8_t I2C_NUMBER(I2C_TypeDef* I2Cx);
static void I2C_peripheral_ENABLE(uint8_t index ,I2C_CHOISE choise);
static void I2C_NVIC_ENABLE(uint8_t index ,I2C_CHOISE choise , I2C_IRQ_CHOISE irqChois );
//=======================================================================================
//=======================================================================================
//								GLOBAL VARIABLES
//=======================================================================================

I2C_Config_t I2C_CNFG[2];

//=======================================================================================

//=======================================================================================
//								MACROS
//=======================================================================================

#define I2C1CNFG			0
#define I2C2CNFG			1
//=======================================================================================


//=======================================================================================
//						APIs Supported by "MCAL I2C DRIVER "
//=======================================================================================


/**======================================================================================
 * @Fn				-MCAL_I2C_init
 * @brief 			-Initializes I2C
 * @param [in]		-I2Cx: where x can be (1,2.....) depending on the device used
 * @param [in] 		-I2C_Config_t: ALL I2C Configuration
 * @retval 			-none
 * Note				-
 *
 */

void MCAL_I2C_init(I2C_TypeDef* I2Cx , I2C_Config_t* I2CCNFG)
{
	uint16_t tempReg = 0;
	uint32_t ABP1_freq,I2C_freqBits,result;
	uint8_t index = I2C_NUMBER(I2Cx);
	//ENABLE PERIHPERAL CLOCK
	I2C_peripheral_ENABLE(index ,I2C_ENABLE);
	I2C_CNFG[index] = *I2CCNFG;

	//MAKING SURE THAT THE PE bit in CR1 is low in order to configure FREQ , CCR
	I2Cx->CR1 &= ~(1<<0);

	if(I2CCNFG->Device_Mode == I2C_DEVICE_MODE_I2C)
	{
		//Choosing I2C MODE
		tempReg |= I2CCNFG->Device_Mode ;

		// 1- Program the peripheral input clock in CR2
		//IN SM NOTE THAT THE INPUT CLOCK FREQUENCY MUST BE 4MHZ AT LEAST (SM IS SUPPORTED )
		//IN FM NOTE THAT THE INPUT CLOCK FREQUENCY MUST BE 4MHZ AT LEAST ( FM NOT SUPPORTED )

		//Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		//CLEARING THE FREQ bits in CR2
		I2Cx->CR2 &= ~(0x3F);
		//Getting the APB1 FREQ in MHZ
		ABP1_freq  =  MCAL_RCC_getAPB1CLKFreq();
		I2C_freqBits = (ABP1_freq/1000000);
		//Writing the frequency value in the FREQ[5:0] bits
		I2Cx->CR2 |=  I2C_freqBits ;

		if (I2CCNFG->CLK_Speed_Mode == I2C_CLK_SPEED_SM)
		{
			//11:0 CCR[11:0]: Clock control register
			//Clearing Bits
			I2Cx->CCR &= ~(0xFFF);

			//Choosing SM MODE
			I2Cx->CCR &= ~(1<<15) ;
			// 2- Configure the clock control registers CCR
			//- CCR CALCULATIONS
			//CCR = Thigh/TAPBCLK
			//CCR = Tclk / (2*TAPBCLK)
			//CCR = ABP1_freq/(2*I2C_Clockspeed)
			result = ABP1_freq/((I2CCNFG->CLK_Speed_Mode) << 1);

			//Writing the CCR RESULT
			I2Cx->CCR |= result;
		}
		else
		{
			// FM MODE NOT SUPPORTED
			//Choosing FM MODE
			//I2Cx->CCR |= (1<<15) ;

		}
		//3- Configure the rise time register
		result = I2C_freqBits + 0x1 ;

		//Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
		//Clearing Bits
		I2Cx->TRISE &= ~(0x3F);
		//Writing the CCR RESULT
		I2Cx->TRISE |= result;

		// I2C->CR1 CONFIGURATIONS
		tempReg |= I2CCNFG->ENGC ;
		tempReg |= I2CCNFG->CLK_Stretching;
		tempReg |= I2CCNFG->ACK_EN;
		//Assigning tempReg into I2Cx->CR1
		I2Cx->CR1 = tempReg;
		tempReg = 0 ;

		// I2C->OAR1 , I2C->OAR2 CONFIGURATIONS
		if ( I2CCNFG->Addressing_Mode.DUAL_addressing_ENABLE )
		{

			if(I2CCNFG->Addressing_Mode.slave_addressing_mode == I2C_SLAVE_ADDRESSING_7BIT)
			{
				//Bit 0 ENDUAL: Dual addressing mode enable
				//1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
				//ENABLING DUAL ADDRESS MODE
				tempReg |= (1<<0);
				tempReg |= (I2CCNFG->Addressing_Mode.secondary_address << 1);
				//Assigning tempReg into I2Cx->OAR2
				I2Cx->OAR2 = tempReg;
				tempReg = 0 ;
				//Bit 15 ADDMODE Addressing mode (slave mode)
				//0: 7-bit slave address
				tempReg &= ~(1<<15) ;
			}


		}
		else // NOT DUAL MODE
		{

			// Only OAR1 is recognized in 7-bit addressing mode
			//DISABLING DUAL ADDRESSING MODE
			I2Cx->OAR2 &= ~(1<<0);
			if(I2CCNFG->Addressing_Mode.slave_addressing_mode == I2C_SLAVE_ADDRESSING_7BIT)
			{
				//Bit 15 ADDMODE Addressing mode (slave mode)
				//0: 7-bit slave address
				tempReg &= ~(1<<15) ;
			}
			else
			{
				/* 10BIT MODE NOT SUPPORTED*/
				//Bit 15 ADDMODE Addressing mode (slave mode)
				//0: 7-bit slave address (10-bit address not acknowledged)
				//1: 10-bit slave address (7-bit address not acknowledged)

			}

		}
		tempReg |= (I2CCNFG->Addressing_Mode.primary_address << 1);
		//Assigning tempReg into I2Cx->OAR2
		I2Cx->OAR1 = tempReg;
		tempReg = 0 ;
	}

	else
	{
		/*SMBUS NOT SUPPORTED*/
		//Choosing SMBUS MODE
		//I2Cx->CR1 |= I2CCNFG->Device_Mode ;


	}

	//THIS DRIVER IS CONFIGURED FOR THE MASTER TO WORK IN POLLING MECHANISM , SLAVE IN INTERRUPT MECHANISM

	//CHECK IS THE PERIPHERAL IS IN SLAVE MODE
	if ( I2CCNFG->p_Slave_Event_CallBAck != NULL )
	{
		//ENABLINE THE INTERRUPTS IN THE CONTROL REGISTER CR2
		//Bit 8 ITERREN: Error interrupt enable
		tempReg |= (1<<8);
		//Bit 9 ITEVTEN: Event interrupt enable
		tempReg |= (1<<9);
		//Bit 10 ITBUFEN: Buffer interrupt enable
		tempReg |= (1<<10);

		I2Cx->CR2 |= tempReg;
		tempReg=0;
		I2C_NVIC_ENABLE(index ,I2C_ENABLE , EV );
		I2C_NVIC_ENABLE(index ,I2C_ENABLE , ER );
	}


	// 4- Program the I2C_CR1 register to enable the peripheral
	I2Cx->CR1 |= (1<<0) ;

}


//=======================================================================================
/**======================================================================================
 * @Fn				-MCAL_I2C_Deinit
 * @brief 			-DeInitializes I2C
 * @param [in]		-I2Cx: where x can be (1,2.....) depending on the device used
 * @retval 			-none
 * Note				-MODULE RESET USING RCC
 *
 */
void MCAL_I2C_Deinit(I2C_TypeDef* I2Cx)
{
	uint8_t index = I2C_NUMBER(I2Cx);

	I2C_peripheral_ENABLE(index ,I2C_DISABLE);
	I2C_NVIC_ENABLE(index ,I2C_DISABLE , EV);
	I2C_NVIC_ENABLE(index ,I2C_DISABLE , ER);
}




/**======================================================================================
 * @Fn				-MCAL_SPI_GPIO_SetPins
 * @brief 			-initialize GPIO pins
 * @param [in]		-SPIx: where x can be (1,2.....) depending on the device used
 * @retval 			-none
 * Note				-none
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIO_PinConfig_t GPIOPIN;
	if (I2C_NUMBER(I2Cx) == I2C1CNFG)
	{
		//I2C1 >> SCL >> PB6
		GPIOPIN.GPIO_PinNumber		= GPIO_PIN_6			;
		GPIOPIN.GPIO_Mode			= GPIO_MODE_AF_OUT_OD	;
		GPIOPIN.GPIO_Output_Speed	= GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOB, &GPIOPIN);

		//I2C1 >> SDA >> PB7
		GPIOPIN.GPIO_PinNumber		= GPIO_PIN_7			;
		GPIOPIN.GPIO_Mode			= GPIO_MODE_AF_OUT_OD	;
		GPIOPIN.GPIO_Output_Speed	= GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOB, &GPIOPIN);
	}
	else //Index == I2C2CNFG
	{
		//I2C2 >> SCL >> PB10
		GPIOPIN.GPIO_PinNumber		= GPIO_PIN_10			;
		GPIOPIN.GPIO_Mode			= GPIO_MODE_AF_OUT_OD	;
		GPIOPIN.GPIO_Output_Speed	= GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOB, &GPIOPIN);

		//I2C2 >> SDA >> PB11
		GPIOPIN.GPIO_PinNumber		= GPIO_PIN_11			;
		GPIOPIN.GPIO_Mode			= GPIO_MODE_AF_OUT_OD	;
		GPIOPIN.GPIO_Output_Speed	= GPIO_SPEED_10M		;
		MCAL_GPIO_Init(GPIOB, &GPIOPIN);
	}
}




/**======================================================================================
 * @Fn				-MCAL_I2C_MASTER_Tx
 * @brief 			-sending data from MASTER
 * @param [in]		-I2Cx: where x can be (1,2.....) depending on the device used
 * @param [in]		-startCondition
 * @param [in]		-devAddress
 * @param [in]		-*data
 * @param [in]		-dataLength
 * @param [in]		-stopCondition
 * @retval 			-NONE
 * Note				- This function is configured for 7BIT SLAVE ADRESSES ONLY
 *
 */



void MCAL_I2C_MASTER_Tx(I2C_TypeDef* I2Cx , start_condition startCondition , uint8_t devAddress , uint8_t * data \
		, uint8_t dataLength ,stop_condition stopCondition)
{

	int i = 0;
	//1- Start Generation
	I2C_Generate_Start(I2Cx,startCondition,I2C_ENABLE);
	//2- wait for EV5 >> SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while (!I2C_Check_flag(I2Cx ,EV5));
	// sending the address
	I2C_Send_Address(I2Cx ,devAddress ,TRANSMITER);
	//3- wait for EV6 >> ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!I2C_Check_flag(I2Cx ,EV6));

	//4- wait for EV8_1 >>TxE=1, shift register empty, data register empty, write Data1 in DR.
	while (!I2C_Check_flag(I2Cx ,EV8_1));
	// sending the data to I2Cx->DR
	for(i=0 ; i< dataLength;i++ )
	{
		I2Cx->DR = data[i] ;

		while (!I2C_Check_flag(I2Cx ,EV8));
	}

	//5- Generating Stop Condition
	if(stopCondition == WITH_STOP)
	{
		I2C_Generate_Stop(I2Cx ,I2C_ENABLE);
	}
}





void MCAL_I2C_MASTER_Rx(I2C_TypeDef* I2Cx , start_condition startCondition, uint8_t devAddress , uint8_t * data \
		,uint8_t dataLength ,stop_condition stopCondition)
{
	int i = 0;
	//1- Start Generation
	I2C_Generate_Start(I2Cx,startCondition,I2C_ENABLE);
	//2- wait for EV5 >> SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while (!I2C_Check_flag(I2Cx ,EV5));
	// sending the address
	I2C_Send_Address(I2Cx ,devAddress ,RECEIVER);
	//3- wait for EV6 >> ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!I2C_Check_flag(I2Cx ,EV6));

	// MAKING SURE THAT THE ACK IS ENABLED
	I2C_ACK_Config(I2Cx ,I2C_ENABLE );

	// sending the data to I2Cx->DR
	if(dataLength)
	{
		for(i=0 ; i < (dataLength-1) ;i++ )
		{
			//- wait for EV7 >> RxNe = 1 cleared by reading DR register
			while (!I2C_Check_flag(I2Cx ,EV7));
			data[i] = I2Cx->DR ;
		}

		//AFTER THE DATA HAS BEEN TRANSMITTED , NACK IS SENT
		I2C_ACK_Config(I2Cx ,I2C_DISABLE );
	}


	//5- Generating Stop Condition
	if(stopCondition == WITH_STOP)
	{
		I2C_Generate_Stop(I2Cx ,I2C_ENABLE);
	}

	//reEnabling the ACK
	if (I2C_CNFG[I2C_NUMBER(I2Cx)].ACK_EN == I2C_ACK_ENABLE )
	{
		I2C_ACK_Config(I2Cx ,I2C_ENABLE );
	}




}











//=======================================================================================
//									STATIC FUNCTIONS IMPLEMENTATION
//=======================================================================================

//=====================================RELATED TO THE Tx/Rx==============================

static void I2C_Generate_Start(I2C_TypeDef* I2Cx,start_condition condition ,I2C_CHOISE choise)
{
	if ( condition != REPEATED_START)
	{
		while ( I2C_Check_flag(I2Cx , BUSY));
	}

	if (choise == I2C_ENABLE)
	{
		//ENABLING START
		I2Cx->CR1 |= 1<<8 ;
	}
	else
	{
		//DISABLLING START
		I2Cx->CR1 &= ~(1<<8) ;
	}
}


static void I2C_Generate_Stop(I2C_TypeDef* I2Cx , I2C_CHOISE choise)
{

	if (choise == I2C_ENABLE)
	{
		//ENABLING STOP
		I2Cx->CR1 |= 1<<9 ;
	}
	else
	{
		//DISABLLING STOP
		I2Cx->CR1 &= ~(1<<9) ;
	}


}



static uint8_t I2C_Check_flag(I2C_TypeDef* I2Cx ,flag_choise flag )
{
	uint8_t retVal = 0;
	switch (flag)
	{
	case BUSY: //I2Cx->SR2 >> Bit 1 BUSY: Bus busy
		retVal = (I2Cx->SR2 >> 1) & 1 ;
		break;
	case EV5: //I2Cx->SR1 >> Bit 0 SB: Start bit (Master mode)
		retVal = (I2Cx->SR1 >> 0) & 1 ;
		break;
	case EV6: //I2Cx->SR1 >> Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		retVal = (I2Cx->SR1 >> 1) & 1 ;
		break;
	case EV8:
	case EV8_1: //I2Cx->SR1 >> Bit 7 TxE: Data register empty (transmitters)
		retVal = (I2Cx->SR1 >> 7) & 1 ;
		break;
	case EV7 : //I2Cx->SR1 >> Bit 6 RxNE: Data register not empty (receivers)
		retVal = (I2Cx->SR1 >> 6) & 1 ;
		break;


	}

	return retVal;

}




static void I2C_Send_Address(I2C_TypeDef* I2Cx ,uint8_t devAddress ,Tx_condition condition)
{
	devAddress = (devAddress << 1) ;
	if (condition == TRANSMITER)
	{
		devAddress &= ~(1<<0);
	}
	else //RECEIVER
	{
		devAddress |= (1<<0);
	}

	I2Cx->DR = devAddress;

}



static void I2C_ACK_Config(I2C_TypeDef* I2Cx ,I2C_CHOISE choise  )
{

	if (choise == I2C_ENABLE) //ACK
	{
		I2Cx->CR1 |= I2C_ACK_ENABLE ;

	}
	else //NACK
	{

		I2Cx->CR1 &= ~(I2C_ACK_ENABLE) ;
	}



}


//===================================GENERIC==================================
static uint8_t I2C_NUMBER(I2C_TypeDef* I2Cx)
{
	if(I2Cx == I2C1)
	{
		return I2C1CNFG;
	}
	else //I2C2
	{
		return I2C2CNFG;
	}

}


static void I2C_peripheral_ENABLE(uint8_t index ,I2C_CHOISE choise)
{

	if(choise == I2C_ENABLE)
	{
		if (index == I2C1CNFG){RCC_I2C1_CLK_EN();}
		else {RCC_I2C2_CLK_EN();}
	}
	else	//DISABLE
	{
		if (index == I2C1CNFG){RCC_I2C1_RESET();}
		else {RCC_I2C2_RESET();}
	}


}


static void I2C_NVIC_ENABLE(uint8_t index ,I2C_CHOISE choise , I2C_IRQ_CHOISE irqChois )
{
	if(index == I2C1CNFG)
	{
		if(choise == I2C_ENABLE )
		{
			if (irqChois == EV){NVIC_IRQ31_I2C1_EV_ENABLE;}
			else {NVIC_IRQ32_I2C1_ER_ENABLE;}
		}
		else  	//DISABLE
		{
			if (irqChois == EV){NVIC_IRQ31_I2C1_EV_DISABLE;}
			else {NVIC_IRQ32_I2C1_ER_DISABLE;}
		}
	}
	else //I2C2
	{
		if(choise == I2C_ENABLE )
		{
			if (irqChois == EV){NVIC_IRQ33_I2C2_EV_ENABLE;}
			else {NVIC_IRQ34_I2C2_ER_ENABLE;}
		}
		else  	//DISABLE
		{
			if (irqChois == EV){NVIC_IRQ33_I2C2_EV_DISABLE;}
			else {NVIC_IRQ34_I2C2_ER_DISABLE;}
		}
	}


}

//=======================================================================================
//									INLINE FUNCTIONS IMPLEMENTATION
//=======================================================================================


inline uint32_t I2C_SM_CONFIG(uint32_t speed )
{
	return speed;

}

inline uint32_t I2C_FM_CONFIG(uint32_t speed)
{

	return speed;

}





