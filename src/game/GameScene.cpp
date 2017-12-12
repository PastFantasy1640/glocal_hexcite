#include "GameScene.hpp"

gh::GameScene::GameScene(std::unique_ptr<Network>&& network) 
	: Scene(), network_(std::move(network)), bg_layer_(std::make_unique<BackgroundLayer>()), hex_layer_(std::make_unique<HexagonFrameLayer>()) {}

gh::GameScene::~GameScene() {}

void gh::GameScene::prepareLayer(void) {
	this->bg_layer_->initialize();
	this->hex_layer_->initialize();
}

int gh::GameScene::update(void) {



	return 0;
}
