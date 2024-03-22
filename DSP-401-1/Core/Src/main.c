/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global_variables.h"
#include "callbacks.h"
#include "FFT.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
//#include "ssd1306.h"
#include "u8g2/u8g2.h"
//#include "st7735.h"
#include "st7735/st7735.h"
#include "st7735/fonts.h"
#include "st7735/testimg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//OLED

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
const unsigned char upir_logo [] = {0xEA, 0x3A, 0xAA, 0x28, 0x6A, 0x1A, 0x26, 0x2A};

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
//extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

static u8g2_t u8g2;
//-----------инициализация вывода команды отладчика print----------------//
int _write(int file, uint8_t *ptr, int len)
{

	for (int DataIdx = 0; DataIdx < len; DataIdx++)
	{
		ITM_SendChar(*ptr++);
	}
	return len;
}
//-----------инициализация вывода команды отладчика print----------------//
void demoTFT(void)
{
 ST7735_SetRotation(r);

 ST7735_FillScreen(ST7735_BLACK);

 for(int x = 0; x < ST7735_GetWidth(); x++)
 {
   ST7735_DrawPixel(x, 0, ST7735_WHITE);
   ST7735_DrawPixel(x, ST7735_GetHeight() - 1, ST7735_WHITE);
 }

 for(int y = 0; y < ST7735_GetHeight(); y++)
 {
   ST7735_DrawPixel(0, y, ST7735_WHITE);
   ST7735_DrawPixel(ST7735_GetWidth() - 1, y, ST7735_WHITE);
 }

 ST7735_DrawLine(0, 0, ST7735_GetWidth(), ST7735_GetHeight(), ST7735_WHITE);
 ST7735_DrawLine(ST7735_GetWidth(), 0, 0, ST7735_GetHeight(), ST7735_WHITE);

 HAL_Delay(2000);

 ST7735_FillScreen(ST7735_BLACK);

 for (int i = 0; i < ST7735_GetHeight(); i += 4)
 {
  ST7735_DrawFastHLine(0, i, ST7735_GetWidth() - 1, ST7735_WHITE);
 }

 for (int i = 0; i < ST7735_GetWidth(); i += 4)
 {
  ST7735_DrawFastVLine(i, 0, ST7735_GetHeight() - 1, ST7735_WHITE);
 }

 HAL_Delay(2000);

 // Check fonts
 ST7735_FillScreen(ST7735_BLACK);
 ST7735_DrawString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
 ST7735_DrawString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
 ST7735_DrawString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
 HAL_Delay(2000);

 // Check colors
 ST7735_FillScreen(ST7735_BLACK);
 ST7735_DrawString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_BLUE);
 ST7735_DrawString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_RED);
 ST7735_DrawString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_GREEN);
 ST7735_DrawString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_CYAN);
 ST7735_DrawString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_MAGENTA);
 ST7735_DrawString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_YELLOW);
 ST7735_DrawString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
 HAL_Delay(500);

 ST7735_FillScreen(ST7735_WHITE);
 ST7735_DrawString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
 HAL_Delay(500);

 // Draw circles
 ST7735_FillScreen(ST7735_BLACK);
 for (int i = 0; i < ST7735_GetHeight() / 2; i += 2)
 {
  ST7735_DrawCircle(ST7735_GetWidth() / 2, ST7735_GetHeight() / 2, i, ST7735_YELLOW);
 }
 HAL_Delay(1000);

 ST7735_FillScreen(ST7735_BLACK);
 ST7735_FillTriangle(0, 0, ST7735_GetWidth() / 2, ST7735_GetHeight(), ST7735_GetWidth(), 0, ST7735_RED);
 HAL_Delay(1000);

 ST7735_FillScreen(ST7735_BLACK);
 ST7735_DrawImage(0, 0, 128, 128, (uint16_t*) test_img_128x128);
 HAL_Delay(3000);

 r++;
}
void main_loop()
{
	int fft_in_ptr = 0;
	if (buffer_state == FFT_BUFFER_HALF)
		  {
			  for (int i = 0;i < 1024; i++)
				  //fft_input_buffer[i] = (float)(int)adc_buffer[i];
			  {
				  fft_input_buffer[fft_in_ptr] = (float) ((int) (adc_buffer[i]<<16)|adc_buffer[i+1]);// | Побитовый инклюзивный оператор OR
				  //fft_input_buffer[fft_in_ptr] = (float)adc_buffer[i] / 4096.0*3.3;
				  //fft_input_buffer[fft_in_ptr] += (float) ((int) (adc_buffer[i+2]<<16)|adc_buffer[i+3]);
				  fft_in_ptr++;
			  }
			  FFT();
		  }

		  if (buffer_state == FFT_BUFFER_FULL)
		  {
			  for (int i = 1024;i < 2048; i++)
				  //fft_input_buffer[i] = (float)(int)adc_buffer[i];
			  {
				  fft_input_buffer[fft_in_ptr] = (float) ((int) (adc_buffer[i]<<16)|adc_buffer[i+1]);// | Побитовый инклюзивный оператор OR
				  //fft_input_buffer[fft_in_ptr] = (float)adc_buffer[i] / 4096.0*3.3;
				  //fft_input_buffer[fft_in_ptr] += (float) ((int) (adc_buffer[i+2]<<16)|adc_buffer[i+3]);
				  fft_in_ptr++;
				  xxx = i;
			   }
			  FFT();
		  }

		  if (buffer_state == FFT_DISPLAY)
		  {
			  //DisplayFFT();
			//  u8g2_ClearBuffer (&u8g2);
			//  u8g2_SetDrawColor(&u8g2,1);

			  switch(display_state)
			  	{
			  	case DISPLAY_MANY:
			  		//u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);
				  		//uint8_t r = 3;
				  		ST7735_SetRotation(r);
				  		ST7735_FillScreen(ST7735_BLACK);


	//			  		 ST7735_DrawString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
	//			  		 ST7735_DrawString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
	//			  		 ST7735_DrawString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
				  		 //HAL_Delay(2000);

				  		for (int i=0; i<32; i++) // loop for every fraquency (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz)
				  		{

				  			//random_value = freqs[chosen_freqs[i]]/maxMagnitude;//freqs[chosen_freqs[i]];//(rand()%53 + 0);//bandValues[i];//(rand()%53 + 0);; // calculate random value between 0-1024

				  			random_value = freqs [chosen_freqs[i]]-maxValue-maxMagnitude;//maxValue*2;//bandValues[i]/maxMagnitude;
				  			if (random_value > 40) random_value = 40;
				  			audio_bar_height[i] = audio_bar_height[i] + ((random_value - audio_bar_height[i]))/value; // update the bar with a new value (slowly)

				  			// calculate the peak position
				  			if (audio_bar_peak[i] < audio_bar_height[i]) // if the peak is below the current bar size
				  			{
				  				audio_bar_peak[i] = audio_bar_height[i]; // move peak to the new max. position (i.e. size of the bar)
				  			}
				  			else if (audio_bar_peak[i] > audio_bar_height[i])
				  			{ // if the bar is lower than the peak
				  				audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
				  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
				  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
				  			}


				  			ST7735_FillRectangle(1 + i*5, 40, 3, audio_bar_height[i], 0x3fe0);
				  			ST7735_FillRectangle(1 + i*5, 40-audio_bar_height[i], 3, audio_bar_height[i], 0xf7e0);
				  			ST7735_FillRectangle(1 + i*5, 40-audio_bar_peak[i], 3, 3, 0x04bf);//(rand()%65534 + 0)); // draw peak 64-audio_bar_peak[i]
				  			ST7735_FillRectangle(1 + i*5, 40+audio_bar_peak[i], 3, 3, 0xf816);//(rand()%65534 + 0)); // draw peak 64-audio_bar_peak[i]
	//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32, 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
	//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_height[i], 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
	//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]
	//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32+audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]

				  		}
				  		//r++;
			  		break;
			  	case DISPLAY_FEW:
			  		//u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);

			  						  		ST7735_SetRotation(r);
			  						  		ST7735_FillScreen(ST7735_BLACK);




			  						  		for (int i=0; i<32; i++) // loop for every fraquency (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz)
			  						  		{

			  						  			//random_value = freqs[chosen_freqs[i]]/maxMagnitude;//freqs[chosen_freqs[i]];//(rand()%53 + 0);//bandValues[i];//(rand()%53 + 0);; // calculate random value between 0-1024

			  						  			random_value = freqs [chosen_freqs[i]]-maxValue-maxMagnitude1;//maxValue*2;//bandValues[i]/maxMagnitude;
			  						  			if (random_value > 80) random_value = 80;
			  						  			audio_bar_height[i] = audio_bar_height[i] + ((random_value - audio_bar_height[i]))/value; // update the bar with a new value (slowly)

			  						  			// calculate the peak position
			  						  			if (audio_bar_peak[i] < audio_bar_height[i]) // if the peak is below the current bar size
			  						  			{
			  						  				audio_bar_peak[i] = audio_bar_height[i]; // move peak to the new max. position (i.e. size of the bar)
			  						  			}
			  						  			else if (audio_bar_peak[i] > audio_bar_height[i])
			  						  			{ // if the bar is lower than the peak
			  						  				audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  						  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  						  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  						  			}


			  						  			ST7735_FillRectangle(1 + i*5, 80-audio_bar_height[i], 3, audio_bar_height[i], 0xffe0);
			  						  			ST7735_FillRectangle(1 + i*5, 80-audio_bar_peak[i], 3, 3, ST7735_RED);

			  			//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32, 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
			  			//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_height[i], 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
			  			//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]
			  			//			  			u8g2_DrawBox(&u8g2,1 + i*4, 32+audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]

			  						  		}
//			  		u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);
//			  		for (int i=0; i<32; i++) // loop for every fraquency (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz)
//			  		{
//
//			  			//random_value = freqs[chosen_freqs[i]]/maxMagnitude;//freqs[chosen_freqs[i]];//(rand()%53 + 0);//bandValues[i];//(rand()%53 + 0);; // calculate random value between 0-1024
//
//			  			random_value = freqs [chosen_freqs[i]]-maxValue-maxMagnitude;//maxValue*2;//bandValues[i]/maxMagnitude;
//			  			if (random_value > 64) random_value = 64;
//			  			audio_bar_height[i] = audio_bar_height[i] + ((random_value - audio_bar_height[i]))/value; // update the bar with a new value (slowly)
//
//			  			// calculate the peak position
//			  			if (audio_bar_peak[i] < audio_bar_height[i]) // if the peak is below the current bar size
//			  			{
//			  				audio_bar_peak[i] = audio_bar_height[i]; // move peak to the new max. position (i.e. size of the bar)
//			  			}
//			  			else if (audio_bar_peak[i] > audio_bar_height[i])
//			  			{ // if the bar is lower than the peak
//			  				audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
//			  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
//			  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
//			  			}
//
//			  			u8g2_DrawBox(&u8g2,1 + i*4, 64-audio_bar_height[i], 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
//			  			u8g2_DrawBox(&u8g2,1 + i*4, 64-audio_bar_peak[i], 1, 1); // draw bar 64-audio_bar_height[i]
//			  			//u8g2_DrawBox(&u8g2,1 + i*4, 64-audio_bar_peak[i], 1, 1); // draw peak 64-audio_bar_peak[i]
//			  			//u8g2_DrawBox(&u8g2,1 + i*4, 64-audio_bar_peak[i], 1, 1); // draw peak 64-audio_bar_peak[i]
//			  		}


			  		break;
			  	case DISPLAY_COW:
			  		u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);
			  					  		for (int i=0; i<32; i++) // loop for every fraquency (63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz)
			  					  		{

			  					  			//random_value = freqs[chosen_freqs[i]]/maxMagnitude;//freqs[chosen_freqs[i]];//(rand()%53 + 0);//bandValues[i];//(rand()%53 + 0);; // calculate random value between 0-1024

			  					  			random_value = freqs [chosen_freqs[i]]-maxValue-maxMagnitude;//maxValue*2;//bandValues[i]/maxMagnitude;
			  					  			if (random_value > 32) random_value = 32;
			  					  			audio_bar_height[i] = audio_bar_height[i] + ((random_value - audio_bar_height[i]))/value; // update the bar with a new value (slowly)

			  					  			// calculate the peak position
			  					  			if (audio_bar_peak[i] < audio_bar_height[i]) // if the peak is below the current bar size
			  					  			{
			  					  				audio_bar_peak[i] = audio_bar_height[i]; // move peak to the new max. position (i.e. size of the bar)
			  					  			}
			  					  			else if (audio_bar_peak[i] > audio_bar_height[i])
			  					  			{ // if the bar is lower than the peak
			  					  				audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  					  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  					  				//audio_bar_peak[i]--; // slowly move the peak down, one pixel every frame
			  					  			}

			  					  			u8g2_DrawBox(&u8g2,1 + i*4, 32, 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
			  					  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_height[i], 1, audio_bar_height[i]); // draw bar 64-audio_bar_height[i]
			  					  			u8g2_DrawBox(&u8g2,1 + i*4, 32-audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]
			  					  			u8g2_DrawBox(&u8g2,1 + i*4, 32+audio_bar_peak[i], 1, 2); // draw peak 64-audio_bar_peak[i]
			  					  		}
			  					  		//u8g2_SendBuffer(&u8g2);

			  					  		//xxx = 23;
			  		break;
			  	default:
			  		break;
			  	}
			 // u8g2_SendBuffer(&u8g2);
			  	buffer_state = FFT_BUFFER_CLEAR;
			  }



