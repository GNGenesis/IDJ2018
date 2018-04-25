#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

class Rect {
public:
	float x;
	float y;
	float w;
	float h;

	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();
	bool Contains(float a, float b);
	bool Contains(Vec2 p);
	Vec2 GetCenter();
};

#endif /* RECT_H_ */
