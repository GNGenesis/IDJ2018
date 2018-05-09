#include "InputManager.h"
#include "Camera.h"

std::unordered_map<int, bool> InputManager::keyState;
std::unordered_map<int, int> InputManager::keyUpdate;
bool InputManager::mouseState [6];
int InputManager::mouseUpdate [6];
int InputManager::mouseX;
int InputManager::mouseY;
int InputManager::updateCounter;
bool InputManager::quitRequested = false;

void InputManager::Update() {
	SDL_Event event;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX += Camera::pos.x;
	mouseY += Camera::pos.y;
	updateCounter++;

	while(SDL_PollEvent(&event)) {
		if(event.key.repeat != 1) {
			if(event.type == SDL_QUIT)
				quitRequested = true;
			if(event.type == SDL_MOUSEBUTTONDOWN) {
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_MOUSEBUTTONUP) {
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_KEYDOWN) {
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			if(event.type == SDL_KEYUP) {
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		}
	}
}

bool InputManager::KeyPress(int key) {
	return (keyUpdate[key] == updateCounter) ? (keyState[key]) : false;
}

bool InputManager::KeyRelease(int key) {
	return (keyUpdate[key] == updateCounter) ? (!keyState[key]) : false;
}

bool InputManager::IsKeyDown(int key) {
	return keyState[key];
}

bool InputManager::MousePress(int button) {
	return (mouseUpdate[button] == updateCounter) ? (mouseState[button]) : false;
}

bool InputManager::MouseRelease(int button) {
	return (mouseUpdate[button] == updateCounter) ? (!mouseState[button]) : false;
}

bool InputManager::IsMouseDown(int button) {
	return mouseState[button];
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

Vec2 InputManager::GetMousePos() {
	return Vec2(mouseX, mouseY);
}

bool InputManager::QuitRequested() {
	return quitRequested;
}
