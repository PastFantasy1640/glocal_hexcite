#pragma once

#ifndef GH_MATCHINGSCENE_HPP
#define GH_MATCHINGSCENE_HPP

#include <memory>
#include "network/Network.hpp"

namespace gh {

extern void MatchingScene(std::unique_ptr<Network>&& network);

};

#endif // GH_MATCHINGSCENE_HPP