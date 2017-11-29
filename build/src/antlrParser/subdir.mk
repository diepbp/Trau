################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/antlrParser/SMTLIB2Lexer.cpp \
../src/antlrParser/SMTLIB2Parser.cpp \
../src/antlrParser/SMTLIB2ParserBaseListener.cpp \
../src/antlrParser/SMTLIB2ParserBaseVisitor.cpp \
../src/antlrParser/SMTLIB2ParserListener.cpp \
../src/antlrParser/SMTLIB2ParserVisitor.cpp 

OBJS += \
./src/antlrParser/SMTLIB2Lexer.o \
./src/antlrParser/SMTLIB2Parser.o \
./src/antlrParser/SMTLIB2ParserBaseListener.o \
./src/antlrParser/SMTLIB2ParserBaseVisitor.o \
./src/antlrParser/SMTLIB2ParserListener.o \
./src/antlrParser/SMTLIB2ParserVisitor.o 

CPP_DEPS += \
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
	g++ -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -I/home/osboxes/Downloads/z3-z3-4.4.1.0/src/api -I/usr/local/include/antlr4-runtime -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


