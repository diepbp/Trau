################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Automaton.cpp \
../src/CreateFlats.cpp \
../src/FileConverter.cpp \
../src/GrmOverApprox.cpp \
../src/GrmUnderApprox.cpp \
../src/StringReduce.cpp \
../src/StringTheory.cpp \
../src/TokenParser.cpp \
../src/UnderApprox.cpp \
../src/fileutils.cpp \
../src/main.cpp \
../src/regex.cpp \
../src/regexpattern.cpp \
../src/regexstate.cpp \
../src/utils.cpp \
../src/z3utils.cpp 

OBJS += \
./src/Automaton.o \
./src/CreateFlats.o \
./src/FileConverter.o \
./src/GrmOverApprox.o \
./src/GrmUnderApprox.o \
./src/StringReduce.o \
./src/StringTheory.o \
./src/TokenParser.o \
./src/UnderApprox.o \
./src/fileutils.o \
./src/main.o \
./src/regex.o \
./src/regexpattern.o \
./src/regexstate.o \
./src/utils.o \
./src/z3utils.o 

CPP_DEPS += \
./src/Automaton.d \
./src/CreateFlats.d \
./src/FileConverter.d \
./src/GrmOverApprox.d \
./src/GrmUnderApprox.d \
./src/StringReduce.d \
./src/StringTheory.d \
./src/TokenParser.d \
./src/UnderApprox.d \
./src/fileutils.d \
./src/main.d \
./src/regex.d \
./src/regexpattern.d \
./src/regexstate.d \
./src/utils.d \
./src/z3utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -I/home/osboxes/Downloads/z3-z3-4.4.1.0/src/api -I/usr/local/include/antlr4-runtime -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


