/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "arm_math.h"
#include "st7735.h"

#define FFT_SIZE 512

extern float32_t fft_input[];
extern float32_t fft_output[];
extern float32_t window[];
extern volatile uint8_t data_ready_flag;
extern arm_rfft_fast_instance_f32 fft_handler;

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

/* USER CODE END Variables */
/* Definitions for Display_Task */
osThreadId_t Display_TaskHandle;
const osThreadAttr_t Display_Task_attributes = {
  .name = "Display_Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Audio_Task */
osThreadId_t Audio_TaskHandle;
const osThreadAttr_t Audio_Task_attributes = {
  .name = "Audio_Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for FFT_Task */
osThreadId_t FFT_TaskHandle;
const osThreadAttr_t FFT_Task_attributes = {
  .name = "FFT_Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for FFTQueue */
osMessageQueueId_t FFTQueueHandle;
const osMessageQueueAttr_t FFTQueue_attributes = {
  .name = "FFTQueue"
};
/* Definitions for DataReadySem */
osSemaphoreId_t DataReadySemHandle;
const osSemaphoreAttr_t DataReadySem_attributes = {
  .name = "DataReadySem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDisplay_Task(void *argument);
void StartAudio_Task(void *argument);
void StartFFT_Task(void *argument);

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
  /* creation of DataReadySem */
  DataReadySemHandle = osSemaphoreNew(1, 1, &DataReadySem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of FFTQueue */
  FFTQueueHandle = osMessageQueueNew (4, 256, &FFTQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Display_Task */
  Display_TaskHandle = osThreadNew(StartDisplay_Task, NULL, &Display_Task_attributes);

  /* creation of Audio_Task */
  Audio_TaskHandle = osThreadNew(StartAudio_Task, NULL, &Audio_Task_attributes);

  /* creation of FFT_Task */
  FFT_TaskHandle = osThreadNew(StartFFT_Task, NULL, &FFT_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDisplay_Task */
/**
  * @brief  Function implementing the Display_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDisplay_Task */
void StartDisplay_Task(void *argument)
{
  /* USER CODE BEGIN StartDisplay_Task */
//	ST7735_Init();
//		ST7735_FillScreen(ST7735_BLACK);


	  /* Infinite loop */
	  for(;;)
	  {
//		  // Тест 1: Текст с разными поворотами
//		  ST7735_FillScreen(ST7735_BLACK);
//		      ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_BLUE);
//		      ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_RED);
//		      ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_GREEN);
//		      ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_CYAN);
//		      ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_MAGENTA);
//		      ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_YELLOW);
//		      ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
//		      osDelay(1000); // 200 мс
//
//		      ST7735_FillScreen(ST7735_WHITE);
//		      ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
		      osDelay(1); // 200 мс

  }
  /* USER CODE END StartDisplay_Task */
}

/* USER CODE BEGIN Header_StartAudio_Task */
/**
* @brief Function implementing the Audio_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAudio_Task */
void StartAudio_Task(void *argument)
{
  /* USER CODE BEGIN StartAudio_Task */

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartAudio_Task */
}

/* USER CODE BEGIN Header_StartFFT_Task */
/**
* @brief Function implementing the FFT_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFFT_Task */
void StartFFT_Task(void *argument)
{
  /* USER CODE BEGIN StartFFT_Task */
	  // Внутренние переменные задачи
	static int prev_heights[160] = {0};


	  float32_t mean;
	  float32_t raw_mag;
	  float32_t mag_db;
	  int col_height;
	  uint16_t color;
	  // Очистка экрана перед стартом
	  ST7735_Init();
	  ST7735_FillScreen(ST7735_BLACK);
  /* Infinite loop */
  for(;;)
  {
	  if(data_ready_flag)
	      {
	        data_ready_flag = 0;

	        // 1. Убираем постоянку (DC Offset)
	        arm_mean_f32(fft_input, FFT_SIZE, &mean);
	        arm_offset_f32(fft_input, -mean, fft_input, FFT_SIZE);

	        // 2. Окно Хэмминга (улучшает четкость)
	        arm_mult_f32(fft_input, window, fft_input, FFT_SIZE);

	        // 3. FFT
	        arm_rfft_fast_f32(&fft_handler, fft_input, fft_output, 0);
	        arm_cmplx_mag_f32(fft_output, fft_output, FFT_SIZE/2);

	        // 4. Отрисовка 160 столбиков
	        for (int i = 0; i < 160; i++)
	        {
	          // Берем амплитуду (пропускаем шум в самом начале спектра)
	        raw_mag = fft_output[i + 2];

	          // Логарифм (дБ).
	          // Если числа маленькие (как 14), mag_db будет около 20-40.
	          // Если числа большие (как 50000), mag_db будет около 90-100.
	         mag_db = 20.0f * log10f(raw_mag + 1.0f);

	          // --- НАСТРОЙКА ПОД ТВОЙ СКРИНШОТ ---
	          // Попробуем вычесть 45.0f.
	          // Если всё еще "красная стена" — УВЕЛИЧИВАЙ до 55.0, 60.0.
	          // Если экран станет черным — УМЕНЬШАЙ до 35.0, 30.0.
	          int col_height = (int)((mag_db - 45.0f) * 2.2f);

	         if (col_height < 0) col_height = 0;
	         if (col_height > 80) col_height = 80;


	          // Плавное падение (Гравитация)
	          if (col_height < prev_heights[i]) {
	              col_height = prev_heights[i] - 2;
	          }
	          prev_heights[i] = col_height;

	          // Цвет (Градиент)
	          if (col_height > 60) color = ST7735_RED;
	          else if (col_height > 30) color = ST7735_YELLOW;
	          else color = ST7735_GREEN;

	          // Рисуем
	          if (80 - col_height > 0) {
	              ST7735_FillRectangle(i, 0, 1, 80 - col_height, ST7735_BLACK);
	          }
	          if (col_height > 0) {
	              ST7735_FillRectangle(i, 80 - col_height, 1, col_height, color);
	          }
	        }
	      }
	      osDelay(1);
  }
  /* USER CODE END StartFFT_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

