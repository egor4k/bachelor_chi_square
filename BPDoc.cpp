
// BPDoc.cpp : implementation of the CBPDoc class
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BP.h"
#endif

#include "BPDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBPDoc

IMPLEMENT_DYNCREATE(CBPDoc, CDocument)

BEGIN_MESSAGE_MAP(CBPDoc, CDocument)
	//ON_COMMAND(ID_CREATE, &CBPDoc::OnCreate)
	ON_COMMAND(ID_REFRESH, &CBPDoc::OnRefresh)
	ON_COMMAND(ID_HISTOGRAM_DRAW, &CBPDoc::OnHistogramDraw)
	ON_COMMAND(ID_HISTOGRAM_REFRESH, &CBPDoc::OnHistogramRefresh)
	ON_COMMAND(ID_PVALUES, &CBPDoc::OnPvalues)
	ON_COMMAND(ID_POWERS, &CBPDoc::OnPowers)
	ON_COMMAND(ID_PVALUES_DRAW, &CBPDoc::OnPvaluesDraw)
	ON_COMMAND(ID_PVALUES_REFRESH, &CBPDoc::OnPvaluesRefresh)
	ON_COMMAND(ID_POWERS_DRAW, &CBPDoc::OnPowersDraw)
	ON_COMMAND(ID_POWERS_REFRESH, &CBPDoc::OnPowersRefresh)
	ON_COMMAND(ID_SET, &CBPDoc::OnSet)
END_MESSAGE_MAP()


// CBPDoc construction/destruction

CBPDoc::CBPDoc() noexcept
{
	// TODO: add one-time construction code here
	s = nullptr;
	pvalues = nullptr;
	powers = nullptr;
	//srand(time(nullptr));
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	//std::uniform_real_distribution<double>distr(0., 1.);
	alpha = 0.2;
	Npval = 100;
	Np1 = 100;
	Ncount_pow = 100;
}

CBPDoc::~CBPDoc()
{
	delete s;
	delete[]pvalues;
	delete[]powers;
	s = nullptr;
	pvalues = nullptr;
	powers = nullptr;
}

BOOL CBPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CBPDoc serialization

void CBPDoc::Serialize(CArchive& ar)
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
void CBPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBPDoc diagnostics

#ifdef _DEBUG
void CBPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBPDoc commands


//void CBPDoc::OnCreate()
//{
//	// TODO: Add your command handler code here
//	CreateDial dial;
//	dial.m_p = d.get_p();
//	dial.m_p0 = d0.get_p();
//	dial.m_alpha = alpha;
//	dial.m_Npval = Npval;
//	dial.m_Np1 = Np1;
//	dial.m_Ncount_pow = Ncount_pow;
//	if (s)
//		dial.m_n = s->get_n();
//	else
//		dial.m_n = 50;
//	if (dial.DoModal() == IDOK) {
//		if (!s||(dial.m_p0 != d0.get_p()) || (dial.m_p != d.get_p()) || (s&&(dial.m_n != s->get_n()))) {
//			delete s;
//			d.set_p(dial.m_p);
//			d0.set_p(dial.m_p0);
//			if (dial.m_method)
//				s = new Sample_Bernoulli(d, dial.m_n);
//			else
//				s = new Sample_exponential(d, dial.m_n);
//			s->simulate_sample(d.get_p());
//			Chisquare ch(d0, *s);
//			plevel = ch.Calc_chi2(&t);
//		}
//
//		alpha = dial.m_alpha;
//		Npval = dial.m_Npval;
//		Np1 = dial.m_Np1;
//		Ncount_pow = dial.m_Ncount_pow;
//
//		f = 0;
//		delete[]pvalues;
//		delete[]powers;
//		pvalues = powers = nullptr;
//		UpdateAllViews(0);
//	}
//}


void CBPDoc::OnRefresh()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	s->reset_sample();
	s->simulate_sample(d.get_p());
	UpdateAllViews(0);
}


