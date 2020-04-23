#pragma once

#include "Draw.h"
#include <vector>
#include <math.h>

using namespace std;


typedef struct Vec3d
{
	float x, y, z;
} Vec3d;

typedef struct Triangle
{
	Vec3d p[3];
} Triangle;

typedef struct Mesh
{
	vector<Triangle> triangles;
} Mesh;

typedef struct Mat4x4
{
	float m[4][4] = { 0 };
}Mat4x4;

class Engine3D 
{
	public:
		Engine3D();
		~Engine3D();

	public:
		virtual void DrawLine(int x1, int y1, int x2, int y2, int lineType, int color);
		virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color);
		virtual void DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color, int brushColor);
	public:
		void setHDC(HDC Hdc);
		void setRect(RECT rect);
	public:
		bool OnUserCreate();
	public:
		bool OnUserUpdate(float fElapsedTime);
		
	private:
		void MultiplyMatrixVector(Vec3d& i, Vec3d& o, Mat4x4& m);
	private:
		Draw draw;
		Mesh meshCube;
		Mat4x4 matrixProjection;




};

