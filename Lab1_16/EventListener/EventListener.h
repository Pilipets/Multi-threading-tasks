#pragma once
#include <windows.h>
#include "stdio.h"

#include <functional>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <chrono>
#include <future>
#include<atomic>
namespace key_listener {
	class BaseEventListener {
	protected:
		virtual void KeyEventProc(KEY_EVENT_RECORD ker);
		void ErrorExit(const char*);
		void CaptureConsole();
		void ReleaseConsole();
	public:
		BaseEventListener();
		~BaseEventListener();
		void Update();
	private:
		DWORD cNumRead, fdwMode;
		HANDLE hStdin;
		DWORD fdwSaveOldMode;
		INPUT_RECORD irInBuf[128];

	};

	class KeyEventListener : public BaseEventListener {
	private:
		void KeyEventProc(KEY_EVENT_RECORD ker) override;
		void StartListening();
	public:
		enum class KeyCode : int {
			ESCAPE = 27,
			q = 113,
			c = 99
		};
		KeyEventListener();
		~KeyEventListener();
		void StartAsync();
		void StopListening();
		void AddHandler(KeyCode key, const std::function<void(bool) > &func);
	private:
		std::unordered_map <int, std::function<void(bool) >> key_handlers;
		std::thread additional_thread;
		std::atomic<bool> is_running;
		mutable std::mutex mx;
	};
};