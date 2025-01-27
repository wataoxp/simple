/*
 * gpio.c
 *
 *  Created on: Jan 12, 2025
 *      Author: wataoxp
 */

#include "gpio.h"

GPIO_Code GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_InitTypedef *InitStruct)
{
	if((InitStruct->PinPos == Pin13) || (InitStruct->PinPos == Pin14))
	{
		if(GPIOx == GPIOA)
		{
			return init_Failed;
		}
	}
	if(InitStruct->Mode == LL_GPIO_MODE_OUTPUT || InitStruct->Mode == LL_GPIO_MODE_ALTERNATE)
	{
		WRITE_REG(GPIOx->BRR,1 << InitStruct->PinPos);
		GPIO_SetPinSpeed(GPIOx, InitStruct->PinPos, InitStruct->Speed);
		GPIO_SetOutputPinType(GPIOx, (1 << InitStruct->PinPos), InitStruct->OutputType);
	}
	if(InitStruct->Mode == LL_GPIO_MODE_ALTERNATE)
	{
		if(InitStruct->PinPos < Pin8)
		{
			GPIO_SetAlternate0_7(GPIOx, InitStruct->PinPos, InitStruct->Alternate);
		}
		else
		{
			GPIO_SetAlternate8_15(GPIOx, InitStruct->PinPos, InitStruct->Alternate);
		}
	}
	GPIO_SetPinPull(GPIOx, InitStruct->PinPos, InitStruct->Pull);
	GPIO_SetPinMode(GPIOx, InitStruct->PinPos, InitStruct->Mode);

	return init_Success;
}

