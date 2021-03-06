#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
	static float restart = 0.0f;
	restart += dDeltaTime;
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	//make 2 quats to use
	glm::quat quatStart = glm::angleAxis(0.0f, REAXISZ);
	glm::quat quatEnd = glm::angleAxis(359.9f, REAXISZ);


	if (restart >= 5.0f) {
		vector3 holder = start;
		start = end;
		end = holder;


		restart = 0.0f;
	}

	//float percent = MapValue((float)(dTotalTime/dDeltaTime), 0.0f, (float)(1.0f / dDeltaTime), 0.0f, 0.2f);
	float percent = MapValue((float)restart, 0.0f, 5.0f, 0.0f, 1.0f);

	matrix4 matrix = ToMatrix4(glm::mix(quatStart, quatEnd, percent));


	vector3 current = glm::lerp(start, end, percent);


	matrix *= glm::translate(current);

	m_m4Steve = matrix;

#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	m_pMeshMngr->Print("restart:");
	m_pMeshMngr->Print(std::to_string(restart), RERED);
#pragma endregion
}
