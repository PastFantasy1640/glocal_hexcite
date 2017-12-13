#pragma once

#ifndef GH_NETWORK_HPP
#define GH_NETWORK_HPP

#include <string>
#include <memory>
#include <list>
#include <mutex>
#include <thread>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "system/wlib_Json.hpp"

namespace gh {

class Network {
public:
	const std::string hostname_;
	const unsigned int port_;

	Network(const std::string & hostname, const unsigned short port);
	~Network();

	bool connect(const sf::Time & timeout = sf::Time::Zero);
	void disconnect();
	bool isConnected() const;

	std::unique_ptr<wlib::Json> send(const std::string & content);
	
	static std::unique_ptr<Network> setupOnline(void);
private:
	
	sf::TcpSocket tcp_socket_;

	std::unique_ptr<std::thread> thread_;

	std::mutex mutex_;

	bool is_connected_;

	static std::string _disconnectJson(void);

};

};

inline bool gh::Network::isConnected() const{
	return this->is_connected_;
}

#endif
