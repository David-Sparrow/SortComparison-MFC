
// SortDoc.h : interface of the CSortDoc class
//


#pragma once


class CSortDoc : public CDocument
{
protected: // create from serialization only
	CSortDoc() noexcept;
	DECLARE_DYNCREATE(CSortDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSortDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	int* m_pTabToSort;
	int* m_pTempTab;

	/*DWORD m_nBubbleTime;
	DWORD m_nInsertTime;
	DWORD m_nSelectTime;
	DWORD m_nHalfTime;
	DWORD m_nQuickTime;
	DWORD m_nHeapTime;*/

	DWORD m_nSortTimes[6]; // 0 - bubble; 1 - insert; 2 - select; 3 - half, 4 - quick, 5 - heap


protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	DWORD* GetSortTimes();
	void RunSimpleSorts();
	void RunQuickSorts();
};
