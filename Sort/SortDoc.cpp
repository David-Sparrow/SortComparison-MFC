
// SortDoc.cpp : implementation of the CSortDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sort.h"
#endif

#include "SortDoc.h"
#include <time.h>
#include "sortAlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSortDoc

IMPLEMENT_DYNCREATE(CSortDoc, CDocument)

BEGIN_MESSAGE_MAP(CSortDoc, CDocument)
END_MESSAGE_MAP()


// CSortDoc construction/destruction

CSortDoc::CSortDoc() noexcept 
	/*m_nBubbleTime(0), m_nHalfTime(0), m_nHeapTime(0), m_nInsertTime(0), m_nQuickTime(0), m_nSelectTime(0)*/
{
	// TODO: add one-time construction code here
	memset(m_nSortTimes, 0, sizeof(m_nSortTimes));

	srand(time(NULL));
	m_pTabToSort = (int*)calloc(TABSIZE, sizeof(int));
	m_pTempTab = (int*)calloc(TABSIZE, sizeof(int));

	int* tempPtr = m_pTabToSort;
	for (size_t i = 0; i < TABSIZE; i++)
	{
		*tempPtr = rand() % 10000;
		tempPtr++;
	}

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);
}

CSortDoc::~CSortDoc()
{
	free(m_pTabToSort);
	free(m_pTempTab);
}

BOOL CSortDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



// CSortDoc serialization

void CSortDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSortDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSortDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSortDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSortDoc diagnostics

#ifdef _DEBUG
void CSortDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSortDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSortDoc commands


DWORD* CSortDoc::GetSortTimes()
{
	// TODO: Add your implementation code here.
	return m_nSortTimes;
}


void CSortDoc::RunSimpleSorts()
{
	// TODO: Add your implementation code here.
	// 0 - bubble; 1 - insert; 2 - select; 3 - half, 4 - quick, 5 - heap
	DWORD startTime = GetTickCount();
	BubbleSort(m_pTempTab, TABSIZE);
	DWORD stopTime = GetTickCount();
	m_nSortTimes[0] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);

	startTime = GetTickCount();
	InsertionSort(m_pTempTab, TABSIZE);
	stopTime = GetTickCount();
	m_nSortTimes[1] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);

	startTime = GetTickCount();
	SelectionSort(m_pTempTab, TABSIZE);
	stopTime = GetTickCount();
	m_nSortTimes[2] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);

	startTime = GetTickCount();
	HalfInsertionSort(m_pTempTab, TABSIZE);
	stopTime = GetTickCount();
	m_nSortTimes[3] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);
}


void CSortDoc::RunQuickSorts()
{
	// TODO: Add your implementation code here.
	// 0 - bubble; 1 - insert; 2 - select; 3 - half, 4 - quick, 5 - heap

	DWORD startTime = GetTickCount();
	QuickSort(m_pTempTab, 0, TABSIZE);
	DWORD stopTime = GetTickCount();
	m_nSortTimes[4] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);

	startTime = GetTickCount();
	HeapSort(m_pTempTab, TABSIZE);
	stopTime = GetTickCount();
	m_nSortTimes[5] = (stopTime - startTime);

	memcpy(m_pTempTab, m_pTabToSort, sizeof(int) * TABSIZE);
}
