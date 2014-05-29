#pragma once
#include "Figure.h"
// RectangleFigure

class RectangleFigure : public CWnd, public Figure
{
	DECLARE_DYNAMIC(RectangleFigure)
	private:
		int topLeftX, topLeftY, downRightX, downRightY;

	public:
		RectangleFigure(int topLeftX, int topLeftY, int downRightX, int downRightY);
		virtual ~RectangleFigure();
		void Draw(CDC* pDC);
		bool IsClicked(int x, int y);
		void Serialize(CArchive& ar);
		void Drag(int x, int y);
		void SetTopLeftX(int x);
		void SetTopLeftY(int y);
		void SetDownRightX(int x);
		void SetDownRightY(int y);
		int GetTopLeftX();
		int GetTopLeftY();
		int GetDownRightX();
		int GetDownRightY();

	protected:
		DECLARE_MESSAGE_MAP()
};