// StarFigure.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "Graphics.h"
#include "StarFigure.h"

// StarFigure

IMPLEMENT_DYNAMIC(StarFigure, CWnd)

StarFigure::StarFigure(int cx, int cy, int x, int y)
{
	this->centerX = cx;
	this->centerY = cy;
	this->x = x;
	this->y = y;
	this->SetRadius();
	this->InitializePoints();
}

void StarFigure::InitializePoints()
{
	float alpha = 3.1415926 / 2;

	for(int i=0; i<5; i++)
	{
		star[i].x = this->centerX + this->radius * cos(alpha);
		star[i].y = this->centerY - this->radius * sin(alpha);
		alpha += 2 * 3.1415926 / 5.0;
	}
}

StarFigure::~StarFigure()
{
}

void StarFigure::Draw(CDC* pDC)
{
	pDC->MoveTo(star[0].x, star[0].y);
	pDC->LineTo(star[2].x, star[2].y);
	pDC->LineTo(star[4].x, star[4].y);
	pDC->LineTo(star[1].x, star[1].y);
	pDC->LineTo(star[3].x, star[3].y);
	pDC->LineTo(star[0].x, star[0].y);
}

bool StarFigure::IsClicked(int x, int y)
{
	/*(if(x >= this->star[2].x && x <= this->star[0].x &&
		y >= this->star[0].y && y <= this->star[2].y)
	{
		return true;
	}*/
	
	if(abs(y - this->star[4].y) <= Figure::IndentationPixels && 
		x >= this->star[1].x && x <= this->star[4].x)
	{
		return true;
	}
	
	return false;
}

void StarFigure::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		CString line;
		line.Format(_T("%d %d %d %d %d \r\n"), 3, this->centerX, this->centerY, this->x, this->y);
		ar.WriteString(line);
	}
}

void StarFigure::SetRadius()
{
	this->radius = sqrt((float)((this->centerX - x) * (this->centerX - x) +
		(this->centerY - y) * (this->centerY - y)));
}

BEGIN_MESSAGE_MAP(StarFigure, CWnd)
END_MESSAGE_MAP()

// StarFigure message handlers