#pragma once

#ifndef GH_GAMESCENE_HPP
#define GH_GAMESCENE_HPP

#include "system/Scene.hpp"

#include <memory>
#include "game/BackgroundLayer.hpp"
#include "network/Network.hpp"

namespace gh {

class GameScene : public gh::Scene{
public:
	GameScene(std::unique_ptr<Network>&& network);
	~GameScene();

	void prepareLayer(void);

	std::shared_ptr<BackgroundLayer> bg_layer_;

private:
	virtual int update(void) override;

	std::unique_ptr<Network> network_;

};

};

#endif