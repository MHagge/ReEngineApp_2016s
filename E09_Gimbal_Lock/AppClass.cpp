#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bobadilla, Alberto - Gimbal Lock");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}
void AppClass::InitVariables(void)
{
	//Loading the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");

	//Set the axis of Steve visible
	m_pMeshMngr->SetVisibleAxis(true, "Steve");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Rotation matrices
	/*
	matrix4 rotX = glm::rotate(IDENTITY_M4, m_v3Orientation.x, REAXISX);
	matrix4 rotY = glm::rotate(IDENTITY_M4, m_v3Orientation.y, REAXISY);
	matrix4 rotZ = glm::rotate(IDENTITY_M4, m_v3Orientation.z, REAXISZ);
	*/
	//glm::quat x = glm::quat()

	glm::quat rotX = glm::angleAxis(m_v3Orientation.x, REAXISX);
	glm::quat rotY = glm::angleAxis(m_v3Orientation.y, REAXISY);
	glm::quat rotZ = glm::angleAxis(m_v3Orientation.z, REAXISZ);


	/*idk
	// RotationAngle is in radians
	float x = REAXISX * sin(m_v3Orientation.x / 2);
	float y = REAXISY * sin(m_v3Orientation.y / 2);
	float z = REAXISZ * sin(m_v3Orientation.z / 2);
	float w = cos(RotationAngle / 2);//uhhhh nope

	glm::quat myQuat = glm::quat(x, y, z, w);
	

	
	//
	vector3 EulerAngles(m_v3Orientation.x, m_v3Orientation.y, m_v3Orientation.z);
	myQuat = glm::quat(EulerAngles);
	//what a mess t.t
	*/
	

	//linear combination
	m_mToWorld = glm::toMat4(rotX * rotY * rotZ);

	

	//Setting the model matrix
	m_pMeshMngr->SetModelMatrix(m_mToWorld, "Steve");

	//Adding the instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve");

	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("X:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.x), RERED);
	m_pMeshMngr->Print("Y:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.y), RERED);
	m_pMeshMngr->Print("Z:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.z), RERED);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	m_pMeshMngr->Render(); //renders the list of meshes in the system.
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release();
}