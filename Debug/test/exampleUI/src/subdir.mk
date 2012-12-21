################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/exampleUI/src/OauthClientUI.cpp \
../test/exampleUI/src/exampleUI.cpp 

OBJS += \
./test/exampleUI/src/OauthClientUI.o \
./test/exampleUI/src/exampleUI.o 

CPP_DEPS += \
./test/exampleUI/src/OauthClientUI.d \
./test/exampleUI/src/exampleUI.d 


# Each subdirectory must supply rules for building sources it contributes
test/exampleUI/src/%.o: ../test/exampleUI/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


