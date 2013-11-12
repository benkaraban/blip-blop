// FNT EditorDlg.h : header file
//

#if !defined(AFX_FNTEDITORDLG_H__0F907868_5B29_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_FNTEDITORDLG_H__0F907868_5B29_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFNTEditorDlg dialog

class CFNTEditorDlg : public CDialog
{
public:
	void change();
	void MetAJourTitre();
	void CreateFNT();
	void LoadFNT( const char * fic_name);

	BOOL		focus_from_edit;
	BOOL		fnt_changed;
	CString		fnt_name;
	int			hauteur_ligne;
	int			largeur_espace;




	void ReleaseAll();
	CFNTEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFNTEditorDlg)
	enum { IDD = IDD_FNTEDITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFNTEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFNTEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonQuit();
	afx_msg void OnSelchangeList();
	afx_msg void OnChangeEditFileName();
	afx_msg void OnButtonBrowse();
	afx_msg void OnChangeEditLine();
	afx_msg void OnChangeEditSpaceSize();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonBidon();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonAbout();
	afx_msg void OnButtonCompile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FNTEDITORDLG_H__0F907868_5B29_11D4_8760_00A024851A35__INCLUDED_)
