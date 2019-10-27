#pragma once
#include "stdio.h"
#include <windows.h>

#include <atomic>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace key_listeners {
	// Base class for handling events over the Console
	class BaseEventListener {
	protected:

		virtual void KeyEventProc(KEY_EVENT_RECORD ker);
		void ErrorExit(const char*);
		void CaptureConsole();
		void ReleaseConsole();
	public:
		BaseEventListener();
		~BaseEventListener();
		void Start() { CaptureConsole(); }
		void Stop() { ReleaseConsole(); }

		// Processes events that has happened to the console
		void Update();
	private:
		DWORD cNumRead, fdwMode;
		HANDLE hStdin;
		DWORD fdwSaveOldMode;
		INPUT_RECORD irInBuf[128];

	};

	// Async listener for console key events
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
		void StopAsync();
		void AddHandler(KeyCode key, const std::function<void(bool) >& func);
	private:
		std::unordered_map <int, std::function<void(bool) >> key_handlers;
		std::thread additional_thread;
		std::atomic<bool> is_running;
	};
};