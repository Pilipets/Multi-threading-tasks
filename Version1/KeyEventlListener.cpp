#include "EventListener.h"

namespace lab1 {
	KeyEventListener::KeyEventListener() :
		BaseEventListener(), is_running(false)
	{}
	KeyEventListener::~KeyEventListener() {
		if (is_running) {
			is_running = false;
			additional_thread.join();
		}
	}
	void KeyEventListener::StartAsync()
	{
		if (!is_running) {
			additional_thread = std::thread(&KeyEventListener::StartListening, this);
		}
	}
	void KeyEventListener::StartListening()
	{
		is_running = true;
		BaseEventListener::CaptureConsole();
		while (is_running)
		{
			BaseEventListener::Update();
			std::this_thread::sleep_for(std::chrono::microseconds(100));
		}
	}
	void KeyEventListener::StopListening()
	{
		if (is_running) {
			is_running = false;
			additional_thread.join();
			BaseEventListener::ReleaseConsole();
		}
	}
	void KeyEventListener::AddHandler(KeyCode key, const std::function<void(bool pressed)>& func)
	{
		///std::lock_guard<std::mutex> lk(mx);
		key_handlers[(int)key] = std::move(func);
	}

	void KeyEventListener::KeyEventProc(KEY_EVENT_RECORD ker) {
		//std::lock_guard<std::mutex> lk(mx);
		auto it = key_handlers.find(ker.uChar.AsciiChar);
		if (it != key_handlers.end())
			it->second(ker.bKeyDown);
		else {
			//BaseEventListener::KeyEventProc(ker);
		}
	}
};