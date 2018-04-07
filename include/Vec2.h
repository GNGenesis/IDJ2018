#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator+(const float rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator-(const float rhs) const;
	Vec2 operator*(const float rhs) const;
	static float Cos(float ang);
	static float Sin(float ang);
	static Vec2 Project(float dist, float ang);
};

#endif /* VEC2_H_ */
