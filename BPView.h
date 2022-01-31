
// BPView.h : interface of the CBPView class
//

#pragma once


class CBPView : public CView
{
protected: // create from serialization only
	CBPView() noexcept;
	DECLARE_DYNCREATE(CBPView)

// Attributes
public:
	CBPDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	void draw_histogram(CDC* pDC, CBPDoc* pDoc);
	void draw_pvalues(CDC* pDC, CBPDoc* pDoc);
	void draw_powers(CDC* pDC, CBPDoc* pDoc);
public:
};

#ifndef _DEBUG  // debug version in BPView.cpp
inline CBPDoc* CBPView::GetDocument() const
   { return reinterpret_cast<CBPDoc*>(m_pDocument); }
#endif

