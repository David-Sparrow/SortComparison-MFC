
// SortView.h : interface of the CSortView class
//

#pragma once


class CSortView : public CView
{
protected: // create from serialization only
	CSortView() noexcept;
	DECLARE_DYNCREATE(CSortView)

// Attributes
public:
	CSortDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	CRect* m_pClientRect;


protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnAllSort();
	afx_msg void OnSimpleSort();
	afx_msg void OnQuickSort();
};

#ifndef _DEBUG  // debug version in SortView.cpp
inline CSortDoc* CSortView::GetDocument() const
   { return reinterpret_cast<CSortDoc*>(m_pDocument); }
#endif

