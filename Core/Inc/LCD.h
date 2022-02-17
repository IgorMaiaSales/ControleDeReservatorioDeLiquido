/*
 * LCD.h
 *
 *  Created on: Feb 16, 2022
 *      Author: rodri
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_RS          GPIO_PIN_15
#define LCD_RW          GPIO_PIN_14
#define LCD_EN          GPIO_PIN_13
#define LCD_D0			GPIO_PIN_12
#define LCD_D1			GPIO_PIN_11
#define LCD_D2			GPIO_PIN_10
#define LCD_D3			GPIO_PIN_9
#define LCD_D4          GPIO_PIN_8
#define LCD_D5          GPIO_PIN_7
#define LCD_D6		    GPIO_PIN_6
#define LCD_D7          GPIO_PIN_5
#define LCD_PORT        GPIOB
#define LCD_D_ALL	    (GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8| GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12)

unsigned char LCD_ReadByte(void);
void LCD_SendByte(unsigned char cmd);
void LCD_SendCmd (unsigned char cmd);
void LCD_SendData(uint32_t data);
void LCD_SendText(char text[]);
void LCD_SendTextPos(char text[], unsigned char line, unsigned char column);
void LCD_GoTo (unsigned char line, unsigned char column);
void LCD_Clear (void);
void LCD_Init (void);
void LCD_NumInt(int x, unsigned char line, unsigned char column);
void LCD_NumFloat(float x, unsigned char line, unsigned char column);

#endif /* INC_LCD_H_ */
