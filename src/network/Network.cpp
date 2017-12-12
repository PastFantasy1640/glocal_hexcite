#include "Network.hpp"

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
		this->send(_disconnectJson());
		
		this->tcp_socket_.disconnect();
		this->is_connected_ = false;
	}
}

std::string gh::Network::_disconnectJson(void) {
	return std::string("{\"command\":\"disconnect\"}\r\n");
}



