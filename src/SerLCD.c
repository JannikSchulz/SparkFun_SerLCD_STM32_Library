/**
 * SerLCD.h
 * @file		SerLCD.h
 * @brief 		STM32 Library for SparkFun OpenLCD display based on HAL
 * @date 		03.06.2019
 * @version		0.0.1
 * @author 		Mario Hesse
 * @copyright 	MIT Licence
 *
 *
 * Original information copied form LCD library for SparkFun RGB 3.3v Serial Open LCD display
 * ------------------------------------------------------------------------------------------
 * LCD library for SparkFun RGB 3.3v Serial Open LCD display
 * with an attached Qwiic adapter.
 *
 * By: Gaston R. Williams
 * Date: August 22, 2018
 *
 * License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 *
 * This library is based heavily on the LiquidCrystal_I2C library and the sample code provided with
 * the SparkFun Serial OpenLCD display.  The original LiquidCrystal library by David A. Mellis and
 * modified by Limor Fried and the OpenLCD code by Nathan Seidle at SparkFun.
 *
 * The LiquidCrystal_I2C library was based on the work by DFRobot.
 * (That's the only attribution I found in the code I have. If anyone can provide better information,
 * Plese let me know and I'll be happy to give credit where credit is due.)
 *
 * Original information copied from OpenLCD:
 *
 * The OpenLCD display information is based based on code by
 * Nathan Seidle
 * SparkFun Electronics
 * Date: April 19th, 2015
 *
 * License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 * OpenLCD gives the user multiple interfaces (serial, I2C, and SPI) to control an LCD. SerLCD was the original
 * serial LCD from SparkFun that ran on the PIC 16F88 with only a serial interface and limited feature set.
 * This is an updated serial LCD.
 *
 * Please Note: 0x72 is the 7-bit I2C address. If you are using a different language than Arduino you will probably
 * need to add the Read/Write bit to the end of the address. This means the default read address for the OpenLCD
 * is 0b.1110.0101 or 0xE5 and the write address is 0b.1110.0100 or 0xE4.
 * For more information see https://learn.sparkfun.com/tutorials/i2c
 * Note: This code expects the display to be listening at the default I2C address. If your display is not at 0x72, you can
 * do a hardware reset. Tie the RX pin to ground and power up OpenLCD. You should see the splash screen
 * then "System reset Power cycle me" and the backlight will begin to blink. Now power down OpenLCD and remove
 * the RX/GND jumper. OpenLCD is now reset.
 *
 * To get this code to work, attach a Qwiic adapter to an OpenLCD. Use the Qwiic cable to attach adapter to a SparkFun Blackboard or
 * an Arduino Uno with the Qwiic shield.
 *
 * The OpenLCD has 4.7k pull up resistors on SDA and SCL. If you have other devices on the
 * I2C bus then you may want to disable the pull up resistors by clearing the PU (pull up) jumper.
 * OpenLCD will work at 400kHz Fast I2C. Use the .setClock() call shown below to set the data rate
 * faster if needed.
 * Command cheat sheet:
 * ASCII / DEC / HEX
 * '|'    / 124 / 0x7C - Put into setting mode
 * Ctrl+c / 3 / 0x03 - Change width to 20
 * Ctrl+d / 4 / 0x04 - Change width to 16
 * Ctrl+e / 5 / 0x05 - Change lines to 4
 * Ctrl+f / 6 / 0x06 - Change lines to 2
 * Ctrl+g / 7 / 0x07 - Change lines to 1
 * Ctrl+h / 8 / 0x08 - Software reset of the system
 * Ctrl+i / 9 / 0x09 - Enable/disable splash screen
 * Ctrl+j / 10 / 0x0A - Save currently displayed text as splash
 * Ctrl+k / 11 / 0x0B - Change baud to 2400bps
 * Ctrl+l / 12 / 0x0C - Change baud to 4800bps
 * Ctrl+m / 13 / 0x0D - Change baud to 9600bps
 * Ctrl+n / 14 / 0x0E - Change baud to 14400bps
 * Ctrl+o / 15 / 0x0F - Change baud to 19200bps
 * Ctrl+p / 16 / 0x10 - Change baud to 38400bps
 * Ctrl+q / 17 / 0x11 - Change baud to 57600bps
 * Ctrl+r / 18 / 0x12 - Change baud to 115200bps
 * Ctrl+s / 19 / 0x13 - Change baud to 230400bps
 * Ctrl+t / 20 / 0x14 - Change baud to 460800bps
 * Ctrl+u / 21 / 0x15 - Change baud to 921600bps
 * Ctrl+v / 22 / 0x16 - Change baud to 1000000bps
 * Ctrl+w / 23 / 0x17 - Change baud to 1200bps
 * Ctrl+x / 24 / 0x18 - Change the contrast. Follow Ctrl+x with number 0 to 255. 120 is default.
 * Ctrl+y / 25 / 0x19 - Change the TWI address. Follow Ctrl+x with number 0 to 255. 114 (0x72) is default.
 * Ctrl+z / 26 / 0x1A - Enable/disable ignore RX pin on startup (ignore emergency reset)
 * '+'    / 43 / 0x2B - Set RGB backlight with three following bytes, 0-255
 * ','    / 44 / 0x2C - Display current firmware version
 * '-'    / 45 / 0x2D - Clear display. Move cursor to home position.
 * '.'    / 46 / 0x2E - Enable system messages (ie, display 'Contrast: 5' when changed)
 * '/'    / 47 / 0x2F - Disable system messages (ie, don't display 'Contrast: 5' when changed)
 * '0'    / 48 / 0x30 - Enable splash screen
 * '1'    / 49 / 0x31 - Disable splash screen
 *        / 128-157 / 0x80-0x9D - Set the primary backlight brightness. 128 = Off, 157 = 100%.
 *        / 158-187 / 0x9E-0xBB - Set the green backlight brightness. 158 = Off, 187 = 100%.
 *        / 188-217 / 0xBC-0xD9 - Set the blue backlight brightness. 188 = Off, 217 = 100%.
 *		For example, to change the baud rate to 115200 send 124 followed by 18.
 *
 */
 */

