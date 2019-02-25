# Makefile for building the NFA to DFA Converter.  Uses g++.
all: NFAConv
	@echo "Compiling..."
	cd NFAConv && g++ *.cpp -o NFAConverter && mv NFAConverter ..
	@echo "Compiled!  Type './NFAConverter [InputFilePath] [OutputFileName]' to run." 
