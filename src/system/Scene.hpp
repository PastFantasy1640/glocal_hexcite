
/** Scene.hpp
 * Refactored in Oct, 2017
 * (c) 2017 white
 */

#pragma once

#ifndef JUBEON_SCENE_HPP_
#define JUBEON_SCENE_HPP_

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include "Graphics/LayerManager.hpp"

namespace jubeon {
class Scene {
public:
	//# constructor and destractor
	Scene() {}
	virtual ~Scene() {};

	//#statical member functions
	static void run(const std::shared_ptr<jubeon::LayerManager> & main_window, std::unique_ptr<Scene> first_scene);
	static void exitGame(void);

protected:
	void setNextScene(std::unique_ptr<Scene> next_scene);
	virtual int update(void) = 0;
	
	jubeon::LayerManager * getMainWindow() { return this->main_window_.get(); }	//never delete
private:
	static std::unique_ptr<Scene> next_scene_;
	static std::unique_ptr<Scene> current_scene_;
	static std::atomic<bool> is_running_process_;
	static std::atomic<bool> is_continue_process_;
	static std::mutex mutex_;
	static void _MainLoop(std::unique_ptr<Scene> first_scene);
	static std::shared_ptr<jubeon::LayerManager> main_window_;
};

};

#endif //JUBEON_SCENE_HPP_

