#pragma once

#ifndef GH_GAMESCENE_HPP
#define GH_GAMESCENE_HPP

#include "system/Scene.hpp"

#include <memory>
#include "game/BackgroundLayer.hpp"
#include "game/HexagonFrameLayer.hpp"
#include "network/Network.hpp"
#include "Player.hpp"
#include "FieldLayer.hpp"

namespace gh {

class GameScene : public gh::Scene{
public:
	GameScene(std::unique_ptr<Network>&& network);
	~GameScene();

	void prepareLayer(LayerManager * layer_manager);
	
	std::shared_ptr<BackgroundLayer> bg_layer_;
	std::shared_ptr<HexagonFrameLayer> hex_layer_;
	std::shared_ptr<Player> player_;
	std::shared_ptr<FieldLayer> field_layer_;


private:
	virtual int update(void) override;

	std::unique_ptr<Network> network_;
	std::vector<Segment> segments_;

};

};

#endif