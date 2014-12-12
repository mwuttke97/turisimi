/*
 * TuringBand.h
 *
 *  Created on: 10.12.2014
 *      Author: maxi
 */

#ifndef TURINGBAND_H_
#define TURINGBAND_H_

#include <vector>
#include "TuringTypes.h"

struct TuringBandPair{
	TURING_POINTER m_pointer;
	TURING_BAND_DATA m_data;
};

typedef std::vector<TuringBandPair*> TuringBandMap;

class TuringBand {
private:
	TuringBandMap m_band;
	bool m_emty;

public:
	TuringBand();
	~TuringBand();
	TuringBand(TuringBandMap & band, bool emty = true);

public:
	bool isEmty();
	bool isEmty(TURING_POINTER index);
	TURING_BAND_DATA get(TURING_POINTER index);
	void write(TURING_POINTER index, TURING_BAND_DATA value);
	void clear();
	TURING_POINTER getFirst() const;
	TURING_POINTER getLast() const;
	TuringBand * clone();
};

#endif /* TURINGBAND_H_ */
