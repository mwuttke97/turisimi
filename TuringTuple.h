/*
 * CTuringTuple.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGTUPLE_H_
#define TURINGTUPLE_H_

#include "TuringTypes.h"

class TuringTuple {
private:
	TURING_POINTER m_to_id;
	TURING_POINTER m_from_id;
	TURING_BAND_DATA m_read;
	TURING_BAND_DATA m_write;
	TURING_MOVE_TYPE m_move;

public:
	TuringTuple(TURING_POINTER to_id, TURING_POINTER from_id, TURING_BAND_DATA read, TURING_BAND_DATA write, TURING_MOVE_TYPE move);

public:
	TURING_POINTER getFromId() const;
	void setFromId(TURING_POINTER fromId);
	TURING_BAND_DATA getRead() const;
	void setRead(TURING_BAND_DATA read);
	TURING_POINTER getToId() const;
	void setToId(TURING_POINTER toId);
	TURING_BAND_DATA getWrite() const;
	void setWrite(TURING_BAND_DATA write);
	TURING_MOVE_TYPE getMove() const;
	void setMove(TURING_MOVE_TYPE move);
};

#endif /* TURINGTUPLE_H_ */
