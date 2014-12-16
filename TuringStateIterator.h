/*
 * TuringStateIterator.h
 *
 *  Created on: 16.12.2014
 *      Author: maxi
 */

#ifndef TURINGSTATEITERATOR_H_
#define TURINGSTATEITERATOR_H_

class TuringState;

class TuringStateIterator {
protected:
	TuringState * m_pointer;

public:
	TuringStateIterator();
	TuringStateIterator(TuringState * pointer);
	virtual ~TuringStateIterator();
	virtual const TuringState * operator++(void) = 0;
	virtual const TuringState * operator++(int) = 0;
	virtual const TuringState * operator--(void) = 0;
	virtual const TuringState * operator--(int) = 0;
	virtual TuringState * operator*(void);
};

class TuringStateHIterator : virtual public TuringStateIterator{
public:
	TuringStateHIterator();
	TuringStateHIterator(TuringState * pointer);
	~TuringStateHIterator();
	virtual const TuringState * operator++(void);
	virtual const TuringState * operator++(int);
	virtual const TuringState * operator--(void);
	virtual const TuringState * operator--(int);
};

class TuringStateVIterator : virtual public TuringStateIterator{
private:
	// UP_RIGHT is default.
	enum{
		UP_LEFT,
		UP_RIGHT,
	} m_up_direction;

public:
	TuringStateVIterator();
	TuringStateVIterator(TuringState * pointer);
	~TuringStateVIterator();
	virtual const TuringState * operator++(void);
	virtual const TuringState * operator++(int);
	virtual const TuringState * operator--(void);
	virtual const TuringState * operator--(int);

public:
	void setUpLeft();
	void setUpRight();
};


#endif /* TURINGSTATEITERATOR_H_ */
