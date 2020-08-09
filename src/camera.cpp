#include "Camera.hpp"
#include "Math.hpp"
#include <iostream>

extern int gMouseWheelDelta;
extern float* gCameraZoom;
extern bool gKeys[4];

CameraCreateInfo::CameraCreateInfo()
:pos(0.f, 0.f), size(0.f, 0.f), zoom(1.f), lag(0.f) {}

Camera::Camera()
:pos(0.f, 0.f), size(0.f, 0.f), zoom(1.f), lag(0.f) {}

Camera::Camera(CameraCreateInfo& p_info)
{
	prevPos = p_info.pos;
	pos = p_info.pos;
	size = p_info.size;
	halfSize = size / 2.f;
	zoom = p_info.zoom;
	
	lag = p_info.lag;
}

void Camera::init()
{
	gCameraZoom = &zoom;
}

void Camera::setPos(Vector2f p_pos)
{
	pos = p_pos;
}

void Camera::setZoom(float p_zoom)
{
	zoom = p_zoom;
}

void Camera::setLag(float p_lag)
{
	lag = p_lag;
}

Vector2f Camera::getPrevPos()
{
	return prevPos; 
}

Vector2f Camera::getPos()
{
	return pos; 
}

Vector2f Camera::getHalfSize()
{
	return halfSize;
}

float Camera::getZoom()
{
	return zoom;
}

void Camera::updatePrev()
{
	prevPos = pos;
}

void Camera::update(Vector2f p_target)
{
	zoom += gMouseWheelDelta;

	if (zoom < 1)
		zoom = 1;
	

	dis = p_target - pos;
	vel = dis * lag;

	pos += vel;
}