################################################################################
# Automatically-generated file. Do not edit!
################################################################################
-include ../config.mk

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/antlrParser/SMTLIB26Lexer.cpp \
../src/antlrParser/SMTLIB26Parser.cpp \
../src/antlrParser/SMTLIB26ParserBaseListener.cpp \
../src/antlrParser/SMTLIB26ParserBaseVisitor.cpp \
../src/antlrParser/SMTLIB26ParserListener.cpp \
../src/antlrParser/SMTLIB26ParserVisitor.cpp \
../src/antlrParser/SMTLIB2Lexer.cpp \
../src/antlrParser/SMTLIB2Parser.cpp \
../src/antlrParser/SMTLIB2ParserBaseListener.cpp \
../src/antlrParser/SMTLIB2ParserBaseVisitor.cpp \
../src/antlrParser/SMTLIB2ParserListener.cpp \
../src/antlrParser/SMTLIB2ParserVisitor.cpp 

OBJS += \
./src/antlrParser/SMTLIB26Lexer.o \
./src/antlrParser/SMTLIB26Parser.o \
./src/antlrParser/SMTLIB26ParserBaseListener.o \
./src/antlrParser/SMTLIB26ParserBaseVisitor.o \
./src/antlrParser/SMTLIB26ParserListener.o \
./src/antlrParser/SMTLIB26ParserVisitor.o \
./src/antlrParser/SMTLIB2Lexer.o \
./src/antlrParser/SMTLIB2Parser.o \
./src/antlrParser/SMTLIB2ParserBaseListener.o \
./src/antlrParser/SMTLIB2ParserBaseVisitor.o \
./src/antlrParser/SMTLIB2ParserListener.o \
./src/antlrParser/SMTLIB2ParserVisitor.o 

CPP_DEPS += \
./src/antlrParser/SMTLIB26Lexer.d \
./src/antlrParser/SMTLIB26Parser.d \
./src/antlrParser/SMTLIB26ParserBaseListener.d \
./src/antlrParser/SMTLIB26ParserBaseVisitor.d \
./src/antlrParser/SMTLIB26ParserListener.d \
./src/antlrParser/SMTLIB26ParserVisitor.d \
./src/antlrParser/SMTLIB2Lexer.d \
./src/antlrParser/SMTLIB2Parser.d \
./src/antlrParser/SMTLIB2ParserBaseListener.d \
./src/antlrParser/SMTLIB2ParserBaseVisitor.d \
./src/antlrParser/SMTLIB2ParserListener.d \
./src/antlrParser/SMTLIB2ParserVisitor.d 


# Each subdirectory must supply rules for building sources it contributes
src/antlrParser/%.o: ../src/antlrParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -I$(ANTLR_RUNTIME_PATH) -I$(CUSTOM_Z3_INCLUDE_PATH) -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


