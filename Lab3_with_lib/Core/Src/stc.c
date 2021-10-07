/*
 * stc.c
 *
 * Source file for writing in 7-seg on the board
 * Contains two fctions one to initialize and enable registers
 * and one to enable the writing.
 *
 *  Created on: 7. 10. 2021
 *      Author: student
 */

#include <stdint.h>
#include "stm32f0xx.h"
#include "sct.h"
#include "main.h"

// Table to translate numbers to 7-seg registers
static const uint32_t reg_values[3][10] = {
 {
 //PCDE--------GFAB @ DIS1
 0b0111000000000111 << 16,
 0b0100000000000001 << 16,
 0b0011000000001011 << 16,
 0b0110000000001011 << 16,
 0b0100000000001101 << 16,
 0b0110000000001110 << 16,
 0b0111000000001110 << 16,
 0b0100000000000011 << 16,
 0b0111000000001111 << 16,
 0b0110000000001111 << 16,
 },
 {
 //----PCDEGFAB---- @ DIS2
 0b0000011101110000 << 0,
 0b0000010000010000 << 0,
 0b0000001110110000 << 0,
 0b0000011010110000 << 0,
 0b0000010011010000 << 0,
 0b0000011011100000 << 0,
 0b0000011111100000 << 0,
 0b0000010000110000 << 0,
 0b0000011111110000 << 0,
 0b0000011011110000 << 0,
 },
 {
 //PCDE--------GFAB @ DIS3
 0b0111000000000111 << 0,
 0b0100000000000001 << 0,
 0b0011000000001011 << 0,
 0b0110000000001011 << 0,
 0b0100000000001101 << 0,
 0b0110000000001110 << 0,
 0b0111000000001110 << 0,
 0b0100000000000011 << 0,
 0b0111000000001111 << 0,
 0b0110000000001111 << 0,
 },
 };



/*Enable registers and signals*/
void sct_init(void)
{
	/*Write 0 to shift registers*/
	sct_led(0);
}

/*Fction to send the value to the 7-seg*/
void sct_led(uint32_t value)
{
	/*Loop 32 times through the value and allow latch after its done*/
	/*Starting from LSB setting it to 1 set clock and continue with shifted 1*/
	for (uint8_t i=0; i<32; i++)
	{
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, value & 1);
		value >>= 1;
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1); ;
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_value(uint16_t value)
{
	uint32_t reg=0;

	/*Extract the right number on the rigt position from the table*/
	/*eg. 231*/
	reg |= reg_values[0][value / 100 % 10]; // 231/100 = 2 % 10 = 2
	reg |= reg_values[1][value / 10 % 10];  // 231/10 = 23 % 10 = 3
	reg |= reg_values[2][value / 1 % 10];   // 231/1 = 231 % 10 = 1

	sct_led(reg);

}

