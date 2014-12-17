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
#include "TuringStateIterator.h"

class TuringState;

class TuringState {

private:
	TuringBand m_band;
	TURING_POINTER m_pointer;
	TURING_STATE m_state;
	TURING_VERTICE m_vertice;
	TuringState * m_brother_left;
	TuringState * m_brother_right;
	TuringState * m_parent;
	TuringState * m_child_left;
	TuringState * m_child_right;
	TURING_POINTER m_id;

	bool m_delete_children;

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

	TuringStateHIterator getIteratorH() const;
	TuringStateHIterator getIteratorH_right() const;
	TuringStateVIterator getIteratorV() const;
	TURING_POINTER getID() const;

	void erase(bool b_deleteChildren = true);
	void deleteChildren();

	friend class TuringStateHIterator;
	friend class TuringStateVIterator;
};

#endif /* TURINGSTATE_H_ */
