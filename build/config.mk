CUSTOM_Z3_LIB_PATH := /home/osboxes/customZ3/lib
CUSTOM_Z3_INCLUDE_PATH := /home/osboxes/customZ3/include
ANTLR_RUNTIME_PATH := /usr/local/include/antlr4-runtime

FOPENMP := 
ifeq ($(shell uname -s) ,Darwin)
    FOPENMP := 
endif 



