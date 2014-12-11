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
#include <algorithm>
#include "TuringTypes.h"
#include "TuringTuple.h"
#include "TuringMashine.h"
#include "Help.h"

static struct{
	bool b_quiet;
	bool b_debug;
	bool b_continue_if_accepted;
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

void toggleBreakPoints(std::stringstream & ss) {
	TURING_POINTER buffer;
	while (ss >> buffer) {
		auto it = std::find(debug.v_break_points.begin(), debug.v_break_points.end(), buffer);
		if (it == debug.v_break_points.end()){
			debug.v_break_points.push_back(buffer);
		} else{
			debug.v_break_points.erase(it);
		}
		if (ss.peek() == ',')
			ss.ignore();
	}
}

void toggleBreakPoints(std::string arg) {
	std::stringstream ss(arg);
	toggleBreakPoints(ss);
}

void toggleBreakPoints(const char* arg) {
	std::stringstream ss(arg);
	toggleBreakPoints(ss);
}

void readTM(){
	TURING_POINTER n_edges, n_accepting_vertices, node_id;
	struct{
		TURING_POINTER from_id;
		TURING_BAND_DATA read;
		TURING_BAND_DATA write;
		TURING_POINTER to_id;
		TURING_MOVE_TYPE move;
	} tuple;

	if (!settings.b_quiet)
		std::cout << "Number of accepting nodes:\t";
	std::cin >> n_accepting_vertices;

	for (; n_accepting_vertices != 0; n_accepting_vertices--){
		if (!settings.b_quiet){
			std::cout << "[Accepting NODE ID]\t\t";
		}
		std::cin >> node_id;
		mashine.addAcceptingState(node_id);
	}

	if (!settings.b_quiet)
		std::cout << "Number of edges:\t\t";
	std::cin >> n_edges;

	if (!settings.b_quiet){
		std::cout << "Please enter data now." << std::endl;
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
	TURING_POINTER n_first;
	std::string line;

	if (!settings.b_quiet){
		std::cout << "Band's first data pointer:\t";
	}
	std::cin >> n_first;

	if (!settings.b_quiet){
		std::cout << "Please enter data now" << std::endl;
	}

	if (!settings.b_quiet){
		std::cout << "[BAND DATA]\t";
	}
	std::cin >> line;
	for (size_t n = 0; n < line.length(); n++){
		mashine.addBandData(n, line[n]);
	}

	if (!settings.b_quiet){
		std::cout << std::endl;
	}
}

void writeStates(){
	// TODO
}

void simulate(){
	if (!settings.b_quiet){
		std::cout << "Start simulation" << std::endl;
	}

	for (;;){
		mashine.doStep();
		if (settings.b_debug){
			bool b_break = false;
			b_break |= debug.b_step_by_step;
			b_break |= mashine.reachedFinalState() && !settings.b_continue_if_accepted;
			if (!b_break){
				for (auto it = debug.v_break_points.begin(); it != debug.v_break_points.end(); it++){
					if (mashine.verticeActive(*it)){
						b_break |= true;
						break;
					}
				}
			}

			if (b_break){
				writeStates();
				for (;;){
					std::string str_input;
					if (!settings.b_quiet){
						std::cout << ">> ";
					}
					std::cin >> str_input;
					if (str_input == "s" || str_input == "step"){
						break;
					}
					if (str_input == "td" || str_input == "toggle debug"){
						settings.b_debug ^= true;
						break;
					}
					if (str_input == "r" || str_input == "run" || str_input == "toggle step by step"){
						debug.b_step_by_step ^= true;
						break;
					}
					if (str_input == "R" || str_input == "Run" || str_input == "RUN" || str_input == "RUN!"){
						settings.b_debug = false;
						debug.b_step_by_step = false;
						settings.b_continue_if_accepted = false;
						debug.v_break_points.clear();
						break;
					}
					if (str_input == "h" || str_input == "help"){
						help::help_step_cmd();
						continue;
					}
					std::stringstream ss(str_input);
					std::string str_cmd, str_args;
					std::getline(ss, str_cmd, ' ');
					if (str_cmd == "toggle"){
						str_cmd.clear();
						std::getline(ss, str_cmd, ' ');
						if (str_cmd == "bp" || str_cmd == "break_point"){
							str_cmd.clear();
							std::getline(ss, str_args);
							toggleBreakPoints(str_args);
						}
					}
					help::invalid_input_simulate_break();
				}
			}
		}
	}
}

int main(int argc, const char *argv[]){
	// get executable file name for help
	const char * prgm = (argv > 0 && argv[0]) ? argv[0] : "turisimi";

	// standard options
	settings.b_quiet = false;
	settings.b_debug = false;
	settings.b_continue_if_accepted = false;
	settings.str_tm_in = "-";
	settings.str_debug_in = "-";
	settings.str_debug_out = "-";
	settings.str_band_in = "-";
	settings.str_band_out = "-";

	debug.b_step_by_step = false;
	debug.v_break_points.clear();

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

		for (int n = 1; n < argc; n++){
			const char * arg = argv[n];
			switch(current_arg){
			case ARG_NEW_ARG:

				if (!strcmp("-q", arg) || !strcmp("--quiet", arg)){
					settings.b_quiet = true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (!strcmp("-tm", arg) || !strcmp("--tm_in", arg)){
					current_arg = ARG_FILE_TM_IN;
					break;
				}
				if (!strcmp("-in", arg) || !strcmp("--band_in", arg)){
					current_arg = ARG_FILE_BAND_IN;
					break;
				}
				if (!strcmp("-out", arg) || !strcmp("--tm_out", arg)){
					current_arg = ARG_FILE_BAND_OUT;
					break;
				}
				if (!strcmp("-din", arg) || !strcmp("--debug_in", arg)){
					current_arg = ARG_FILE_DEBUG_IN;
					break;
				}
				if (!strcmp("-dout", arg) || !strcmp("--debug_out", arg)){
					current_arg = ARG_FILE_DEBUG_OUT;
					break;
				}
				if (!strcmp("-sbs", arg) || !strcmp("--step_by_step", arg)){
					settings.b_debug	= true;
					debug.b_step_by_step= true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (!strcmp("-c", arg) || !strcmp("--continue", arg)){
					settings.b_continue_if_accepted = true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (!strcmp("-bp", arg) || !strcmp("--brake-points", arg)){
					settings.b_debug	= true;
					current_arg = ARG_DEBUG_BREAK_POINTS;
					break;
				}

				if (!strcmp("-h", arg) || !strcmp("--help", arg)){
					help::help_args(prgm);
				}
				help::invalid_args(prgm, arg);
				exit(0);

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
				toggleBreakPoints(arg);
				current_arg = ARG_NEW_ARG;
				break;

			default:
				help::invalid_args(prgm, arg);
				exit(0);
			}
		}
	}
	if (!settings.b_quiet)
		help::info();

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

	// start simulation:
	// read from std::cin and write to std::cout
	simulate();
	std::cin.rdbuf(cinbuff);
	std::cout.rdbuf(coutbuff);

	// close open streams
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();

	return 1;
}
