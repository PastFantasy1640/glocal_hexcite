#include "GameScene.hpp"

gh::GameScene::GameScene(std::unique_ptr<Network>&& network) 
	:network_(std::move(network)), bg_layer_(std::make_unique<BackgroundLayer>()) {}

gh::GameScene::~GameScene() {}

void gh::GameScene::prepareLayer(void) {
	this->bg_layer_->initialize();
	
	//ƒŒƒCƒ„[‚Ì’Ç‰Á
	this->getMainWindow()->addLayer(this->bg_layer_, 0);
}

int gh::GameScene::update(void) {



	return 0;
}
