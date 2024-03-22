################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/st7735/fonts.c \
../Core/Src/st7735/st7735.c 

OBJS += \
./Core/Src/st7735/fonts.o \
./Core/Src/st7735/st7735.o 

C_DEPS += \
./Core/Src/st7735/fonts.d \
./Core/Src/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/st7735/%.o Core/Src/st7735/%.su Core/Src/st7735/%.cyclo: ../Core/Src/st7735/%.c Core/Src/st7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-st7735

clean-Core-2f-Src-2f-st7735:
	-$(RM) ./Core/Src/st7735/fonts.cyclo ./Core/Src/st7735/fonts.d ./Core/Src/st7735/fonts.o ./Core/Src/st7735/fonts.su ./Core/Src/st7735/st7735.cyclo ./Core/Src/st7735/st7735.d ./Core/Src/st7735/st7735.o ./Core/Src/st7735/st7735.su

.PHONY: clean-Core-2f-Src-2f-st7735

