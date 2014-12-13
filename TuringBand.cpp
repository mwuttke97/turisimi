/*
 * TuringBand.cpp
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#include "TuringBand.h"

void TuringBand::clear() {
	while (!m_band.empty()){
		if (m_band.back())
			delete m_band.back();
		m_band.pop_back();
	}
	m_band.clear();
}

TURING_BAND_DATA TuringBand::get(TURING_POINTER index) {
	for (auto it = m_band.begin(); it != m_band.end(); it++){
		if ((*it)->m_pointer == index){
			return (*it)->m_data;
		}
	}
	return TURING_PLACE_HOLDER;
}

void TuringBand::write(TURING_POINTER index, TURING_BAND_DATA value) {
	bool b_new;
	TuringBandPair * pair = 0;
	for (auto it = m_band.begin(); it != m_band.end(); it++){
		if ((*it)->m_pointer == index){
			pair = *it;
			b_new = false;
			break;
		}
	}
	if (pair == 0){
		pair = new TuringBandPair();
		b_new = true;
	}
	pair->m_pointer = index;
	pair->m_data = value;
	if (b_new)
		m_band.push_back(pair);
}

TuringBand::TuringBand() : m_band() {
}

TuringBand::~TuringBand() {
	clear();
}

void TuringBand::copyMap(TuringBandMap const & band) {
	TuringBandPair* pair;
	TuringBandMap::const_iterator it;
	TuringBandMap::size_type c;
	for (it = band.begin(), c = 0; it != band.end(); it++, c++) {
		pair = new TuringBandPair();
		*pair = **it;
		m_band.push_back(pair);
	}
}

TuringBand::TuringBand(TuringBandMap& band) : m_band() {
	copyMap(band);
}

TURING_POINTER TuringBand::getFirst() const {
	TURING_POINTER min = TURING_POINTER_MAX;
	for (auto it = m_band.begin(); it != m_band.end(); it++){
		if ((*it)->m_pointer < min)
			min = (*it)->m_pointer;
	}
	return min;
}

TURING_POINTER TuringBand::getLast() const {
	TURING_POINTER max = TURING_POINTER_MIN;
	for (auto it = m_band.begin(); it != m_band.end(); it++){
		if ((*it)->m_pointer > max)
			max = (*it)->m_pointer;
	}
	return max;
}

TuringBand * TuringBand::clone() {
	return new TuringBand(m_band);
}

void TuringBand::operator =(const TuringBand& band) {
	m_band.clear();
	copyMap(band.m_band);
}
