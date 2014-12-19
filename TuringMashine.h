/*
 * TuringMashine.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGMASHINE_H_
#define TURINGMASHINE_H_

#include <list>
#include <queue>
#include "TuringTypes.h"
#include "TuringTuple.h"
#include "TuringState.h"
#include "TuringStateIterator.h"

class TuringMashine{
public:
	typedef std::vector<TuringTuple*> TupleVector;
	typedef std::vector<TURING_POINTER> TuringPointerVector;

private:
	TupleVector m_tuples;
	TuringPointerVector m_accepting_states;
	TuringState * m_latest_state;
	TURING_STATE m_final_state;

public:
	TuringMashine();
	~TuringMashine();

public:
	TuringStateHIterator getStates() const;
	TupleVector& getTuples();
	TURING_STATE getFinalState() const;
	bool reachedFinalState();

public:
	void addTuple(const TuringTuple * tuple);
	void addBandData(TURING_POINTER index, TURING_BAND_DATA value);
	void addAcceptingState(TURING_POINTER node_id);
	std::vector<TURING_POINTER> & getAcceptingStates();

public:
	void doStep();
	void loopyStupi();

public:
	bool verticeActive(TURING_VERTICE node_id);

public:
	bool eraseState(TURING_POINTER id);

private:
	void eraseState(TuringStateHIterator & id);

public:
	TuringState * addEmtyState();
	TuringState * cloneState(TURING_POINTER id);
	TuringState * spuleBack(TURING_POINTER count);
};

#endif /* TURINGMASHINE_H_ */
