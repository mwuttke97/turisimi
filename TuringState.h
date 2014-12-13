/*
 * TuringState.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGSTATE_H_
#define TURINGSTATE_H_

#include <list>
#include "TuringTypes.h"
#include "TuringBand.h"

typedef std::list<TURING_VERTICE> TuringStateHistory;

class TuringState {

private:
	TuringBand m_band;
	TURING_POINTER m_pointer;
	TURING_STATE m_state;
	TURING_VERTICE m_vertice;
	TuringStateHistory m_history;

public:
	TuringState();
	TuringState(const TuringState & state);
private:
	TuringState(
			const TuringBand &band,
			const TuringStateHistory &history,
			const TURING_POINTER &pointer	= TURING_INIT_POINTER,
			const TURING_STATE &state		= TURING_INIT_STATE,
			const TURING_VERTICE &vertice	= TURING_INIT_VERTICE);

public:
	TuringBand* getBand() const;
	TURING_POINTER getPointer() const;
	void setPointer(TURING_POINTER pointer);
	void incPointer();
	void decPointer();
	TURING_STATE getState() const;
	void setState(TURING_STATE state);
	const TuringStateHistory& getHistory() const;

public:
	// Band methods
	TURING_BAND_DATA peek();
	void move(TURING_MOVE_TYPE move);
	void write(TURING_BAND_DATA data);

public:
	TuringState * clone() const;
	TURING_VERTICE getVertice() const;
	void setVertice(TURING_VERTICE node_id);
};

#endif /* TURINGSTATE_H_ */
