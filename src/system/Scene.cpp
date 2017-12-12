#include "Scene.hpp"
#include "Logger.hpp"

std::atomic<bool> jubeon::Scene::is_running_process_ = false;
std::atomic<bool> jubeon::Scene::is_continue_process_ = true;
std::mutex jubeon::Scene::mutex_;
std::unique_ptr<jubeon::Scene> jubeon::Scene::next_scene_;
std::unique_ptr<jubeon::Scene> jubeon::Scene::current_scene_;
std::shared_ptr<jubeon::LayerManager> jubeon::Scene::main_window_;

void jubeon::Scene::run(const std::shared_ptr<jubeon::LayerManager> & main_window, std::unique_ptr<Scene> first_scene) {

	if (main_window == nullptr) {
		Logger("Scene").error("Main window was nullptr.");
		return;
	}
	if (!first_scene) {
		Logger("Scene").error("First scene was empty.");
		return;
	}

	Scene::main_window_ = main_window;
	if (!Scene::main_window_->createWindow()) {
		//Failed to create window
		Logger("Scene").error("Failed to create window. This system will shutdown.");
		return;
	}
	std::thread thread(&Scene::_MainLoop, std::move(first_scene));
	//first_scene has gone away...
	thread.detach();
}

void jubeon::Scene::exitGame() {
	Scene::is_continue_process_ = false;

	//waiting for exit processing loop
	while (Scene::is_running_process_) std::this_thread::sleep_for(std::chrono::microseconds(1));
	Scene::main_window_->closeWindow();
}

void jubeon::Scene::setNextScene(std::unique_ptr<Scene> next_scene){
	std::lock_guard<std::mutex> lock(this->mutex_);
	this->next_scene_ = (std::move(next_scene));
}

void jubeon::Scene::_MainLoop(std::unique_ptr<Scene> first_scene)
{
	if (!Scene::is_running_process_) {
		Scene::is_running_process_ = true;
		Scene::is_continue_process_ = true;

        Logger("Scene").information("Start to scene main loop.");
		Scene::current_scene_ = std::move(first_scene);
		
		int ret = 0;	//return status.
		while (ret == 0 && Scene::current_scene_ && Scene::is_continue_process_) {

			//updates
			ret = Scene::current_scene_->update();
			Scene::main_window_->drawAllLayers();

			//is going next scene?
			if (Scene::next_scene_) {
				Scene::current_scene_ = std::move(Scene::next_scene_);	//ƒV[ƒ“‚ðˆÚ‚·
                Logger("Scene").information("Move to next scene.");
			}
		}

        Logger("Scene").information("Closing the scene process.");
		//Scene::main_window_->closeWindow();
		Scene::main_window_->closeAllLayers();
		Scene::is_running_process_ = false;
	}
}