################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Help.cpp \
../TuringBand.cpp \
../TuringMachine.cpp \
../TuringState.cpp \
../TuringStateIterator.cpp \
../TuringTuple.cpp \
../TuringTypes.cpp \
../main.cpp 

OBJS += \
./Help.o \
./TuringBand.o \
./TuringMachine.o \
./TuringState.o \
./TuringStateIterator.o \
./TuringTuple.o \
./TuringTypes.o \
./main.o 

CPP_DEPS += \
./Help.d \
./TuringBand.d \
./TuringMachine.d \
./TuringState.d \
./TuringStateIterator.d \
./TuringTuple.d \
./TuringTypes.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


