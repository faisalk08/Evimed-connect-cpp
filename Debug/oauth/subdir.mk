################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../oauth/OAuthClient.cpp 

OBJS += \
./oauth/OAuthClient.o 

CPP_DEPS += \
./oauth/OAuthClient.d 


# Each subdirectory must supply rules for building sources it contributes
oauth/%.o: ../oauth/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../Evimed-connect-cpp/Evimed-connect-cpp/src -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/model" -I/Users/indra/Documents/projects/development/Library/qt-everywhere-opensource-src-4.8.4/include -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/header" -O0 -g3 -Wall -c -fmessage-length=0 -static -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


