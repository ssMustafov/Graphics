#pragma once
#include "Figure.h"
// EllipseFigure

class EllipseFigure : public CWnd, public Figure
{
	DECLARE_DYNAMIC(EllipseFigure)
	private:
		int centerX, centerY, radius;

	public:
		EllipseFigure(int x, int y, int r);
		virtual ~EllipseFigure();
		void Draw(CDC* pDC);
		bool IsClicked(int x, int y);
		void Serialize(CArchive& ar);
		void SetX(int x);
		void SetY(int y);
		void SetRadius(int x);
		int GetX();
		int GetY();
		int GetRadius();

	protected:
		DECLARE_MESSAGE_MAP()
};