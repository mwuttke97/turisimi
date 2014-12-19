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

TuringMashine::TupleVector& TuringMashine::getTuples() {
	return m_tuples;
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
	for (auto it = m_latest_state->getIteratorH(); *it != 0; it++){
		(*it)->getBand()->write(index, value);
	}
}

void TuringMashine::addAcceptingState(TURING_POINTER node_id) {
	m_accepting_states.push_back(node_id);
}

TuringStateHIterator TuringMashine::getStates() const {
	if (m_latest_state){
		return m_latest_state->getIteratorH();
	}
	return TuringStateHIterator();
}

bool TuringMashine::verticeActive(TURING_VERTICE node_id) {
	for (auto it = m_latest_state->getIteratorH(); *it != 0; it++){
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

void TuringMashine::doStep() {
	TURING_BAND_DATA read;
	TuringStateHIterator stateIt;
	TupleVector::iterator tupleIt;

	if (m_latest_state == 0){
		return;
	}

	switch (m_final_state){
	case TURING_STATE_INIT:
		m_final_state = TURING_STATE_NORMAL;
		break;

	case TURING_STATE_NORMAL:
		if (m_latest_state == 0){
			m_final_state = TURING_STATE_REJECTED;
			return;
		}
		break;

	case TURING_STATE_REJECTED:
		return;

	case TURING_STATE_ACCEPTED:
	default:
		break;
	}

	for (stateIt = m_latest_state->getIteratorH_right(); *stateIt != 0; stateIt--){
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
			eraseState(stateIt);
			if (m_latest_state){
				if (m_latest_state->getState() == TURING_STATE_OLD){
					m_latest_state->setState(TURING_STATE_REJECTED);
				}
			}
			continue;
		}
		read = state->peek();

		// search for good tuples
		for (tupleIt = m_tuples.begin(); tupleIt != m_tuples.end(); tupleIt++){
			if ((*tupleIt)->getFromId() == state->getVertice()){
				if ((*tupleIt)->getRead() == read){
					TuringState * clonedState = state->clone();
					clonedState->setState(cloneState);
					clonedState->write((*tupleIt)->getWrite());
					clonedState->move((*tupleIt)->getMove());
					clonedState->setVertice((*tupleIt)->getToId());
					m_latest_state = clonedState;
					state->setState(TURING_STATE_OLD);
				}
			}
		}
		if ((*stateIt)->getState() != TURING_STATE_OLD){
			(*stateIt)->setState(TURING_STATE_REJECTED);
		}
	}

	if (!reachedFinalState()){
		for (stateIt = m_latest_state->getIteratorH(); *stateIt != 0; stateIt++){
			if (std::find(m_accepting_states.begin(), m_accepting_states.end(), (*stateIt)->getVertice()) != m_accepting_states.end()){
				(*stateIt)->setState(TURING_STATE_ACCEPTED);
				m_final_state = TURING_STATE_ACCEPTED;
			}
		}
	}

	if (m_final_state == TURING_STATE_NORMAL){
		bool b_rejected = true;
		for (stateIt = m_latest_state->getIteratorH(); *stateIt != 0; stateIt++){
			if ((*stateIt)->getState() == TURING_STATE_NORMAL){
				b_rejected = false;
				break;
			}
		}
		if (b_rejected){
			m_final_state = TURING_STATE_REJECTED;
		}
	}
}

void TuringMashine::loopyStupi() {
	while(m_final_state == TURING_STATE_NORMAL){
		doStep();
	}
}

bool TuringMashine::eraseState(TURING_POINTER id) {
	for (TuringStateHIterator it = getStates(); *it != 0; it++){
		if (id-- == 0){
			eraseState(it);
			return true;
		}
	}
	return false;
}

void TuringMashine::eraseState(TuringStateHIterator & it){
	TuringState * buffer = *it;
	if (buffer){
		if (buffer == m_latest_state){
			m_latest_state = (TuringState*) --it;
			if (m_latest_state == 0){
				m_latest_state = (TuringState*) --buffer->getIteratorV();
			}
		}
		buffer->erase(true);
		delete buffer;
	}
}

TuringState * TuringMashine::addEmtyState() {
	TuringState * buff;
	if (m_latest_state){
		TuringStateVIterator it = m_latest_state->getIteratorV();
		if (--it){
			buff = (*it)->clone();
			buff->getBand()->clear();
			buff->setState(TURING_STATE_INIT);
			return buff;
		}
	}
	if (m_latest_state == 0){
		return m_latest_state = new TuringState();
	}
}

TuringState * TuringMashine::cloneState(TURING_POINTER id) {
	TuringState * buff;
	for (auto it = getStates(); *it != 0; it++){
		if (id-- == 0){
			buff = (*it)->clone();
			buff->setState(TURING_STATE_INIT);
			return buff;
		}
	}
	return 0;
}

TuringState * TuringMashine::spuleBack(TURING_POINTER count){
	TuringState * buff = m_latest_state;
	if (buff == 0){
		return buff;
	}

	auto it = m_latest_state->getIteratorV();
	for (it--; *it != 0; it--){
		m_latest_state = *it;
		if (--count == 0){
			break;
		}
	}
	m_latest_state->deleteChildren();
	if (m_latest_state->getState() == TURING_STATE_OLD){
		if (m_latest_state->isRoot()){
			  m_latest_state->setState(TURING_STATE_INIT);
				m_final_state = TURING_STATE_INIT;
			} else{
			  m_latest_state->setState(TURING_STATE_NORMAL);
				m_final_state = TURING_STATE_NORMAL;
			}
	}
	return m_latest_state;
}

TuringMashine::TuringMashine() {
	m_latest_state = new TuringState();
	m_final_state = TURING_INIT_STATE;
}

TuringMashine::~TuringMashine() {
	// Delete only the "latest" state.
	// The rest will be deleted, through.
	if (m_latest_state)
		delete m_latest_state;
}
