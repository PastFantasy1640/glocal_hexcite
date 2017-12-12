
/** LayerManager.hpp
 * Refactored in Oct, 2017
 * (c) 2017 white
 */

#pragma once

#ifndef JUBEON_LAYERMANAGER_HPP_
#define JUBEON_LAYERMANAGER_HPP_

#include <functional>
#include <string>
#include <list>
#include <memory>
#include <mutex>
#include <atomic>
#include <SFML/Graphics.hpp>
#include "LayerBase.hpp"

namespace jubeon {
typedef std::function<void(const sf::Event &)> Callback;

class LayerManager : private sf::RenderWindow {
public:

	enum LayoutType {
		kYPlus,
		kXPlus,
		kYMinus,
		kXMinus
	};

	LayerManager(const sf::Vector2u & window_size, const sf::Vector2u & layer_size,	const std::string & window_title, const LayoutType & layout_type, const sf::Uint32 & window_style = sf::Style::None);
		

	virtual ~LayerManager() {}

	bool createWindow();

	void addLayer(const std::shared_ptr<LayerBase> & layer, const unsigned char layernumber);

	void closeWindow(void);

	void drawAllLayers(void);

	void eventLoop(void);
	
	void setCallback(Callback function);

	void closeAllLayers(void);

	//window size. user Variable
	const sf::Vector2u window_size_;

	//layer size. program Fixation
	const sf::Vector2u layer_size_;

	const LayoutType layout_type_;
	const sf::Uint32 window_style_;
	const std::string window_title_;
	
	//using
	using sf::RenderWindow::isOpen;
	using sf::RenderWindow::getSettings;
	using sf::RenderWindow::getPosition;
	using sf::RenderWindow::setPosition;
	using sf::RenderWindow::getSize;
	using sf::RenderWindow::setSize;
	using sf::RenderWindow::setTitle;
	using sf::RenderWindow::setIcon;
	using sf::RenderWindow::setVisible;
	using sf::RenderWindow::setVerticalSyncEnabled;
	using sf::RenderWindow::setMouseCursorVisible;
	using sf::RenderWindow::setFramerateLimit;
	using sf::RenderWindow::setActive;

private:
	LayerManager() = delete;
	LayerManager(const LayerManager & copy) = delete;
	
	std::list<std::shared_ptr<LayerBase>> layer_list_;
	sf::RenderTexture window_buffer_;
	std::mutex mutex_;

	Callback event_cb;

	bool is_initialized_;
	sf::Sprite window_buffer_sprite_;
	
	std::atomic<bool> is_continue_eventloop_;
};

}; //namespace jubeon

#endif //JUBEON_LAYERMANAGER_HPP_
