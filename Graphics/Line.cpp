// Line.cpp : implementation file
//

#include "stdafx.h"
#include "Graphics.h"
#include "Line.h"
// Line

IMPLEMENT_DYNAMIC(Line, CWnd)

Line::Line(int x, int y, int length)
{
	this->SetX(x);
	this->SetY(y);
	this->SetLength(length);
}

Line::~Line()
{
}

void Line::Draw(CDC* pDC)
{
	pDC->MoveTo(this->x, this->y);
	pDC->LineTo(this->x + this->length, this->y);
}

bool Line::IsClicked(int x, int y)
{
	if(abs(y - this->y) <= Figure::IndentationPixels &&
		(x >= this->x && x <= (this->length + this->x)))
	{
		return true;
	}
	else if(abs(y - this->y) <= Figure::IndentationPixels &&
		(x >= (this->length + this->x) && x <= this->x))
	{
		return true;
	}

	return false;
}

void Line::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		CString line;
		line.Format(_T("%d %d %d %d \r\n"), 0, this->x, this->y, this->length);
		ar.WriteString(line);
	}
}

void Line::SetX(int x)
{
	this->x = x;
}

void Line::SetY(int y)
{
	this->y = y;
}

void Line::SetLength(int x)
{
	this->length = x - this->x;
}

int Line::GetX()
{
	return this->x;
}

int Line::GetY()
{
	return this->y;
}

int Line::GetLength()
{
	return this->length;
}

BEGIN_MESSAGE_MAP(Line, CWnd)
END_MESSAGE_MAP()

// Line message handlers