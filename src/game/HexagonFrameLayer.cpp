#include "HexagonFrameLayer.hpp"

gh::HexagonFrameLayer::HexagonFrameLayer()
	: LayerBase(LayerType::kForeground, sf::Vector2u(870, 909)), f_visible(false)
{
	this->tex_.setSmooth(true);
	this->tex_.setSmooth(true);
	this->sp_.setPosition(0, 0);
	this->f_sp_.setPosition(0, 0);
	this->layer_sprite_.setPosition(960, 540);
	this->layer_sprite_.setOrigin(435, 454.5);
}

gh::HexagonFrameLayer::~HexagonFrameLayer()
{
}

bool gh::HexagonFrameLayer::initialize(void) {
	bool ret = true;

	ret &= this->tex_.loadFromFile("media/field_outline.png");
	ret &= this->f_tex_.loadFromFile("media/field.png");
	
	this->sp_.setTexture(this->tex_);
	this->f_sp_.setTexture(this->f_tex_);
	return ret;
}

void gh::HexagonFrameLayer::drawLayer() {
	this->clearLayer();
	if(this->f_visible) this->draw(this->f_sp_);
	this->draw(this->sp_);
}

void gh::HexagonFrameLayer::toggleFieldVisible() {
	this->f_visible = !this->f_visible;
}



