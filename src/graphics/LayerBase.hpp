
/** LayerBase.hpp
 * Refactored in Oct, 2017
 * (c) 2017 white
 */

#pragma once

#ifndef GH_LAYERBASE_HPP_
#define GH_LAYERBASE_HPP_

#include <SFML/Graphics.hpp>
#include <atomic>
#include "system/Logger.hpp"

namespace gh {

class LayerBase : public sf::RenderTexture {
public:
	
	enum LayerType {
		kSystem = 0,
		kForeground,
		kMain,
		kBackground
	};

	virtual void drawLayer() = 0;
	
	virtual ~LayerBase();

	bool createLayerBuffer(void);
	int getExitCode(void) const;
	void setExitCode(const int code);
	const sf::Sprite & getSprite(void) const;

	const LayerType layer_type_;
	const sf::Vector2u layer_size_;

private:
	LayerBase() = delete;
	explicit LayerBase(const LayerBase & copy) = delete;

	bool is_create_buffer_;
	std::atomic<int> exit_code_;

protected:
	LayerBase(const LayerType layer_type, const sf::Vector2u layer_size);

	void clearLayer(void);

	sf::Sprite layer_sprite_;

};	//class LayerBase
};//namespace gh


//### inline functions ###
inline int gh::LayerBase::getExitCode(void) const {
	return this->exit_code_;
}

inline void gh::LayerBase::setExitCode(const int code) {
	this->exit_code_ = code;
	gh::Logger("LayerBase").information("This Layer's exit code has been changed to " + std::to_string(this->exit_code_) + ".");
}

inline const sf::Sprite & gh::LayerBase::getSprite(void) const {
	return this->layer_sprite_;
}

inline void gh::LayerBase::clearLayer(void) {
	this->clear(sf::Color(0, 0, 0, 0));
}

#endif	//GH_LAYERBASE_HPP_
