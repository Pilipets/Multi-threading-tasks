#include "EventListener.h"

#include <chrono>

namespace key_listeners {
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
	void KeyEventListener::StopAsync()
	{
		if (is_running) {
			is_running = false;
			additional_thread.join();
			BaseEventListener::ReleaseConsole();
		}
	}
	void KeyEventListener::AddHandler(KeyCode key, const std::function<void(bool)>& func)
	{
		key_handlers[(int)key] = func;
	}

	void KeyEventListener::KeyEventProc(KEY_EVENT_RECORD ker) {
		auto it = key_handlers.find(ker.uChar.AsciiChar);
		if (it != key_handlers.end())
			it->second(ker.bKeyDown);
	}
};