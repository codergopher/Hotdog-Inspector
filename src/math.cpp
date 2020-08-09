#include "Math.hpp"
#include <math.h>
#include <bits/stdc++.h>
#include <iostream>


float roundToScale(float f, float zoom)
{
	float pixelUnit = 1.f/zoom;
	float halfPixelUnit = pixelUnit/2.f;

	float d = std::fmod(f, pixelUnit);


	d = abs(d);

	if (d >= halfPixelUnit)
		f += (pixelUnit - d);
	else
		f -= d;


	return f;
}

Vector2f roundToScale(Vector2f vec, float zoom)
{
	vec.x = roundToScale(vec.x, zoom);
	vec.y = roundToScale(vec.y, zoom);

	return vec;
}

int roundToInt(float f)
{
	float d = std::fmod(f, 1.f);

	d = abs(d);
	if(d >= 0.5)
		f += (1.f - d);
	else
		f -= d;

	return (int)f;
}

float distance(Vector2f a, Vector2f b)
{
	return sqrt( powf((a.x - b.x), 2) + powf((a.y - b.y), 2));
}
float sqrDistance(Vector2f a, Vector2f b)
{
	return powf((a.x - b.x), 2) + powf((a.y - b.y), 2);
}



float dotProduct(Vector2f a, Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

Vector2f normalise(Vector2f vec)
{
	float length = vec.length();

	if (length != 0.0f)
	{
		length = 1.0f / length;
		vec.x *= length;
		vec.y *= length;
	}
	return vec;
}

Vector2f clamp(Vector2f vec, Vector2f min, Vector2f max)
{
	Vector2f clamped = vec;

	if (vec.x < min.x)
		clamped.x = min.x;
	if (vec.y < min.y)
		clamped.y = min.y;

	if (vec.x > max.x)
		clamped.x = max.x;
	if (vec.y > max.y)
		clamped.y = max.y;

	return clamped;
}

Vector2f toVector2f(const b2Vec2& vec)
{
	return {vec.x, vec.y};
}

Vector2f scaleToVector2f(const b2Vec2& vec)
{
	return {vec.x * 30.f, vec.y * 30.f};
}

b2Vec2 to_b2Vec2(const Vector2f& vec)
{
	return {vec.x, vec.y};
}

b2Vec2 scaleToBox2D( const Vector2f& vec)
{
	return {vec.x / 30.f, vec.y / 30.f};
}



Mat3x3::Mat3x3()
{
	m00 = 1.f; m10 = 0.f; m20 = 0;
	m01 = 0.f; m11 = 1.f; m21 = 0;
	m02 = 0.f; m12 = 0.f; m22 = 1.f;
}

void Mat3x3::setScale(Vector2f s)
{
	m00 = s.x; m10 = 0;   m20 = 0;
	m01 = 0;   m11 = s.y; m21 = 0;
	m02 = 0;   m12 = 0;   m22 = 1;
//  _         _
// |  Sx 0  0  |
// |  0  Sy 0  |
// |_ 0  0  1 _|
}

void Mat3x3::setTranslate(Vector2f d)
{
	m00 = 1; m10 = 0; m20 = d.x;
	m01 = 0; m11 = 1; m21 = d.y;
	m02 = 0; m12 = 0; m22 = 1;
//  _        _
// |  1 0 Dx  |
// |  0 1 Dy  |
// |_ 0 0  1 _|
}

void Mat3x3::setRotation(float theta)
{
	float cos = std::cos(theta);
	float sin = std::sin(theta);

	if (theta < 0)
		sin *= -1.f;

	m00 = cos; m10 = -sin;  m20 = 0;
	m01 = sin; m11 = cos; m21 = 0;
	m02 = 0;   m12 = 0;    m22 = 1;

//  _          _
// |  cos sin 0 |
// | -sin cos 0 |
// |_ 0   0   1_|
}

Vector3f Mat3x3::getXCol() const
{
	return {m00, m01, m02};
}
Vector3f Mat3x3::getYCol() const 
{
	return {m10, m11, m12};
}
Vector3f Mat3x3::getZCol() const
{
	return {m20, m21, m22};
}

void Mat3x3::setXCol(Vector3f p_vec)
{
	m00 = p_vec.x;
	m01 = p_vec.y;
	m02 = p_vec.z;
}
void Mat3x3::setYCol(Vector3f p_vec)
{
	m10 = p_vec.x;
	m11 = p_vec.y;
	m12 = p_vec.z;
}
void Mat3x3::setZCol(Vector3f p_vec)
{
	m20 = p_vec.x;
	m21 = p_vec.y;
	m22 = p_vec.z;
}


Mat3x3 operator*(const Mat3x3& p_matrixA, const Mat3x3& p_matrixB)
{
	Mat3x3 result;

	Vector3f xColA = p_matrixA.getXCol();
	Vector3f yColA = p_matrixA.getYCol();
	Vector3f zColA = p_matrixA.getZCol();

	xColA = xColA * p_matrixB;
	yColA = yColA * p_matrixB;
	zColA = zColA * p_matrixB;

	result.setXCol(xColA);
	result.setYCol(yColA);
	result.setZCol(zColA);

	return result;

}

Vector3f operator*(const Mat3x3& p_matrix, const Vector3f& p_vec)
{
	Vector3f xCol = p_matrix.getXCol();
	Vector3f yCol = p_matrix.getYCol();
	Vector3f zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * p_vec.z;

	Vector3f result = xCol + yCol + zCol;

	return result;
}


Vector3f operator*(const Vector3f& p_vec, const Mat3x3& p_matrix)
{
	Vector3f xCol = p_matrix.getXCol();
	Vector3f yCol = p_matrix.getYCol();
	Vector3f zCol = p_matrix.getZCol();

	xCol = xCol * p_vec.x;
	yCol = yCol * p_vec.y;
	zCol = zCol * p_vec.z;

	Vector3f result = xCol + yCol + zCol;

	return result;
}


Vector2i operator-(Vector2i a)
{
	return {-a.x, -a.y};
}

Vector2i operator+(Vector2i a, Vector2i b)
{
	return {a.x + b.x, a.y + b.y};
}
Vector2i operator-(Vector2i a, Vector2i b)
{
	return {a.x - b.x, a.y - b.y};
}
Vector2i operator*(Vector2i a, Vector2i b)
{
	return {a.x * b.x, a.y * b.y};
}
Vector2i operator/(Vector2i a, Vector2i b)
{
	return {a.x / b.x, a.y / b.y};
}

Vector2i operator+(Vector2i a, int s)
{
	return {a.x + s, a.y + s};
}
Vector2i operator-(Vector2i a, int s)
{
	return {a.x - s, a.y - s};
}
Vector2i operator*(Vector2i a, int s)
{
	return {a.x * s, a.y * s};
}
Vector2i operator/(Vector2i a, int s)
{
	return {a.x / s, a.y / s};
}

Vector2i operator+(int s, Vector2i a)
{
	return {a.x + s, a.y + s};
}
Vector2i operator-(int s, Vector2i a)
{
	return {a.x - s, a.y - s};
}
Vector2i operator*(int s, Vector2i a)
{
	return {a.x * s, a.y * s};
}
Vector2i operator/(int s, Vector2i a)
{
	return {a.x / s, a.y / s};
}




Vector2f operator-(Vector2f a)
{
	return {-a.x, -a.y};
}

Vector2f operator+(Vector2f a, Vector2f b)
{
	return {a.x + b.x, a.y + b.y};
}
Vector2f operator-(Vector2f a, Vector2f b)
{
	return {a.x - b.x, a.y - b.y};
}
Vector2f operator*(Vector2f a, Vector2f b)
{
	return {a.x * b.x, a.y * b.y};
}
Vector2f operator/(Vector2f a, Vector2f b)
{
	return {a.x / b.x, a.y / b.y};
}

Vector2f operator+(Vector2f a, float s)
{
	return {a.x + s, a.y + s};
}
Vector2f operator-(Vector2f a, float s)
{
	return {a.x - s, a.y - s};
}
Vector2f operator*(Vector2f a, float s)
{
	return {a.x * s, a.y * s};
}
Vector2f operator/(Vector2f a, float s)
{
	return {a.x / s, a.y / s};
}

Vector2f operator+(float s, Vector2f a)
{
	return {a.x + s, a.y + s};
}
Vector2f operator-(float s, Vector2f a)
{
	return {a.x - s, a.y - s};
}
Vector2f operator*(float s, Vector2f a)
{
	return {a.x * s, a.y * s};
}
Vector2f operator/(float s, Vector2f a)
{
	return {a.x / s, a.y / s};
}

/* Vector 3f */

Vector3f operator-(Vector3f a)
{
	return {-a.x, -a.y, -a.z};
}

Vector3f operator+(Vector3f a, Vector3f b)
{
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Vector3f operator-(Vector3f a, Vector3f b)
{
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}
Vector3f operator*(Vector3f a, Vector3f b)
{
	return {a.x * b.x, a.y * b.y, a.z * b.z};
}
Vector3f operator/(Vector3f a, Vector3f b)
{
	return {a.x / b.x, a.y / b.y, a.z / b.z};
}

Vector3f operator+(Vector3f a, float s)
{
	return {a.x + s, a.y + s, a.z + s};
}
Vector3f operator-(Vector3f a, float s)
{
	return {a.x - s, a.y - s, a.z - s};
}
Vector3f operator*(Vector3f a, float s)
{
	return {a.x * s, a.y * s, a.z * s};
}
Vector3f operator/(Vector3f a, float s)
{
	return {a.x / s, a.y / s, a.z / s};
}

Vector3f operator+(float s, Vector3f a)
{
	return {a.x + s, a.y + s, a.z + s};
}
Vector3f operator-(float s, Vector3f a)
{
	return {a.x - s, a.y - s, a.z - s};
}
Vector3f operator*(float s, Vector3f a)
{
	return {a.x * s, a.y * s, a.z * s};
}
Vector3f operator/(float s, Vector3f a)
{
	return {a.x / s, a.y / s, a.z / s};
}