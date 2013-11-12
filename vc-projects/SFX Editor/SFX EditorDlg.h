// SFX EditorDlg.h : header file
//

#if !defined(AFX_SFXEDITORDLG_H__099615A9_58DB_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_SFXEDITORDLG_H__099615A9_58DB_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSFXEditorDlg dialog

class CSFXEditorDlg : public CDialog
{
// Construction
public:
	void LoadSBK( const char *);
	void MetAJourTitre();
	void FreeMemory();
	void change();

	CString	cmd_line;

	BOOL	sbk_changed;
	CString	sbk_name;


	CSFXEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSFXEditorDlg)
	enum { IDD = IDD_SFXEDITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFXEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSFXEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonQuit();
	afx_msg void OnDestroy();
	afx_msg void OnButtonIns();
	afx_msg void OnButtonSupp();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonPlay();
	afx_msg void OnSelchangeList();
	afx_msg void OnChangeEditNb();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonCompile();
	afx_msg void OnButtonAbout();
	afx_msg void OnButtonHtml();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFXEDITORDLG_H__099615A9_58DB_11D4_8760_00A024851A35__INCLUDED_)
