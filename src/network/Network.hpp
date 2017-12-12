#pragma once

#ifndef GH_NETWORK_HPP
#define GH_NETWORK_HPP

#include <string>
#include <memory>
#include <list>
#include <mutex>
#include "NetworkContent.hpp"

namespace gh {

class Network {
public:
	const std::string hostname_;
	const unsigned int port_;

	Network(const std::string & hostname, const unsigned int port);
	~Network();

	bool connect();
	void disconnect();
	bool isConnected() const;

	void send(std::unique_ptr<NetworkContent>&& content);
	std::unique_ptr<NetworkContent> pop(void);

private:
	std::mutex mutex_;

	std::list<std::unique_ptr<NetworkContent>> queue_;
	bool is_connected_;
	bool is_keeping_connected_;
};

};

#endif
