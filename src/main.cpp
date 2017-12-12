#include <iostream>

#include "game/SprashScreens.hpp"
#include "network/Network.hpp"

int main(void) {
	gh::drawSprashScreen();

	bool is_online = true;

	std::cout << std::endl;
	std::cout << "�I�����C���ŗV�т܂����H�I�t���C���ŗV�т܂����H" << std::endl;
	std::cout << "�I�����C��:1 / �I�t���C��:2 / �I��:0 ? 1" << std::endl;
	std::cout << "�i���݃I�t���C���͖������Ȃ��߁A�����I�ɃI�����C����I�����Ă��܂��j" << std::endl;

	if (is_online) {
		std::unique_ptr<gh::Network> network = gh::Network::setupOnline();
		if (network) {
			//����
			
		}
	}


	return 0;
}