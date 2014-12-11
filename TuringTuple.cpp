/*
 * TuringTuple.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringTuple.h"

TURING_POINTER TuringTuple::getFromId() const {
	return m_from_id;
}

void TuringTuple::setFromId(TURING_POINTER fromId) {
	m_from_id = fromId;
}

TURING_BAND_DATA TuringTuple::getRead() const {
	return m_read;
}

void TuringTuple::setRead(TURING_BAND_DATA read) {
	m_read = read;
}

TURING_DATA TuringTuple::getToId() const {
	return m_to_id;
}

void TuringTuple::setToId(TURING_POINTER toId) {
	m_to_id = toId;
}

TURING_BAND_DATA TuringTuple::getWrite() const {
	return m_write;
}

void TuringTuple::setWrite(TURING_BAND_DATA write) {
	m_write = write;
}

TuringTuple::TuringTuple(TURING_POINTER to_id, TURING_POINTER from_id, TURING_BAND_DATA read, TURING_BAND_DATA write, TURING_MOVE_TYPE move){
	m_to_id		= to_id;
	m_from_id	= from_id;
	m_read		= read;
	m_write		= write;
	m_move		= move;
}
