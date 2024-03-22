#include "global_variables.h"

uint8_t buffer_state = FFT_BUFFER_CLEAR;
uint8_t display_state = DISPLAY_MANY;
uint32_t adc_buffer[4096] = {0};
float32_t fft_input_buffer[1024] = {0};
float32_t fft_output_buffer[1024] = {0};
//float32_t output_buffer2[1024] = {0};
uint16_t chosen_freqs[32] = {4,
		5,
		6,
		7,
		8,
		9,
		10,
		11,
		12,
		13,
		14,
		15,
		16,
		17,
		18,
		20,
		23,
		26,
		29,
		32,
		36,
		41,
		45,
		51,
		57,
		64,
		72,
		80,
		90,
		101,
		113,
		127


};
                    //     1  2  3  4  5  6  7  8  9  10 11  12  13  14  15  16  17  18  19  20  21  22  23  24  25   26   27   28   29   30   31   32
//uint16_t chosen_freqs[] = {290,315,344};
int random_value = 0;
//uint8_t uart_freq_buffer[0] = {0};
int freqs[512] = {0};
arm_rfft_fast_instance_f32 fft_handler;
uint16_t maxValue;
uint32_t maxIndex;
float32_t maxMagnitude = 32;
float32_t maxMagnitude1 = 22;
int displayBuffer[128];
uint8_t audio_bar_height[32]; // sizes for the individual bars
uint8_t audio_bar_peak[32]; // positions for the individual peaks (lines over the bars)
int xxx = 0;
float offset = 0.0f;
float value = 2.5;
float32_t Value2 = 0;
int bandValues [512] = {0};
int offset2 = 190;
uint8_t r = 3;
