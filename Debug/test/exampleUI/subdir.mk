################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../test/exampleUI/OauthClientUI.o \
../test/exampleUI/exampleUI.o \
../test/exampleUI/moc_OauthClientUI.o 

CPP_SRCS += \
../test/exampleUI/moc_OauthClientUI.cpp 

OBJS += \
./test/exampleUI/moc_OauthClientUI.o 

CPP_DEPS += \
./test/exampleUI/moc_OauthClientUI.d 


# Each subdirectory must supply rules for building sources it contributes
test/exampleUI/%.o: ../test/exampleUI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


