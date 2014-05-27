// EllipseFigure.cpp : implementation file

#include "stdafx.h"
#include "Graphics.h"
#include "EllipseFigure.h"

// EllipseFigure
IMPLEMENT_DYNAMIC(EllipseFigure, CWnd)

EllipseFigure::EllipseFigure(int x, int y, int r)
{
	this->SetX(x);
	this->SetY(y);
	this->SetRadius(r);
}

EllipseFigure::~EllipseFigure()
{
}

void EllipseFigure::Draw(CDC* pDC)
{
	pDC->Ellipse(this->centerX - this->radius, this->centerY - this->radius * 2,
		this->centerX + this->radius, this->centerY + this->radius * 2);
}

bool EllipseFigure::IsClicked(int x, int y)
{
	if(y - this->radius*2 <= this->centerY || y + this->radius*2 == this->centerY
		|| x - this->radius == this->centerX || x + this->radius == this->centerX)
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

void EllipseFigure::SetX(int x)
{
	this->centerX = x;
}

void EllipseFigure::SetY(int y)
{
	this->centerY = y;
}

void EllipseFigure::SetRadius(int x)
{
	this->radius = this->centerX - x;
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