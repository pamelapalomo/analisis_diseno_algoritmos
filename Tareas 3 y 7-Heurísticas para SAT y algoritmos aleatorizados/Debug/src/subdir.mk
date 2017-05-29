################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Instance.cpp \
../src/SS_SAT.cpp \
../src/ScatterSearch.cpp \
../src/Solution.cpp 

OBJS += \
./src/Instance.o \
./src/SS_SAT.o \
./src/ScatterSearch.o \
./src/Solution.o 

CPP_DEPS += \
./src/Instance.d \
./src/SS_SAT.d \
./src/ScatterSearch.d \
./src/Solution.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


