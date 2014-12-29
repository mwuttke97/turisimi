/*
 * Help.h
 *
 *  Created on: 11.12.2014
 *      Author: Maximilian Wuttke (mwuttke97@gmail.com)
 */

#ifndef HELP_H_
#define HELP_H_

namespace help{
void info();
void invalid_input_simulate_break();
void invalid_args(const char * prgm, const char * arg);
void help_step_cmd();
void help_args(const char *prgm);
}

#endif /* HELP_H_ */
