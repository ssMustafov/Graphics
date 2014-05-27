
// GraphicsDoc.cpp : implementation of the CGraphicsDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Graphics.h"
#endif

#include "GraphicsDoc.h"
#include "Line.h"
#include "EllipseFigure.h"
#include "RectangleFigure.h"
#include "StarFigure.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicsDoc

IMPLEMENT_DYNCREATE(CGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicsDoc construction/destruction

CGraphicsDoc::CGraphicsDoc()
{
	// TODO: add one-time construction code here

}

CGraphicsDoc::~CGraphicsDoc()
{
}

BOOL CGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Set specifications
	numberOfClicks = 0;
	numberOfObjects = 0;
	mode = 0;

	// Allocate memory for 50 elements in the vector
	figures.reserve(50);

	// Temporary variables
	x = 0;
	y = 0;

	return TRUE;
}

// CGraphicsDoc serialization

void CGraphicsDoc::Serialize(CArchive& ar)
{
	CString line;

	if (ar.IsStoring())
	{
		// storing code
		for(int i=0; i<numberOfObjects; i++)
		{
			figures[i]->Serialize(ar);
		}
	}
	else
	{
		// loading code
		numberOfObjects = 0;
		numberOfClicks = 0;
		mode = 0;
		CString line;
		int x1, y1, m, length, radius;

		while(ar.ReadString(line))
		{
			CT2A ascii(line);
			TRACE(_T("ASCII: %S\n"), ascii.m_psz);

			if(line[0] == '0')
			{
				sscanf(ascii, "%d %d %d %d", &m, &x, &y, &length);
				figures.push_back(new Line(x, y, length+x));
				numberOfObjects++;
			}
			else if(line[0] == '1')
			{
				sscanf(ascii, "%d %d %d %d", &m, &x, &y, &radius);
				figures.push_back(new EllipseFigure(x, y, radius+x));
				numberOfObjects++;
			}
			else if(line[0] == '2')
			{
				sscanf(ascii, "%d %d %d %d %d", &m, &x, &y, &x1, &y1);
				figures.push_back(new RectangleFigure(x, y, x1, y1));
				numberOfObjects++;
			}
			else if(line[0] == '3')
			{
				sscanf(ascii, "%d %d %d %d %d", &m, &x, &y, &x1, &y1);
				figures.push_back(new StarFigure(x, y, x1, y1));
				numberOfObjects++;
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CGraphicsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CGraphicsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphicsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphicsDoc diagnostics

#ifdef _DEBUG
void CGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicsDoc commands
