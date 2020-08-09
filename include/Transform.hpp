#pragma once

#include "Math.hpp"

class Transform
{
public:
	void setWorldPos(const Vector2f& p_worldPos);
	void setLocalPos(const Vector2f& p_localPos);

	Vector2f getWorldPos();
	Vector2f getLocalPos();


private:
	Vector2f worldPos;
	Vector2f localPos;

	float angle;

	Mat3x3 rotMat;

};