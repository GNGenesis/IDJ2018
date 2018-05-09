#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Vec2.h"

#include <unordered_map>

class InputManager {
private:
	static std::unordered_map<int, bool> keyState;
	static std::unordered_map<int, int> keyUpdate;
	static bool mouseState [6];
	static int mouseUpdate [6];
	static int mouseX;
	static int mouseY;
	static int updateCounter;
	static bool quitRequested;

public:
	static void Update();
	static bool KeyPress(int key);
	static bool KeyRelease(int key);
	static bool IsKeyDown(int key);
	static bool MousePress(int button);
	static bool MouseRelease(int button);
	static bool IsMouseDown(int button);
	static int GetMouseX();
	static int GetMouseY();
	static Vec2 GetMousePos();
	static bool QuitRequested();
};

#endif /* INPUTMANAGER_H_ */
