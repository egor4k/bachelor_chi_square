// CreateDial.cpp : implementation file
//

#include "pch.h"
#include "BP.h"
#include "CreateDial.h"
#include "afxdialogex.h"
#include"Distribution.h"


// CreateDial dialog

IMPLEMENT_DYNAMIC(CreateDial, CDialogEx)

CreateDial::CreateDial(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREATE_DIAL, pParent)
	, m_method(0)
	, m_p(0)
	, m_p0(0)
	, m_n(0)
	, m_alpha(0)
	, m_Npval(0)
	, m_Np1(0)
	, m_Ncount_pow(0)
{

}

CreateDial::~CreateDial()
{
}

void CreateDial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_EXPONENTIAL, m_method);
	DDX_Text(pDX, IDC_SIMULATION, m_p);
	DDX_Text(pDX, IDC_HYPHOTHESIS, m_p0);
	DDX_Text(pDX, IDC_SIZE, m_n);
	DDX_Text(pDX, IDC_EDIT4, m_alpha);
	DDX_Text(pDX, IDC_NPVALUES, m_Npval);
	DDX_Text(pDX, IDC_NP1, m_Np1);
	DDX_Text(pDX, IDC_NITERATIONSP1, m_Ncount_pow);
}


BEGIN_MESSAGE_MAP(CreateDial, CDialogEx)
	ON_EN_KILLFOCUS(IDC_SIMULATION, &CreateDial::OnKillfocusSimulation)
	ON_EN_KILLFOCUS(IDC_HYPHOTHESIS, &CreateDial::OnKillfocusHyphothesis)
	ON_EN_KILLFOCUS(IDC_SIZE, &CreateDial::OnKillfocusSize)
	ON_EN_KILLFOCUS(IDC_ALPHA, &CreateDial::OnKillfocusAlpha)
	ON_EN_KILLFOCUS(IDC_NPVALUES, &CreateDial::OnKillfocusNPvalues)
	ON_EN_KILLFOCUS(IDC_NP1, &CreateDial::OnKillfocusNp1)
	ON_EN_KILLFOCUS(IDC_NITERATIONSP1, &CreateDial::OnKillfocusNiterationsp1)
END_MESSAGE_MAP()


// CreateDial message handlers


void CreateDial::OnKillfocusSimulation()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if ((m_p < eps) || (m_p > 1)) {
		m_p = 0.5;
		AfxMessageBox(L"Input probability from 0 to 1");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusHyphothesis()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if ((m_p0 < eps) || (m_p0 > 1)) {
		m_p0 = 0.5;
		AfxMessageBox(L"Input probability from 0 to 1");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusSize()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if (m_n <= 0) {
		m_n = 50;
		AfxMessageBox(L"Input natural sample size");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusAlpha()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if ((m_alpha < eps) || (m_alpha > 1)) {
		m_alpha = 0.2;
		AfxMessageBox(L"Input significance level from 0 to 1");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusNPvalues()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if (m_Npval <= 0){
		m_Npval = 100;
		AfxMessageBox(L"Input natural number of iterations for counting pvalues distribution");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusNp1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if (m_Np1 <= 0) {
		m_Np1 = 100;
		AfxMessageBox(L"Input natural number of iterations for counting powers");
		UpdateData(0);
	}
}


void CreateDial::OnKillfocusNiterationsp1()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	if (m_Ncount_pow <= 0) {
		m_Ncount_pow = 100;
		AfxMessageBox(L"Input natural number of iterations for counting powers");
		UpdateData(0);
	}
}
