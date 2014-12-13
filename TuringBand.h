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
	void copyMap(TuringBandMap const & band);

public:
	TuringBand();
	~TuringBand();
	TuringBand(TuringBandMap & band);

public:
	TURING_BAND_DATA get(TURING_POINTER index);
	void write(TURING_POINTER index, TURING_BAND_DATA value);
	void clear();
	TURING_POINTER getFirst() const;
	TURING_POINTER getLast() const;
	TuringBand * clone();

public:
	void operator =(const TuringBand & band);
};

#endif /* TURINGBAND_H_ */
