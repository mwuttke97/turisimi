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

class TuringState;
typedef TuringState * TuringStateIterator;

class TuringState {

private:
	TuringBand m_band;
	TURING_POINTER m_pointer;
	TURING_STATE m_state;
	TURING_VERTICE m_vertice;
	TuringStateIterator m_parent;
	TuringStateIterator m_child_right;
	TuringStateIterator m_brother_left;

public:
	TuringState();
	TuringState(TuringState & parentState);
	~TuringState();

public:
	TuringBand* getBand() const;
	TURING_POINTER getPointer() const;
	void setPointer(TURING_POINTER pointer);
	void incPointer();
	void decPointer();
	TURING_STATE getState() const;
	void setState(TURING_STATE state);

public:
	// Band methods
	TURING_BAND_DATA peek();
	void move(TURING_MOVE_TYPE move);
	void write(TURING_BAND_DATA data);

public:
	TuringState * clone() const;
	TURING_VERTICE getVertice() const;
	void setVertice(TURING_VERTICE node_id);
	TuringStateIterator getParent() const;
};

#endif /* TURINGSTATE_H_ */
