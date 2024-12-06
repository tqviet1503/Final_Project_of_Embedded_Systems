################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ST7789/fonts.c \
../Core/ST7789/st7789.c 

OBJS += \
./Core/ST7789/fonts.o \
./Core/ST7789/st7789.o 

C_DEPS += \
./Core/ST7789/fonts.d \
./Core/ST7789/st7789.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ST7789/%.o Core/ST7789/%.su Core/ST7789/%.cyclo: ../Core/ST7789/%.c Core/ST7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/final_year/embedded/TH/ES/Core/ST7789" -I"D:/final_year/embedded/TH/ES/Core/XPT2046-HAL-SPI-master" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ST7789

clean-Core-2f-ST7789:
	-$(RM) ./Core/ST7789/fonts.cyclo ./Core/ST7789/fonts.d ./Core/ST7789/fonts.o ./Core/ST7789/fonts.su ./Core/ST7789/st7789.cyclo ./Core/ST7789/st7789.d ./Core/ST7789/st7789.o ./Core/ST7789/st7789.su

.PHONY: clean-Core-2f-ST7789

