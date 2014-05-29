#pragma once
#include "Figure.h"
// EllipseFigure

class EllipseFigure : public CWnd, public Figure
{
	DECLARE_DYNAMIC(EllipseFigure)
	private:
		int centerX, centerY, radius;

	public:
		EllipseFigure(int cx, int cy, int x, int y);
		EllipseFigure(int cx, int cy, int r);
		virtual ~EllipseFigure();
		void Draw(CDC* pDC);
		bool IsClicked(int x, int y);
		void Serialize(CArchive& ar);
		void Drag(int x, int y);
		void SetX(int x);
		void SetY(int y);
		void SetRadius(int x, int y);
		int GetX();
		int GetY();
		int GetRadius();

	protected:
		DECLARE_MESSAGE_MAP()
};