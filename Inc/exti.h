/*
 * exti.h
 *
 *  Created on: Jan 28, 2025
 *      Author: wataoxp
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "main.h"

void EXTI_Init(LL_EXTI_InitTypeDef *InitStruct);
void EXTI_SetSource(uint32_t port,uint32_t pin);

#endif /* INC_EXTI_H_ */
