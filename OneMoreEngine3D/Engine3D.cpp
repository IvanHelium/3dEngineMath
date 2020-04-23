#include "Engine3D.h"


# define M_PI           3.14159265358979323846f



Engine3D::Engine3D()
{
	
}
Engine3D::~Engine3D()
{

}
//------------------------------------------------------------------------------------------------------------------------
void Engine3D::DrawLine(int x1, int y1, int x2, int y2, int lineType, int color)
{
	draw.DrawLine(x1, y1, x2, y2, lineType, 1, color);
}

void Engine3D::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color)
{
	draw.DrawTriangle(x1, y1, x2, y2, x3, y3, lineType, color);
}

void Engine3D::DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color, int brushColor)
{
	draw.DrawFilledTriangle(x1, y1, x2, y2, x3, y3, lineType, color, brushColor);
}
//------------------------------------------------------------------------------------------------------------------------
void Engine3D::setHDC(HDC Hdc)
{
	draw.SetHDC(Hdc);
}

void Engine3D::setRect(RECT rect)
{
	draw.SetRect(rect);
}
//------------------------------------------------------------------------------------------------------------------------
bool Engine3D::OnUserCreate() 
{
	meshCube.triangles = {

		// SOUTH
			{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

			// EAST                                                      
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

			// NORTH                                                     
			{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

			// WEST                                                      
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

			// TOP                                                       
			{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

			// BOTTOM                                                    
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },


	};

	//
	float screenHeight = (float)draw.GetRect().bottom;
	float screenWidth = (float)draw.GetRect().right;

	//projection matrix
	float fNear = 0.1f;
	float fFar = 1000.f;
	float fFov = 90.0f;
	float fAspectRatio = screenHeight / screenWidth;
	float fFovRad =  1.0f / tanf(fFov * 0.5f / 180.0f * M_PI);

	matrixProjection.m[0][0] = fAspectRatio * fFovRad;
	matrixProjection.m[1][1] = fFovRad;
	matrixProjection.m[2][2] = fFar / (fFar - fNear);
	matrixProjection.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matrixProjection.m[2][3] = 1.0f;
	matrixProjection.m[3][3] = 0.0f;


	return true;
}

float fTheta = 0.0f;

bool Engine3D::OnUserUpdate(float fElapsedTime)
{
	//draw triangles
	float screenHeight = (float)draw.GetRect().bottom;
	float screenWidth = (float)draw.GetRect().right;


	Mat4x4 matRotateZ, matRotateX, matRotateY;

	fTheta += 1.0f * fElapsedTime; 

	//fTheta = (30.0f / 180.0f) * M_PI;

	//rotation Z 
	matRotateZ.m[0][0] = cosf(fTheta);
	matRotateZ.m[0][1] = sinf(fTheta);
	matRotateZ.m[0][2] = 0;
	matRotateZ.m[1][0] = -sinf(fTheta);
	matRotateZ.m[1][1] = cosf(fTheta);
	matRotateZ.m[1][2] = 0;
	matRotateZ.m[2][0] = 0;
	matRotateZ.m[2][1] = 0;
	matRotateZ.m[2][2] = 1;
	matRotateZ.m[3][3] = 1;

	//rotation X + 
	matRotateX.m[0][0] = 1;
	matRotateX.m[0][1] = 0;
	matRotateX.m[0][2] = 0;
	matRotateX.m[1][0] = 0;
	matRotateX.m[1][1] = cosf(fTheta);
	matRotateX.m[1][2] = sinf(fTheta);
	matRotateX.m[2][0] = 0;
	matRotateX.m[2][1] = -sinf(fTheta);
	matRotateX.m[2][2] = cosf(fTheta);
	matRotateX.m[3][3] = 1;

	//rotation Y  
	matRotateY.m[0][0] = cosf(fTheta);
	matRotateY.m[0][1] = 0;
	matRotateY.m[0][2] = -sinf(fTheta);
	matRotateY.m[1][0] = 0;
	matRotateY.m[1][1] = 1;
	matRotateY.m[1][2] = 0;
	matRotateY.m[2][0] = sinf(fTheta);
	matRotateY.m[2][1] = 0;
	matRotateY.m[2][2] = cosf(fTheta);
	matRotateY.m[3][3] = 1;




	for (auto triangle : meshCube.triangles)
	{
		Triangle triangleProjected , triangleTranslated, triangleRotatedZ, triangleRotatedY, triangleRotatedX, triangleRotatedXZ;

		

		MultiplyMatrixVector(triangle.p[0], triangleRotatedZ.p[0], matRotateZ);
		MultiplyMatrixVector(triangle.p[1], triangleRotatedZ.p[1], matRotateZ);
		MultiplyMatrixVector(triangle.p[2], triangleRotatedZ.p[2], matRotateZ); 

		MultiplyMatrixVector(triangle.p[0], triangleRotatedX.p[0], matRotateX);
		MultiplyMatrixVector(triangle.p[1], triangleRotatedX.p[1], matRotateX);
		MultiplyMatrixVector(triangle.p[2], triangleRotatedX.p[2], matRotateX);

		MultiplyMatrixVector(triangleRotatedX.p[0], triangleRotatedXZ.p[0], matRotateZ);
		MultiplyMatrixVector(triangleRotatedX.p[1], triangleRotatedXZ.p[1], matRotateZ);
		MultiplyMatrixVector(triangleRotatedX.p[2], triangleRotatedXZ.p[2], matRotateZ);



		triangleTranslated = triangleRotatedXZ;
		triangleTranslated.p[0].z = triangleRotatedXZ.p[0].z + 3.0f;
		triangleTranslated.p[1].z = triangleRotatedXZ.p[1].z + 3.0f;
		triangleTranslated.p[2].z = triangleRotatedXZ.p[2].z + 3.0f;

		MultiplyMatrixVector(triangleTranslated.p[0], triangleProjected.p[0], matrixProjection);
		MultiplyMatrixVector(triangleTranslated.p[1], triangleProjected.p[1], matrixProjection);
		MultiplyMatrixVector(triangleTranslated.p[2], triangleProjected.p[2], matrixProjection);

		//Scale into view
		triangleProjected.p[0].x += 1.0f; 
		triangleProjected.p[0].y += 1.0f;
		triangleProjected.p[1].x += 1.0f; 
		triangleProjected.p[1].y += 1.0f; 
		triangleProjected.p[2].x += 1.0f; 
		triangleProjected.p[2].y += 1.0f;

		triangleProjected.p[0].x *= 0.5f * screenWidth;
		triangleProjected.p[0].y *= 0.5f * screenHeight;
		triangleProjected.p[1].x *= 0.5f * screenWidth;
		triangleProjected.p[1].y *= 0.5f * screenHeight;
		triangleProjected.p[2].x *= 0.5f * screenWidth;
		triangleProjected.p[2].y *= 0.5f * screenHeight;

		DrawTriangle((int)triangleProjected.p[0].x, (int)triangleProjected.p[0].y, (int)triangleProjected.p[1].x, (int)triangleProjected.p[1].y, (int)triangleProjected.p[2].x, (int)triangleProjected.p[2].y, BS_SOLID, 0x0000FF00);
		
		
	}

	return true;
}

//------------------------------------------------------------------------------------------------------------------------

void Engine3D::MultiplyMatrixVector(Vec3d &i, Vec3d &o, Mat4x4 &m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}