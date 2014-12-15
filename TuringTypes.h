/*
 * TuringTypes.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGTYPES_H_
#define TURINGTYPES_H_

// Note: VERTICES are sometimes called nodes
typedef int TURING_DATA, TURING_POINTER, TURING_VERTICE;

#ifdef __INT_MAX__
enum{
	TURING_POINTER_MAX = (TURING_POINTER) +__INT_MAX__,
	TURING_POINTER_MIN = (TURING_POINTER) -__INT_MAX__,
};
#else
#include <limits.h>
enum{
	TURING_POINTER_MAX = (TURING_POINTER) INT_MAX,
	TURING_POINTER_MIN = (TURING_POINTER) INT_MAX,
};
#endif // __INT_MAX__

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
	TURING_STATE_INIT		= 1 << 0,
	TURING_STATE_NORMAL		= 1 << 1,
	TURING_STATE_ACCEPTED	= 1 << 2,
	TURING_STATE_REJECTED	= 1 << 3,
	TURING_STATE_OLD		= 1 << 4,
};

enum{
	TURING_INIT_STATE		= (TURING_STATE) TURING_STATE_INIT,
	TURING_INIT_POINTER		= (TURING_POINTER) 0,
	TURING_INIT_VERTICE		= (TURING_VERTICE) 0,
};

const char * turingStateString(TURING_STATE state);

#endif /* TURINGTYPES_H_ */
