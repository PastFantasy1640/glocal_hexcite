#include "GameScene.hpp"

gh::GameScene::GameScene(std::unique_ptr<Network>&& network) 
	: Scene(), network_(std::move(network)), 
	bg_layer_(std::make_unique<BackgroundLayer>()), 
	hex_layer_(std::make_unique<HexagonFrameLayer>()) ,
	player_(std::make_unique<Player>("TestPlayer1"))
{}

gh::GameScene::~GameScene() {}

void gh::GameScene::prepareLayer(LayerManager * layer_manager) {
	this->bg_layer_->initialize();
	this->hex_layer_->initialize();

	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
	font->loadFromFile("media/RictyDiminished-Regular.ttf");

	this->player_->initialize(font, 0);


	//ƒŒƒCƒ„[‚Ì’Ç‰Á
	layer_manager->addLayer(this->bg_layer_, 0);
	layer_manager->addLayer(this->hex_layer_, 0);
	layer_manager->addLayer(this->player_, 0);
}

int gh::GameScene::update(void) {



	return 0;
}
