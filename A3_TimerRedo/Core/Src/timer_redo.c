/*
 * timer_redo.c
 *
 *  Created on: May 9, 2023
 *      Author: msrik
 */

#include "timer_redo.h"
void TIM2_init(void)
{
  // configure TIM2 to interrupt every 0.5s
  RCC -> APB1ENR1 |= (RCC_APB1ENR1_TIM2EN);

  TIM2 -> DIER  |=(TIM_DIER_UIE | TIM_DIER_CC1IE); // enable interrupt on update event
  TIM2 -> SR    &= ~(TIM_SR_UIF | TIM_SR_CC1IF);  // clear update interrupt flag
  TIM2->ARR      = 800 - 1; //4 MHz clock, setting ot the MAX
  TIM2->CCR1    |= 200 - 1; // setting to a 50% duty cycle, this is like our first timer.
  TIM2->CR1     |= (TIM_CR1_CEN);  // start timer


  // enable interrupts in NVIC
  NVIC->ISER[0] = (1 << (TIM2_IRQn & 0x1F));

  __enable_irq(); // enable interrupts globally

}


void TIM2_IRQHandler(void)
{
	//GPIOB->ODR |= GPIO_ODR_OD5; // toggle LED(PA5)
	// check status register for update event flag - if 0xfffffff is hit
	if(TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~(TIM_SR_UIF); // clear flag
		GPIOB->ODR &= ~(GPIO_ODR_OD5); // toggle LED(PA5)
	}

	else if(TIM2->SR & TIM_SR_CC1IF)
	{
		TIM2->SR &= ~(TIM_SR_CC1IF); // clear flag
		GPIOB->ODR |= (GPIO_ODR_OD5); // toggle LED(PA5)
		//TIM2->CCR1 += 400;
	}

}
