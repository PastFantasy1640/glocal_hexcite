#pragma once

#ifndef GH_PLAYER_HPP
#define GH_PLAYER_HPP

#include <string>
#include <memory>
#include "graphics/LayerBase.hpp"
#include <SFML/Graphics.hpp>
#include <array>


namespace gh {

class Player : public LayerBase{
public:
	const std::string name_;

	Player(const std::string & name);
	~Player();

	bool initialize(const std::shared_ptr<sf::Font> & font, const std::size_t index);

	virtual void drawLayer()override;


	void setScore(const int score);
	int getScore(void) const;

private:
	
	int score_;

	//TODO:パーツリスト

	sf::Texture tex_;
	sf::Sprite sp_;
	std::shared_ptr<sf::Font> font_;
	
	const static std::array<std::string, 4> _player_texture_filename;
	const static std::array<sf::Vector2f, 4> _player_texture_position;

};

};

#endif // GH_PLAYER_HPP