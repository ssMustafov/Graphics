#pragma once

#include "Figure.h"
// Line

class Line : public CWnd, public Figure
{
	DECLARE_DYNAMIC(Line)
	private:
		int x, y, length;

	public:
		Line(int x, int y, int length);
		virtual ~Line();
		void Draw(CDC* pDC);
		bool IsClicked(int x, int y);
		void Serialize(CArchive& ar);
		void Drag(int x, int y);
		void SetX(int x);
		void SetY(int y);
		void SetLength(int x);
		int GetX();
		int GetY();
		int GetLength();

	protected:
		DECLARE_MESSAGE_MAP()
};


