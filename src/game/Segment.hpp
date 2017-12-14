#pragma once

#ifndef GH_SEGMENT_HPP
#define GH_SEGMENT_HPP

#include "SegmentPos.hpp"
#include <array>
#include <SFML/Graphics.hpp>

namespace gh {

class Segment {
public:

	enum Type : size_t{
		kTriangleSmall = 0,
		kTriangleBig,
		kDiamondSmall,
		kDiamondBig,
		kTrapezoidSmall,
		kTrapezoidBig,
		kHexagon,
		kAllPartsNum
	};


	Segment(const Type t, const SegmentPos & r, const SegmentPos & g, const SegmentPos & b, const size_t color_no);
	~Segment();

	const Type t;
	const SegmentPos r;
	const SegmentPos g;
	const SegmentPos b;
	const size_t color_no;

	sf::Sprite getSprite(const std::array<std::array<sf::Texture, Segment::Type::kAllPartsNum>, 4> & textures) const;
	
	static char getIntersectionPointRG(const unsigned char r, const unsigned char g);
	static char getIntersectionPointGB(const unsigned char g, const unsigned char b);
	static char getIntersectionPointBR(const unsigned char b, const unsigned char r);

private:
	Segment() = delete;



};

};

inline gh::Segment::Segment(const Type t, const SegmentPos & r, const SegmentPos & g, const SegmentPos & b, const size_t color_no)
	: t(t),r(r),g(g),b(b), color_no(color_no) {}

inline gh::Segment::~Segment() {}

inline char gh::Segment::getIntersectionPointRG(const unsigned char r, const unsigned char g){
	return (g - r + 6);
}

inline char gh::Segment::getIntersectionPointGB(const unsigned char g, const unsigned char b) {
	return (g - b + 6);
}

inline char gh::Segment::getIntersectionPointBR(const unsigned char b, const unsigned char r) {
	return (r + b - 6);
}

#endif