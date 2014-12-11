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
	bool m_accepted;
	
public:
	TuringMashine();

public:
	const StateList& getStates() const;
	const TupleVector& getTuples() const;

public:
	void addTuple(const TuringTuple * tuple);
	void addBandData(TURING_POINTER index, TURING_BAND_DATA value);
	void addAcceptingState(TURING_POINTER node_id);

public:
	void doStep();
	bool isAccepted();
	void loopyStupi();
};

#endif /* TURINGMASHINE_H_ */
