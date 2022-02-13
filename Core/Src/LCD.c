/*
 * lcd.c
 *
 *  Created on: 13 de fev de 2022
 *      Author: Rodrigo Hiury
 */

#include "LCD.h"
#include "stm32f0xx_hal.h"
#include "string.h"


/*----------------------------------------------------------
 * LCD_SendByte: sending byte to LCD.
 *
 * Parameters:	uint8_t.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_SendByte(uint8_t cmd)
{

	HAL_GPIO_WritePin(LCD_PORT, LCD_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET);

	if( cmd & 0x01 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D0, GPIO_PIN_SET);
	if( cmd & 0x02 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D1, GPIO_PIN_SET);
	if( cmd & 0x04 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D2, GPIO_PIN_SET);
	if( cmd & 0x08 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D3, GPIO_PIN_SET);
	if( cmd & 0x10 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D4, GPIO_PIN_SET);
	if( cmd & 0x20 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D5, GPIO_PIN_SET);
	if( cmd & 0x40 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D6, GPIO_PIN_SET);
	if( cmd & 0x80 )
		HAL_GPIO_WritePin(LCD_PORT, LCD_D7, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT, LCD_D_ALL, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET);
	HAL_Delay(5); //While Busy Flag is 1
}

/*----------------------------------------------------------
 * LCD_SendCmd: sending command to LCD.
 *
 * Parameters:	uint8_t.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_SendCmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET);
	HAL_Delay(1);
	LCD_SendByte(cmd);
}

/*----------------------------------------------------------
 * LCD_SendData: sending data to LCD.
 *
 * Parameters:	uint32.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_SendData(uint32_t data)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_SET);
	HAL_Delay(1);
	LCD_SendByte(data);
}

/*----------------------------------------------------------
 * LCD_Num: print a number up to 9999.
 *
 * Parameters:	uint32.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_Num(uint32_t x)
{
	LCD_SendData((x/1000) + 0x30);
	LCD_SendData((x/100)%10 + 0x30);
	LCD_SendData((x%100)/10 + 0x30);
	LCD_SendData((x%10) + 0x30);
}

/*----------------------------------------------------------
 * LCD_SendText: print a string on LCD.
 *
 * Parameters:	char.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_SendText(char text[])
{
	for (int i = 0; i < strlen(text); i++){
		LCD_SendData(text[i]);
	}
}

/*----------------------------------------------------------
 * LCD_Clear: clear the LCD.
 *
 * Parameters:	none.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_Clear(void)
{
	LCD_SendCmd(0x01);
}

/*----------------------------------------------------------
 * LCD_GoTo: set cursor position on LCD.
 *
 * Parameters:	column and line.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_GoTo(unsigned char line, unsigned char column)
{
	uint8_t position = 0;

	switch(line)
	{
		case 0:	position = 0x00;
				break;
		case 1:	position = 0x40;
				break;
		case 2:	position = 0x10;
				break;
		case 3:	position = 0x50;
				break;
		default: position = 0x00;
				break;
	}
	LCD_SendCmd(0x80 | (position + column));
}

/*----------------------------------------------------------
 * LCD_Init: initialize the LCD.
 *
 * Parameters:	none.
 * Return:	none.
 *---------------------------------------------------------*/
void LCD_Init(void)
{
	LCD_SendCmd(0x38); /* 2 lines, 5x8 character matrix      	*/
	LCD_SendCmd(0x08); /* Turn off display				*/
	LCD_SendCmd(0x0C); /* Display ctrl:Disp=ON,Curs/Blnk=OFF 	*/
	LCD_SendCmd(0x06); /* Entry mode: Move right, no shift   	*/
	LCD_SendCmd(0x01); /* Clean display with home cursor 		*/
	LCD_SendCmd(0x02); /* Force Cursor to the beginning */

	HAL_Delay(1);
}


