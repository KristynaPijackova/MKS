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

#define sct_nla(x) do { if (x) GPIOB->BSRR = (1 << 5); else GPIOB->BRR = (1 << 5); } while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSRR = (1 << 4); else GPIOB->BRR = (1 << 4);} while (0)
#define sct_clk(x) do { if (x) GPIOB->BSRR = (1 << 3); else GPIOB->BRR = (1 << 3);} while (0)
#define sct_noe(x) do { if (x) GPIOB->BSRR = (1 << 10); else GPIOB->BRR = (1 << 10);} while (0)


/*Enable registers and signals*/
void sct_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable register GPIO B
	GPIOB->MODER |= GPIO_MODER_MODER5_0; // signal initializations
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->MODER |= GPIO_MODER_MODER3_0;
	GPIOB->MODER |= GPIO_MODER_MODER10_0;

	/*Write 0 to shift registers*/
	sct_led(0);
	sct_noe(0);

}

/*Fction to send the value to the 7-seg*/
void sct_led(uint32_t value)
{
	/*Loop 32 times through the value and allow latch after its done*/
	/*Starting from LSB setting it to 1 set clock and continue with shifted 1*/
	for (uint8_t i=0; i<32; i++)
	{
		sct_sdi(value & 1);
		value >>= 1;
		sct_clk(1);
		sct_clk(0);
	}
	sct_nla(1);
	sct_nla(0);
}
