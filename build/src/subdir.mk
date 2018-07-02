################################################################################
# Automatically-generated file. Do not edit!
################################################################################
-include ../config.mk

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Automaton.cpp \
../src/CreateFlats.cpp \
../src/FileConverter.cpp \
../src/FileUtils.cpp \
../src/GrmOverApprox.cpp \
../src/GrmUnderApprox.cpp \
../src/Regex.cpp \
../src/RegexPattern.cpp \
../src/RegexState.cpp \
../src/StringReduce.cpp \
../src/StringTheory.cpp \
../src/TokenParser.cpp \
../src/UnderApprox.cpp \
../src/Utils.cpp \
../src/Z3Utils.cpp \
../src/main.cpp 

OBJS += \
./src/Automaton.o \
./src/CreateFlats.o \
./src/FileConverter.o \
./src/FileUtils.o \
./src/GrmOverApprox.o \
./src/GrmUnderApprox.o \
./src/Regex.o \
./src/RegexPattern.o \
./src/RegexState.o \
./src/StringReduce.o \
./src/StringTheory.o \
./src/TokenParser.o \
./src/UnderApprox.o \
./src/Utils.o \
./src/Z3Utils.o \
./src/main.o 

CPP_DEPS += \
./src/Automaton.d \
./src/CreateFlats.d \
./src/FileConverter.d \
./src/FileUtils.d \
./src/GrmOverApprox.d \
./src/GrmUnderApprox.d \
./src/Regex.d \
./src/RegexPattern.d \
./src/RegexState.d \
./src/StringReduce.d \
./src/StringTheory.d \
./src/TokenParser.d \
./src/UnderApprox.d \
./src/Utils.d \
./src/Z3Utils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -I$(ANTLR_RUNTIME_PATH) -I$(CUSTOM_Z3_INCLUDE_PATH) -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


