#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop) {
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}


void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1

	//*************************************************************************************************************************************

	
	std::vector<vector3>point;
	//TRIvvv
	//point.push_back(vector3(-fValue, -fValue, -fValue));//0
	//point.push_back(vector3(-fValue, -fValue, -fValue));//1
	//point.push_back(vector3(-fValue, -fValue, -fValue));//2
	//
	//AddTri(point[0], point[1], point[2]);
	//TRI^^^

	//*************************************************************************************************************************************
	
	//DYNAMICvvv
	//for (int i = 0; i < a_nSubdivisions; i++) {
	//	point.push_back(vector3(0, 0, 0));//0 yeah but how the fuck are we supposed to get the coords in?
	//}
	//DYNAMIC^^^

	//*************************************************************************************************************************************

	float theta = 0;
	float steps = 2* PI / static_cast<float>(a_nSubdivisions);

	point.push_back(vector3(0.0f, 0.0f, -a_fHeight/2));

	//DYNAMICvvv
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta*-1), sin(theta*-1), a_fHeight/2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i+1]);
	}

	//AddTri(point[0], point[1], point[2]);
	//AddTri(point[0], point[2], point[3]);
	//AddTri(point[0], point[3], point[4]);
	//AddTri(point[0], point[4], point[5]);

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.pop_back();
	}

	//PART_TWO
	point.push_back(vector3(0.0f, 0.0f, a_fHeight/2));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), a_fHeight/2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.pop_back();
	}


	//*************************************************************************************************************************************
	
	//vector3 point0(-fValue, -fValue, fValue); //0
	//vector3 point1(fValue, -fValue, fValue); //1
	//vector3 point2(fValue, fValue, fValue); //2
	//vector3 point3(-fValue, fValue, fValue); //3

	//AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	std::vector<vector3>point;

	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//BASE 1
	point.push_back(vector3(0.0f, 0.0f, a_fHeight / 2));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta), sin(theta), a_fHeight / 2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.pop_back();
	}

	//BASE 2
	point.push_back(vector3(0.0f, 0.0f, -a_fHeight / 2));

	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(-theta), sin(-theta), -a_fHeight / 2));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.pop_back();
	}

	//ROUND BIT
	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.push_back(vector3(cos(theta), sin(theta), -a_fHeight / 2));
		theta += steps;
	}
	for (int i = 0; i < a_nSubdivisions+1; i++) {
		point.push_back(vector3(cos(theta), sin(theta), a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions+1; i++) {
		//(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
		AddQuad(point[i], point[i+1], point[a_nSubdivisions + i], point[a_nSubdivisions + i + 1]);
	}

	for (int i = 0; i < a_nSubdivisions*2 + 2; i++) {
		point.pop_back();
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	std::vector<vector3>point;

	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//BASE 1
	for (int i = 0; i < a_nSubdivisions+1; i++) { //points for outer radius
		point.push_back(vector3(cos(theta)*a_fOuterRadius, sin(theta)*a_fOuterRadius, a_fHeight / 2));
		theta += steps;
	}
	for (int i = 0; i < a_nSubdivisions + 1; i++) { //points for inner radius
		point.push_back(vector3(cos(theta)*a_fInnerRadius, sin(theta)*a_fInnerRadius, a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions+1; i++) { //AddQuad
		AddQuad(point[i], point[i+1], point[a_nSubdivisions + i], point[a_nSubdivisions +i+1]);
	}

	for (int i = 0; i < a_nSubdivisions*2+2; i++) {
		point.pop_back();
	}

	//BASE 2
	for (int i = 0; i < a_nSubdivisions + 1; i++) { //points for outer radius
		point.push_back(vector3(cos(-theta)*a_fOuterRadius, sin(-theta)*a_fOuterRadius, -a_fHeight / 2));
		theta += steps;
	}
	for (int i = 0; i < a_nSubdivisions + 1; i++) { //points for inner radius
		point.push_back(vector3(cos(-theta)*a_fInnerRadius, sin(-theta)*a_fInnerRadius, -a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) { //AddQuad
		AddQuad(point[i], point[i + 1], point[a_nSubdivisions + i], point[a_nSubdivisions + i + 1]);
	}

	for (int i = 0; i < a_nSubdivisions * 2 + 2; i++) {
		point.pop_back();
	}

	//ROUND BIT OUTER
	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(theta)*a_fOuterRadius, sin(theta)*a_fOuterRadius, -a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(theta)*a_fOuterRadius, sin(theta)*a_fOuterRadius, a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		//(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
		AddQuad(point[i], point[i + 1], point[a_nSubdivisions + i], point[a_nSubdivisions + i + 1]);
	}

	for (int i = 0; i < a_nSubdivisions * 2 + 2; i++) {
		point.pop_back();
	}

	//ROUND BIT INNER
	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(-theta)*a_fInnerRadius, sin(-theta)*a_fInnerRadius, -a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.push_back(vector3(cos(-theta)*a_fInnerRadius, sin(-theta)*a_fInnerRadius, a_fHeight / 2));
		theta += steps;
	}

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		//(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
		AddQuad(point[i], point[i + 1], point[a_nSubdivisions + i], point[a_nSubdivisions + i + 1]);
	}

	for (int i = 0; i < a_nSubdivisions * 2 + 2; i++) {
		point.pop_back();
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	std::vector<vector3>point;

	float thetaRight = 0.0f;
	float thetaLeft = 0.0f;
	float phiRight = 0.0f;
	float phiLeft = 0.0f;

	float r = a_fOuterRadius - a_fInnerRadius;
	float R = a_fInnerRadius + r;

	for (int j = 0; j < a_nSubdivisionsA; j++) {
		phiRight = 2* PI*j / a_nSubdivisionsA;
		phiLeft = 2*PI*(j + 1) / a_nSubdivisionsA;
		for (int i = 0; i < a_nSubdivisionsB; i++) {
			thetaRight = 2 * PI*i / a_nSubdivisionsB;
			thetaLeft = 2 * PI*(i + 1) / a_nSubdivisionsB;

			point.push_back(vector3((R+r*cos(thetaLeft))*cos(phiLeft), (R+r*cos(thetaLeft))*sin(phiLeft), r*sin(thetaLeft)));
			point.push_back(vector3((R+r*cos(thetaLeft))*cos(phiRight), (R+r*cos(thetaLeft))*sin(phiRight), r*sin(thetaLeft)));
			point.push_back(vector3((R+r*cos(thetaRight))*cos(phiLeft), (R + r*cos(thetaRight))*sin(phiLeft), r*sin(thetaRight)));
			point.push_back(vector3((R + r*cos(thetaRight))*cos(phiRight), (R + r*cos(thetaRight))*sin(phiRight), r*sin(thetaRight)));

			AddQuad(point[0], point[1], point[2], point[3]);

			point._Pop_back_n(4);
		}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 15)
		a_nSubdivisions = 15;

	Release();
	Init();

	//Your code starts here
	/*std::vector<vector3>point;

	float theta = 0;
	float phi = 0;//idk
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//BASE 1
	point.push_back(vector3(0.0f, 0.0f, a_fRadius));

	//for loop for the # of levels 
	for (int i = 0; i < a_nSubdivisions+5; i++) {
		//loop for rounds 
		for (int i = 0; i < a_nSubdivisions; i++) {
			point.push_back(vector3(a_fRadius* cos(theta)*sin(phi), a_fRadius*sin(theta)*sin(phi), a_fRadius *cos(phi)));
			theta += steps;
		}
		phi += steps;
	}

	//top base bit 
	for (int i = 1; i < a_nSubdivisions+1; i++) {
		AddTri(point[0], point[i], point[i + 1]);
	}

	//middle bits that use quads
	for (int i = 1; i < a_nSubdivisions; i++) {
		for (int j= 1; j < a_nSubdivisions; j++) {
			AddQuad(point[a_nSubdivisions * i + j + 1], point[a_nSubdivisions * i + j], point[a_nSubdivisions * i * 2 + j + 1], point[a_nSubdivisions * i * 2 + j]);
		}
	}
	//AddQuad(point[a_nSubdivisions + 2], point[a_nSubdivisions + 1], point[a_nSubdivisions * 2 + 2], point[a_nSubdivisions * 2  + 1]);
	//AddQuad(point[a_nSubdivisions + 4], point[a_nSubdivisions + 3], point[a_nSubdivisions * 2 + 4], point[a_nSubdivisions *2 + 3]);
	//AddQuad(point[a_nSubdivisions + 6], point[a_nSubdivisions + 5], point[a_nSubdivisions * 2 + 6], point[a_nSubdivisions * 2 + 5]);
	//AddQuad(point[a_nSubdivisions + 8], point[a_nSubdivisions + 7], point[a_nSubdivisions * 2 + 8], point[a_nSubdivisions * 2 + 7]);

	//bottom base bit
	for (int i = 0; i < a_nSubdivisions+1; i++) {
		AddTri(point[0], point[a_nSubdivisions*a_nSubdivisions-a_nSubdivisions+i], point[a_nSubdivisions*a_nSubdivisions - a_nSubdivisions + i +1]);
	}

	//AddTri(point[0], point[a_nSubdivisions], point[1]);

	for (int i = 0; i < a_nSubdivisions + 1; i++) {
		point.pop_back();
	}
	*/
	//well none of that ^^^ works :(



	std::vector<vector3>point;

	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	float thetaRight = 0.0f;
	float thetaLeft = 0.0f;
	float phiRight = 0.0f;
	float phiLeft = 0.0f;

	for (int j = 0; j < a_nSubdivisions; j++) {
		phiRight = PI*j / a_nSubdivisions;
		phiLeft = PI*(j + 1) / a_nSubdivisions;
		for (int i = 0; i < a_nSubdivisions; i++) {
			thetaRight = 2 * PI*i / a_nSubdivisions;
			thetaLeft = 2 * PI*(i + 1) / a_nSubdivisions;

			point.push_back(vector3(a_fRadius*cos(thetaLeft)*sin(phiLeft), a_fRadius*cos(phiLeft), a_fRadius*sin(thetaLeft)*sin(phiLeft)));
			point.push_back(vector3(a_fRadius*cos(thetaLeft)*sin(phiRight), a_fRadius*cos(phiRight), a_fRadius*sin(thetaLeft)*sin(phiRight)));
			point.push_back(vector3(a_fRadius*cos(thetaRight)*sin(phiLeft), a_fRadius*cos(phiLeft), a_fRadius*sin(thetaRight)*sin(phiLeft)));
			point.push_back(vector3(a_fRadius*cos(thetaRight)*sin(phiRight), a_fRadius*cos(phiRight), a_fRadius*sin(thetaRight)*sin(phiRight)));

			AddQuad(point[1], point[0], point[3], point[2]);

			point._Pop_back_n(4);
		}
	}


	



	//Your code ends here
	CompileObject(a_v3Color);
}