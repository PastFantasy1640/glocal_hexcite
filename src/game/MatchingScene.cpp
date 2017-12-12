#include "MatchingScene.hpp"

#include <memory>
#include "graphics/LayerManager.hpp"
#include "system/Scene.hpp"
#include "GameScene.hpp"

void gh::MatchingScene(std::unique_ptr<Network>&& network) {

	//ñºëOÇ∆Ç©ópà”Ç∑ÇÈÇØÇ«ç°ÇÕÇ¢Ç¢Ç‚

	std::shared_ptr<gh::LayerManager> layer_manager = std::make_shared<gh::LayerManager>(
		sf::Vector2u(1920, 1080),
		sf::Vector2u(1920, 1080),
		"Glocal Hexcite Remake",
		LayerManager::kYPlus,
		sf::Style::Default & ~sf::Style::Resize);

	layer_manager->createWindow();
	layer_manager->setPosition(sf::Vector2i(-8, -31));
	layer_manager->setVerticalSyncEnabled(false);
	layer_manager->setActive(false);

	std::unique_ptr<GameScene> game_scene = std::make_unique<GameScene>(std::move(network));
	game_scene->prepareLayer(layer_manager.get());


	Scene::run(layer_manager, std::move(game_scene));

	
	
	layer_manager->eventLoop();

	Scene::exitGame();

}
