#include "MatchingScene.hpp"

#include <memory>
#include "graphics/LayerManager.hpp"
#include "system/Scene.hpp"
#include "GameScene.hpp"
#include <iostream>

void gh::MatchingScene(std::unique_ptr<Network>&& network) {

	//ñºëOÇ∆Ç©ópà”Ç∑ÇÈÇØÇ«ç°ÇÕÇ¢Ç¢Ç‚
	std::unique_ptr<Network> net = std::move(network);

	std::string name;
	do {
		do {
			std::cout << "namae wo nyuuryoku site kudasai (\"E\" de exit) ? ";
			std::cin >> name;
			if (name == "E") return;
			if (name.size() >= 2 && name.size() <= 12) break;
			std::cout << "2 ~ 12mozi inaide siteisite kudasai" << std::endl;
		} while (1);

		std::cout << name << "de touroku simasu" << std::endl;
		
		std::unique_ptr<wlib::Json> retjson = net->send(std::string("{\"name\" : \"") + name + std::string("\"}"));
		if (retjson) {
			if ((*retjson)["result"].str("-NG") == "+OK") {
				name = (*retjson)["name"].str("default");
				break;
			}
		}
		std::cout << "server kara error ga kaesare masita." << std::endl;
	} while (1);



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
