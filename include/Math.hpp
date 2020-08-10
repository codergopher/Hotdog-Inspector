#pragma once

#include <iostream>
#include <math.h>


namespace math
{
	const float degToRad = 0.017453293f;
	const float pi = 3.14159265359f;
}

struct Vector2i
{
	int x, y;
	Vector2i():x(0.f), y(0.f) {};
	Vector2i(int p_x, int p_y)
	:x(p_x), y(p_y) {}

	void print()
	{
		std::cout << x << ", " << y;
	}

	float length()
	{
		return sqrt(x*x + y*y);
	}

	void operator+=(Vector2i p_v)
	{
		x += p_v.x;
		y += p_v.y;
	}
	void operator-=(Vector2i p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
	}
	void operator*=(Vector2i p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
	}
	void operator/=(Vector2i p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
	}

	// Scalar
	void operator+=(int p_s)
	{
		x += p_s;
		y += p_s;
	}
	void operator-=(int p_s)
	{
		x -= p_s;
		y -= p_s;
	}
	void operator*=(int p_s)
	{
		x *= p_s;
		y *= p_s;
	}
	void operator/=(int p_s)
	{
		x /= p_s;
		y /= p_s;
	}
};

struct Vector2f
{
	float x, y;
	Vector2f():x(0.f), y(0.f) {};
	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y) {}

	void print() const
	{
		std::cout << x << ", " << y << std::endl;
	}

	float length()
	{
		return sqrt(x*x + y*y);
	}

	void operator+=(Vector2f p_v)
	{
		x += p_v.x;
		y += p_v.y;
	}
	void operator-=(Vector2f p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
	}
	void operator*=(Vector2f p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
	}
	void operator/=(Vector2f p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
	}

	// Scalar
	void operator+=(float p_s)
	{
		x += p_s;
		y += p_s;
	}
	void operator-=(float p_s)
	{
		x -= p_s;
		y -= p_s;
	}
	void operator*=(float p_s)
	{
		x *= p_s;
		y *= p_s;
	}
	void operator/=(float p_s)
	{
		x /= p_s;
		y /= p_s;
	}
};



struct Vector3f
{
	float x, y, z;
	Vector3f():x(0.f), y(0.f), z(0.f) {};
	Vector3f(float p_x, float p_y, float p_z)
	:x(p_x), y(p_y), z(p_z) {}

	void print()
	{
		std::cout << x << ", " << y << ", " << z << std::endl;
	}

	float length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	void operator+=(Vector3f p_v)
	{
		x += p_v.x;
		y += p_v.y;
		z += p_v.z;
	}
	void operator-=(Vector3f p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
		z -= p_v.z;
	}
	void operator*=(Vector3f p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
		z *= p_v.z;
	}
	void operator/=(Vector3f p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
		z /= p_v.z;
	}

	// Scalar
	void operator+=(float p_s)
	{
		x += p_s;
		y += p_s;
		z += p_s;
	}
	void operator-=(float p_s)
	{
		x -= p_s;
		y -= p_s;
		z -= p_s;
	}
	void operator*=(float p_s)
	{
		x *= p_s;
		y *= p_s;
		z *= p_s;
	}
	void operator/=(float p_s)
	{
		x /= p_s;
		y /= p_s;
		z /= p_s;
	}
};


struct IntRect
{
	int x, y, w, h;
	IntRect() {}
	IntRect(int p_x, int p_y, int p_w, int p_h) 
	:x(p_x), y(p_y), w(p_w), h(p_h) 
	{}
};

Vector2f toVector2f(const Vector2i& p_v);
Vector2i toVector2i(const Vector2f& p_v);

float roundToScale(float f, float p_zoom);

Vector2f roundToScale(Vector2f vec, float p_zoom);

int roundToInt(float f);

Vector2f roundToInt(const Vector2f& p_v);

float distance(Vector2f a, Vector2f b);
float sqrDistance(Vector2f a, Vector2f b);

float dotProduct(Vector2f a, Vector2f b);

Vector2f normalise(Vector2f vec);

Vector2f clamp(Vector2f vec, Vector2f min, Vector2f max);

struct Mat3x3
{
	Mat3x3();

	float m00, m10, m20,
	      m01, m11, m21,
	      m02, m12, m22;

	void setScale(Vector2f s);
	void setTranslate(Vector2f d);
	void setRotation(float theta);

	Vector3f getXCol() const;
	Vector3f getYCol() const;
	Vector3f getZCol() const;

	void setXCol(Vector3f p_vec);
	void setYCol(Vector3f p_vec);
	void setZCol(Vector3f p_vec);

};

Mat3x3 operator*(const Mat3x3& p_matrixA, const Mat3x3& p_matrixB);

Vector3f operator*(const Mat3x3& p_matrix, const Vector3f& p_vec);
Vector3f operator*(const Vector3f& p_vec, const Mat3x3& p_matrix);


Vector2i operator-(Vector2i a);
Vector2i operator+(Vector2i a, Vector2i b);
Vector2i operator-(Vector2i a, Vector2i b);
Vector2i operator*(Vector2i a, Vector2i b);
Vector2i operator/(Vector2i a, Vector2i b);
Vector2i operator+(Vector2i a, float s);
Vector2i operator-(Vector2i a, float s);
Vector2i operator*(Vector2i a, float s);
Vector2i operator/(Vector2i a, float s);
Vector2i operator+(float s, Vector2i a);
Vector2i operator-(float s, Vector2i a);
Vector2i operator*(float s, Vector2i a);
Vector2i operator/(float s, Vector2i a);

Vector2f operator-(Vector2f a);
Vector2f operator+(Vector2f a, Vector2f b);
Vector2f operator-(Vector2f a, Vector2f b);
Vector2f operator*(Vector2f a, Vector2f b);
Vector2f operator/(Vector2f a, Vector2f b);
Vector2f operator+(Vector2f a, float s);
Vector2f operator-(Vector2f a, float s);
Vector2f operator*(Vector2f a, float s);
Vector2f operator/(Vector2f a, float s);
Vector2f operator+(float s, Vector2f a);
Vector2f operator-(float s, Vector2f a);
Vector2f operator*(float s, Vector2f a);
Vector2f operator/(float s, Vector2f a);

Vector3f operator-(Vector3f a);
Vector3f operator+(Vector3f a, Vector3f b);
Vector3f operator-(Vector3f a, Vector3f b);
Vector3f operator*(Vector3f a, Vector3f b);
Vector3f operator/(Vector3f a, Vector3f b);
Vector3f operator+(Vector3f a, float s);
Vector3f operator-(Vector3f a, float s);
Vector3f operator*(Vector3f a, float s);
Vector3f operator/(Vector3f a, float s);
Vector3f operator+(float s, Vector3f a);
Vector3f operator-(float s, Vector3f a);
Vector3f operator*(float s, Vector3f a);
Vector3f operator/(float s, Vector3f a);
