/*
 * TuringTypes.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGTYPES_H_
#define TURINGTYPES_H_

typedef long long TURING_DATA, TURING_POINTER, TURING_NODE;

typedef unsigned char TURING_BAND_DATA;

enum{
	TURING_PLACE_HOLDER = (TURING_BAND_DATA) '#',
};

typedef unsigned char TURING_MOVE_TYPE;

enum{
	MOVE_RIGHT = 'r',
	MOVE_LEFT = 'l',
	MOVE_STOP = 'S',
};

enum TURING_STATE{
	TURING_STATE_ERROR = 0,
	TURING_STATE_OK = 1,
	TURING_STATE_FAILED = 'f',
	TURING_STATE_SUCCES = 's',
};

#define TURING_INIT_STATE	(TURING_STATE) TURING_STATE_OK
#define TURING_INIT_POINTER	(TURING_POINTER) 0
#define TURING_INIT_NODE	(TURING_NODE) 0

#endif /* TURINGTYPES_H_ */
