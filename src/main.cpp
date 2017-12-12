#include <iostream>

#include "game/SprashScreens.hpp"
#include "network/Network.hpp"

int main(void) {
	gh::drawSprashScreen();

	bool is_online = true;

	std::cout << std::endl;
	std::cout << "オンラインで遊びますか？オフラインで遊びますか？" << std::endl;
	std::cout << "オンライン:1 / オフライン:2 / 終了:0 ? 1" << std::endl;
	std::cout << "（現在オフラインは未実装なため、強制的にオンラインを選択しています）" << std::endl;

	if (is_online) {
		std::unique_ptr<gh::Network> network = gh::Network::setupOnline();
		if (network) {
			//成功
			
		}
	}


	return 0;
}