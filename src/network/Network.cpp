#include "Network.hpp"
#include <iostream>

gh::Network::Network(const std::string & hostname, const unsigned short port)
	: hostname_(hostname), port_(port) ,tcp_socket_(), is_connected_(false){}

gh::Network::~Network() {}

bool gh::Network::connect(const sf::Time & timeout) {
	sf::Socket::Status status = this->tcp_socket_.connect(sf::IpAddress(this->hostname_), this->port_, timeout);

	if (status == sf::Socket::Status::Done) {
		this->is_connected_ = true;
	}

	return this->is_connected_;
}

void gh::Network::disconnect() {
	if (this->is_connected_) {
		std::unique_ptr<wlib::Json> ret;
		do {
			ret = this->send(_disconnectJson());
		} while (!ret);

		this->tcp_socket_.disconnect();
		this->is_connected_ = false;
	}
}

std::unique_ptr<wlib::Json> gh::Network::send(std::string & content){
	std::unique_ptr<wlib::Json> ret;

	if (this->is_connected_) {
		sf::Socket::Status status = this->tcp_socket_.send(content.c_str(), content.size());
		if (status == sf::Socket::Done) {
			char data[256];
			std::size_t received;
			std::string received_data;
			while (this->tcp_socket_.receive(data, 256, received) == sf::Socket::Done) {
				//��M����
				received_data += std::string(data).substr(0, received);
				if (received_data.size() > 2) {
					if (*(received_data.rbegin() + 1) == '\r' && *received_data.rbegin() == '\n') {
						//FOR DEBUG
						std::cout << "RECEIVED : " << received_data << std::endl;
						ret = std::make_unique<wlib::Json>(received_data.substr(0, received_data.size() - 2));
						break;
					}
				}
			}
		}
	}

	return ret;
}

std::unique_ptr<gh::Network> gh::Network::setupOnline(void) {
	std::string ipaddress;
	unsigned short port = 0;
	std::unique_ptr<Network> ret;
	int status = 0;

	do {
		std::cout << "�ڑ����IP�A�h���X����͂��Ă������� ? ";
		std::cin >> ipaddress;
		std::cout << "�ڑ�����|�[�g�ԍ����w�肵�Ă�������(1-65535, �f�t�H���g��60000) ? ";
		std::cin >> port;

		if (port < 1 || 65535 < port) port = 60000;

		std::cout << std::endl << "IP:" << ipaddress << " port:" << port << "�֐ڑ���..." << std::endl;
		
		status = 0;
		ret = std::make_unique<Network>(ipaddress, port);
		while (!ret->connect(sf::milliseconds(1000))) {
			std::cout << "�ڑ��Ɏ��s�������A�^�C���A�E�g���܂����B" << std::endl;
			std::cout << "������x�g���C����ꍇ��1�A�I������ꍇ��0�A�ݒ��ς��ă��g���C����ꍇ��2������ȊO����͂��Ă������� ? ";
			std::cin >> status;
			if (status != 1) break;
			std::cout << std::endl << "IP:" << ipaddress << " port:" << port << "�֐ڑ���..." << std::endl;
		}
	} while (status != 0);

	if (ret->isConnected()){
		std::cout << "�ڑ��ɐ������܂����B" << std::endl;
	}
	else {
		//ret.release();
	}

	return ret;
}

std::string gh::Network::_disconnectJson(void) {
	return std::string("{\"command\":\"disconnect\"}\r\n");
}