//			  					  	  			  		      u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);
//			  					  	  			  			  u8g2_DrawStr(&u8g2,  2, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 7, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 12, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 17, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 22, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 27, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 32, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 37, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 42, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 47, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 52, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 57, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 62, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 67, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 72, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 77, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 82, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 87, 64, ".");
//			  					  	  			  			  u8g2_DrawStr(&u8g2, 92, 64, ".");
//			  					  	  			  		      u8g2_DrawStr(&u8g2, 97, 64, ".");
//			  					  	  			  		      u8g2_DrawStr(&u8g2, 102, 64, ".");
//			  					  	  			  		      u8g2_DrawStr(&u8g2, 107, 64, ".");
//			  					  	  			  		      u8g2_DrawStr(&u8g2, 112, 64, ".");
//			  					  	  			  		      u8g2_DrawStr(&u8g2, 117, 64, ".");
			  					  	  		//	  			u8g2_DrawXBMP(&u8g2,0, 0, 16, 4, upir_logo);  // draw upir logo
			  					  	  			  			//u8g2_SendBuffer (& u8g2);



			  					  	  			  	//	u8g2_SendBuffer(&u8g2);
			  					  	  		//	  buffer_state = FFT_BUFFER_CLEAR;
		 // }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C3_Init();
  MX_I2S2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  //ssd1306_Init();

  ST7735_Init();
  HAL_Delay(500);
    ST7735_Backlight_On();

    //ssd1306_Fill(1);
    //ssd1306_UpdateScreen();
  //HAL_ADC_Start_DMA(&hadc1, adc_buffer, 4096);

    HAL_I2S_Receive_DMA(&hi2s2, (uint32_t *)adc_buffer, 2048);

    arm_rfft_fast_init_f32(&fft_handler, 1024);
    //arm_rfft_init_q31(&fft_handler, 2048, 0,0);

    // для корректной работы этой функции нужно добавить файл gettimeofday.c в проект
            srand(time(NULL)); // правильно работает функция rand()
           /*gettimeofday.c - содержимое файла ниже
            #include <sys/time.h>

          int _gettimeofday( struct timeval *tv, void *tzvp )
          {
              // you can add code here there many example in google search.
              return 0;  // return non-zero for error
          } // end _gettimeofday()*/
          // для корректной работы этой функции нужно добавить файл gettimeofday.c в проект
            //---------------какой дисплей используется ?----------//
                //u8g2_Setup_ssd1306_i2c_128x32_univision_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);// инициализация дисплей маленький
                //u8g2_Setup_max7219_8x8_1(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);// инициализация дисплей max7219
//                u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);// инициализация дисплей большой
//                 //---------------какой дисплей используется ?----------//
//                 /* I2C Interface */
//                                            /* Initialize Display */
//
//
//                   	    	u8g2_InitDisplay(&u8g2);
//                   	    	u8g2_SetPowerSave(&u8g2, 0);
//                   	    	u8g2_SetDrawColor(&u8g2,1);
//                   	    	u8g2_SetFont(&u8g2, u8g2_font_nerhoe_tr);
//                   	    	u8g2_DrawStr(&u8g2, 7, 64, "PRIVET");
//                   	    	u8g2_SendBuffer(&u8g2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  main_loop();
	  //demoTFT();

  }
  /* USER CODE END 3 */
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
