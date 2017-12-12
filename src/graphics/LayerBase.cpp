#include "LayerBase.hpp"

gh::LayerBase::~LayerBase()
{
}

gh::LayerBase::LayerBase(const LayerType layer_type, const sf::Vector2u layer_size)
	: sf::RenderTexture(), layer_size_(layer_size), layer_type_(layer_type_), is_create_buffer_(false), exit_code_(0)
{
}

bool gh::LayerBase::createLayerBuffer(){
	if (!this->is_create_buffer_) {
		if (!this->create(this->layer_size_.x, this->layer_size_.y)) {
			//Failed to create layer
			gh::Logger("LayerBase").error("Failed to create a layer.");
			return false;
		}
		this->setActive(false);
		this->setSmooth(true);
		this->layer_sprite_.setTexture(this->getTexture());
		this->is_create_buffer_ = true;
	}
	return true;
}

