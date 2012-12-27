################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ExampleConsole.cpp 

OBJS += \
./src/ExampleConsole.o 

CPP_DEPS += \
./src/ExampleConsole.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


