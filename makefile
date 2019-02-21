# Makefile for building the NFA to DFA Converter.  Uses g++.
all: NFAConv
	cd NFAConv && g++ *.cpp -o NFAConverter && mv NFAConverter ..
