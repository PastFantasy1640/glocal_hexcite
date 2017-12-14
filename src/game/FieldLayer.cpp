#include "FieldLayer.hpp"

gh::FieldLayer::FieldLayer(const std::vector<Segment>& segments)
	: LayerBase(kMain, sf::Vector2u(870, 909)), segments_(segments){
	this->layer_sprite_.setPosition(960, 540);
	this->layer_sprite_.setOrigin(435, 909.0f / 2.0f);
}

gh::FieldLayer::~FieldLayer() {}

void gh::FieldLayer::initialize() {
	
	for (int i = 0; i < 2; i++) {
		std::string filename = "media/parts_player" + std::to_string(i+1) + ".png";
		this->parts_tex_.at(i).at(Segment::kHexagon).loadFromFile(filename, sf::IntRect(4, 0, 172, 150));
		this->parts_tex_.at(i).at(Segment::kTriangleBig).loadFromFile(filename, sf::IntRect(359, 155, 172, 150));
		this->parts_tex_.at(i).at(Segment::kDiamondBig).loadFromFile(filename, sf::IntRect(548, 0, 172, 300));
		this->parts_tex_.at(i).at(Segment::kTrapezoidBig).loadFromFile(filename, sf::IntRect(5, 155, 344, 150));
		this->parts_tex_.at(i).at(Segment::kTriangleSmall).loadFromFile(filename, sf::IntRect(227, 77, 86, 75));
		this->parts_tex_.at(i).at(Segment::kDiamondSmall).loadFromFile(filename, sf::IntRect(371, 0, 86, 150));
		this->parts_tex_.at(i).at(Segment::kTrapezoidSmall).loadFromFile(filename, sf::IntRect(184, 0, 172, 75));
		for (auto p = this->parts_tex_.at(i).begin(); p != this->parts_tex_.at(i).end(); ++p) p->setSmooth(true);
	}
}

void gh::FieldLayer::drawLayer() {
	this->clearLayer();

	for (auto p = segments_.begin(); p != segments_.end(); ++p) {
		sf::Sprite sp = p->getSprite(this->parts_tex_);
		this->draw(sp);
	}

}

