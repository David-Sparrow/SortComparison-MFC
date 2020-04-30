#include "pch.h"
#include "CColorRect.h"

CColorRect::CColorRect(CRect * pRect, int penWidth, COLORREF penColor, COLORREF bkgColor) :
	CRect(pRect)
{
	CreateAttr(penWidth, penColor, bkgColor);
}

CColorRect::CColorRect(const CRect & rect, int penWidth, COLORREF penColor, COLORREF bkgColor) :
	CRect(rect)
{
	CreateAttr(penWidth, penColor, bkgColor);
}

CColorRect::CColorRect(const CPoint & leftTop, const CPoint & rightBottom, int penWidth, COLORREF penColor, COLORREF bkgColor) :
	CRect(leftTop,rightBottom)
{
	CreateAttr(penWidth, penColor, bkgColor);
}

CColorRect::CColorRect(const CPoint & point, const CSize & size, int penWidth, COLORREF penColor, COLORREF bkgColor) :
	CRect(point, size)
{
	CreateAttr(penWidth, penColor, bkgColor);
}

CColorRect::~CColorRect()
{
	delete m_pBrush;
	delete m_pPen;
}

void CColorRect::PaintColorRect(CDC * pDC)
{
	CBrush* oldBrush = pDC->SelectObject(m_pBrush);
	CPen* oldPen = pDC->SelectObject(m_pPen);
	pDC->Rectangle(this);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

void CColorRect::setAttr(int penWidth, COLORREF penColor, COLORREF bkgColor)
{
	m_pBrush->DeleteObject();
	m_pPen->DeleteObject();
	m_pBrush->CreateSolidBrush(bkgColor);
	m_pPen->CreatePen(PS_SOLID, penWidth, penColor);
}

CPen * CColorRect::getRectPen() const
{
	return m_pPen;
}

CBrush * CColorRect::getRectBrush() const
{
	return m_pBrush;
}

void CColorRect::CreateAttr(int penWidth, COLORREF penColor, COLORREF bkgColor)
{
	m_pPen = new CPen(PS_SOLID, penWidth, penColor);
	m_pBrush = new CBrush(bkgColor);
}
