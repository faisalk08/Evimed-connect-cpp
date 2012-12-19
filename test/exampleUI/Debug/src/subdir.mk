################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OauthClientUI.cpp \
../src/exampleUI.cpp 

OBJS += \
./src/OauthClientUI.o \
./src/exampleUI.o 

CPP_DEPS += \
./src/OauthClientUI.d \
./src/exampleUI.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/indra/Documents/projects/development/Library/qt-everywhere-opensource-src-4.8.4/include -I"/Users/indra/Documents/workspace_indigo/c++_project/evimedwrappercpp/src" -I"/Users/indra/Documents/workspace_indigo/c++_project/exampleUI/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


