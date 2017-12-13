#include <iostream>

#include <SFML/Network.hpp>

bool cycle(sf::TcpSocket & socket) {

	char data[512];
	std::size_t received;
	std::string received_data;
	while (socket.receive(data, 512, received) == sf::Socket::Done) {
		//受信成功
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
	std::cout << "テストサーバー" << std::endl;
	std::cout << "ポート番号を入力してください ? ";
	std::cin >> port;

	if (port < 1 && 65535 < port) port = 60000;

	std::cout << "ポート番号" << port << "にてTCP待機します";

	sf::TcpListener listener;

	if (listener.listen(port) != sf::Socket::Done) {
		std::cerr << "エラーが発生しました" << std::endl;
		return 0;
	}

	// accept a new connection
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done) {
		std::cerr << "エラーが発生しました" << std::endl;
		return 0;
	}

	std::cout << "新しいクライアントが接続しました" << std::endl;

	bool keep = true;
	while (keep) {
		keep = cycle(client);
		
	
	}

	return 0;
}
