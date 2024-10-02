/*
 * uart.c
 *
 *  Created on: May 3, 2023
 *      Author: msrik
 */
#include "uart.h"
#define USARTDIV 0x0023UL
#define ESC_CHAR 0x1B

void UART_init(void)
{
	/* enable clock for GPIOA and USART2*/
	RCC->AHB2ENR |=  (RCC_AHB2ENR_GPIOAEN);
	RCC->APB1ENR1|= (RCC_APB1ENR1_USART2EN);

	/* set to alternate function mode */
	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
	GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);


	/* enable alternate function registers */
	GPIOA->AFR[0]   	&= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk);	// clear AFR
	GPIOA->AFR[0]		|=  ( (0x7UL << GPIO_AFRL_AFSEL2_Pos) |				// set PA2, PA3
							  (0x7UL << GPIO_AFRL_AFSEL3_Pos));

	/* set to high speed (11) */
	GPIOA->OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3);
	GPIOA->OSPEEDR |=   (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3);

	/* program the M bits in USART_CR1 to define the word length */
	USART2->CR1 &= ~(USART_CR1_M); // bit 28: set to 00 (8 data bits) 1 char is 8 bits ??????

	USART2->CR1 &= ~(USART_CR1_UE); // disable UE to write BRR

	/* select the desired baud rate using the USART_BRR register */
	//USART2->BRR  &= ~(USART_BRR_DIV_MANTISSA| USART_BRR_DIV_FRACTION); // clear bits [15:4] and [3:0] in BRR
	USART2->BRR  = (USARTDIV); // set bits of BRR to USARTDIV

	/* program the number of stop bits in USART_CR2. */
	USART2->CR2 &= ~(USART_CR2_STOP);               // setting stop bit to 1 (00)

	/*enable the USART by writing the UE bit in USART_CR1 register to 1*/
	USART2->CR1 |= (USART_CR1_UE);                 // setting bit 0 to 1

	/*set the TE bit in USART_CR1 to send an idle frame as first transmission*/
	USART2->CR1 |= (USART_CR1_TE);               // setting transmission enable to  ?


	/* enable interrupts */
	USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC->ISER[1] = (1 << (USART2_IRQn & 0x1F));
	__enable_irq();
	USART2->CR1 |= (USART_CR1_RE);               // setting reception enable to 1   ?
}

void UART_print_char(char string) // right now just printing one character
{
	/*set the TE bit in USART_CR1 to send an idle frame as first transmission*/
	//USART2->CR1 |= (USART_CR1_TE);
 /* check the TXE flag*/

	while (!(USART_ISR_TXE & USART2->ISR));// wait until it is ready to be written to, if it is empty then write to it
	USART2->TDR  = string;           // write a char
}

void UART_print(char* string)
{
	int i = 0;
	while(string[i] != '\0')
	{
		UART_print_char(string[i]);
		i += 1;
	}
}

void USART_ESC_Code(char* code)
{
	/* printing an escape character 0x1B*/
	while (!(USART_ISR_TXE & USART2->ISR));
		USART2->TDR  = ESC_CHAR;
	UART_print(code);
}

