#pragma once

#include<Windows.h> //implemented realisation
#include <windowsx.h>

//#define PS_SOLID            (0)
//#define PS_DASH             (1)       /* -------  */
//#define PS_DOT              (2)       /* .......  */
//#define PS_DASHDOT          (3)       /* _._._._  */
//#define PS_DASHDOTDOT       (4)       /* _.._.._  */


#define	LINEWIDTHLIMIT		(10)	//limit maximum size of line
#define TRIANGLE_LINE_WIDTH (1)

typedef struct DrawColor
{
	byte RED;
	byte GREEN;
	byte BLUE;
} DrawColor;


class Draw
{
	public:
		Draw();
		~Draw();
	public:
		virtual BOOL DrawLine(int x1, int y1, int x2, int y2, int lineType, int width, DrawColor color);
		virtual BOOL DrawLine(int x1, int y1, int x2, int y2, int lineType, int width, int color);
		virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, DrawColor color);
		virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color);
		virtual void DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, DrawColor color);
		virtual void DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color, int brushColor);
	public:
		HDC GetHDC();
		void SetHDC(HDC Hdc);
		RECT GetRect();
		void SetRect(RECT Rect);
	private:
		HDC hdc;
		RECT rect;
		HPEN hPen;
};

