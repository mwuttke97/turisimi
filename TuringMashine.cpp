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

bool TuringMashine::reachedFinalState() {
	return m_final_state == TURING_STATE_ACCEPTED;
}

void TuringMashine::addTuple(const TuringTuple * tuple) {
	m_tuples.push_back(const_cast<TuringTuple*> (tuple));
}

void TuringMashine::addBandData(TURING_POINTER index, TURING_BAND_DATA value) {
	for (StateList::iterator it = m_states.begin(); it != m_states.end(); it++){
		(*it)->getBand()->write(index, value);
	}
}

void TuringMashine::addAcceptingState(TURING_POINTER node_id) {
	m_accepting_states.push_back(node_id);
}

bool TuringMashine::verticeActive(TURING_VERTICE node_id) {
	StateList::iterator it;
	for (it = m_states.begin(); it != m_states.end(); it++){
		if ((*it)->getVertice() == node_id){
			switch((*it)->getState()){
			case TURING_STATE_ACCEPTED:
			case TURING_STATE_NORMAL:
				return true;

			default:
				break;
			}
		}
	}
	return false;
}

void TuringMashine::deleteStates(TURING_STATE stateToDelete) {
	for (auto stateIt = m_states.begin(); stateIt != m_states.end();) {
		if ((*stateIt)->getState() == stateToDelete) {
			if (*stateIt)
				delete *stateIt;
			if (stateIt == m_states.begin()) {
				m_states.pop_front();
				stateIt = m_states.begin();
			} else {
				m_states.erase(stateIt--);
				stateIt++;
			}
		} else {
			stateIt++;
		}
	}
}

void TuringMashine::doStep() {
	TURING_BAND_DATA read;
	StateList::iterator stateIt;
	TupleVector::iterator tupleIt;

	// delete old states
	deleteStates(TURING_STATE_OLD);

	switch (m_final_state){
	case TURING_STATE_INIT:
		m_final_state = TURING_STATE_NORMAL;
		break;

	case TURING_STATE_NORMAL:
		if (m_states.empty()){
			m_final_state = TURING_STATE_REJECTED;
		}
		break;

	case TURING_STATE_REJECTED:
		return;

	case TURING_STATE_ACCEPTED:
	default:
		break;
	}

	for (stateIt = m_states.begin(); stateIt != m_states.end(); stateIt++){
		TuringState * state = *stateIt;
		TURING_STATE cloneState;
		switch (state->getState()){
		case TURING_STATE_INIT:
		case TURING_STATE_NORMAL:
			cloneState = TURING_STATE_NORMAL;
			break;

		case TURING_STATE_ACCEPTED:
			cloneState = TURING_STATE_ACCEPTED;
			break;

		case TURING_STATE_OLD:
		case TURING_STATE_REJECTED:
		default:
			continue;
		}
		read = state->peek();

		// search for good tuples
		for (tupleIt = m_tuples.begin(); tupleIt != m_tuples.end(); tupleIt++){
			if ((*tupleIt)->getFromId() == state->getPointer()){
				if ((*tupleIt)->getRead() == read){
					TuringState * clonedState = state->clone();
					clonedState->setState(cloneState);
					clonedState->write((*tupleIt)->getWrite());
					clonedState->move((*tupleIt)->getMove());
					clonedState->setVertice((*tupleIt)->getToId());
					m_states.push_front(clonedState);
					state->setState(TURING_STATE_OLD);
				}
			}
		}
		if ((*stateIt)->getState() != TURING_STATE_OLD){
			(*stateIt)->setState(TURING_STATE_REJECTED);
		}
	}

	if (!reachedFinalState()){
		for (stateIt = m_states.begin(); stateIt != m_states.end(); stateIt++){
			if (std::find(m_accepting_states.begin(), m_accepting_states.end(), (*stateIt)->getVertice()) != m_accepting_states.end()){
				(*stateIt)->setState(TURING_STATE_ACCEPTED);
				m_final_state = TURING_STATE_ACCEPTED;
			}
		}
	}

	// delete rejected states
	deleteStates(TURING_STATE_REJECTED);
}

void TuringMashine::loopyStupi() {
	while(m_final_state == TURING_STATE_NORMAL){
		doStep();
	}
}

TuringMashine::TuringMashine() {
	m_states.push_back(new TuringState());
	m_final_state = TURING_INIT_STATE;
}
