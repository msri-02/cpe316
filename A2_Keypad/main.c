/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#define WAIT_TIME 10000
#define COL_PORT GPIOA
#define ROW_PORT GPIOB
#define LED_PORT GPIOC
#define NUM_OF_ROWS 4
#define NUM_OF_COLS 4
#define ROW_MASK 0x000F
#define COL_HIGH 0x000F


void SystemClock_Config(void);

void led_config(void)
{
  RCC->AHB2ENR   |=  (RCC_AHB2ENR_GPIOCEN);
  LED_PORT->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 |
					  GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
  LED_PORT->MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 |
					  GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
  LED_PORT->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 |
					  GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
  LED_PORT->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
					  GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
  LED_PORT->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED0_Pos) |
					  (3 << GPIO_OSPEEDR_OSPEED1_Pos) |
					  (3 << GPIO_OSPEEDR_OSPEED2_Pos) |
					  (3 << GPIO_OSPEEDR_OSPEED3_Pos));
  GPIOC->BRR = (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);   // preset PC0, PC1 to 0
}

uint8_t LedFunction(uint8_t num) {

	uint8_t test_var;  				// local variable

  //GPIOC->BSRR = (GPIO_PIN_1);             // turn on PC1

  {
	  test_var = num;
	  if(test_var == 0)//0000
	  {
		  GPIOC->BRR = (GPIO_PIN_0);
		  GPIOC->BRR = (GPIO_PIN_1);
		  GPIOC->BRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 1) //0001
	  {
		  GPIOC->BSRR = (GPIO_PIN_0);
		  GPIOC->BRR = (GPIO_PIN_1);
		  GPIOC->BRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 2) //0010
	  {
		  GPIOC->BRR = (GPIO_PIN_0);
		  GPIOC->BSRR = (GPIO_PIN_1);
		  GPIOC->BRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 3) //0011
	  {
		  GPIOC->BSRR = (GPIO_PIN_0);
		  GPIOC->BSRR = (GPIO_PIN_1);
		  GPIOC->BRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 4) //0100
	  {
		  GPIOC->BRR = (GPIO_PIN_0);
		  GPIOC->BRR = (GPIO_PIN_1);
		  GPIOC->BSRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 5) //0101
	  {
		  GPIOC->BSRR = (GPIO_PIN_0);
		  GPIOC->BRR = (GPIO_PIN_1);
		  GPIOC->BSRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 6) //0110
	  {
		  GPIOC->BRR = (GPIO_PIN_0);
		  GPIOC->BSRR = (GPIO_PIN_1);
		  GPIOC->BSRR = (GPIO_PIN_2);
		  GPIOC->BRR = (GPIO_PIN_3);
	  }
	  if(test_var == 7) //0111
	  {
		  GPIOC->BRR = (GPIO_PIN_0);
		  GPIOC->BSRR = (GPIO_PIN_1);
		  GPIOC->BSRR = (GPIO_PIN_2);
		  GPIOC->BSRR = (GPIO_PIN_3);
	  }
	  if (test_var == 8){					//1000
	  	  GPIOC->BRR = (GPIO_PIN_0);
	  	  GPIOC->BRR = (GPIO_PIN_1);
	  	  GPIOC->BRR = (GPIO_PIN_2);
	  	  GPIOC->BSRR = (GPIO_PIN_3);
	    }
	    if (test_var == 9){					//1001
	  	  GPIOC->BSRR = (GPIO_PIN_0);
	  	  GPIOC->BRR = (GPIO_PIN_1);
	  	  GPIOC->BRR = (GPIO_PIN_2);
	  	  GPIOC->BSRR = (GPIO_PIN_3);
	    }
	    if (test_var == 10){					//1010
	    	  GPIOC->BRR = (GPIO_PIN_0);
	    	  GPIOC->BSRR = (GPIO_PIN_1);
	    	  GPIOC->BRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
	    if (test_var == 11){					//1011
	    	  GPIOC->BSRR = (GPIO_PIN_0);
	    	  GPIOC->BSRR = (GPIO_PIN_1);
	    	  GPIOC->BRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
	    if (test_var == 12){					//1100
	    	  GPIOC->BRR = (GPIO_PIN_0);
	    	  GPIOC->BRR = (GPIO_PIN_1);
	    	  GPIOC->BSRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
	    if (test_var == 13){					//1101
	    	  GPIOC->BSRR = (GPIO_PIN_0);
	    	  GPIOC->BRR = (GPIO_PIN_1);
	    	  GPIOC->BSRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
	    if (test_var == 14){					//1110
	    	  GPIOC->BRR = (GPIO_PIN_0);
	    	  GPIOC->BSRR = (GPIO_PIN_1);
	    	  GPIOC->BRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
	    if (test_var == 15){					//1111
	    	  GPIOC->BSRR = (GPIO_PIN_0);
	    	  GPIOC->BSRR = (GPIO_PIN_1);
	    	  GPIOC->BSRR = (GPIO_PIN_2);
	    	  GPIOC->BSRR = (GPIO_PIN_3);
	      }
  }

  GPIOC->BRR = (GPIO_PIN_0);
  GPIOC->BRR = (GPIO_PIN_1);              // turn off PC1
  GPIOC->BRR = (GPIO_PIN_2);
  GPIOC->BRR = (GPIO_PIN_3);

  return test_var;
}

void keypad_config(void)
{
	//COLUMN CONFIG
	RCC->AHB2ENR      |=  (RCC_AHB2ENR_GPIOAEN);
	COL_PORT -> MODER |= ((1 << GPIO_MODER_MODE0_Pos) | (1 << GPIO_MODER_MODE1_Pos) |
			          (1 << GPIO_MODER_MODE2_Pos) | (1 << GPIO_MODER_MODE3_Pos)); // configure output pins = 01
	COL_PORT->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
			  	  	  	GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3); // setup pull up/pull down resistors = 00
	COL_PORT->OSPEEDR &=  ~(GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED1|GPIO_OSPEEDR_OSPEED2|GPIO_OSPEEDR_OSPEED3);
	COL_PORT->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);  // set pushpull to 00
	COL_PORT->ODR     |= (GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD2| GPIO_ODR_OD3);

	// ROWS CONFIG
	RCC->AHB2ENR      |=  (RCC_AHB2ENR_GPIOBEN);
	ROW_PORT -> MODER &= ~((GPIO_MODER_MODE0) | (GPIO_MODER_MODE1) |
			               (GPIO_MODER_MODE2) | (GPIO_MODER_MODE3)); // configure input pins to 00
//	ROW_PORT -> MODER &= ~((GPIO_MODER_MODE0) | (GPIO_MODER_MODE1_Pos) |
//			               (GPIO_MODER_MODE2_Pos) | (GPIO_MODER_MODE3_Pos)); // configure input pins = 01
	ROW_PORT->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
			  	  	       GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3); // clears out the registers to 00
	ROW_PORT->PUPDR   |= (GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD1_1 |
	  	                  GPIO_PUPDR_PUPD2_1 | GPIO_PUPDR_PUPD3_1); // sets MSB to 1, we get 10 for pd
	ROW_PORT->IDR     |= (GPIO_IDR_ID0 | GPIO_IDR_ID1 | GPIO_IDR_ID2| GPIO_IDR_ID3);
}


uint8_t keypad_getkey()
{
	uint32_t rows = ROW_PORT -> IDR;
	uint16_t cols = 0x0001;
	uint8_t keynum;
	if ((rows & ROW_MASK) == 0)
	{
		return -1;
	}
	while(cols <= 4)
	{
		COL_PORT -> ODR &= ~(GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD2| GPIO_ODR_OD3);
		COL_PORT -> ODR |= cols; // setting colpin0 to 1// changes each time "toggling"
		if((rows & ROW_MASK)!= 0)
		{
			uint16_t currentrow = rows & ROW_MASK;
			if ((cols != 4) & (currentrow != 3))
			{
				keynum = (currentrow * 3) + cols;
				return keynum;
			}
			else if(cols == 4)
			{
				keynum = (cols * 3) + currentrow;
				return keynum;
			}
			else if (currentrow == 3)
			{
				if(cols == 1)
				{
					return 10;
				}
				if(cols == 2)
				{
					return 0;
				}
				if(cols == 3)
				{
					return 11;
				}
				if(cols == 4)
				{
					return 12;
				}
			}
		}
		cols ++;
	}
	return -1;

}
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  led_config();
  keypad_config();
  while (1)
  {
    uint8_t key = keypad_getkey();
    LedFunction(key);
  }
  /* USER CODE END 3 */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
