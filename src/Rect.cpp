#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

Rect::~Rect() {

}

bool Rect::Contains(float a, float b) {
	return((a > x) && (a < x+w) && (b > y) && (b < y+h));
}
