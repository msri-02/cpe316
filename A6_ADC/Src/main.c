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
#include "adc.h"
#include "uart.h"
#define NUMSAMPLES 20
#define MAX_IDX 8
#define NOT_WHOLE 6

void SystemClock_Config(void);

uint32_t getmin(uint16_t array[])
{
	uint32_t min = array[0];
	for(int i = 0; i < NUMSAMPLES; i++)
	{
		if(array[i] < min)
		{
			min = array[i];
		}
	}
	return min;
}

uint32_t getmax(uint16_t array[])
{
	uint32_t max = 0;
	for(int i = 0; i < NUMSAMPLES; i++)
	{
		if(array[i] > max)
		{
			max = array[i];
		}
	}
	return max;
}

uint32_t getavg(uint16_t array[])
{
	uint32_t avg = 0;
	for(int i = 0; i < NUMSAMPLES; i++)
	{
		avg += array[i];
	}
	avg = avg / NUMSAMPLES;
	return avg;

}

uint32_t calibrate(uint32_t dig_volt)
{
	uint32_t calib_voltage = (800 * dig_volt) + 3350; // old was 13350
	return calib_voltage;
}

void print_voltage(uint32_t voltage)
{
	char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char string[MAX_IDX];
	string[MAX_IDX - 1] = '\0'; // setting to null
	int idx = MAX_IDX - 1;
	int size = 0 ;
	while(voltage)
	{
		char toprint = nums[voltage % 10];
		string[idx] = toprint;
		idx -= 1;
		voltage /= 10;
		size += 1;
	}
	if(size == NOT_WHOLE) // for printing numbers like 0.5
	{
		UART_print_char(nums[0]);
		UART_print_char('.');
		UART_print_char(string[MAX_IDX - size]);
		UART_print_char(string[MAX_IDX - size + 1]);
		UART_print_char(string[MAX_IDX - size + 2]);
	}
	else
	{
		UART_print_char(string[MAX_IDX - size]);
		UART_print_char('.');
		UART_print_char(string[MAX_IDX - size + 1]);
		UART_print_char(string[MAX_IDX - size + 2]);
	}

}

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  UART_init();
  ADC_init();
  uint16_t samples[NUMSAMPLES]; // saving an array for 20 samples
  int idx = 0;
  while (1)
  {
	  if(adc_flag == 1) // checking if the flag is set
	  {
		  // save the converted value into an array
		  samples[idx] = digi_conv;
		  idx += 1;
		  adc_flag = 0;                 // reset the flag
		  ADC1 -> CR |= ADC_CR_ADSTART; // start another conversion
	  }

	  if(idx == (NUMSAMPLES)) // collected all of the samples
	  {
		  uint32_t avg = calibrate(getavg(samples));
		  uint32_t min = calibrate(getmin(samples));
		  uint32_t max = calibrate(getmax(samples));
		  UART_print("min");
		  print_voltage(min);
		  UART_print("max");
		  print_voltage(max);
		  UART_print("avg");
		  print_voltage(avg);
		  USART_ESC_Code("[1B");
		  idx = 0;
	  }

  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
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
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
