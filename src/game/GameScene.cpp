#include "GameScene.hpp"

gh::GameScene::GameScene(std::unique_ptr<Network>&& network) 
	:network(std::move(network)) {}

gh::GameScene::~GameScene() {}

void gh::GameScene::prepareLayerTh(void) {
	
}

int gh::GameScene::update(void) {
	return 0;
}
