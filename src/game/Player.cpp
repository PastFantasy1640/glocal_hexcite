#include "Player.hpp"

const std::array<std::string, 4> gh::Player::_player_texture_filename{
	"media/player1.png",
	"media/player2.png",
	"media/player3.png",
	"media/player4.png"
};

const std::array<sf::Vector2f, 4> gh::Player::_player_texture_position{
	sf::Vector2f(16, 18),
	sf::Vector2f(1516, 18),
	sf::Vector2f(16, 558),
	sf::Vector2f(1516, 558)
};

gh::Player::Player(const std::string & name)
	: LayerBase(kMain, sf::Vector2u(391,481)) ,name_(name){}

gh::Player::~Player() {}

bool gh::Player::initialize(const std::shared_ptr<sf::Font>& font, const std::size_t index) {
	this->font_ = font;
	
	bool ret = this->tex_.loadFromFile(this->_player_texture_filename.at(index));
	this->sp_.setTexture(this->tex_);
	this->sp_.setPosition(0, 20);

	this->layer_sprite_.setPosition(this->_player_texture_position.at(index));
	return ret;
}

void gh::Player::drawLayer() {
	this->clearLayer();
	this->draw(this->sp_);
}

void gh::Player::setScore(const int score) {
	this->score_ = score;
}

int gh::Player::getScore(void) const{
	return this->score_;
}
