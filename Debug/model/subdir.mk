################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../model/EvimedConfig.cpp \
../model/EvimedModel.cpp \
../model/EvimedSearchModel.cpp \
../model/EvimedService.cpp \
../model/Patient.cpp \
../model/PatientService.cpp 

OBJS += \
./model/EvimedConfig.o \
./model/EvimedModel.o \
./model/EvimedSearchModel.o \
./model/EvimedService.o \
./model/Patient.o \
./model/PatientService.o 

CPP_DEPS += \
./model/EvimedConfig.d \
./model/EvimedModel.d \
./model/EvimedSearchModel.d \
./model/EvimedService.d \
./model/Patient.d \
./model/PatientService.d 


# Each subdirectory must supply rules for building sources it contributes
model/%.o: ../model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../Evimed-connect-cpp/Evimed-connect-cpp/src -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/model" -I/Users/indra/Documents/projects/development/Library/qt-everywhere-opensource-src-4.8.4/include -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/header" -O0 -g3 -Wall -c -fmessage-length=0 -static -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


