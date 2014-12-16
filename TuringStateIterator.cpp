/*
 * TuringStateIterator.cpp
 *
 *  Created on: 16.12.2014
 *      Author: maxi
 */

#include "TuringStateIterator.h"
#include "TuringState.h"

TuringStateIterator::TuringStateIterator() {
	m_pointer = 0;
}

TuringStateIterator::TuringStateIterator(TuringState* pointer) {
	m_pointer = pointer;
}

TuringStateIterator::~TuringStateIterator() {
}

TuringState* TuringStateIterator::operator *(void) {
	return m_pointer;
}

TuringStateHIterator::TuringStateHIterator() : TuringStateIterator() {
}

TuringStateHIterator::TuringStateHIterator(
		TuringState* pointer) : TuringStateIterator(pointer) {
}

TuringStateHIterator::~TuringStateHIterator() {
}

const TuringState* TuringStateHIterator::operator ++(void) {
	if (m_pointer)
		m_pointer = m_pointer->m_brother_left;
	return m_pointer;
}

const TuringState* TuringStateHIterator::operator ++(int) {
	const TuringState * buffer = m_pointer;
	if (m_pointer)
		m_pointer = m_pointer->m_brother_left;
	return buffer;
}

const TuringState* TuringStateHIterator::operator --(void) {
	if (m_pointer)
		m_pointer = m_pointer->m_brother_right;
	return m_pointer;
}

const TuringState* TuringStateHIterator::operator --(int) {
	const TuringState * buffer = m_pointer;
	if (m_pointer)
		m_pointer = m_pointer->m_brother_right;
	return buffer;
}

TuringStateVIterator::TuringStateVIterator() : TuringStateIterator() {
}

TuringStateVIterator::TuringStateVIterator(
		TuringState* pointer)  : TuringStateIterator(pointer) {
}

TuringStateVIterator::~TuringStateVIterator() {
}

const TuringState* TuringStateVIterator::operator ++(void) {
	if (m_pointer)
		m_pointer = m_pointer->m_child_right;
	return m_pointer;
}

const TuringState* TuringStateVIterator::operator ++(int) {
	const TuringState * buffer = m_pointer;
	if (m_pointer)
		m_pointer = m_pointer->m_child_right;
	return buffer;
}

const TuringState* TuringStateVIterator::operator --(void) {
	if (m_pointer)
		m_pointer = m_pointer->m_parent;
	return m_pointer;
}

const TuringState* TuringStateVIterator::operator --(int int1) {
	const TuringState * buffer = m_pointer;
	if (m_pointer)
		m_pointer = m_pointer->m_parent;
	return buffer;
}
