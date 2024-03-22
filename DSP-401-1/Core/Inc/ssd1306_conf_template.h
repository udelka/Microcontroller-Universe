/**
 * Private configuration file for the SSD1306 library.
 * This example is configured for STM32F0, I2C and including all fonts.
 */

#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

// Choose a microcontroller family

#define STM32F4


// Choose a bus
#define SSD1306_USE_I2C


// I2C Configuration
#define SSD1306_I2C_PORT        hi2c3
#define SSD1306_I2C_ADDR        (0x3C << 1)


// Mirror the screen if needed
 #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ

// Set inverse color if needed
// # define SSD1306_INVERSE_COLOR



// The width of the screen can be set using this
// define. The default value is 128.
#define SSD1306_WIDTH           128

// If your screen horizontal axis does not start
// in column 0 you can use this define to
// adjust the horizontal offset
#define SSD1306_X_OFFSET 		2

// The height can be changed as well if necessary.
// It can be 32, 64 or 128. The default value is 64.
#define SSD1306_HEIGHT          64

#endif /* __SSD1306_CONF_H__ */
