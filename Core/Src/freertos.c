/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
void initScreen();
void GenerateSineWave(void);
void GenerateSineWave2(void);
extern UART_HandleTypeDef huart2;
extern DAC_HandleTypeDef hdac;

#define pi 3.14155926
#define SAMPLES 10
#define res_8b 245
#define res_12b 4096

uint16_t *sine_wave_play;
uint16_t *sine_wave;
volatile uint32_t sampleIndex = 0;

/* USER CODE END Variables */
/* Definitions for TouchPin */
osThreadId_t TouchPinHandle;
const osThreadAttr_t TouchPin_attributes = {
  .name = "TouchPin",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for dac_play */
osThreadId_t dac_playHandle;
const osThreadAttr_t dac_play_attributes = {
  .name = "dac_play",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for dac_button */
osThreadId_t dac_buttonHandle;
const osThreadAttr_t dac_button_attributes = {
  .name = "dac_button",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for buttonSemaphore */
osSemaphoreId_t buttonSemaphoreHandle;
const osSemaphoreAttr_t buttonSemaphore_attributes = {
  .name = "buttonSemaphore"
};
/* Definitions for dac */
osSemaphoreId_t dacHandle;
const osSemaphoreAttr_t dac_attributes = {
  .name = "dac"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void DacPlayTask(void *argument);
void DacButtonPlay(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of buttonSemaphore */
  buttonSemaphoreHandle = osSemaphoreNew(1, 1, &buttonSemaphore_attributes);

  /* creation of dac */
  dacHandle = osSemaphoreNew(1, 1, &dac_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of TouchPin */
  TouchPinHandle = osThreadNew(StartDefaultTask, NULL, &TouchPin_attributes);

  /* creation of dac_play */
  dac_playHandle = osThreadNew(DacPlayTask, NULL, &dac_play_attributes);

  /* creation of dac_button */
  dac_buttonHandle = osThreadNew(DacButtonPlay, NULL, &dac_button_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the TouchPin thread.
 * @param  argument: Not used
 * @retval None
 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	osDelay(500);
	if (GPIO_Pin == TP_IRQ_Pin)
	{
		osSemaphoreRelease(buttonSemaphoreHandle);
		HAL_UART_Transmit(&huart2, (uint8_t *)"2\n\r", strlen("2\n\r"), 100);
	}

}

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

	initScreen();
	/* Infinite loop */
	for (;;)
	{
		osSemaphoreAcquire(buttonSemaphoreHandle, portMAX_DELAY);
		uint16_t x, y;

		if (XPT2046_TouchPressed())
		{

			if (XPT2046_TouchGetCoordinates(&x, &y))
			{
				char buffer[50];
				snprintf(buffer, sizeof(buffer), "X: %d, Y: %d\r\n", x, y);
				HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer),
								  1000);

				if (x > 170 && x < 220 && y > 60 && y < 100)
				{
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
					ST7789_DrawFilledCircle(180, 90, 20, YELLOW);
				}
				else if (x > 170 && x < 220 && y > 140 && y < 180)
				{
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
					ST7789_DrawFilledCircle(180, 160, 20, YELLOW);
				}

				else if (x > 170 && x < 220 && y > 210 && y < 270)
				{
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
					ST7789_DrawFilledCircle(180, 230, 20, YELLOW);
				}
				else
				{
				}
			}
		}
		else
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			ST7789_DrawFilledCircle(180, 230, 20, RED);
			ST7789_DrawFilledCircle(180, 160, 20, RED);
			ST7789_DrawFilledCircle(180, 90, 20, RED);
		}
		osDelay(100);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DacPlayTask */
/**
 * @brief Function implementing the dac_play thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_DacPlayTask */
void DacPlayTask(void *argument)
{
  /* USER CODE BEGIN DacPlayTask */
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	GenerateSineWave();
	for (;;)
	{

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, sine_wave_play[sampleIndex]);
		if (sampleIndex >= SAMPLES)
			sampleIndex = 0;

		sampleIndex++;
		osDelay(1);
	}
  /* USER CODE END DacPlayTask */
}

/* USER CODE BEGIN Header_DacButtonPlay */
/**
 * @brief Function implementing the dac_buttun thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_DacButtonPlay */
void DacButtonPlay(void *argument)
{
  /* USER CODE BEGIN DacButtonPlay */
	/* Infinite loop */
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	GenerateSineWave2();
	for (;;)
	{
		if (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) ==GPIO_PIN_RESET)
		{
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, sine_wave[sampleIndex]);
			if (sampleIndex >= SAMPLES)
				sampleIndex = 0;

			sampleIndex++;
			osDelay(1);
		}
	}
  /* USER CODE END DacButtonPlay */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void initScreen()
{
	ST7789_Fill_Color(WHITE);
	ST7789_WriteString(10, 10, "Embedded HCMUS", Font_16x26, GREEN, WHITE);

	ST7789_WriteString(40, 50, "BTN1", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(60, 90, 20, BLUE);

	ST7789_WriteString(160, 50, "LED1", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(180, 90, 20, RED);

	ST7789_WriteString(40, 120, "BTN2", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(60, 160, 20, BLUE);

	ST7789_WriteString(160, 120, "LED2", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(180, 160, 20, RED);

	ST7789_WriteString(20, 190, "BTN_DUAL", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(60, 230, 20, BLUE);

	ST7789_WriteString(140, 190, "DUAL_LED", Font_11x18, RED, WHITE);
	ST7789_DrawFilledCircle(180, 230, 20, RED);
	ST7789_WriteString(30, 270, "20200381-21200370", Font_11x18, BLUE, WHITE);
	ST7789_WriteString(30, 290, "  Trung -  Viet", Font_11x18, BLUE, WHITE);
}
void GenerateSineWave()
{
	for (int i = 0; i < SAMPLES; i++)
	{
		sine_wave_play[i] = ((sin(i * 2 * pi / SAMPLES) + 1) * res_12b / 2);
	}
}
void GenerateSineWave2()
{
	for (int i = 0; i < SAMPLES; i++)
	{
		sine_wave[i] = ((sin(i * 2 * pi / SAMPLES) + 1) * res_8b / 2);
	}
}

/* USER CODE END Application */

