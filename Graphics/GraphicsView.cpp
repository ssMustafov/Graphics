
// GraphicsView.cpp : implementation of the CGraphicsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Graphics.h"
#endif

#include "GraphicsDoc.h"
#include "GraphicsView.h"
#include "Line.h"
#include "EllipseFigure.h"
#include "RectangleFigure.h"
#include "StarFigure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsView::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_MODE_0, &CGraphicsView::OnButtonMode0)
	ON_COMMAND(ID_BUTTON_MODE_1, &CGraphicsView::OnButtonMode1)
	ON_COMMAND(ID_BUTTON_MODE_2, &CGraphicsView::OnButtonMode2)
	ON_COMMAND(ID_BUTTON_MODE_3, &CGraphicsView::OnButtonMode3)
END_MESSAGE_MAP()

// CGraphicsView construction/destruction

CGraphicsView::CGraphicsView()
{
	// TODO: add construction code here

}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGraphicsView drawing

void CGraphicsView::OnDraw(CDC* pDC)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	
	// Select transparent brush
	pDC->SelectStockObject(HOLLOW_BRUSH);
	
	// Draw objects
	for(int i=0; i<pDoc->numberOfObjects; i++)
	{
		pDoc->figures[i]->Draw(pDC);
	}
}

// CGraphicsView printing

void CGraphicsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

//void CGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CGraphicsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CGraphicsView diagnostics

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsView message handlers

void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	
	if(nFlags == 0x0008)
	{
		// if Ctrl is holding down delete object
		OnRButtonDown(nFlags, point);
	}
	else
	{
		// Add new objects
		if(pDoc->numberOfClicks % 2 == 0)
		{
			// If the click is even set the first point of the figure
			pDoc->x = point.x;
			pDoc->y = point.y;
		}
		else
		{
			// If the click is odd check which figure is drawing
			// and add it to the vector 
			if(pDoc->mode == 0)
			{
				// Line
				pDoc->figures.push_back(new Line(pDoc->x, pDoc->y, point.x));
			}
			else if(pDoc->mode == 1)
			{
				// Ellipse
				pDoc->figures.push_back(new EllipseFigure(pDoc->x, pDoc->y, point.x));
			}
			else if(pDoc->mode == 2)
			{
				// Rectangle
				pDoc->figures.push_back(new RectangleFigure(pDoc->x, pDoc->y, point.x, point.y));
			}
			else if(pDoc->mode == 3)
			{
				// Star
				pDoc->figures.push_back(new StarFigure(pDoc->x, pDoc->y, point.x, point.y));
			}
			
			pDoc->numberOfObjects++;

			// Update the screen
			Invalidate();
		}

		pDoc->numberOfClicks++;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CGraphicsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	// Detect if clicked on any object and delete it
	for(int i=0; i<pDoc->numberOfObjects; i++)
	{
		if(pDoc->figures[i]->IsClicked(point.x, point.y))
		{
			pDoc->figures.erase(pDoc->figures.begin() + i);
			pDoc->numberOfObjects--;
			Invalidate();
		}
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CGraphicsView::OnButtonMode0()
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	pDoc->mode = 0;
	Invalidate();
}


void CGraphicsView::OnButtonMode1()
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	pDoc->mode = 1;
	Invalidate();
}


void CGraphicsView::OnButtonMode2()
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	pDoc->mode = 2;
	Invalidate();
}


void CGraphicsView::OnButtonMode3()
{
	// Get the current document
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	pDoc->mode = 3;
	Invalidate();
}
