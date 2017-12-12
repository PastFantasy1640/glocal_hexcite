#pragma once

#ifndef GH_BACKGROUNDLAYER_HPP
#define GH_BACKGROUNDLAYER_HPP

#include "graphics/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace gh {

class BackgroundLayer : public gh::LayerBase {
public:
	
	BackgroundLayer();
	~BackgroundLayer();

	bool initialize(void);

	virtual void drawLayer()override;

private:
	sf::Sprite background_sp_;
	sf::Texture background_tex_;
};

};

#endif // GH_BACKGROUNDLAYER_HPP