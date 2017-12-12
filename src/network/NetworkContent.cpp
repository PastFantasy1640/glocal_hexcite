#include "NetworkContent.hpp"

gh::NetworkContent::NetworkContent(const std::string & content, const Type type)
	: content_(content), responce_to_(nullptr), type_(type)
{
}

gh::NetworkContent::NetworkContent(const std::string & content, std::unique_ptr<NetworkContent>&& responce, const Type type)
	: content_(content), responce_to_(std::move(responce)), type_(type)
{
}

gh::NetworkContent::~NetworkContent()
{
}
