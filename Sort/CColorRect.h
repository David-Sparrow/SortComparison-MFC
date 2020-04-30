#pragma once
#include <atltypes.h>

class CColorRect : public CRect
{
private:
	CPen* m_pPen;
	CBrush* m_pBrush;

	void CreateAttr(int penWidth, COLORREF penColor, COLORREF bkgColor);

public:
	CColorRect(CRect* pRect = NULL, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
	CColorRect(const CRect&, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
	CColorRect(const CPoint& leftTop, const CPoint& rightBottom, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
	CColorRect(const CPoint&, const CSize&, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);

	~CColorRect();

public:
	void PaintColorRect(CDC* pDC);
	void setAttr(int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
	CPen* getRectPen() const;
	CBrush* getRectBrush() const;

};
