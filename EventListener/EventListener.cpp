#include "EventListener.h"

namespace key_listener {
	void BaseEventListener::KeyEventProc(KEY_EVENT_RECORD ker)
	{
		printf("Key event: ");

		if (ker.bKeyDown)
			printf("key pressed\n");
		else printf("key released\n");
	}

	void BaseEventListener::ErrorExit(const char *err_msg)
	{
		fprintf(stderr, "%s\n", err_msg);

		ReleaseConsole();
		ExitProcess(0);
	}

	void BaseEventListener::CaptureConsole()
	{
		if (!SetConsoleMode(hStdin, fdwMode))
			ErrorExit("SetConsoleMode");
	}

	void BaseEventListener::ReleaseConsole()
	{
		// Restore input mode on exit.
		SetConsoleMode(hStdin, fdwSaveOldMode);
	}

	BaseEventListener::BaseEventListener()
	{
		// Get the standard input handle. 
		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		if (hStdin == INVALID_HANDLE_VALUE)
			ErrorExit("GetStdHandle");

		// Save the current input mode, to be restored on exit. 
		if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
			ErrorExit("GetConsoleMode");

		// Enable the window and mouse input events. 
		fdwMode = ENABLE_WINDOW_INPUT;
	}

	BaseEventListener::~BaseEventListener()
	{
		ReleaseConsole();
		ExitProcess(0);
	}

	void BaseEventListener::Update()
	{
		if (!GetNumberOfConsoleInputEvents(hStdin, &cNumRead) || !cNumRead)
			return;

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		for (DWORD i = 0; i < cNumRead; ++i) {
			switch (irInBuf[i].EventType) {
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
			case FOCUS_EVENT:  // disregard focus events 
			case MENU_EVENT:   // disregard menu events
				break;
			default:
				ErrorExit("Unknown event type");
			}
		}
	}
};