void CBPDoc::count_pvalues(int _m)
{
	// TODO: Add your implementation code here.
	delete[]pvalues;
	Nsteps_pvalues = _m;
	pvalues = new double[Nsteps_pvalues] {0};
	int* a = new int[Nsteps_pvalues] {0};
	Sample* stemp = nullptr;
	if (s->get_method())
		stemp = new Sample_Bernoulli(d, s->get_n());
	else
		stemp = new Sample_exponential(d, s->get_n());
	Chisquare ch(d0, *stemp);
	double ps(d.get_p());
	for (int i = 0; i < Npval; ++i) {
		stemp->simulate_sample(ps);
		ch.change_sample(*stemp);
		double p(ch.Calc_chi2());
		p *= Nsteps_pvalues;
		p = p < Nsteps_pvalues ? p : Nsteps_pvalues - 1;
		++a[int(p)];
	}
	delete stemp;
	pvalues[0] = double(a[0]) / Npval;
	for (int i = 1; i < Nsteps_pvalues; ++i)
		pvalues[i] = pvalues[i - 1] + double(a[i]) / Npval;
	delete[]a;
}


void CBPDoc::OnHistogramDraw()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	f = 1;
	UpdateAllViews(0);
}


void CBPDoc::OnHistogramRefresh()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	s->simulate_sample(d.get_p());
	Chisquare ch(d0, *s);
	plevel = ch.Calc_chi2(&t);
	f = 1;
	UpdateAllViews(0);
}


void CBPDoc::OnPvalues()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	count_pvalues();
	f = 2;
	UpdateAllViews(0);
}


void CBPDoc::OnPowers()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	count_powers();
	f = 3;
	UpdateAllViews(0);
}


void CBPDoc::count_powers()
{	
	// TODO: Add your implementation code here.
	delete[]powers;
	powers = new double[Np1];
	double step(1. / Np1);
	int i(0);
	Sample* stemp = nullptr;
	if (s->get_method())
		stemp = new Sample_Bernoulli(d, s->get_n());
	else
		stemp = new Sample_exponential(d, s->get_n());
	Chisquare ch(d0, *stemp);
	for (double p1 = step; p1 < 1; p1 += step) {
		int c(0);
		for (int j = 0; j < Ncount_pow; ++j) {
			stemp->simulate_sample(p1);
			ch.change_sample(*stemp);
			if (ch.Calc_chi2() < alpha)
				++c;
		}
		powers[i++] = double(c)/Ncount_pow;
	}
	length_powers = i;
	delete stemp;
}


void CBPDoc::OnPvaluesDraw()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	if(!pvalues)
	 count_pvalues();
	f = 2;
	UpdateAllViews(0);
}


void CBPDoc::OnPvaluesRefresh()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	count_pvalues();
	f = 2;
	UpdateAllViews(0);
}


void CBPDoc::OnPowersDraw()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	if(!powers)
		count_powers();
	f = 3;
	UpdateAllViews(0);
}


void CBPDoc::OnPowersRefresh()
{
	// TODO: Add your command handler code here
	if (!s) {
		AfxMessageBox(L"Create a sample");
		return;
	}
	count_powers();
	f = 3;
	UpdateAllViews(0);
}


void CBPDoc::OnSet()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CreateDial dial;
	dial.m_p = d.get_p();
	dial.m_p0 = d0.get_p();
	dial.m_alpha = alpha;
	dial.m_Npval = Npval;
	dial.m_Np1 = Np1;
	dial.m_Ncount_pow = Ncount_pow;
	if (s)
		dial.m_n = s->get_n();
	else
		dial.m_n = 50;
	if (dial.DoModal() == IDOK) {
		if (!s || (dial.m_p0 != d0.get_p()) || (dial.m_p != d.get_p()) || (s && (dial.m_n != s->get_n()))) {
			delete s;
			d.set_p(dial.m_p);
			d0.set_p(dial.m_p0);
			if (dial.m_method)
				s = new Sample_Bernoulli(d, dial.m_n);
			else
				s = new Sample_exponential(d, dial.m_n);
			s->simulate_sample(d.get_p());
			Chisquare ch(d0, *s);
			plevel = ch.Calc_chi2(&t);
		}

		alpha = dial.m_alpha;
		Npval = dial.m_Npval;
		Np1 = dial.m_Np1;
		Ncount_pow = dial.m_Ncount_pow;

		f = 0;
		delete[]pvalues;
		delete[]powers;
		pvalues = powers = nullptr;
		UpdateAllViews(0);
	}
}
