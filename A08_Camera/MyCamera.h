#pragma once


#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>


class MyCamera
{
public:
	matrix4 viewMatrix;
	matrix4 projMatrix;
	vector3 eye;
	vector3 target;
	vector3 up;
	float pitch;
	float yaw;
	float roll;
	MyCamera();
	~MyCamera();
	matrix4 GetView(void); //Should get the View Matrix from your class
	matrix4 GetProjection(bool bOrtographic); //Should get the Projection Matrix from your class, this function should let me choose between a Perspective or an Orthographic projection depending on the bool argument.
	void SetPosition(vector3 v3Position);//Sets the position of the camera
	void SetTarget(vector3 v3Target);//Sets the target of the camera
	void SetUp(vector3 v3Up);//Sets the up vector of the camera
	void MoveForward(float fIncrement);//Move the camera forward (or backwards) depending on the “view vector”
	void MoveSideways(float fIncrement);//Move the camera based on the “right” vectordepending on the “view vector”
	void MoveVertical(float fIncrement);//Move the camera up or down depending on the “up vector”
	void ChangePitch(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in x
	void ChangeRoll(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in z
	void ChangeYaw(float fIncrement);//Orient your camera (meaning the forward and up vectors) changing its angle in y
};
