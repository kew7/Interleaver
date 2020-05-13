// Interleaver_DialogDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afx.h"
#include "afxcmn.h"

// CInterleaver_DialogDlg dialog
class CInterleaver_DialogDlg : public CDialog
{
// Construction
public:
	CInterleaver_DialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_INTERLEAVER_DIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL CInterleaver_DialogDlg::PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CButton IDC_PUSK;
	CString m_Num_String;
	CString m_Num_Column;
	void Func_FileIn_BYTE(void);
	CFile	FileIn,				// входной файл в битовом виде
			FileOut,			// выходной файл в битовом виде
			FileIn_BYTE,		// входной файл в байтовой форме
			FileOut_BYTE;		// выходной файл в байтовой форме
	void OnRabota(CString);
	void Func_Perem(void);
	void Func_FileOut_BIT(void);
	CString StrDir;
	CProgressCtrl m_Progress;
	CButton m_Del_File_BYTE;
	CString m_FileName;
	afx_msg void OnFile();
	afx_msg void CInterleaver_DialogDlg::OnBnClickedPUSK();
	HBRUSH hbr;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	COLORREF m_Color_Check_Del;
};
