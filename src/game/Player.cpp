#include "Player.hpp"
#include <cstdio>

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
	: LayerBase(kMain, sf::Vector2u(391,481)) ,name_(name), score_(0), current_round_score_(0){}

gh::Player::~Player() {}

bool gh::Player::initialize(const std::shared_ptr<sf::Font>& font, const std::size_t index) {
	this->font_ = font;
	
	bool ret = this->tex_.loadFromFile(this->_player_texture_filename.at(index));
	this->sp_.setTexture(this->tex_);
	this->sp_.setPosition(0, 20);

	this->layer_sprite_.setPosition(this->_player_texture_position.at(index));
	
	this->name_txt_.setFont(*this->font_);
	this->name_txt_.setColor(sf::Color::White);
	
	//score_text
	this->name_txt_.setCharacterSize(40);
	this->score_txt_ = this->name_txt_;
	this->score_txt_.setString("0");
	this->score_txt_.setPosition(211, 110-42);
	this->round_score_txt_ = this->name_txt_;
	this->round_score_txt_.setString("0");
	this->round_score_txt_.setPosition(211, 156-42);
	
	//timer_text
	this->timer_txt_ = this->name_txt_;
	this->timer_txt_.setString("-.-sec");
	this->timer_txt_.setPosition(233, 467-42);

	//parts_text
	this->name_txt_.setCharacterSize(27);
	for (auto p = this->parts_txts_.begin(); p != this->parts_txts_.end(); ++p) {
		*p = this->name_txt_;
		p->setString("0"); //TEMPORARY
	}
	this->parts_txts_.at(0).setPosition(139, 251-42);
	this->parts_txts_.at(1).setPosition(139, 306-42);
	this->parts_txts_.at(2).setPosition(274, 306-42);
	this->parts_txts_.at(3).setPosition(139, 361-42);
	this->parts_txts_.at(4).setPosition(274, 361-42);
	this->parts_txts_.at(5).setPosition(139, 416-42);
	this->parts_txts_.at(6).setPosition(274, 416-42);

	//name_text
	this->name_txt_.setString(this->name_);
	this->name_txt_.setCharacterSize(40);
	this->name_txt_.setPosition(391 - this->name_txt_.getGlobalBounds().width, 0);

	return ret;
}

void gh::Player::drawLayer() {
	this->clearLayer();
	this->draw(this->sp_);

	//名前、スコアなどを表示
	const unsigned int y = 380;
	this->score_txt_.setString(std::to_string(this->score_));
	this->score_txt_.setPosition(y - this->score_txt_.getGlobalBounds().width, this->score_txt_.getPosition().y);
	this->round_score_txt_.setString(std::to_string(this->current_round_score_));
	this->round_score_txt_.setPosition(y - this->round_score_txt_.getGlobalBounds().width, this->round_score_txt_.getPosition().y);

	char dst[32];
	std::sprintf(dst, "%.1fsec", this->time_.asSeconds());

	this->timer_txt_.setString(std::string(dst));
	this->timer_txt_.setPosition(y - this->timer_txt_.getGlobalBounds().width, this->timer_txt_.getPosition().y);
	//for (auto p = this->parts_txts_.begin(); p != this->parts_txts_.end(); ++p) this->draw(*p);

	this->draw(this->name_txt_);
	this->draw(this->score_txt_);
	this->draw(this->round_score_txt_);
	this->draw(this->timer_txt_);
	for (auto p = this->parts_txts_.begin(); p != this->parts_txts_.end(); ++p) this->draw(*p);
}

void gh::Player::setScore(const int score) {
	this->score_ = score;
}

int gh::Player::getScore(void) const{
	return this->score_;
}

void gh::Player::setRoundScore(const int round_score) {
	this->current_round_score_ = round_score;
}

int gh::Player::getRoundScore(void) const {
	return this->current_round_score_;
}

void gh::Player::resetRoundScore(void) {
	this->setRoundScore(0);
}
