#include <iostream>

#include <SFML/Network.hpp>

bool cycle(sf::TcpSocket & socket) {

	char data[512];
	std::size_t received;
	std::string received_data;
	while (socket.receive(data, 512, received) == sf::Socket::Done) {
		//��M����
		received_data += std::string(data).substr(0, received);
		if (received_data.size() > 2) {
			if (*(received_data.rbegin() + 1) == '\r' && *received_data.rbegin() == '\n') {
				//FOR DEBUG
				std::cout << "RECEIVED : " << received_data.substr(0,received_data.size() - 2) << std::endl;
				break;
			}
		}
	}

	if (received_data.empty()) {
		std::cout << "Exit" << std::endl;
		return false;
	}

	std::string responce;
	std::cout << "RESPONCE ? ";
	std::cin >> responce;
	responce += "\r\n";

	sf::Socket::Status status = socket.send(responce.c_str(), responce.size());
	if (status != sf::Socket::Done) {
		return false;
	}

	return true;

}

int main(void) {
	unsigned short port = 0;
	std::cout << "�e�X�g�T�[�o�[" << std::endl;
	std::cout << "�|�[�g�ԍ�����͂��Ă������� ? ";
	std::cin >> port;

	if (port < 1 && 65535 < port) port = 60000;

	std::cout << "�|�[�g�ԍ�" << port << "�ɂ�TCP�ҋ@���܂�";

	sf::TcpListener listener;

	if (listener.listen(port) != sf::Socket::Done) {
		std::cerr << "�G���[���������܂���" << std::endl;
		return 0;
	}

	// accept a new connection
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done) {
		std::cerr << "�G���[���������܂���" << std::endl;
		return 0;
	}

	std::cout << "�V�����N���C�A���g���ڑ����܂���" << std::endl;

	bool keep = true;
	while (keep) {
		keep = cycle(client);
		
	
	}

	return 0;
}
