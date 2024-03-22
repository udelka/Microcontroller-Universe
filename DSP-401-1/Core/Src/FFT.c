#include "FFT.h"
#include "global_variables.h"
#include "arm_math.h"
//#include "ssd1306.h"
#include "u8g2/u8g2.h"
static u8g2_t u8g2;



// Returns absolute value of complex number
float abs_complex(float real, float imag)
{
	return sqrtf(real * real + imag * imag);
}

// Displays FFT result on a screen
void DisplayFFT()
{

	switch(display_state)
	{
	case DISPLAY_MANY:



		break;
	case DISPLAY_FEW:


		break;
	case DISPLAY_COW:
		break;
	default:
		break;
	}

	buffer_state = FFT_BUFFER_CLEAR;
}

// Calculates FFT
void FFT()
{
	//arm_scale_f32(fft_input_buffer, 1.0f/1024, fft_input_buffer, 1024);
	arm_mean_f32(fft_input_buffer, 1024, &offset);
		//arm_cmplx_mag_f32(fft_output_buffer, output_buffer2, 1024);
		for (int i=0; i<1024; i++)
			{
			fft_input_buffer[i] -= offset;
			}
	arm_rfft_fast_f32(&fft_handler, fft_input_buffer, fft_output_buffer, 0);

	//(output_buffer2, 1.0f/1024, output_buffer2, 1024);
	//arm_rfft_q15(&fft_handler, fft_input_buffer, fft_output_buffer);
	//arm_cmplx_mag_f32(fft_output_buffer, output_buffer2, 1024);
	//arm_cmplx_mag_q15(fft_output_buffer, (q15_t*) fft_input_buffer, 1024);	//вычисление амплитуд гармоник
	int freqs_ptr = 0;

	for (int i=1; i<1024; i=i+2)
	{

		freqs[freqs_ptr] = (int)(20*log10f(abs_complex(fft_output_buffer[i], fft_output_buffer[i+1]))) - offset2;
		//freqs[freqs_ptr] = (int)(20*log10f(fft_output_buffer[i]));

		if (freqs[freqs_ptr] < 0)
			freqs[freqs_ptr] = 0;

     	++freqs_ptr;
		//freqs[0] = 0;
	}
	arm_max_f32(freqs, 512, &maxValue, &maxIndex);
//
//		// Normalize spectrum
		for (int i = 0; i < 512; i++)
		{
			freqs[i] = freqs[i] * 128 / maxValue;
			//freqs[0] = 0;
//		      if (i<=3 )           bandValues[0]  = (int)freqs[i];
//		      if (i>3   && i<=4  ) bandValues[1]  = (int)freqs[i];
//		      if (i>4   && i<=5  ) bandValues[2]  = (int)freqs[i];
//		      if (i>5   && i<=6  ) bandValues[3]  = (int)freqs[i];
//		      if (i>6   && i<=7  ) bandValues[4]  = (int)freqs[i];
//		      if (i>7   && i<=8  ) bandValues[5]  = (int)freqs[i];
//		      if (i>8   && i<=9  ) bandValues[6]  = (int)freqs[i];
//		      if (i>9   && i<=10  ) bandValues[7]  = (int)freqs[i];
//		      if (i>10   && i<=12  ) bandValues[8]  = (int)freqs[i];
//		      if (i>12   && i<=14  ) bandValues[9]  = (int)freqs[i];
//		      if (i>14   && i<=16  ) bandValues[10]  = (int)freqs[i];
//		      if (i>16   && i<=19  ) bandValues[11]  = (int)freqs[i];
//		      if (i>19   && i<=23  ) bandValues[12]  = (int)freqs[i];
//		      if (i>23   && i<=26  ) bandValues[13]  = (int)freqs[i];
//		      if (i>26   && i<=31  ) bandValues[14]  = (int)freqs[i];
//		      if (i>31   && i<=36  ) bandValues[15]  = (int)freqs[i];
//		      if (i>36   && i<=42  ) bandValues[16]  = (int)freqs[i];
//		      if (i>42   && i<=49  ) bandValues[17]  = (int)freqs[i];
//		      if (i>49   && i<=58  ) bandValues[18]  = (int)freqs[i];
//		      if (i>58   && i<=67  ) bandValues[19]  = (int)freqs[i];
//		      if (i>67   && i<=79  ) bandValues[20]  = (int)freqs[i];
//		      if (i>79   && i<=92  ) bandValues[21]  = (int)freqs[i];
//		      if (i>92   && i<108  ) bandValues[22]  = (int)freqs[i];
//		      if (i>=108             ) bandValues[23]  = (int)freqs[i];



		}
	// Scale magnitude values to fit display height

//				for (int i = 0; i < 256; i++)
//						    {
//						        if (freqs[i] > maxMagnitude)
//						        {
//						            maxMagnitude = freqs[i];
//						        }
//						    }
//
//				for (int i = 0; i < 128; i++) {
//						            int index = i*2;
//						            int magnitude = freqs[index];
//						            displayBuffer[i] = (magnitude / maxMagnitude) * 128;
//						        }

//	for (int i = 0; i < 256; i++)
//		{
//		freqs[i] = ( (freqs[i]) / (maxValue) ) * (62 - 0) + 0;
//			  //new_value = ( (old_value - old_min) / (old_max - old_min) ) * (new_max - new_min) + new_min
//
//		}


//xxx = 0;
	buffer_state = FFT_DISPLAY;
}
