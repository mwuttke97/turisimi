/*
 * main.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include "TuringTypes.h"
#include "TuringTuple.h"
#include "TuringState.h"
#include "TuringStateIterator.h"
#include "TuringMashine.h"
#include "Help.h"

static struct{
	bool b_quiet;
	bool b_was_quiet;
	bool b_debug;
	bool b_verbose;
	bool b_one_input_file;
	bool b_continue_if_accepted;
	const char * str_tm_in;
	const char * str_debug_in;
	const char * str_debug_out;
	const char * str_band_in;
	const char * str_band_file_in;
	const char * str_band_out;
	unsigned long n_trace_lenght;

	TURING_POINTER p_first_band_data_pointer;
} settings;

static struct{
	bool b_step_by_step;
	std::vector<TURING_POINTER> v_break_points;
} debug;

TuringMashine * mashine;

void quit(int status = 0){
	if (mashine)
		delete mashine;
	exit(status);
}

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

void setInitPointer(const char * arg){
	std::stringstream ss(arg);
	ss >> settings.p_first_band_data_pointer;
}

void read_tuple(std::istream & s, TuringTuple & tuple){
	TURING_POINTER from_id;
	TURING_BAND_DATA read;
	TURING_BAND_DATA write;
	TURING_POINTER to_id;
	TURING_MOVE_TYPE move;
	s
	>> from_id
	>> read
	>> write
	>> to_id
	>> move;

	tuple.setFromId(from_id);
	tuple.setRead(read);
	tuple.setWrite(write);
	tuple.setToId(to_id);
	tuple.setMove(move);
}

void readTM(){
	TURING_POINTER n_edges, n_accepting_vertices, node_id;

	if (!settings.b_quiet)
		std::cout << "Number of accepting nodes:\t";
	std::cin >> n_accepting_vertices;

	for (; n_accepting_vertices != 0; n_accepting_vertices--){
		if (!settings.b_quiet){
			std::cout << "[Accepting NODE ID]\t\t";
		}
		std::cin >> node_id;
		mashine->addAcceptingState(node_id);
	}

	if (!settings.b_quiet)
		std::cout << "Number of edges:\t\t";
	std::cin >> n_edges;

	if (!settings.b_quiet){
		std::cout << "Please enter data now." << std::endl;
	}

	for (; n_edges != 0; n_edges--){
		if (!settings.b_quiet){
			std::cout << "[EDGE 5-TUPLE]\t\t\t";
		}
		TuringTuple * tuple = new TuringTuple();
		read_tuple(std::cin, *tuple);
		mashine->addTuple(tuple);
		if (std::cin.fail()){
			std::cin.clear();
			std::cin.ignore();
		}
	}
	if (!settings.b_quiet){
		std::cout << "OK." << std::endl;
	}
}

void readBand(){
	std::string line;

	if (settings.str_band_in){
		line += settings.str_band_in;
	} else{
		if (!settings.b_quiet){
			std::cout << "[BAND DATA]\t\t\t";
		}
		std::getline(std::cin, line);
	}

	for (TURING_POINTER n = 0; n < (TURING_POINTER) line.length(); n++){
		mashine->addBandData(n + settings.p_first_band_data_pointer, line[n]);
	}

	if (!settings.b_quiet){
		std::cout << "OK." << std::endl;
	}
}

void writeBand(const TuringState& state) {
	TURING_POINTER n_first, n_last, n_pointer, n_width;

	auto band	= state.getBand();
	n_pointer	= state.getPointer();
	n_first		= std::min(band->getFirst(), n_pointer);
	n_last		= std::max(band->getLast(), n_pointer);
	n_width		= n_last - n_first;

	std::stringstream line0, line1, line2;

	for (auto i = n_first; i <= n_last; i++){
		line0 << band->get(i) << " ";
	}

	for (auto i = n_pointer - n_first; i != 0; i--){
		line1 << "  ";
	}
	line1 << "^";
	line2.width(n_width * 2 + 1);
	line2 << n_last;
	line2.seekp(0);
	line2 << n_first;

	std::cout << "## " << line0.str() << "##" << std::endl;
	std::cout << "   " << line1.str() << std::endl;
	std::cout << "   " << line2.str() << std::endl;
}

void writeState(const TuringState & state){
	std::cout << "State: " << turingStateString(state.getState()) << "; [" << state.getID() << "] " <<  std::endl;

	if (settings.n_trace_lenght != 0){
		std::cout << "Trace: ";
		std::string str_history;
		unsigned long l_count;
		TuringStateVIterator it;
		for (it = state.getIteratorV(), l_count = 0; *it != 0; it--, l_count++){
			if (l_count == 0){
				std::stringstream ss_buffer;
				ss_buffer << state.getVertice();
				str_history = ss_buffer.str();
			} else if (l_count < settings.n_trace_lenght){
				std::stringstream ss_buffer;
				ss_buffer << (*it)->getVertice();
				str_history = ss_buffer.str() + " >> " + str_history;
			} else{
				str_history = "... >> " + str_history;
				break;
			}
		}
		std::cout << str_history << std::endl;
	}
	writeBand(state);
	std::cout << std::endl;
}

void writeStates(){
	std::cout << "Simulation state: " << turingStateString(mashine->getFinalState()) << std::endl;

	for (auto states = mashine->getStates(); *states != 0; states++){
		assert(*states);
		writeState(**states);
	}
	std::cout << std::endl;
}

void erase_state(TURING_POINTER id){
	if (!mashine->eraseState(id)){
		std::cerr << "Failed to erase state " << id << "." << std::endl;
	}
}

void add_state(){
	TuringState * buff = mashine->addEmtyState();
	if (buff == 0){
		std::cerr << "Failed to add state." << std::endl;
	} else{
		writeState(*buff);
	}
}

void clone_state(TURING_POINTER id){
	TuringState * buff = mashine->cloneState(id);
	if (buff == 0){
		std::cerr << "Failed to clone state " << id << "." << std::endl;
	} else{
		writeState(*buff);
	}
}

void edit_state(TURING_POINTER id){
	TURING_POINTER i;

	auto it = mashine->getStates();

	for (i = 0; i < id; i++){
		if ((++it)->getID() == id){
			break;
		}
	}
	TuringState * state = *it;

	if (i > id || *it == 0){
		std::cout << "No such state: " << id << std::endl;
		return;
	}

	for (;;){
		if (!settings.b_quiet){
			writeBand(*state);
			std::cout << "[EDIT STATE] ";
		}

		std::string str_line, str_cmd;
		std::getline(std::cin, str_line);
		std::stringstream ss_line(str_line);
		std::getline(ss_line, str_cmd, ' ');

		if (str_cmd == ""){
			str_cmd += MOVE_RIGHT;
		}

		switch (str_cmd[0]){
			case 'm':
			case 'M':
			{
				TURING_POINTER buffer0, buffer1;
				buffer0 = state->getPointer();
				ss_line >> buffer1;
				if (ss_line.peek() == ' '){
					ss_line.ignore();
				}
				if (!ss_line.eof()){
					switch (ss_line.get()){
						case MOVE_LEFT:
							buffer1 = -buffer1;
							break;

						case MOVE_RIGHT:
							buffer0 = +buffer1;
							break;

						default:
							break;
					}
					buffer1 += buffer0;
				}
				state->setPointer(buffer1);
				break;
			}

			case MOVE_LEFT:
				state->move(MOVE_LEFT);
				break;

			case MOVE_RIGHT:
				state->move(MOVE_RIGHT);
				break;

			case 'w':
			case 'W':
			{
				TURING_BAND_DATA buffer = ' ';
				ss_line >> buffer;
				state->write(buffer);
				break;
			}

			case 's':
			case 'S':
				return;

			case 'q':
			case 'Q':
				quit(1);
				break;

			default:
				// TODO invalid cmd
				break;
		}
	}
}

void spule_back(TURING_POINTER count) {
	TuringState * buffer = mashine->spuleBack(count);
	if (buffer == 0){
		std::cerr << "Failed to spule back." << std::endl;
	} else if (!settings.b_quiet){
		writeStates();
	}
}

void writeTuple(std::ostream & ss, TuringTuple & tuple){
	ss
	<< tuple.getFromId() << " "
	<< tuple.getRead() << " "
	<< tuple.getWrite() << " "
	<< tuple.getToId() << " "
	<< tuple.getMove();
}

void edit_tuples(){
	auto & tuples = mashine->getTuples();
	TURING_POINTER edit_id, buffer;
	TuringTuple * edit;

	edit_id = 0;

	for (;;){
		auto it = tuples.begin();
		for (buffer = 0; it != tuples.end(); it++, buffer++){
			if (edit_id == buffer){
				edit = *it;
				break;
			}
		}
		if (it == tuples.end()){
			edit_id = buffer - 1;
			edit = *--it;
		}
		if (!settings.b_quiet){
			auto it = tuples.begin();
			for (buffer = 0; it != tuples.end(); it++, buffer++){
				writeTuple(std::cout, **it);
				std::cout << "\t[" << buffer << "]";
				if (edit_id == buffer){
					std::cout << "\t<--";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << "[TUPLES] ";
		}

		std::string str_line, str_cmd;
		std::getline(std::cin, str_line);
		std::stringstream ss_line(str_line);
		std::getline(ss_line, str_cmd, ' ');

		if (str_cmd == ""){
			str_cmd += MOVE_RIGHT;
		}

		switch (str_cmd[0]){
			case 'm':
			case 'M':
				buffer = edit_id;
				ss_line >> edit_id;
				if (ss_line.peek() == ' '){
					ss_line.ignore();
				}
				if (!ss_line.eof()){
					switch (ss_line.get()){
						case MOVE_LEFT:
							edit_id = -edit_id;
							break;

						case MOVE_RIGHT:
							edit_id = +edit_id;
							break;

						default:
							break;
					}
					edit_id += buffer;
				}
				break;

			case MOVE_LEFT:
				edit_id--;
				break;

			case MOVE_RIGHT:
				edit_id++;
				break;

			case 'w':
			case 'W':
				if (edit)
					read_tuple(ss_line, *edit);
				break;

			case 'a':
			case 'A':
				tuples.push_back(new TuringTuple());
				edit_id = buffer;
				break;

			case 'e':
			case 'E':
				if (!edit)
					break;

				it = std::find(tuples.begin(), tuples.end(), edit);
				if (it != tuples.end()){
					tuples.erase(it);
				}
				delete edit;
				break;

			case 's':
			case 'S':
				return;

			case 'q':
			case 'Q':
				quit(1);
				break;

			default:
				// TODO invalid cmd
				break;
		}
	}
}

void writeTM(std::ostream & os){
	auto states = mashine->getAcceptingStates();
	auto tuples = mashine->getTuples();

	os << states.size() << std::endl;
	for (auto it = states.begin(); it != states.end(); it++){
		os << *it <<  std::endl;
	}

	os << tuples.size() << std::endl;
	for (auto it = tuples.begin(); it != tuples.end(); it++){
		if (*it){
			writeTuple(os, **it);
			os << std::endl;
		}
	}
}

void simulate(){
	if (!settings.b_quiet){
		std::cout << "Start simulation" << std::endl << std::endl;
	}

	for (;;){
		bool b_interupt = false;
		if (mashine->reachedFinalState()){
			b_interupt = *mashine->getStates() == 0 || !settings.b_continue_if_accepted;
		}
		if (settings.b_debug || b_interupt){
			bool b_break = false;
			b_break |= debug.b_step_by_step || b_interupt;
			if (!b_break){
				for (auto it = debug.v_break_points.begin(); it != debug.v_break_points.end(); it++){
					if (mashine->verticeActive(*it)){
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
					std::getline(std::cin, str_input);
					if (str_input.empty() || str_input == "s" || str_input == "step"){
						settings.b_debug = true;
						debug.b_step_by_step = true;
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
					if (str_input == "q" || str_input == "quit"){
						return;
					}
					if (str_input == "h" || str_input == "help"){
						help::help_step_cmd();
						continue;
					}
					std::stringstream ss(str_input);
					std::string str_cmd, str_cmd_flags, str_args;
					std::getline(ss, str_cmd, ' ');
					if (str_cmd == "toggle"){
						std::getline(ss, str_cmd_flags, ' ');
						if (str_cmd_flags == "b" || str_cmd_flags == "bp" || str_cmd_flags == "break_point"){
							std::getline(ss, str_args);
							toggleBreakPoints(str_args);
							continue;
						}
					} else if (str_cmd == "state"){
						TURING_POINTER arg;
						std::getline(ss, str_cmd_flags, ' ');
						if (str_cmd_flags == "erase"){
							if (ss.eof()){
								erase_state(0);
								continue;
							}
							while (!ss.eof()){
								ss >> arg;
								if (ss.peek() == ',')
									ss.ignore();
								erase_state(arg);
							}
							continue;
						} else if (str_cmd_flags == "add"){
							// No further arguments allowed
							if (!str_args.empty()){
								help::invalid_input_simulate_break();
								continue;
							}
							add_state();
							continue;
						} else if (str_cmd_flags == "clone"){
							if (ss.eof()){
								clone_state(0);
								continue;
							}
							while (!ss.eof()){
								ss >> arg;
								if (ss.peek() == ',')
									ss.ignore();
								clone_state(arg);
							}
							continue;
						} else if (str_cmd_flags == "edit"){
							if (ss.eof()){
								edit_state(0);
								continue;
							}
							while (!ss.eof()){
								ss >> arg;
								if (ss.peek() == ',')
									ss.ignore();
								edit_state(arg);
							}
							continue;
						}
					} else if (str_cmd == "spule"){
						TURING_POINTER arg;
						if (ss.eof()){
							arg = -1;
						} else {
							ss >> arg;
							if (arg < 0){
								arg = -arg;
							}
						}
						spule_back(arg);
						continue;
					} else if (str_cmd == "tuples"){
						edit_tuples();
						continue;
					} else if (str_cmd == "export"){
						std::getline(ss, str_cmd_flags, ' ');
						if (str_cmd_flags == ""){
							if (strcmp(settings.str_tm_in, "-") != 0){
								str_cmd_flags += settings.str_tm_in;
							} else{
								std::cerr << "Path is eamty!" << std::endl;
								continue;
							}
						}
						std::ofstream of_tm(str_cmd_flags, std::ios::out);
						if (of_tm.fail()){
							std::cerr << "An error occured while opening file \"" << str_cmd_flags << "\"." << std::endl;
							of_tm.close();
							continue;
						}
						writeTM(of_tm);
						if (of_tm.fail()){
							std::cerr << "An error occured while writing to file \"" << str_cmd << "\"." << std::endl;
						}
						of_tm.close();
						continue;
					}

					help::invalid_input_simulate_break();
				}
			}
		} else if (settings.b_verbose){
			writeStates();
		}
		mashine->doStep();
	}
}

int main(int argc, const char *argv[]){
	// get executable file name for help
	const char * prgm = (argv > 0 && argv[0]) ? argv[0] : "turisimi";

	// create TM
	mashine = new TuringMashine();

	// standard options
	settings.b_quiet = false;
	settings.b_was_quiet = false;
	settings.b_debug = false;
	settings.b_verbose = false;
	settings.b_one_input_file = false;
	settings.b_continue_if_accepted = false;
	settings.str_tm_in = "-";
	settings.str_debug_in = "-";
	settings.str_debug_out = "-";
	settings.str_band_in = 0;
	settings.str_band_file_in = "-";
	settings.str_band_out = "-";
	settings.n_trace_lenght = 0;
	settings.p_first_band_data_pointer = TURING_INIT_POINTER;

	debug.b_step_by_step = false;
	debug.v_break_points.clear();

	// Handle params
	if (argc > 1){
		enum{
			ARG_NEW_ARG = 0,
			ARG_FILE_INPUT,
			ARG_FILE_TM_IN,
			ARG_FILE_BAND_IN,
			ARG_FILE_BAND_OUT,
			ARG_FILE_DEBUG_IN,
			ARG_FILE_DEBUG_OUT,
			ARG_DEBUG_BREAK_POINTS,
			ARG_TRACE_LENGTH,
			ARG_TURING_BAND_DATA,
			ARG_TURING_INIT_POINTER,
		} current_arg = ARG_NEW_ARG;

		for (int n = 1; n < argc; n++){
			const char * arg = argv[n];

			switch(current_arg){
			case ARG_NEW_ARG:

				if (!strcmp("-q", arg) || !strcmp("--quiet", arg)){
					settings.b_quiet = true;
					settings.b_was_quiet = true;
					current_arg = ARG_NEW_ARG;
					break;
				}
				if (!strcmp("-tm", arg) || !strcmp("--tm_in", arg)){
					current_arg = ARG_FILE_TM_IN;
					break;
				}
				if (!strcmp("-i", arg) || !strcmp("-in", arg) || !strcmp("--input", arg)){
					settings.b_one_input_file = true;
					current_arg = ARG_FILE_INPUT;
					break;
				}

				if (!strcmp("-b", arg) || !strcmp("--band", arg)){
					current_arg = ARG_TURING_BAND_DATA;
					break;
				}
				if (!strcmp("-bin", arg) || !strcmp("--band_in", arg)){
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
				if (!strcmp("-v", arg) || !strcmp("--verbose", arg)){
					settings.b_verbose = true;
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
				if (!strcmp("-tl", arg) || !strcmp("--trace-length", arg)){
					current_arg = ARG_TRACE_LENGTH;
					break;
				}
				if (!strcmp("-p", arg) || !strcmp("--band-init", arg)){
					current_arg = ARG_TURING_INIT_POINTER;
					break;
				}

				if (!strcmp("-h", arg) || !strcmp("--help", arg)){
					help::help_args(prgm);
				}
				help::invalid_args(prgm, arg);
				exit(0);

			case ARG_FILE_INPUT:
				settings.str_tm_in = arg;
				settings.str_band_file_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_TM_IN:
				settings.str_tm_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_FILE_BAND_IN:
				settings.str_band_file_in = arg;
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

			case ARG_TRACE_LENGTH:
				if (strcmp(arg, "*") == 0)
					settings.n_trace_lenght = -1;
				else
					settings.n_trace_lenght = atoll(arg);
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_TURING_BAND_DATA:
				settings.str_band_in = arg;
				current_arg = ARG_NEW_ARG;
				break;

			case ARG_TURING_INIT_POINTER:
				setInitPointer(arg);
				current_arg = ARG_NEW_ARG;
				break;
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

	if (strcmp("-", settings.str_tm_in) != 0){
		// redirect std::cin to input file if `settings.str_tm_in` is not equal to "-"
		in.open(settings.str_tm_in, std::ios::in);
		std::cin.rdbuf(in.rdbuf());
		settings.b_quiet = true;
	}
	// read tur	ing mashine from std::cin
	readTM();
	if (settings.b_one_input_file){
		settings.b_quiet = true;
	} else{
		in.close();
		std::cin.rdbuf(cinbuff);
		if (strcmp("-", settings.str_band_file_in) != 0){
			// redirect std::cin to input file if `settings.str_band_file_in` is not equal to "-"
			in.open(settings.str_band_file_in, std::ios::in);
			std::cin.rdbuf(in.rdbuf());
		}
		settings.b_quiet = settings.b_was_quiet;
	}

	// read band data from std::cin
	readBand();
	std::cin.rdbuf(cinbuff);
	settings.b_quiet = settings.b_was_quiet;

	if (strcmp("-", settings.str_debug_in) != 0){
		// redirect std::cin to input file if `settings.str_debug_in` is not equal to "-"
		in.open(settings.str_debug_in, std::ios::in);
		std::cin.rdbuf(in.rdbuf());
	}

	if (strcmp("-", settings.str_debug_out) != 0){
		// redirect std::cout to output file if `settings.str_debug_out` is not equal to "-"
		out.open(settings.str_debug_out, std::ios::out);
		std::cout.rdbuf(out.rdbuf());
		settings.b_quiet = true;
	}

	// start simulation:
	// read from std::cin and write to std::cout
	simulate();
	std::cin.rdbuf(cinbuff);
	std::cout.rdbuf(coutbuff);
	settings.b_quiet = settings.b_was_quiet;

	// close open streams
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();

	delete mashine;

	return 1;
}
