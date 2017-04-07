#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Camera - YOUR USER NAME GOES HERE"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 20.0f));
	//m_pCamera->ChangeRoll(135.0f);
	m_pCamera->SetTarget(ZERO_V3);
	m_pCamera->SetUp(vector3(0.0f, 1.0f, 0.0f));

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
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

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

#pragma region 
	//don't need any of this

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//make 2 quats to use
	glm::quat quatStart = glm::angleAxis(0.0f, REAXISY);
	glm::quat quatEnd = glm::angleAxis(359.0f, REAXISY);

	float earthPercent = MapValue((float)fRunTime, 0.0f, (float)fEarthHalfOrbTime*2, 0.0f, 1.0f);
	float moonPercent = MapValue((float)fRunTime, 0.0f, (float)fMoonHalfOrbTime * 2, 0.0f, 1.0f);

	//
	matrix4 earthMatrix = ToMatrix4(glm::mix(quatStart, quatEnd, earthPercent));
	//translate
	earthMatrix *= glm::translate(11.0f, 0.0f, 0.0f);
	//scale
	earthMatrix *= glm::scale(0.524f, 0.524f, 0.524f);

	//moon
	//matrix4 moonMatrix = ToMatrix4(glm::mix(quatStart, quatEnd, moonPercent));
	matrix4 moonMatrix = earthMatrix;
	moonMatrix *= ToMatrix4(glm::mix(quatStart, quatEnd, moonPercent));
	//moonMatrix *= glm::translate(11.0f, 0.0f, 0.0f);
	moonMatrix *= glm::translate(2.0f, 0.0f, 0.0f);
	moonMatrix *= glm::scale(0.27f, 0.27f, 0.27f);
	
	//earth spin
	glm::quat earthQuat = glm::mix(quatStart, quatEnd, MapValue((float)fRunTime, 0.0f, (float)fEarthHalfRevTime*2, 0.0f, 1.0f));//(float)fmod(fRunTime, 2*fEarthHalfRevTime));
	earthMatrix *= ToMatrix4(earthQuat);

	matrix4 sunMatrix = glm::scale(5.936f, 5.936f, 5.936f);

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(sunMatrix, "Sun");
	m_pMeshMngr->SetModelMatrix(earthMatrix, "Earth");
	m_pMeshMngr->SetModelMatrix(moonMatrix, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	int nEarthOrbits = fRunTime/fEarthHalfOrbTime/2;
	int nEarthRevolutions = fRunTime/fEarthHalfRevTime/2;
	int nMoonOrbits = fRunTime/fMoonHalfOrbTime/2;

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
	static float speed = 1.0f;

	
	
	
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;

	if (bModifier)
		speed *= 10.0f;
	*/
	/*

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCamera->MoveForward(speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCamera->MoveForward(-speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCamera->MoveSideways(-speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCamera->MoveSideways(speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCamera->MoveVertical(-speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCamera->MoveVertical(speed);
		*/
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	//m_pMeshMngr->Render(); //renders the render list

	//Render the grid based on the camera's mode:
	PrimitiveClass cube = PrimitiveClass();
	cube.GenerateCube(2.0f, RERED);
	cube.Render(m_pCamera->GetProjection(false), m_pCamera->GetView(), IDENTITY_M4);

	m_pMeshMngr->ClearRenderList();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}