#include "SerLCD.h"
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



uint8_t _i2cAddr = DISPLAY_ADDRESS1;
I2C_HandleTypeDef *_i2cHandler;
uint8_t _displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
uint8_t _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;



/*
 *  @brief	Initial start of the display - defines the maximum rows and
 *  		columns on the display refered to
 *  		• MAX_ROWS and
 *  		• MAX_COLUMNS
 * 	@param	hi2c - pointer to the i2c handler
 *  @retval status (0...OK, other...error)
 */
uint8_t displayInit(I2C_HandleTypeDef *hi2c)
{
	uint8_t retval = LCD_OK;

	uint8_t rows;
	uint8_t columns;

	_i2cHandler = hi2c;			// pointer for i2c handler is stored in library

	switch(MAX_ROWS)
	{
	case 1: 	rows = 0x07;
				break;

	case 2:		rows = 0x06;
				break;

	case 4: 	rows = 0x05;
				break;

	default:	rows = 0x07;
				retval = LCD_ERROR_STD;
				break;

	}

	switch(MAX_COLUMNS)
	{
	case 16: 	columns = 0x04;
				break;

	case 20:	columns = 0x03;
				break;

	default:	columns = 0x04;
				retval = LCD_ERROR_STD;
				break;

	}

    uint8_t TransmitData[6] = {SETTING_COMMAND, columns, 			// maximum columns
    						   SETTING_COMMAND, rows, 				// maximum rows
							   SETTING_COMMAND, CLEAR_COMMAND}; 	// clear display

    if(HAL_I2C_Master_Transmit(_i2cHandler, DISPLAY_ADDRESS1<<1, TransmitData, sizeof(TransmitData), 100) != HAL_OK)		// transmit data
    {
    	retval = LCD_ERROR_TRANSMIT_I2C;
    }

    return retval;
}



/*
 * @brief  Defines a RGB display background color
 * @param  r - can be 0...255
 * @param  g - can be 0...255
 * @param  b - can be 0...255
 *
 */
