
// BPView.cpp : implementation of the CBPView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BP.h"
#endif

#include "BPDoc.h"
#include "BPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBPView

IMPLEMENT_DYNCREATE(CBPView, CView)

BEGIN_MESSAGE_MAP(CBPView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBPView construction/destruction

CBPView::CBPView() noexcept
{
	// TODO: add construction code here

}

CBPView::~CBPView()
{
}

BOOL CBPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBPView drawing

void CBPView::OnDraw(CDC* pDC)
{
	CBPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	pDoc->SetTitle(L"Geometric distribution");
	switch (pDoc->f) {
	case 1:draw_histogram(pDC, pDoc); break;
	case 2:draw_pvalues(pDC, pDoc); break;
	case 3:draw_powers(pDC, pDoc); break;
	}
}

void CBPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBPView diagnostics

#ifdef _DEBUG
void CBPView::AssertValid() const
{
	CView::AssertValid();
}

void CBPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBPDoc* CBPView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBPDoc)));
	return (CBPDoc*)m_pDocument;
}
#endif //_DEBUG


// CBPView message handlers


void CBPView::draw_histogram(CDC* pDC, CBPDoc* pDoc)
{
	// TODO: Add your implementation code here.
	CRect rc;
	GetClientRect(&rc);
	pDC->SelectStockObject(BLACK_PEN);

	int k(pDoc->s->get_df()), m,max_a(0),n(pDoc->s->get_n());
	for (int i = 0; i < k; ++i) {
		if (pDoc->s->empirical_freq[i])
			m = i;
		if (pDoc->s->empirical_freq[i] > max_a)
			max_a = pDoc->s->empirical_freq[i];
	}
	max_a = max_a > n*pDoc->d.get_p() ? max_a : n *pDoc->d.get_p();
	int step_x((rc.Width() - 50) / m);
	step_x = step_x % 2 ? step_x - 1 : step_x;
	int j_x(30),j_n(30 + step_x / 2),j_y(rc.Height()-65);
	for (int i = 0; i < m; ++i) {
		CStringW s;
		s.Format(_T("%d"), i);
		pDC->TextOut(j_n, rc.Height() - 20, s);
		j_n += step_x;
		pDC->SelectStockObject(GRAY_BRUSH);
		//pDC->Rectangle(j_x, 40 + j_y - j_y *n* pDoc->d.get_probability(i)/max_a, j_x + step_x, rc.Height() - 25);
		pDC->Rectangle(j_x, 40 + j_y - j_y * pDoc->s->empirical_freq[i] / max_a, j_x + step_x, rc.Height() - 25);
		pDC->SelectStockObject(LTGRAY_BRUSH);
		if (n*pDoc->d.get_probability(i) > pDoc->s->empirical_freq[i])
			pDC->Rectangle(j_x, 40 + j_y - j_y * n * pDoc->d.get_probability(i) / max_a, j_x + step_x, 40 + j_y - j_y * pDoc->s->empirical_freq[i] / max_a);
		else
			pDC->Rectangle(j_x, 40 + j_y - j_y * n * pDoc->d.get_probability(i) / max_a, j_x + step_x, rc.Height() - 25);
		j_x += step_x;
	}
	

	//X line
	pDC->MoveTo(20, rc.Height() - 25);
	pDC->LineTo(rc.Width() - 20, rc.Height() - 25);
	pDC->TextOut(rc.Width() - 40, rc.Height() - 20, L"Value");

	//Y line
	pDC->MoveTo(30, rc.Height() - 10);
	pDC->LineTo(30, 20);

	//parameters
	CStringW s;
	s.Format(_T("%d"), max_a);
	pDC->TextOut(5, 35, s);
	s.Format(_T("Frequencies     t=%.2lf   degrees of freedom=%d   pvalue=%.2lf"), pDoc->t, pDoc->s->get_df(), pDoc->plevel);
	pDC->TextOut(35, 20, s);
	//s.Format(_T("t=%.2lf"), pDoc->t);
	//pDC->TextOut(200, 20, s);
	//s.Format(_T("degrees of freedom=%d"), pDoc->s->get_k());
	//pDC->TextOut(300, 20, s);
	//s.Format(_T("pvalue=%.2lf"), pDoc->plevel);
	//pDC->TextOut(500, 20, s);
}

