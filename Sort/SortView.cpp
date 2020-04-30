
// SortView.cpp : implementation of the CSortView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sort.h"
#endif

#include "SortDoc.h"
#include "SortView.h"
#include "CColorRect.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortView

IMPLEMENT_DYNCREATE(CSortView, CView)

BEGIN_MESSAGE_MAP(CSortView, CView)
	ON_COMMAND(ID_ALL_SORT, &CSortView::OnAllSort)
	ON_COMMAND(ID_SIMPLE_SORT, &CSortView::OnSimpleSort)
	ON_COMMAND(ID_QUICK_SORT, &CSortView::OnQuickSort)
END_MESSAGE_MAP()

// CSortView construction/destruction

CSortView::CSortView() noexcept
{
	// TODO: add construction code here
	m_pClientRect = new CRect();

}

CSortView::~CSortView()
{
	delete m_pClientRect;
}

BOOL CSortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSortView drawing

void CSortView::OnDraw(CDC* pDC)
{
	CSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// 0 - bubble; 1 - insert; 2 - select; 3 - half, 4 - quick, 5 - heap
	DWORD* sortTimes = pDoc->GetSortTimes();

	DWORD maxTime = 0L;
	for (size_t i = 0; i < 6; i++)
	{
		if (maxTime < sortTimes[i])
			maxTime = sortTimes[i];
	}

	//Wartosci do wypisania
	DWORD maxValueOnChart = maxTime + OFFSET;
	while (maxValueOnChart++ % NUMLINES);
	DWORD stepBetweenLines = maxValueOnChart / NUMLINES;

	//Dlugosci w pikselach
	unsigned int verticalAxisLength = m_pClientRect->Height() - 80;
	unsigned int verticalGap = (verticalAxisLength - 10) / NUMLINES; //Minus 10 aby os wystwala ponad 20sta linie o 10px
	unsigned int horizontalAxisLength = m_pClientRect->Width() - 60;

	//Rysowanie osi
	pDC->MoveTo(40, 40);
	pDC->LineTo(40, 40 + verticalAxisLength);
	pDC->LineTo(40 + horizontalAxisLength, 40 + verticalAxisLength);

	//Rysowanie siatki
	CPen* pGrayPen = new CPen(PS_SOLID, 1, RGB(110, 110, 110));
	CPen* pOldPen = pDC->SelectObject(pGrayPen);
	
	//Tworzenie fontu dla wartosci numerycznych oraz nazw sortowan
	CFont* pFontNum = new CFont();
	pFontNum->CreateFontW(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("FontNum"));

	CFont* pFontName = new CFont();
	pFontName->CreateFontW(16, 0, 0, 0, FW_BOLD, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("FontName"));

	CFont* pOldFont = pDC->SelectObject(pFontNum);

	for (size_t i = 1; i <= NUMLINES; i++)
	{
		CString valueOfLine;
		valueOfLine.Format(L"%ld", i * stepBetweenLines);
		CSize sizeOfText = pDC->GetTextExtent(valueOfLine);
		pDC->TextOutW(35 - sizeOfText.cx, 32 + verticalAxisLength - (i * verticalGap), valueOfLine);
		pDC->MoveTo(40, 40 + verticalAxisLength - (i * verticalGap));
		pDC->LineTo(40 + horizontalAxisLength, 40 + verticalAxisLength - (i * verticalGap));
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);

	//Wypisywanie nazw sortowan
	unsigned int lengthFromVerticalAxis = 10;
	int middlesOfNames[6] = { 0 };
	pOldFont = pDC->SelectObject(pFontName);
	for (size_t i = 0; i < 6; i++)
	{
		CString nameSort;
		nameSort.LoadStringW(IDS_BUBBLE + i);
		CSize sizeOfText = pDC->GetTextExtent(nameSort);
		middlesOfNames[i] = 40 + lengthFromVerticalAxis + (sizeOfText.cx / 2);
		pDC->TextOutW(40 + lengthFromVerticalAxis, m_pClientRect->Height() - 30, nameSort);
		lengthFromVerticalAxis += sizeOfText.cx + 20;
	}

	pDC->SelectObject(pOldFont);
	
	//Obliczanie wysokosci prostokatow
	int heightOfRect[6] = { 0 };
	for (size_t i = 0; i < 6; i++)
	{
		heightOfRect[i] = (verticalGap * sortTimes[i]) / stepBetweenLines;
	}
	
	//Rysowanie prostokatow
	for (size_t i = 0; i < 6; i++)
	{
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;
		CColorRect x(CPoint(middlesOfNames[i] - 10, m_pClientRect->Height() - 40), CSize(20, -heightOfRect[i]), 1, BLACK, RGB(r,g,b));
		x.PaintColorRect(pDC);
	}

	delete pGrayPen;
	delete pFontName;
	delete pFontNum;
	
	
	/*//DEBUG
	CString str;
	str.Format(L"[0] = %ld, [1] = %ld, [2] = %ld, [3] = %ld, [4] = %ld, [5] = %ld",sortTimes[0], sortTimes[1], sortTimes[2], sortTimes[3], sortTimes[4], sortTimes[5]);
	pDC->TextOutW(200, 300, MAKEINTRESOURCE(IDS_INSERTION) str);*/
}


// CSortView diagnostics

#ifdef _DEBUG
void CSortView::AssertValid() const
{
	CView::AssertValid();
}

void CSortView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortDoc* CSortView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortDoc)));
	return (CSortDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortView message handlers


void CSortView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	GetClientRect(m_pClientRect);

	CView::OnPrepareDC(pDC, pInfo);
}


void CSortView::OnAllSort()
{
	// TODO: Add your command handler code here
	CSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RunSimpleSorts();
	pDoc->RunQuickSorts();
	Invalidate();
}


void CSortView::OnSimpleSort()
{
	// TODO: Add your command handler code here
	CSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RunSimpleSorts();
	Invalidate();
	//pDoc->UpdateAllViews(NULL);
}


void CSortView::OnQuickSort()
{
	// TODO: Add your command handler code here
	CSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RunQuickSorts();
	Invalidate();
}
