#ifndef INC_GLOBAL_VARIABLES_H_
#define INC_GLOBAL_VARIABLES_H_

#define ARM_MATH_CM4
#define __FPU_PRESENT             1U

// Includes
#include "arm_math.h"
#include <stdint.h>

// FFT States
enum buffer_states{FFT_BUFFER_CLEAR, FFT_BUFFER_HALF, FFT_BUFFER_FULL, FFT_DISPLAY};
extern uint8_t buffer_state;

// Display States
enum display_states{DISPLAY_MANY, DISPLAY_FEW, DISPLAY_COW};
extern uint8_t display_state;

// Declare Arrays
extern uint32_t adc_buffer[4096];
extern float32_t fft_input_buffer[1024];
extern float32_t fft_output_buffer[1024];
//extern float32_t output_buffer2[1024];
extern uint16_t chosen_freqs[32];
//extern uint8_t uart_freq_buffer[0];
extern int freqs[512];
extern uint16_t maxValue;
extern uint32_t maxIndex;
extern uint8_t audio_bar_height[32]; // sizes for the individual bars
extern uint8_t audio_bar_peak[32]; // positions for the individual peaks (lines over the bars)

extern float value;
extern float32_t Value2;
extern int bandValues [512];
extern int offset2;

extern uint8_t r;

extern int random_value;
extern int xxx;
extern float offset;
extern float32_t maxMagnitude;
extern float32_t maxMagnitude1;
extern int displayBuffer[128];
// FFT_handler
extern arm_rfft_fast_instance_f32 fft_handler;
//extern arm_rfft_instance_q31 fft_handler;
#endif /* INC_GLOBAL_VARIABLES_H_ */
