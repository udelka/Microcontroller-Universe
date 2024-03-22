#include "callbacks.h"
#include "global_variables.h"

#define USER_Btn_Pin GPIO_PIN_0
#define USER_Btn_GPIO_Port GPIOA

//void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (buffer_state != FFT_DISPLAY)
		buffer_state = FFT_BUFFER_HALF;
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (buffer_state != FFT_DISPLAY)
		buffer_state = FFT_BUFFER_FULL;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == USER_Btn_Pin)
	{
		if(display_state++ >= 3) display_state = DISPLAY_MANY;

	}
}

