#include "BackgroundLayer.hpp"

gh::BackgroundLayer::BackgroundLayer()
	: LayerBase(LayerType::kBackground, sf::Vector2u(1920,1080)){
	this->background_tex_.setSmooth(true);
	this->background_sp_.setTexture(this->background_tex_);
	this->background_sp_.setPosition(0, 0);
}

gh::BackgroundLayer::~BackgroundLayer() {}

bool gh::BackgroundLayer::initialize(void) {
	bool ret = true;

	ret &= this->background_tex_.loadFromFile("media/background.png");

	return ret;
}

void gh::BackgroundLayer::drawLayer() {
	this->clearLayer();
	this->draw(this->background_sp_);
}

