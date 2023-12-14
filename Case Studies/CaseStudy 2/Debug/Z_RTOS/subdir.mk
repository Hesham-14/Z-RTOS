################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Z_RTOS/CortexMX_OS_porting.c \
../Z_RTOS/Scheduler.c \
../Z_RTOS/Z_RTOS_FIFO.c 

OBJS += \
./Z_RTOS/CortexMX_OS_porting.o \
./Z_RTOS/Scheduler.o \
./Z_RTOS/Z_RTOS_FIFO.o 

C_DEPS += \
./Z_RTOS/CortexMX_OS_porting.d \
./Z_RTOS/Scheduler.d \
./Z_RTOS/Z_RTOS_FIFO.d 


# Each subdirectory must supply rules for building sources it contributes
Z_RTOS/CortexMX_OS_porting.o: ../Z_RTOS/CortexMX_OS_porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL/includes" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_V5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Z_RTOS/CortexMX_OS_porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Z_RTOS/Scheduler.o: ../Z_RTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL/includes" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_V5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Z_RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Z_RTOS/Z_RTOS_FIFO.o: ../Z_RTOS/Z_RTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Z_RTOS" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL/includes" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers/inc" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/CMSIS_V5" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/HAL" -I"C:/Users/hesham mohamed/STM32CubeIDE/workspace_2_1.4.0/U15_Z-RTOS_Session_3/Stm32_F103C6_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Z_RTOS/Z_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

