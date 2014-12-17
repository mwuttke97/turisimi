/*
 * TuringState.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include <string.h> // memcpy()
#include "TuringState.h"
#include "TuringStateIterator.h"

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

TuringState::TuringState() : m_band(), m_parent(0), m_child_left(0), m_child_right(0), m_brother_left(0), m_brother_right(0), m_id(0) {
	this->m_state	= TURING_INIT_STATE;
	this->m_pointer	= TURING_INIT_POINTER;
	this->m_vertice = TURING_INIT_VERTICE;
}

TuringState::TuringState(TuringState& parentState) : m_band(), m_parent(&parentState), m_child_left(0), m_child_right(0) {
	m_band		= parentState.m_band;
	m_pointer	= parentState.m_pointer;
	m_state		= parentState.m_state;
	m_vertice	= parentState.m_vertice;
	m_brother_left = parentState.m_child_right;

	if (parentState.m_child_left == 0)
		parentState.m_child_left = this;

	m_id = 0;

	m_brother_right = 0;
	parentState.m_child_right = this;
	if (m_brother_left){
		if (m_brother_left->m_brother_right == 0){
			m_brother_left->m_brother_right = this;
			m_id = m_brother_left->m_id + 1;
		}
	}
}

TuringState::~TuringState() {
	TuringState * buffer;
	if (m_parent){
		buffer = m_parent;
		if (this == buffer){
			TuringStateHIterator it = getIteratorH();
			for (it++; *it != 0; it++){
				(*it)->m_parent = 0;
				delete *it;
			}
			delete m_parent;
		} else{
			delete buffer;
		}
	}
	erase(true);
}

TuringState* TuringState::clone() const{
	return new TuringState((TuringState&) *this);
}

TuringStateHIterator TuringState::getIteratorH() const {
	if (m_parent){
		return TuringStateHIterator((TuringState*) m_parent->m_child_left);
	}
	return TuringStateHIterator((TuringState*) this);
}

TuringStateHIterator TuringState::getIteratorH_right() const {
	if (m_parent){
		return TuringStateHIterator((TuringState*) m_parent->m_child_right);
	}
	return TuringStateHIterator((TuringState*) this);
}

TuringStateVIterator TuringState::getIteratorV() const {
	return TuringStateVIterator((TuringState*) this);
}

TURING_POINTER TuringState::getID() const {
	return m_id;
}

void TuringState::erase(bool deleteChildren) {
	if (m_brother_left){
		m_brother_left->m_brother_right = m_brother_right;
	}
	if (m_brother_right){
		m_brother_right->m_brother_left = m_brother_left;
	}
	if (deleteChildren && m_child_left){
		auto it = m_child_left->getIteratorH();
		for (; *it != 0; it++){
			(*it)->erase(deleteChildren);
			delete *it;
		}
	}
	if (m_parent){
		if (m_parent->m_child_left == this)
			m_parent->m_child_left = 0;
		if (m_parent->m_child_right == this)
			m_parent->m_child_right = 0;
	}
	m_parent = 0;
	m_child_left = 0;
	m_child_right = 0;
}
