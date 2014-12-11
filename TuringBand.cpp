/*
 * TuringBand.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringBand.h"

bool TuringBand::isEmty() {
	return m_emty;
}

bool TuringBand::isEmty(TURING_POINTER index) {
	return get(index) == TURING_PLACE_HOLDER;
}

void TuringBand::clear(TURING_POINTER index) {
	m_band[index] = TURING_PLACE_HOLDER;
}

void TuringBand::clear() {
	m_band.clear();
}

TURING_BAND_DATA TuringBand::get(TURING_DATA index) {
	TURING_BAND_DATA buffer = m_band.at(index);
	if (buffer)
		return buffer;
	return TURING_PLACE_HOLDER;
}

void TuringBand::write(TURING_POINTER index, TURING_BAND_DATA value) {
	m_band[index] = value;
	m_emty &= (value == TURING_PLACE_HOLDER);
}

TuringBand::TuringBand() {
	m_emty = false;
}

TuringBand::TuringBand(TuringBandMap& band, bool emty) {
	m_band = band;
	m_emty = emty;
}

const TuringBand & TuringBand::clone_(){
	return TuringBand(m_band, m_emty);
}


TuringBand * TuringBand::clone() {
	return new TuringBand(m_band, m_emty);
}
