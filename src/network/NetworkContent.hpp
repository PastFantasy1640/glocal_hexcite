#pragma once

#ifndef GH_NETWORKCONTENT_HPP
#define GH_NETWORKCONTENT_HPP

#include <string>
#include <memory>
#include <mutex>

namespace gh {

class NetworkContent {
public:
	enum Type {
		kQuestion,
		kAnswer,
		kNotification
	};

	const std::string content_;

	NetworkContent(const std::string & content, const Type type = kNotification);
	NetworkContent(const std::string & content, std::unique_ptr<NetworkContent>&& responce, const Type type = kAnswer);
	~NetworkContent();

	const std::unique_ptr<NetworkContent> responce_to_;	//Ž¿–â‚É‘Î‚·‚é•Ô“š‚ðŠi”[‚·‚é

private:

};

};

#endif