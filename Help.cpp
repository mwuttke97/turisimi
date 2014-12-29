/*
 * Help.cpp
 *
 *  Created on: 11.12.2014
 *      Author: Maximilian Wuttke (mwuttke97@gmail.com)
 */

#include <stdio.h>
#include <iostream>
#include "Help.h"

void help::info() {
	std::cout << "Turing Machine Simulator" << std::endl;
}

void help::invalid_input_simulate_break(){
	fprintf(stderr, "Invalid input. Try help.\n");
}

void help::invalid_args(const char * prgm, const char * arg){
	fprintf(stderr, "ERROR: Unknown parameter: %s\n", arg);
	fprintf(stderr, "Try %s --help\n", prgm);
}

void help::help_step_cmd() {
	// TODO
}

void help::help_args(const char* prgm) {
	// TODO
}
