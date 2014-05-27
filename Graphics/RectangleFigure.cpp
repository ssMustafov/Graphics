// RectangleFigure.cpp : implementation file

#include "stdafx.h"
#include "Graphics.h"
#include "RectangleFigure.h"
// RectangleFigure

IMPLEMENT_DYNAMIC(RectangleFigure, CWnd)

RectangleFigure::RectangleFigure(int topLeftX, int topLeftY, int downRightX, int downRightY)
{
	this->SetTopLeftX(topLeftX);
	this->SetTopLeftY(topLeftY);
	this->SetDownRightX(downRightX);
	this->SetDownRightY(downRightY);
}

RectangleFigure::~RectangleFigure()
{
}

void RectangleFigure::Draw(CDC* pDC)
{
	pDC->Rectangle(this->topLeftX, this->topLeftY, this->downRightX, this->downRightY);
}

bool RectangleFigure::IsClicked(int x, int y)
{
	bool topAndBottomLines = ((x >= this->topLeftX && x <= this->downRightX) || x >= this->downRightX && x <= this->topLeftX);
	bool leftAndRightLines = ((y >= this->topLeftY && y <= this->downRightY) || (y >= this->downRightY && y <= this->topLeftY));

	// Top line
	if(abs(y - this->topLeftY) <= Figure::IndentationPixels && topAndBottomLines)
	{
		return true;
	}
	
	// Bottom line;
	if(abs(y - this->downRightY) <= Figure::IndentationPixels && topAndBottomLines)
	{
		return true;
	}

	// Left line
	if(abs(x - this->topLeftX) <= Figure::IndentationPixels && leftAndRightLines)
	{
		return true;
	}

	// Right line
	if(abs(x - this->downRightX) <= Figure::IndentationPixels && leftAndRightLines)
	{
		return true;
	}
	
	return false;
}

void RectangleFigure::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		CString line;
		line.Format(_T("%d %d %d %d %d \r\n"), 2, this->topLeftX, this->topLeftY, this->downRightX, this->downRightY);
		ar.WriteString(line);
	}
}

void RectangleFigure::SetTopLeftX(int x)
{
	this->topLeftX = x;
}

void RectangleFigure::SetTopLeftY(int y)
{
	this->topLeftY = y;
}

void RectangleFigure::SetDownRightX(int x)
{
	this->downRightX = x;
}

void RectangleFigure::SetDownRightY(int y)
{
	this->downRightY = y;
}

int RectangleFigure::GetTopLeftX()
{
	return this->topLeftX;
}

int RectangleFigure::GetTopLeftY()
{
	return this->topLeftY;
}

int RectangleFigure::GetDownRightX()
{
	return this->downRightX;
}

int RectangleFigure::GetDownRightY()
{
	return this->downRightY;
}

BEGIN_MESSAGE_MAP(RectangleFigure, CWnd)
END_MESSAGE_MAP()

// RectangleFigure message handlers