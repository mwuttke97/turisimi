/*
 * TuringState.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringState.h"

TuringBand* TuringState::getBand() const {
	return (TuringBand*) &m_band;
}

TURING_POINTER TuringState::getPointer() const {
	return m_pointer;
}

void TuringState::setPointer(TURING_POINTER pointer) {
	m_pointer = pointer;
}

void TuringState::decPointer() {
	m_pointer--;
}

void TuringState::incPointer() {
	m_pointer++;
}

TURING_STATE TuringState::getState() const {
	return m_state;
}

void TuringState::setState(TURING_STATE state) {
	m_state = state;
}

TURING_VERTICE TuringState::getVertice() const {
	return m_vertice;
}

TuringStateIterator TuringState::getParent() const {
	return m_parent;
}

void TuringState::setVertice(TURING_VERTICE node_id) {
	m_vertice = node_id;
}

TURING_BAND_DATA TuringState::peek() {
	return m_band.get(m_pointer);
}

void TuringState::move(TURING_MOVE_TYPE move) {
	switch (move){
	case MOVE_LEFT:
		decPointer();
		break;

	case MOVE_RIGHT:
		incPointer();
		break;

	case MOVE_STOP:
	default:
		break;
	}
}

void TuringState::write(TURING_BAND_DATA data) {
	m_band.write(m_pointer, data);
}

TuringState::TuringState() : m_band(), m_parent(0) {
	this->m_state	= TURING_INIT_STATE;
	this->m_pointer	= TURING_INIT_POINTER;
	this->m_vertice = TURING_INIT_VERTICE;
}

TuringState::TuringState(const TuringState& parentState) : m_band(), m_parent((TuringStateIterator) &parentState){
	m_band		= parentState.m_band;
	m_pointer	= parentState.m_pointer;
	m_state		= parentState.m_state;
	m_vertice	= parentState.m_vertice;
}

TuringState* TuringState::clone() const{
	return new TuringState(*this);
}
