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

	void setRoundScore(const int round_score);
	int getRoundScore(void) const;
	void resetRoundScore(void);

private:
	
	int score_;
	int current_round_score_;

	//TODO:パーツリスト

	sf::Texture tex_;
	sf::Sprite sp_;
	std::shared_ptr<sf::Font> font_;
	sf::Text name_txt_;
	sf::Text score_txt_;
	sf::Text round_score_txt_;
	std::array<sf::Text, 7> parts_txts_;
	sf::Text timer_txt_;
	
	sf::Time time_;

	const static std::array<std::string, 4> _player_texture_filename;
	const static std::array<sf::Vector2f, 4> _player_texture_position;

};

};

#endif // GH_PLAYER_HPP