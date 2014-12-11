/*
 * TuringState.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringState.h"

TuringBand* TuringState::getBand() {
	return &m_band;
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

TURING_VERTICLE TuringState::getVerticle() const {
	return m_verticle;
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

TuringState::TuringState() {
	this->m_state	= TURING_INIT_STATE;
	this->m_pointer	= TURING_INIT_POINTER;
	this->m_verticle= TURING_INIT_VERTICLE;
}

TuringState::TuringState(const TuringState& state) : TuringState::TuringState(state.m_band, state.m_pointer, state.m_state, state.m_verticle){
}

TuringState::TuringState(const TuringBand & band, const TURING_DATA &pointer, const TURING_STATE &state, const TURING_VERTICLE &verticle){
	m_band		= band;
	m_pointer	= pointer;
	m_state		= state;
	m_verticle	= verticle;
}

TuringState* TuringState::clone() {
	return new TuringState(m_band.clone_(), m_pointer, m_state, m_verticle);
}
