#pragma once
#include "Math.hpp"

struct CameraCreateInfo
{
	CameraCreateInfo();
	Vector2f pos;
	Vector2f size;
	float zoom;
	float lag;
};

class Camera
{
public:
	Camera();
	Camera(CameraCreateInfo& p_info);
	void init();
	void setPos(Vector2f p_pos);
	void setZoom(float p_zoom);
	void setLag(float p_lag);
	Vector2f getPrevPos();
	Vector2f getPos() const;
	Vector2f getHalfSize() const;
	float getZoom() const;
	void updatePrev();
	void update(Vector2f p_target);
private:
	Vector2f prevPos;
	Vector2f pos;
	Vector2f size;
	Vector2f halfSize;

	Vector2f vel;
	Vector2f dis;

	float zoom;
	float lag;
};