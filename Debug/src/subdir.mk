################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HttpClient.cpp \
../src/OAuthClient.cpp \
../src/WebCookie.cpp \
../src/WebView.cpp 

OBJS += \
./src/HttpClient.o \
./src/OAuthClient.o \
./src/WebCookie.o \
./src/WebView.o 

CPP_DEPS += \
./src/HttpClient.d \
./src/OAuthClient.d \
./src/WebCookie.d \
./src/WebView.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/indra/Documents/projects/development/github/Evimed-connect-cpp/src" -I/Users/indra/Documents/projects/development/Library/qt-everywhere-opensource-src-4.8.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


