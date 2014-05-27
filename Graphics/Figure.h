#pragma once
// Figure

class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure)

	public:
		static const int IndentationPixels = 3;
		Figure();
		virtual ~Figure();
		virtual void Draw(CDC* pDC){};
		virtual bool IsClicked(int x, int y) {return false;};

	protected:
		DECLARE_MESSAGE_MAP()
};