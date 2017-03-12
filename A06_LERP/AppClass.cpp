#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	positions.push_back(vector3(-4.0f, -2.0f, 5.0f));
	positions.push_back(vector3(1.0f, -2.0f, 5.0f));
	positions.push_back(vector3(-3.0f, -1.0f, 3.0f));
	positions.push_back(vector3(2.0f, -1.0f, 3.0f));
	positions.push_back(vector3(-2.0f, 0.0f, 0.0f));
	positions.push_back(vector3(3.0f, 0.0f, 0.0f));
	positions.push_back(vector3(-1.0f, 1.0f, -3.0f));
	positions.push_back(vector3(4.0f, 1.0f, -3.0f));
	positions.push_back(vector3(0.0f, 2.0f, -5.0f));
	positions.push_back(vector3(5.0f, 2.0f, -5.0f));
	positions.push_back(vector3(1.0f, 3.0f, -5.0f));
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");

	for (int i = 0; i < 11; i++) {
		matrix4 m4SpherePosition = glm::translate(positions[i])* glm::scale(vector3(0.1f));

		m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, RERED, SOLID);
	}

	
	static float fTimer = 0.0f;
	static DWORD timerSinceBoot = GetTickCount(); //timer since the computer boot
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot; //current time - boot time
	fTimer = timerSinceStart / 1000.0f; //was in milliseconds
										//print info
	m_pMeshMngr->PrintLine(""); //print emplty line purely for positioning 
	m_pMeshMngr->Print("Time: "); //print
	m_pMeshMngr->PrintLine(std::to_string(fTimer)); //print


	static int posInt = 0;
	static bool cycle = false;


	static float OSMinInt = 0;
	static float OSMaxInt = 5;

	percentage = MapValue(fTimer, OSMinInt, OSMaxInt, 0.0f, 1.0f);
	
	if (percentage > 1.0f) {
		percentage = 0.0f;
		posInt++;
		OSMinInt += 5;
		OSMaxInt += 5;

		cycle = false;
	}

	vector3 v3Start;
	vector3 v3End;

	if (posInt == 10 || cycle) {
		
		posInt = -1;

		v3Start = positions[10];
		v3End = positions[0];
		cycle = true;
	}
	else {
		v3Start = positions[posInt];
		v3End = positions[posInt + 1];
	}



	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);

	matrix4 m4WallEye = glm::translate(v3Current);

	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");

	m_pMeshMngr->Print("Percentage: "); //print
	m_pMeshMngr->PrintLine(std::to_string(percentage)); //print
	


#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}