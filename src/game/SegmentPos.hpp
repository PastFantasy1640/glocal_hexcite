#pragma once

#ifndef GH_SEGMENTPOS_HPP
#define GH_SEGMENTPOS_HPP

namespace gh {

class SegmentPos {
public:
	unsigned char s;
	unsigned char e;

	SegmentPos();
	SegmentPos(const unsigned char s, const unsigned char e);
	~SegmentPos();

	unsigned char getWidth(void) const;

private:

};

};

inline gh::SegmentPos::SegmentPos()
	: s(0), e(0){}

inline gh::SegmentPos::SegmentPos(const unsigned char s, const unsigned char e) 
	: s(s), e(e){}

inline gh::SegmentPos:: ~SegmentPos() {}

inline unsigned char gh::SegmentPos::getWidth(void) const {
	return this->e - this->s;
}

#endif