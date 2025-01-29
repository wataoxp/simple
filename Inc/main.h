#ifndef __MAIN_H
#define __MAIN_H

/* initFile */
#include "stm32g0xx.h"
#include "core_cm0plus.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"

/* Option File */
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_i2c.h"
#include <stdint.h>

/* MyLibrary */
#include "gpio.h"
#include "rcc.h"
#include "delay.h"
#include "exti.h"

#define MOD(n,m) (n & (m-1))
#define DIV(n,m) (n >> m)

#endif /* __MAIN_H */
