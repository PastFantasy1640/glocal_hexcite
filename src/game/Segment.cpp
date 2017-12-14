#include "Segment.hpp"
#include <cmath>

sf::Sprite gh::Segment::getSprite(const std::array<std::array<sf::Texture, Segment::Type::kAllPartsNum>, 4> & textures) const{
	sf::Sprite ret;

	//b.s‚Ær.s‚ÌŒð“_‚Æb.s‚Æg.s‚ÌŒð“_‚Ì·(g‚Å”äŠrj
	unsigned char sss = std::abs(this->getIntersectionPointBR(b.s, r.s) - g.s);

	//b.s‚Ær.e‚ÌŒð“_‚Æb.s‚Æg.e‚ÌŒð“_‚Ì·
	unsigned char ees = std::abs(this->getIntersectionPointBR(b.s, r.e) - g.e);

	int idx = -1;
	switch (sss) {
	case 0:
		switch (ees) {
		case 0:	idx = 0; break;
		case 1: idx = 2; break;
		case 2: idx = 7; break;
		}
		break;
	case 1:
		switch (ees) {
		case 0: idx = 4; break;
		case 1: idx = 3; break;
		case 2: idx = 5; break;
		}
		break;
	case 2:
		switch (ees) {
		case 0: idx = 9; break;
		case 1: idx = 1; break;
		case 2: idx = 8; break;
		case 4: idx = 10; break;
		}
		break;
	}

	if (idx == -1) {
		abort();	//DEBUG
	}

	//‰ñ“]Šp“x
	int index = (idx % 6 + idx / 6); //0 - 5

	if (t == kDiamondBig || t == kDiamondSmall) {
		if (index == 2) index = 4;
		else if (index == 4) index = 2;
	}

	ret.setRotation(index * 60.0f);
	char c_r, c_b;
	switch (index) {
	case 0:
		c_r = r.s;
		c_b = this->getIntersectionPointRG(r.s, g.e);
		break;
	case 1:
		c_r = r.e;
		c_b = b.e;
		break;
	case 2:
		c_r = this->getIntersectionPointGB(g.e, b.s);
		c_b = b.s;
		break;
	case 3:
		c_r = r.e;
		c_b = this->getIntersectionPointRG(r.e, g.s);
		break;
	case 4:
		c_r = r.s;
		c_b = b.s;
		break;
	case 5:
		c_r = this->getIntersectionPointGB(g.s, b.e);
		c_b = b.e;
		break;
	}

	ret.setTexture(textures.at(color_no).at(t));
	switch (t) {
	case kHexagon:
	case kTrapezoidSmall:
		ret.setOrigin(ret.getTextureRect().width / 2.0f, -75);
		break;
	case kDiamondSmall:
	case kDiamondBig:
		ret.setRotation(ret.getRotation());
	case kTriangleSmall:
	case kTriangleBig:
		ret.setOrigin(ret.getTextureRect().width / 2.0f, 0);
		break;
	case kTrapezoidBig:
		ret.setOrigin(ret.getTextureRect().width / 2.0f, -150);
		break;
	}

	ret.setPosition((450 - 50 * c_r - 25 * c_b) * 1.7320508f, 75 * c_b - 450.0f);
	ret.setPosition(435 - ret.getPosition().x, 909.0f / 2.0f - ret.getPosition().y);

	return ret;
}
