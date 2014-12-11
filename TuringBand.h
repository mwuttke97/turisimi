/*
 * TuringBand.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGBAND_H_
#define TURINGBAND_H_

#include <map>
#include "TuringTypes.h"

class TuringBand {
public:
	typedef std::map<TURING_DATA, TURING_BAND_DATA> TuringBandMap;

private:
	TuringBandMap m_band;
	bool m_emty;

public:
	TuringBand();
	TuringBand(TuringBandMap & band, bool emty = true);

public:
	bool isEmty();
	bool isEmty(TURING_POINTER index);
	TURING_BAND_DATA get(TURING_POINTER index);
	void write(TURING_POINTER index, TURING_BAND_DATA value);
	void clear(TURING_POINTER index);
	void clear();

public:
	TuringBand * clone();
};

#endif /* TURINGBAND_H_ */
