// EllipseFigure.cpp : implementation file

#include "stdafx.h"
#include <math.h>
#include "Graphics.h"
#include "EllipseFigure.h"

// EllipseFigure
IMPLEMENT_DYNAMIC(EllipseFigure, CWnd)

EllipseFigure::EllipseFigure(int cx, int cy, int x, int y)
{
	this->SetX(cx);
	this->SetY(cy);
	this->SetRadius(x, y);
}

EllipseFigure::EllipseFigure(int cx, int cy, int r)
{
	this->SetX(cx);
	this->SetY(cy);
	this->radius = r;
}

EllipseFigure::~EllipseFigure()
{
}

void EllipseFigure::Draw(CDC* pDC)
{
	pDC->Ellipse(this->centerX - this->radius * 2, this->centerY - this->radius,
		this->centerX + this->radius * 2, this->centerY + this->radius);
}

bool EllipseFigure::IsClicked(int x, int y)
{
	float rX = pow((float)x - this->centerX, 2);
	float rY = pow((float)y - this->centerY, 2);
	int radius = sqrt((rX + 4 * rY) / 4);

	if(abs(radius - this->radius) <= 3)
	{
		return true;
	}
	
	return false;
}

void EllipseFigure::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		CString line;
		line.Format(_T("%d %d %d %d \r\n"), 1, this->centerX, this->centerY, this->radius);
		ar.WriteString(line);
	}
}

void EllipseFigure::Drag(int x, int y)
{
	this->centerX = x;
	this->centerY = y;
}

void EllipseFigure::SetX(int x)
{
	this->centerX = x;
}

void EllipseFigure::SetY(int y)
{
	this->centerY = y;
}

void EllipseFigure::SetRadius(int x, int y)
{
	float rX = pow((float)x - this->centerX, 2);
	float rY = pow((float)y - this->centerY, 2);
	this->radius = sqrt((rX + 4 * rY) / 4);
}

int EllipseFigure::GetX()
{
	return this->centerX;
}

int EllipseFigure::GetY()
{
	return this->centerY;
}

int EllipseFigure::GetRadius()
{
	return this->radius;
}

BEGIN_MESSAGE_MAP(EllipseFigure, CWnd)
END_MESSAGE_MAP()

// EllipseFigure message handlers