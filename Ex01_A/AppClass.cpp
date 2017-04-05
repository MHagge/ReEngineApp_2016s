#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock

	static float restart = 0.0f;//creates a timer
	restart += fDeltaTime;//add the delta time to the current clock

#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;
								 //make 2 quats to use
	glm::quat quatStart = glm::angleAxis(0.0f, REAXISZ);
	glm::quat quatEnd = glm::angleAxis(359.9f, REAXISZ);


	if (restart >= 2.0f) {
		vector3 holder = start;
		start = end;
		end = holder;


		restart = 0.0f;
	}

	//float percent = MapValue((float)(dTotalTime/dDeltaTime), 0.0f, (float)(1.0f / dDeltaTime), 0.0f, 0.2f);
	float percent = MapValue((float)restart, 0.0f, 2.0f, 0.0f, 1.0f);

	matrix4 matrix = ToMatrix4(glm::mix(quatStart, quatEnd, percent));


	vector3 current = glm::lerp(start, end, percent);


	modelMatrix = glm::translate(current);

	modelMatrix *= matrix;




#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

