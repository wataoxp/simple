#include "main.h"
#include "lcd.h"

#include <string.h>

static I2C_TypeDef *I2Cx;

static void RCC_Set(void);
static void GPIO_Set(GPIO_Port);
static void EXTI_Set(GPIO_Port);
static void I2C_Set(void);

void EXTI4_15_IRQHandler(void)
{
	if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_6) != RESET)
	{
		LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_6);
		if(READ_BIT(GPIOA->ODR,(1 << Pin0)))
		{
			WRITE_REG(GPIOA->BRR,1 << Pin0);
		}
		else
		{
			WRITE_REG(GPIOA->BSRR,1 << Pin0);
		}
	}
}

int main(void)
{

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	RCC_Set();
	GPIO_Set(PORTA);
	SysTick_Init(MILL_SECOND);
	EXTI_Set(PORTB);

	while (1)
	{
	  WRITE_REG(GPIOA->BSRR,1 << Pin1);
	  Delay(500);
	  WRITE_REG(GPIOA->BRR,1 << Pin1);
	  Delay(500);
	}
}
static void RCC_Set(void)
{
	RCC_InitTypedef rcc;
	rcc.Latency = LL_FLASH_LATENCY_2;
	rcc.PLLSrc = LL_RCC_PLLSOURCE_HSI;
	rcc.PLLM = LL_RCC_PLLM_DIV_1;
	rcc.PLLN = 8;
	rcc.PLLR = LL_RCC_PLLR_DIV_2;
	rcc.AHBdiv = LL_RCC_SYSCLK_DIV_1;
	rcc.SysClkSrc = LL_RCC_SYS_CLKSOURCE_PLL;
	rcc.APBdiv = LL_RCC_APB1_DIV_1;
	rcc.clock = 64000000;

	RCC_InitG0(&rcc);
}
static void GPIO_Set(GPIO_Port port)
{
	GPIO_TypeDef *GPIOx;
	GPIO_InitTypedef init;
	init.PinPos = Pin0;
	init.Pull = LL_GPIO_PULL_NO;
	init.Mode = LL_GPIO_MODE_OUTPUT;
	init.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

	LL_IOP_GRP1_EnableClock(1 << port);
	switch(port)
	{
	case PORTA:
		GPIOx = GPIOA;
		break;
	case PORTB:
		GPIOx = GPIOB;
		break;
	case PORTC:
		GPIOx = GPIOC;
		break;
	default:
		break;
	}
	GPIO_Init(GPIOx, &init);
	init.PinPos = Pin1;
	GPIO_Init(GPIOx, &init);
}
static void EXTI_Set(GPIO_Port port)
{
	LL_EXTI_InitTypeDef init;
	init.Line_0_31 = LL_EXTI_LINE_6;
	init.Mode = LL_EXTI_MODE_IT;
	init.Trigger = LL_EXTI_TRIGGER_FALLING;

	LL_IOP_GRP1_EnableClock(1 << port);

	__NVIC_SetPriority(EXTI4_15_IRQn, 2);
	__NVIC_EnableIRQ(EXTI4_15_IRQn);

	EXTI_SetSource(port, Pin6);
	//LL_EXTI_SetEXTISource(port, LL_EXTI_CONFIG_LINE6);
	EXTI_Init(&init);

	GPIO_SetPinPull(GPIOB, Pin6, LL_GPIO_PULL_UP);
	GPIO_SetPinMode(GPIOB, Pin6, LL_GPIO_MODE_INPUT);
}
static void I2C_Set(void)
{
	GPIO_InitTypedef init[2] = {
		{
			.Mode = LL_GPIO_MODE_ALTERNATE,
			.Speed = LL_GPIO_SPEED_FREQ_LOW,
			.OutputType = LL_GPIO_OUTPUT_OPENDRAIN,
			.Pull = LL_GPIO_PULL_NO,
			.Alternate = LL_GPIO_AF_6
		},{
			.Mode = LL_GPIO_MODE_ALTERNATE,
			.Speed = LL_GPIO_SPEED_FREQ_LOW,
			.OutputType = LL_GPIO_OUTPUT_OPENDRAIN,
			.Pull = LL_GPIO_PULL_NO,
			.Alternate = LL_GPIO_AF_6
		},
	};
	init[0].PinPos = Pin11;
	GPIO_Init(GPIOA, &init[0]);

	init[1].PinPos = Pin12;
	GPIO_Init(GPIOA, &init[1]);

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

	LL_I2C_Disable(I2Cx);
	LL_I2C_ConfigFilters(I2Cx, LL_I2C_ANALOGFILTER_ENABLE,0);
	LL_I2C_SetTiming(I2Cx, 0x00C12166);

	LL_I2C_Enable(I2Cx);
	LL_I2C_EnableAutoEndMode(I2Cx);
	LL_I2C_EnableClockStretching(I2Cx);
}
