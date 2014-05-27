#pragma once

#include "Figure.h"
// StarFigure

class StarFigure : public CWnd, public Figure
{
	DECLARE_DYNAMIC(StarFigure)
private:
	int centerX, centerY, radius, x, y;
	CPoint star[5];
	void SetRadius();
	void InitializePoints();

public:
	StarFigure(int cx, int cy, int x, int y);
	virtual ~StarFigure();
	void Draw(CDC* pDC);
	bool IsClicked(int x, int y);
	void Serialize(CArchive& ar);

protected:
	DECLARE_MESSAGE_MAP()
};


