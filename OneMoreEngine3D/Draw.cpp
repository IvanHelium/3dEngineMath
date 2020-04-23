#include "Draw.h"


Draw::Draw()
{
    hdc = nullptr;
    rect = {640, 480};
    hPen = CreatePen(0, 0, RGB(0x00,0xFF,0x00));
}

Draw::~Draw()
{

}

BOOL Draw::DrawLine(int x1, int y1, int x2, int y2, int lineType, int width, DrawColor color)
{
    POINT pt;
    switch (lineType)
    {
        case PS_SOLID:
            break;
        case PS_DASH:
            break;
        case PS_DOT:
            break;
        case PS_DASHDOT:
            break;
        case PS_DASHDOTDOT:
            break;
        default:
            lineType = 0;
            break;
    }
    if (width > LINEWIDTHLIMIT){
        width = LINEWIDTHLIMIT;
    }
    HPEN dashPen = CreatePen(lineType, width, RGB(color.RED, color.GREEN, color.BLUE));
    SelectObject(hdc, dashPen);
    MoveToEx(hdc, x1, y1, &pt);
    return LineTo(hdc, x2, y2);
}

BOOL Draw::DrawLine(int x1, int y1, int x2, int y2, int lineType, int width, int color)
{
    POINT pt;
    switch (lineType)
    {
    case PS_SOLID:
        break;
    case PS_DASH:
        break;
    case PS_DOT:
        break;
    case PS_DASHDOT:
        break;
    case PS_DASHDOTDOT:
        break;
    default:
        lineType = 0;
        break;
    }
    if (width > LINEWIDTHLIMIT) {
        width = LINEWIDTHLIMIT;
    }
    
    //HPEN hPen = CreatePen(lineType, width, RGB((byte)(color&(0x000000FF)), (byte)((color & (0x0000FF00)) >> 8), (byte)((color & (0x00FF0000)) >> 16)));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, x1, y1, &pt);
    return LineTo(hdc, x2, y2);
}

void Draw::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, DrawColor color)
{

}

void Draw::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color)
{
    DrawLine(x1, y1, x2, y2, lineType, TRIANGLE_LINE_WIDTH, color);
    DrawLine(x2, y2, x3, y3, lineType, TRIANGLE_LINE_WIDTH, color);
    DrawLine(x3, y3, x1, y1, lineType, TRIANGLE_LINE_WIDTH, color);
}
void Draw::DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, DrawColor color)
{

}

void Draw::DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int lineType, int color, int brushColor)
{
    HPEN hPen = CreatePen(lineType, TRIANGLE_LINE_WIDTH, RGB((byte)(color & (0x000000FF)), (byte)((color & (0x0000FF00)) >> 8), (byte)((color & (0x00FF0000)) >> 16)) );
    HPEN hOldPen = SelectPen(hdc, hPen);

    HBRUSH hBrush = CreateSolidBrush(RGB((byte)(brushColor & (0x000000FF)), (byte)((brushColor & (0x0000FF00)) >> 8), (byte)((brushColor & (0x00FF0000)) >> 16)));
    HBRUSH hOldBrush = SelectBrush(hdc, hBrush);

    POINT vertices[] = { {x1, y1}, {x2, y2}, {x3, y3} };
    Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

    SelectBrush(hdc, hOldBrush);
    DeleteObject(hBrush);

    SelectPen(hdc, hOldPen);
    DeleteObject(hPen);
}

//-----------------------------------------------------------------------------------------------
HDC Draw::GetHDC()
{
    return hdc;
}

void Draw::SetHDC(HDC Hdc)
{
    hdc = Hdc;
}

//------------------------------------------------------------------------------------------------

RECT Draw::GetRect()
{
    return rect;
}

void Draw::SetRect(RECT Rect)
{
    rect = Rect;
}