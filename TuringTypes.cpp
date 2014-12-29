/*
 * TuringTypes.cpp
 *
 *  Created on: 11.12.2014
 *      Author: Maximilian Wuttke (mwuttke97@gmail.com)
 */

#include "TuringTypes.h"

const char* turingStateString(TURING_STATE state) {
	switch (state){
	case TURING_STATE_INIT:
		return "init";

	case TURING_STATE_NORMAL:
		return "normal";

	case TURING_STATE_ACCEPTED:
		return "accepted";

	case TURING_STATE_REJECTED:
		return "rejected";

	case TURING_STATE_OLD:
		return "old";

	default:
		return "???";
	}
}
