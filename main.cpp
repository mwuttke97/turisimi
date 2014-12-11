/*
 * main.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include "TuringTypes.h"
#include "TuringTuple.h"
#include "TuringMashine.h"


static struct{
	bool b_quiet;
	bool b_debug;
	const char * str_tm_in;
	const char * str_debug_in;
	const char * str_debug_out;
	const char * str_band_in;
	const char * str_band_out;
} settings;

static struct{
	bool b_step_by_step;
	std::vector<TURING_POINTER> v_break_points;
} debug;

static TuringMashine mashine;

void info() {
	std::cout << "Turing mashine simulator" << std::endl;
	std::cout << "========================" << std::endl;
}

void readTM(){
	TURING_POINTER n_edges, n_accepting_verticles, node_id;
	struct{
		TURING_POINTER from_id;
		TURING_BAND_DATA read;
		TURING_BAND_DATA write;
		TURING_POINTER to_id;
		TURING_MOVE_TYPE move;
	} tuple;

	if (!settings.b_quiet)
		std::cout << "Number of accepting nodes: ";
	std::cin >> n_accepting_verticles;

	for (; n_accepting_verticles != 0; n_accepting_verticles--){
		if (!settings.b_quiet){
			std::cout << "[Accepting NODE ID]\t";
		}
		std::cin >> node_id;
		mashine.addAcceptingState(node_id);
	}

	if (!settings.b_quiet)
		std::cout << "Number of edges:\t\t";
	std::cin >> n_edges;

	if (!settings.b_quiet){
		std::cout << "Please enter data now" << std::endl;
	}

	for (; n_edges != 0; n_edges--){
		if (!settings.b_quiet){
			std::cout << "[EDGE 5-TUPLE]\t";
		}
		memset(&tuple, 0, sizeof(tuple));
		std::cin >> tuple.from_id >> tuple.read >> tuple.write >> tuple.to_id >> tuple.move;
		if (std::cin.fail()){
			std::cin.clear();
			std::cin.ignore();
		}
		mashine.addTuple(new TuringTuple(tuple.to_id, tuple.from_id, tuple.read, tuple.write, (TURING_MOVE_TYPE) tuple.move));
	}
	if (!settings.b_quiet){
		std::cout << "OK." << std::endl;
	}
}

void readBand(){
	TURING_POINTER n_first, n_last;
	TURING_BAND_DATA band_value;

	if (!settings.b_quiet){
		std::cout << "Band's first data pointer:\t";
	}

	std::cin >> n_first;
	if (!settings.b_quiet){
		std::cout << "Band's last data pointer:\t";
	}
	std::cin >> n_last;

	if (!settings.b_quiet){
		std::cout << "Please enter data now" << std::endl;
	}

	for (TURING_POINTER n = n_first; n <= n_last; n++){
		if (!settings.b_quiet){
			std::cout << "[BAND DATA]\t";
		}
		memset(&band_value, 0, sizeof(band_value));
		std::cin >> band_value;
		mashine.addBandData(n, band_value);
	}

	if (!settings.b_quiet){
		std::cout << std::endl;
	}
}

void writeStates(){
	// TODO
}

void simulate(){
	// TODO
}

int main(int argc, const char *argv[]){

	TURING_POINTER buffer;

	// Handle params
	if (argc > 1){
		enum{
			ARG_NEW_ARG = 0,
			ARG_FILE_TM_IN,
			ARG_FILE_BAND_IN,
			ARG_FILE_BAND_OUT,
			ARG_FILE_DEBUG_IN,
			ARG_FILE_DEBUG_OUT,
			ARG_DEBUG_BREAK_POINTS,
		} current_arg = ARG_NEW_ARG;
		
		// standard options
		settings.b_quiet = false;
		settings.str_tm_in = "-";
		settings.str_debug_in = "-";
		settings.str_debug_out = "-";
		settings.str_band_in = "-";
		settings.str_band_out = "-";

		for (int n = 1; n < argc; n++){
			const char * arg = argv[n];
			switch(current_arg){
			case ARG_NEW_ARG:

				if (strcmp("-q", arg) || strcmp("--quiet", arg)){
					settings.b_quiet = true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (strcmp("-tm", arg) || strcmp("--tm_in", arg)){
					current_arg = ARG_FILE_TM_IN;
					break;
				}
				if (strcmp("-in", arg) || strcmp("--band_in", arg)){
					current_arg = ARG_FILE_BAND_IN;
					break;
				}
				if (strcmp("-out", arg) || strcmp("--tm_out", arg)){
					current_arg = ARG_FILE_BAND_OUT;
					break;
				}
				if (strcmp("-din", arg) || strcmp("--debug_in", arg)){
					current_arg = ARG_FILE_DEBUG_IN;
					break;
				}
				if (strcmp("-dout", arg) || strcmp("--debug_out", arg)){
					current_arg = ARG_FILE_DEBUG_OUT;
					break;
				}
				if (strcmp("-sbs", arg) || strcmp("--step-by-step", arg)){
					settings.b_debug	= true;
					debug.b_step_by_step= true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (strcmp("-bp", arg) || strcmp("--brake-points", arg)){
					settings.b_debug	= true;
					current_arg = ARG_DEBUG_BREAK_POINTS;
					break;
				}
				goto err_arg;

			case ARG_FILE_TM_IN:
				settings.str_tm_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_BAND_IN:
				settings.str_band_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_BAND_OUT:
				settings.str_band_out = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_DEBUG_IN:
				settings.str_debug_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_DEBUG_OUT:
				settings.str_debug_out = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_DEBUG_BREAK_POINTS:
			{
				std::stringstream ss(arg);
				while (ss >> buffer){
				    debug.v_break_points.push_back(buffer);
				    if (ss.peek() == ',')
				        ss.ignore();
				}
			}
				current_arg = ARG_NEW_ARG;
				break;

			default:
				goto err_arg;
			}
			continue;
			err_arg:
			fprintf(stderr, "ERROR: Unknown parameter: %s", arg);
			exit(0);
		}
	}
	if (!settings.b_quiet)
		info();

	// Handle input
	std::ifstream in;
	std::ofstream out;
	std::streambuf * cinbuff, * coutbuff;
	cinbuff = std::cin.rdbuf();
	coutbuff= std::cout.rdbuf();

	if (strcmp("-", settings.str_tm_in)){
		// redirect std::cin to input file if `settings.str_tm_in` is not equal to "-"
		in.open(settings.str_tm_in, std::ios::in);
		std::cin.rdbuf(cinbuff);
	}
	// read turing mashine from std::cin
	readTM();
	std::cin.rdbuf(cinbuff);

	if (strcmp("-", settings.str_band_in)){
		// redirect std::cin to input file if `settings.str_band_in` is not equal to "-"
		in.open(settings.str_band_in, std::ios::in);
		std::cin.rdbuf(cinbuff);
	}
	// read baand data from std::cin
	readBand();
	std::cin.rdbuf(cinbuff);

	if (strcmp("-", settings.str_debug_in)){
		// redirect std::cin to input file if `settings.str_debug_in` is not equal to "-"
		in.open(settings.str_debug_in, std::ios::in);
		std::cin.rdbuf(cinbuff);
	}

	if (strcmp("-", settings.str_debug_out)){
		// redirect std::cout to output file if `settings.str_debug_out` is not equal to "-"
		out.open(settings.str_debug_out, std::ios::out);
		std::cout.rdbuf(coutbuff);
	}

	// start simulation;
	// read from std::cin;
	// write to std::cout
	simulate();
	std::cin.rdbuf(cinbuff);
	std::cout.rdbuf(coutbuff);

	// close streams
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();

	return 1;
}
