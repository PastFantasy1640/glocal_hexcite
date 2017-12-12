#pragma once

#ifndef GH_GAMESCENE_HPP
#define GH_GAMESCENE_HPP

#include "system/Scene.hpp"

#include <memory>
#include "network/Network.hpp"

namespace gh {

class GameScene : public gh::Scene{
public:
	GameScene(std::unique_ptr<Network>&& network);
	~GameScene();

	void prepareLayerTh(void);

private:
	virtual int update(void) override;

	std::unique_ptr<Network> network;


};

};

#endif