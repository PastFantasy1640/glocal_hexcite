#pragma once

#ifndef GH_FIELDLAYER_HPP
#define GH_FIELDLAYER_HPP

#include "graphics/LayerBase.hpp"
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "Segment.hpp"

namespace gh {

class FieldLayer : public LayerBase{
public:

	FieldLayer(const std::vector<Segment> & segments);
	~FieldLayer();

	void initialize();
	virtual void drawLayer() override;

private:

	std::array<std::array<sf::Texture, Segment::Type::kAllPartsNum>, 4> parts_tex_;

	FieldLayer() = delete;
	const std::vector<Segment> & segments_;


};

};

#endif