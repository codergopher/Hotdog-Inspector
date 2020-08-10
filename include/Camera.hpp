#pragma once
#include "Math.hpp"

// Simple struct to pass parameters to the Camera
struct CameraCreateInfo
{
	CameraCreateInfo();
	Vector2f pos;
	Vector2f size;
	float zoom;
	float lag;
};

// The camera modifies the position and size of every Sprite that is drawn
// to give the illusion of camera
class Camera
{
public:
	Camera();
	Camera(CameraCreateInfo& p_info);
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
	// Prev pos is the keep a record of where the sprite was in
	// the last time step, so that the renderer can "guess" where the 
	// sprite should be drawn in between timesteps
	Vector2f prevPos;
	Vector2f pos;
	Vector2f size;
	Vector2f halfSize;

	Vector2f vel;
	// Distance between the camera and the target position
	// (yeah pretty bad var name)
	Vector2f dis;

	float zoom;

	// The lag is how "lazy" the camera is
	// How far behind the camera will drag behind it's target
	float lag;
};