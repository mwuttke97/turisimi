/*
 * TuringMashine.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include <algorithm>
#include <assert.h>
#include "TuringMashine.h"
#include "TuringTypes.h"

const TuringMashine::TupleVector& TuringMashine::getTuples() const {
	return m_tuples;
}

const TuringMashine::StateList& TuringMashine::getStates() const {
	return m_states;
}

TURING_STATE TuringMashine::getFinalState() const {
	return m_final_state;
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
	TURING_BAND_DATA read;
	StateList::iterator stateIt;
	TupleVector::iterator tupleIt;
	for (stateIt = m_states.begin(); stateIt != m_states.end(); stateIt++){
		if ((*stateIt)->getState() == TURING_STATE_NORMAL){
			read = (*stateIt)->peek();
			// search for i in m_accepting_states
			if (std::find(m_accepting_states.begin(), m_accepting_states.end(), (*stateIt)->getVerticle()) != m_accepting_states.end()){
				(*stateIt)->setState(TURING_STATE_ACCEPTED);
				m_final_state = TURING_STATE_ACCEPTED;
			}

			// search for good tuples
			for (tupleIt = m_tuples.begin(); tupleIt != m_tuples.end(); tupleIt++){
				if ((*tupleIt)->getFromId() == (*stateIt)->getPointer()){
					if ((*tupleIt)->getRead() == read){
						TuringState * clonedState = (*stateIt)->clone();
						clonedState->write((*tupleIt)->getWrite());
						clonedState->move((*tupleIt)->getMove());
						m_states.push_front(clonedState);
						(*stateIt)->setState(TURING_STATE_OLD);
					}
				}
			}
			if ((*stateIt)->getState() != TURING_STATE_OLD){
				(*stateIt)->setState(TURING_STATE_REJECTED);
			}
		}
	}

	// delete old and rejected states
	for (stateIt = m_states.begin(); stateIt != m_states.end(); stateIt++){
		if ((*stateIt)->getState() == TURING_STATE_REJECTED || (*stateIt)->getState() == TURING_STATE_OLD){
			delete *stateIt;
			if (stateIt == m_states.begin()){
				m_states.pop_front();
			} else{
				m_states.erase(stateIt--);
			}
		}
	}
}

void TuringMashine::loopyStupi() {
	while(m_final_state == TURING_STATE_NORMAL){
		doStep();
	}
}

TuringMashine::TuringMashine() {
	m_states.push_back(new TuringState());
	m_final_state = TURING_STATE_NORMAL;
}
