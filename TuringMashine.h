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

class TuringMashine{
public:
	typedef std::vector<TuringTuple*> TupleVector;
	typedef std::vector<TURING_POINTER> TuringPointerVector;
	typedef std::list<TuringState*> StateList;

private:
	TupleVector m_tuples;
	StateList m_states;
	TuringPointerVector m_accepting_states;
	TURING_STATE m_final_state;

	void deleteStates(TURING_STATE stateToDelete);

public:
	TuringMashine();

public:
	const StateList& getStates() const;
	const TupleVector& getTuples() const;
	TURING_STATE getFinalState() const;
	bool reachedFinalState();

public:
	void addTuple(const TuringTuple * tuple);
	void addBandData(TURING_POINTER index, TURING_BAND_DATA value);
	void addAcceptingState(TURING_POINTER node_id);

public:
	void doStep();
	void loopyStupi();

public:
	bool verticeActive(TURING_VERTICE node_id);
};

#endif /* TURINGMASHINE_H_ */
