//This code will create an empty sfml window using Win32
//This window can be used as a normal sfml blank window for drawing

#include <SFML/Graphics.hpp>
#include <Windows.h>

HWND button;

LRESULT CALLBACK ProcessMessage(HWND handle, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
	case WM_COMMAND:
		if ((HWND)(lparam) == button)
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(handle, message, wparam, lparam); //in default case
}

int main()
{
	HINSTANCE instance = GetModuleHandle(NULL);

	WNDCLASS windowClass;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = 0;
	windowClass.hIcon = NULL;
	windowClass.hInstance = instance;
	windowClass.lpfnWndProc = &ProcessMessage;
	windowClass.lpszClassName = TEXT("SFML_APP");
	windowClass.lpszMenuName = NULL;
	windowClass.style = 0;
	RegisterClass(&windowClass);

	HWND window = CreateWindow(TEXT("SFML_APP"), TEXT("Sfml Win32"), WS_VISIBLE | WS_SYSMENU, 200, 200, 640, 480,
		NULL, NULL, instance, NULL);
	button = CreateWindow(TEXT("BUTTON"), TEXT("EXIT"), WS_VISIBLE | WS_CHILD, 520, 380, 80, 40,
		window, NULL, instance, NULL);

	//sfml window
	HWND childWindow = CreateWindow(TEXT("STATIC"), NULL, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN,
		20, 20, 580, 350, window, NULL, instance, NULL);
	sf::RenderWindow sfmlWindow(childWindow);

	MSG message;
	message.message = static_cast<UINT>(~WM_QUIT);
	while (message.message != WM_QUIT) {
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			sfmlWindow.clear();
			sfmlWindow.display();
		}

	}

	return 0;
}