// GFX_EditorDlg.h : header file
//
#include <fstream.h>
#include <stdio.h>
#include "winLGX.h"

#if !defined(AFX_GFX_EDITORDLG_H__21A834A7_2F39_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_GFX_EDITORDLG_H__21A834A7_2F39_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		MAX_ANIM	100

/////////////////////////////////////////////////////////////////////////////
// CGFX_EditorDlg dialog

class CGFX_EditorDlg : public CDialog
{
// Construction
public:
	void LoadPBK( const char * nom_fic);
	CString		cmd_line;

	CString		pbk_name;
	BOOL		pbk_changed;

	LONG		ymouse;
	LONG		xmouse;

	HBITMAP		hbm;

	BOOL		animating;
	HBITMAP *	anim_bmp;
	int			anim_pix[MAX_ANIM];
	int			nb_anim;
	int			frame;

	CGFX_EditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGFX_EditorDlg)
	enum { IDD = IDD_GFX_EDITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGFX_EditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void change();
	void metAJourTitre();
	void freeMemory();
	void AfficheImage( BOOL clear = FALSE, 
					   BOOL reinit = FALSE, 
					   BOOL reload = FALSE,
					   BOOL spotChange = FALSE);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGFX_EditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonSupp();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnSelchangeList();
	afx_msg void OnButtonQuit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeComboZoom();
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonNewPbk();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonCompile();
	afx_msg void OnSelchangeComboPak();
	afx_msg void OnButtonAbout();
	afx_msg void OnButtonHtml();
	afx_msg void OnButtonAnim();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFX_EDITORDLG_H__21A834A7_2F39_11D4_8760_00A024851A35__INCLUDED_)
