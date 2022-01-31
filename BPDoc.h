
// BPDoc.h : interface of the CBPDoc class
//


#pragma once

#include"Distribution.h"
#include"Sample.h"
#include"CreateDial.h"
#include"Sample_exponential.h"
#include"Sample_Bernoulli.h"
#include"Chisquare.h"
#include<ctime>
#include<chrono>


class CBPDoc : public CDocument
{
protected: // create from serialization only
	CBPDoc() noexcept;
	DECLARE_DYNCREATE(CBPDoc)

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
	virtual ~CBPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	Distribution d;
	Distribution d0;
	Sample* s;
	//afx_msg void OnCreate();
	int f=0;
	afx_msg void OnRefresh();
	double *pvalues;
	void count_pvalues(int _m=20);
	afx_msg void OnHistogramDraw();
	afx_msg void OnHistogramRefresh();
	afx_msg void OnPvalues();
	int Nsteps_pvalues;
	double alpha;
	afx_msg void OnPowers();
	double* powers;
	void count_powers();
	int length_powers;
	int Npval;
	double t;
	double plevel;
	int Np1;
	int Ncount_pow;
	afx_msg void OnPvaluesDraw();
	afx_msg void OnPvaluesRefresh();
	afx_msg void OnPowersDraw();
	afx_msg void OnPowersRefresh();
	afx_msg void OnSet();
	std::mt19937 generator;
	//std::uniform_real_distribution<double>distr;
};
