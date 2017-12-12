#pragma once

#ifndef GH_HEXAGONFRAMELAYER_HPP
#define GH_HEXAGONFRAMELAYER_HPP

#include "graphics/LayerBase.hpp"
#include <SFML/Graphics.hpp>

namespace gh {

class HexagonFrameLayer : public gh::LayerBase {
public:
	
	HexagonFrameLayer();
	~HexagonFrameLayer();

	bool initialize(void);

	virtual void drawLayer()override;

	void toggleFieldVisible();

private:
	sf::Sprite sp_;
	sf::Texture tex_;

	sf::Sprite f_sp_;
	sf::Texture f_tex_;
	bool f_visible;
};

};

#endif // GH_BACKGROUNDLAYER_HPP