/*
 * TuringState.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGSTATE_H_
#define TURINGSTATE_H_

#include "TuringTypes.h"
#include "TuringBand.h"

class TuringState {

private:
	TuringBand m_band;
	TURING_POINTER m_pointer;
	TURING_STATE m_state;
	TURING_NODE m_node;

public:
	TuringState();
	TuringState(const TuringState & state);
private:
	TuringState(
			const TuringBand & band,
			const TURING_DATA &pointer	= TURING_INIT_POINTER,
			const TURING_STATE &state	= TURING_INIT_STATE,
			const TURING_NODE &node		= TURING_INIT_NODE);

public:
	TuringBand* getBand();
	TURING_POINTER getPointer() const;
	void setPointer(TURING_POINTER pointer);
	void incPointer();
	void decPointer();
	TURING_STATE getState() const;
	void setState(TURING_STATE state);

public:
	TuringState * clone();
};

#endif /* TURINGSTATE_H_ */