void CBPView::draw_pvalues(CDC* pDC, CBPDoc* pDoc)
{
	// TODO: Add your implementation code here.
	CRect rc;
	GetClientRect(&rc);
	pDC->SelectStockObject(BLACK_PEN);

	int m(pDoc->Nsteps_pvalues), step_x((rc.Width() - 50) / m);
	step_x = step_x % 2 ? step_x - 1 : step_x;
	int j_x(30), j_n(30 + step_x / 2), length_y(rc.Height() - 65),j_y(40), step_y((rc.Height() - 65) / 10);
	for (int i = 0; i < m; ++i) {
		CStringW s;
		s.Format(_T("%.2f"), double(i+1)/m);
		pDC->TextOut(j_n, rc.Height() - 20, s);
		j_n += step_x;
		s.Format(_T("%.1f"), (10 - i) / 10.);
		pDC->TextOut(5, j_y, s);
		j_y += step_y;
		
		pDC->SelectStockObject(GRAY_BRUSH);
		pDC->Rectangle(j_x, 40 + length_y -length_y * pDoc->pvalues[i], j_x + step_x, rc.Height() - 25);
		j_x += step_x;
	}
	//X line
	pDC->MoveTo(20, rc.Height() - 25);
	pDC->LineTo(rc.Width() - 20, rc.Height() - 25);
	pDC->TextOut(rc.Width() - 50, rc.Height() - 20, L"P-value");

	//Y line
	pDC->MoveTo(30, rc.Height() - 10);
	pDC->LineTo(30, 20);
	//pDC->TextOut(35, 20, L"Cumulate");

	//y=x line
	pDC->MoveTo(30, rc.Height() - 25);
	pDC->LineTo(j_x, 40);

	//parameters
	CStringW s;
	s.Format(_T("Cumulate     p0=%.2lf   p=%.2lf   number of pvalues =%d"), pDoc->d0.get_p(), pDoc->d.get_p(), pDoc->Npval);
	pDC->TextOut(35, 20, s);
	/*pDC->TextOut(200, 20, s);
	s.Format(_T("p=%.2lf"), pDoc->d.get_p());
	pDC->TextOut(300, 20, s);
	s.Format(_T("number of pvalues =%d"), pDoc->Npval);
	pDC->TextOut(500, 20, s);*/
}


void CBPView::draw_powers(CDC* pDC, CBPDoc* pDoc)
{
	// TODO: Add your implementation code here.
	CRect rc;
	GetClientRect(&rc);
	pDC->SelectStockObject(BLACK_PEN);

	int w(pDoc->length_powers);
	double step_x(double(rc.Width() - 50) / w),j_x(30);
	//step_x = step_x % 2 ? step_x - 1 : step_x;
	int j_n(30 + step_x / 2), length_y(rc.Height() - 65), j_y(40), step_y((rc.Height() - 65) / 10);
	pDC->MoveTo(j_x, 40 + length_y - length_y * pDoc->powers[0]);
	for (int i = 1; i < w; ++i) {
		pDC->LineTo(j_x, 40 + length_y - length_y * pDoc->powers[i]);
		pDC->MoveTo(j_x, 40 + length_y - length_y * pDoc->powers[i]);
		j_x += step_x;
	}
	//X line
	pDC->MoveTo(20, rc.Height() - 25);
	pDC->LineTo(rc.Width() - 20, rc.Height() - 25);
	pDC->TextOut(rc.Width() - 90, rc.Height() - 20, L"P alternative");

	//Y line
	/*CStringW s;
	s.Format(_T("%d"), max_a);
	pDC->TextOut(5, 35, s);*/
	pDC->MoveTo(30, rc.Height() - 10);
	pDC->LineTo(30, 20);
	//pDC->TextOut(35, 20, L"Power");
	const int mm = 20;
	int step_xx = (rc.Width() - 50) / mm;
	step_xx = step_xx % 2 ? step_xx - 1 : step_xx;
	for (int i = 0; i < mm; ++i) {
		CStringW s;
		s.Format(_T("%.2f"), double(i + 1) / mm);
		pDC->TextOut(j_n, rc.Height() - 20, s);
		j_n += step_xx;
		s.Format(_T("%.1f"), (10 - i) / 10.);
		pDC->TextOut(5, j_y, s);
		j_y += step_y;
	}
	//y=x line
	/*pDC->MoveTo(30, rc.Height() - 25);
	pDC->LineTo(rc.Width() - 60, 40);*/
	//parameters
	CStringW s;

	s.Format(_T("Power     p0=%.2lf   number of powers=%d   number of iterations for counting powers =%d"), pDoc->d0.get_p(), pDoc->Np1, pDoc->Ncount_pow);
	pDC->TextOut(35, 20, s);
	/*pDC->TextOut(200, 20, s);
	s.Format(_T("number of powers=%d"), pDoc->Np1);
	pDC->TextOut(300, 20, s);
	s.Format(_T("number of iterations for counting powers =%d"), pDoc->Ncount_pow);
	pDC->TextOut(500, 20, s);*/
}
