/*
 * TuringTypes.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGTYPES_H_
#define TURINGTYPES_H_

// Note: VERTICES are sometimes called nodes
typedef long long TURING_DATA, TURING_POINTER, TURING_VERTICE;

typedef char TURING_BAND_DATA;

enum{
	TURING_PLACE_HOLDER = (TURING_BAND_DATA) '#',
};

typedef char TURING_MOVE_TYPE, TURING_STATE;

enum{
	MOVE_RIGHT = 'r',
	MOVE_LEFT = 'l',
	MOVE_STOP = 's',
};

enum{
	TURING_STATE_NORMAL		= 'n',
	TURING_STATE_ACCEPTED	= 'a',
	TURING_STATE_REJECTED	= 'r',
	TURING_STATE_OLD		= 'o',
};

enum{
	TURING_INIT_STATE		= (TURING_STATE) TURING_STATE_NORMAL,
	TURING_INIT_POINTER		= (TURING_POINTER) 0,
	TURING_INIT_VERTICE		= (TURING_VERTICE) 0,
};

const char * turingStateString(TURING_STATE state);

#endif /* TURINGTYPES_H_ */