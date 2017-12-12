#include "LayerManager.hpp"
#include <SFML/Window/Sensor.hpp>
#include "Systems/Logger.hpp"
#include <utility>
jubeon::LayerManager::LayerManager(const sf::Vector2u & window_size, const sf::Vector2u & layer_size, const std::string & window_title, const LayoutType & layout_type, const sf::Uint32 & window_style)
	: layout_type_(layout_type),
		window_size_(window_size),
		layer_size_(layer_size),
		window_title_(window_title),
		window_style_(window_style),
		is_initialized_(false),
		is_continue_eventloop_(true)
{
}
/*
#include <thread>
#include <chrono>
*/
bool jubeon::LayerManager::createWindow(){
	//has been initialized?
	if (this->is_initialized_) return true;

	//initialize this window
	if (!this->window_buffer_.create(this->layer_size_.x, this->layer_size_.y)) {
		jubeon::Logger("LayerManager").error("Failed to create the window render buffer.");
		return false;
	}
	this->window_buffer_.clear();
	this->window_buffer_.setSmooth(true);
	this->window_buffer_.setActive(false);

	this->create(sf::VideoMode(this->window_size_.x, this->window_size_.y), this->window_title_, this->window_style_);
	this->is_initialized_ = true;
	
	//window buffer sprite initialize
	//window direction and window buffer matching
	this->window_buffer_sprite_.setTexture(this->window_buffer_.getTexture());
	sf::Vector2f scale(1.0f, 1.0f);
	sf::Vector2u size = this->layer_size_;
	float rotate = 0.0f;
	switch (this->layout_type_){
	case LayoutType::kXPlus:
		std::swap(size.x, size.y);
		rotate = 90.0f;
		break;
	case LayoutType::kXMinus:
		rotate = 180.0f;
		break;
	case LayoutType::kYMinus:
		std::swap(size.x, size.y);
		rotate = 270.0f;
		break;
	default: break;
	}
	scale.x = static_cast<float>(this->window_size_.x) / static_cast<float>(size.x);
	scale.y = static_cast<float>(this->window_size_.y) / static_cast<float>(size.y);
	if (scale.x > scale.y) scale.x = scale.y;	//smallest
	else scale.y = scale.x;

	this->window_buffer_sprite_.setOrigin(static_cast<float>(this->layer_size_.x) / 2.0f, static_cast<float>(this->layer_size_.y) / 2.0f);
	this->window_buffer_sprite_.setPosition(static_cast<float>(this->window_size_.x) / 2.0f, static_cast<float>(this->window_size_.y) / 2.0f);
	this->window_buffer_sprite_.setRotation(rotate);
	this->window_buffer_sprite_.setScale(scale);
	
	return true;
}

void jubeon::LayerManager::addLayer(const std::shared_ptr<jubeon::LayerBase> & layer, const unsigned char layernumber){

	unsigned char i = 0;
	std::list <std::shared_ptr<LayerBase>>::const_iterator p;
	for (p = this->layer_list_.begin(); p != this->layer_list_.end(); p++) {
		//is same type?
		if ((*p)->layer_type_ == layer->layer_type_) {
			if (i == layernumber) break;
			i++;
		}
		else if ((*p)->layer_type_ > layer->layer_type_) break;	//next layer level, latest position
	}

	//insert
	if (!layer->createLayerBuffer()) {
		jubeon::Logger("LayerManager").error("Failed to create the layer buffer.\nThis layer was not added the layers list.");
		return;
	}
	this->layer_list_.insert(p, layer);
}

void jubeon::LayerManager::closeWindow(void){
	this->close();
}

void jubeon::LayerManager::closeAllLayers(void) {
	for (auto p = this->layer_list_.begin(); p != this->layer_list_.end(); ++p) (*p)->setExitCode(1);
	this->is_continue_eventloop_ = false;
}

void jubeon::LayerManager::drawAllLayers(void) {
	//clear window buffer
	this->window_buffer_.clear();
	
	//all layers drawing
	for (auto p = this->layer_list_.rbegin(); p != this->layer_list_.rend(); ++p) {
		(*p)->drawLayer();	//draw
		(*p)->display();//update texture
		this->window_buffer_.draw((*p)->getSprite());
	}

	//remove the stopped layer
	for (auto p = this->layer_list_.begin(); p != this->layer_list_.end(); ) {
		if ((*p)->getExitCode() != 0) p = this->layer_list_.erase(p);
		else p++;
	}
	this->window_buffer_.display();

    this->clear();
	this->draw(this->window_buffer_sprite_);
	this->display();    
}

void jubeon::LayerManager::eventLoop(void)
{
	if (!this->createWindow()) {
		Logger("LayerManager").error("Failed create Layer. Event loop was skipped.");
		return;
	}
	sf::Event e;
	while (this->isOpen() && this->is_continue_eventloop_) {
		if (this->pollEvent(e)) {
			if (e.type == sf::Event::Closed) break;
			if (e.type == sf::Event::KeyPressed && e.key.alt == true && e.key.code == sf::Keyboard::F4) break;

			if (this->event_cb) this->event_cb(e);
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	jubeon::Logger("LayerManager").information("Closed event has been received.");
}

void jubeon::LayerManager::setCallback(Callback function)
{
	std::lock_guard<std::mutex> lock(this->mutex_);
	this->event_cb = function;
}

