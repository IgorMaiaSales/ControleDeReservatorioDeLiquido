/*
 * keypad.h
 *
 *  Created on: Feb 16, 2022
 *      Author: rodri
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stm32f1xx_hal.h"

#define COLUMNPORT GPIOA
#define ROWPORT GPIOB
#define ROW1 GPIO_PIN_0
#define ROW2 GPIO_PIN_1
#define ROW3 GPIO_PIN_2
#define ROW4 GPIO_PIN_3
#define COLUMN1 GPIO_PIN_12
#define COLUMN2 GPIO_PIN_13
#define COLUMN3 GPIO_PIN_14
#define COLUMN4 GPIO_PIN_15

char* readKeypad(void);

#endif /* INC_KEYPAD_H_ */