uint8_t displayColor(uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t retval = LCD_OK;

	// size reduction of the percentage to a value between 0 and 29
	if(r != 0)
		r = r*29/255;
	if(g != 0)
		g = g*29/255;
	if(b != 0)
		b = b*29/255;

	// create i2c data stream
    uint8_t TransmitData[10] = {SPECIAL_COMMAND,								//Send special command character
    						    LCD_DISPLAYCONTROL |(_displayControl & ~LCD_DISPLAYON), // turn display off
    						    SETTING_COMMAND, (128 + r),						// red: 0...100% ~ 0...29
    						    SETTING_COMMAND, (158 + g), 					// green: 0...100% ~ 0...29
							    SETTING_COMMAND, (188 + b), 					// blue: 0...100% ~ 0...29
								SPECIAL_COMMAND,                      			//Send special command character
								LCD_DISPLAYCONTROL | (_displayControl |= LCD_DISPLAYON)}; // turn display off as before

    // transmission of data stream
    if(HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDRESS1<<1, TransmitData, sizeof(TransmitData), 100) != HAL_OK)		// transmit data
    	retval = LCD_ERROR_TRANSMIT_I2C;
    HAL_Delay(50);

	return retval;
}



/*
 * @brief	Send a command to the display.
 * 			Used by other functions.
 * @retval	status (0...OK, other...error)
 */
uint8_t displayCommand(uint8_t command)
{
	uint8_t retval = LCD_OK;
	uint8_t TransmitData[2] = {SETTING_COMMAND, command}; 												// create data stream
	if(HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDRESS1<<1, TransmitData, sizeof(TransmitData), 100) != HAL_OK)		// transmit data
		retval = LCD_ERROR_TRANSMIT_I2C;
	HAL_Delay(10); //Wait a bit longer for special display commands
	return retval;
}



/*
 * @brief	Send a special command to the display.  Used by other functions.
 * @retval	status (0...OK, other...error)
 */
uint8_t displaySpecialCommand(uint8_t command)
{
	uint8_t retval = LCD_OK;
	uint8_t TransmitData[2] = {SPECIAL_COMMAND, command}; 												// create data stream
	if(HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDRESS1<<1, TransmitData, sizeof(TransmitData), 100) != HAL_OK)		// transmit data
		retval = LCD_ERROR_TRANSMIT_I2C;
	HAL_Delay(50); //Wait a bit longer for special display commands
	return retval;
}




char* displayPrepareText(uint16_t Value)
{
	extern char DisplayText[DisplayChar];
    strcpy(DisplayText, "ADC:      Bit ");				// create 1. row
    //strcat(DisplayText, "                ");				// create 2. row
    char ValueString[5] = {""};
    snprintf(ValueString, 5, "%d", Value);

    uint8_t i = 0;

    if (ValueString[3] == 0)
    {
    	i=1;
    }
    else
    	DisplayText[8+i] = ValueString[3];

    if (ValueString[2] == 0)
    {
    	i=2;
    }
    else
       	DisplayText[7+i] = ValueString[2];

    if (ValueString[1] == 0)
    {
    	i=3;
    }
    else
       	DisplayText[6+i] = ValueString[1];

    if (ValueString[0] == 0)
    {
    	i=4;
    }
    else
       	DisplayText[5+i] = ValueString[0];


    return DisplayText;
}



/*
 * @brief	writes a string to the display
 * @param	*String - pointer to the string to be written
 * @param	Length  - length of the string to be written
 * @retval	status (0...OK, other...error)
 *
 */
uint8_t displayWriteString(char *String, uint16_t Length)
{

    HAL_I2C_Master_Transmit(_i2cHandler, DISPLAY_ADDRESS1<<1, String, Length, 100);		// transmit data
    HAL_Delay(50);

    return 0;
}



/*
 * @brief	Send the clear command to the display.  This clears the
 * 			display and forces the cursor to return to the beginning
 * 			of the display.
 * @retval 	status (0...OK, other...error)
 */
uint8_t DisplayClear()
{
	uint8_t retval = displayCommand(CLEAR_COMMAND);
	HAL_Delay(10);
	return retval;
}



/*
 * @brief	Send the home command to the display.  This returns the cursor
 * 			to return to the beginning of the display, without clearing
 * 			the display.
 * @retval	status (0...OK, other...error)
 */
uint8_t displayHome()
{
	return displayCommand(LCD_RETURNHOME);
}



/*
 * @brief	Set the cursor position to a particular column and row.
 * @param	col - column number (0...19)
 * @param	row  - row number (0...3)
 * @retval	status (0...OK, other...error)
 */
uint8_t displaySetCursor(uint8_t col, uint8_t row)
{
  uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};

  //kepp variables in bounds
  //row = max(0, row);            //row cannot be less than 0
  //row = min(row, MAX_ROWS - 1); //row cannot be greater than max rows

  //send the command
  return displaySpecialCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}













