################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/XPT2046-HAL-SPI-master/XPT2046_touch.c 

OBJS += \
./Core/XPT2046-HAL-SPI-master/XPT2046_touch.o 

C_DEPS += \
./Core/XPT2046-HAL-SPI-master/XPT2046_touch.d 


# Each subdirectory must supply rules for building sources it contributes
Core/XPT2046-HAL-SPI-master/%.o Core/XPT2046-HAL-SPI-master/%.su Core/XPT2046-HAL-SPI-master/%.cyclo: ../Core/XPT2046-HAL-SPI-master/%.c Core/XPT2046-HAL-SPI-master/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/final_year/embedded/TH/ES/Core/ST7789" -I"D:/final_year/embedded/TH/ES/Core/XPT2046-HAL-SPI-master" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-XPT2046-2d-HAL-2d-SPI-2d-master

clean-Core-2f-XPT2046-2d-HAL-2d-SPI-2d-master:
	-$(RM) ./Core/XPT2046-HAL-SPI-master/XPT2046_touch.cyclo ./Core/XPT2046-HAL-SPI-master/XPT2046_touch.d ./Core/XPT2046-HAL-SPI-master/XPT2046_touch.o ./Core/XPT2046-HAL-SPI-master/XPT2046_touch.su

.PHONY: clean-Core-2f-XPT2046-2d-HAL-2d-SPI-2d-master

