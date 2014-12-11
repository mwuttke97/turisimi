/*
 * TuringMashine.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringMashine.h"
#include "TuringTypes.h"

bool TuringMashine::isAccepted() {
	return m_accepted;
}

const TuringMashine::TupleVector& TuringMashine::getTuples() const {
	return m_tuples;
}

const TuringMashine::StateList& TuringMashine::getStates() const {
	return m_states;
}

void TuringMashine::addTuple(const TuringTuple * tuple) {
	m_tuples.push_back(const_cast<TuringTuple*> (tuple));
}

void TuringMashine::addBandData(TURING_POINTER index, TURING_BAND_DATA value) {
	for (StateList::iterator it = m_states.begin(); it != m_states.end(); it++){
		(*it)->getBand()->clear();
	}
}

void TuringMashine::addAcceptingState(TURING_POINTER node_id) {
	m_accepting_states.push_back(node_id);
}

void TuringMashine::doStep() {
	// TODO
}

void TuringMashine::loopyStupi() {
	while (!m_accepted)
		doStep();
}

TuringMashine::TuringMashine() {
	m_states.push_back(new TuringState());
	m_accepted = false;
}
