#include "MyCamera.h"



MyCamera::MyCamera()
{
	viewMatrix = IDENTITY_M4;
	projMatrix = IDENTITY_M4;
	eye = vector3(0, 0, 0);
	target = vector3(0, 0, 0);
	up = vector3(0, 0, 0);
	pitch = 0;
	yaw = 0;
	roll = 0;
}


MyCamera::~MyCamera()
{
}

matrix4 MyCamera::GetView(void)
{
	glm::quat rotate = glm::quat(vector3(pitch, yaw, roll));
	viewMatrix = glm::toMat4(rotate);
	viewMatrix *= glm::lookAt(eye, target, up);
	return viewMatrix;
}

matrix4 MyCamera::GetProjection(bool bOrtographic)
{
	projMatrix = glm::perspective(45.0f, 1.75f, 0.1f, 100.0f);
	return projMatrix;
}

void MyCamera::SetPosition(vector3 v3Position)
{
	eye = v3Position;
}

void MyCamera::SetTarget(vector3 v3Target)
{
	target = v3Target;
}

void MyCamera::SetUp(vector3 v3Up)
{
	up = v3Up;
}

void MyCamera::MoveForward(float fIncrement)
{
	eye.x += fIncrement;
	target.x += fIncrement;
}

void MyCamera::MoveSideways(float fIncrement)
{
	eye.z += fIncrement;
	target.z += fIncrement;
}

void MyCamera::MoveVertical(float fIncrement)
{
	eye.y += fIncrement;
	target.y += fIncrement;
}

void MyCamera::ChangePitch(float fIncrement)
{
	pitch += fIncrement;
}

void MyCamera::ChangeRoll(float fIncrement)
{
	roll += fIncrement;
}

void MyCamera::ChangeYaw(float fIncrement)
{
	yaw += fIncrement;
}
