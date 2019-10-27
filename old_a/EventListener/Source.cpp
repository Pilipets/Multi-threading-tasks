#include "EventListener.h"

using namespace key_listener;
int main()
{
	KeyEventListener handler;
	handler.AddHandler(KeyEventListener::KeyCode::ESCAPE, [](bool pressed) {
		printf("Key Escape: ");
		if (pressed)
			printf("pressed\n");
		else
			printf("released\n");
	});
	handler.AddHandler(KeyEventListener::KeyCode::q, [](bool pressed) {
		printf("Key q\n");
	});
	handler.AddHandler(KeyEventListener::KeyCode::c, [](bool pressed) {
		printf("Key c\n");
	});

	handler.StartAsync();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	handler.StopListening();
	system("pause");
	return 0;
}
