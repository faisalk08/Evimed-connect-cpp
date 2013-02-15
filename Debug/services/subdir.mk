################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../services/ERecruitment.cpp \
../services/Patient.cpp 

OBJS += \
./services/ERecruitment.o \
./services/Patient.o 

CPP_DEPS += \
./services/ERecruitment.d \
./services/Patient.d 


# Each subdirectory must supply rules for building sources it contributes
services/%.o: ../services/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../Evimed-connect-cpp/Evimed-connect-cpp/src -I/Users/indra/Documents/projects/development/Library/qt-everywhere-opensource-src-4.8.4/include -I../Evimed-connect-cpp/header -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


