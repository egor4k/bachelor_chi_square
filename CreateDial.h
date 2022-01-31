#pragma once


// CreateDial dialog

class CreateDial : public CDialogEx
{
	DECLARE_DYNAMIC(CreateDial)

public:
	CreateDial(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CreateDial();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_DIAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_method;
	double m_p;
	double m_p0;
	int m_n;
	double m_alpha;
	afx_msg void OnKillfocusSimulation();
	afx_msg void OnKillfocusHyphothesis();
	afx_msg void OnKillfocusSize();
	afx_msg void OnKillfocusAlpha();
	int m_Npval;
	//int m_Np1;
	int m_Np1;
	afx_msg void OnKillfocusNPvalues();
	afx_msg void OnKillfocusNp1();
	int m_Ncount_pow;
	afx_msg void OnKillfocusNiterationsp1();
};
