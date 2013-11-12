// FNT EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FNT Editor.h"
#include "FNT EditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFNTEditorDlg dialog

CFNTEditorDlg::CFNTEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFNTEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFNTEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFNTEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFNTEditorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFNTEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CFNTEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT_FILE_NAME, OnChangeEditFileName)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_EN_CHANGE(IDC_EDIT_LINE, OnChangeEditLine)
	ON_EN_CHANGE(IDC_EDIT_SPACE_SIZE, OnChangeEditSpaceSize)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_BIDON, OnButtonBidon)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_COMPILE, OnButtonCompile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFNTEditorDlg message handlers

BOOL CFNTEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// OUR INIT ------------------------------
	//

	CreateFNT();
	fnt_changed = FALSE;
	fnt_name = "Sans titre.fnt";
	MetAJourTitre();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFNTEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFNTEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFNTEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFNTEditorDlg::ReleaseAll()
{
	char *	ptr;

	CListBox * list = (CListBox*) GetDlgItem( IDC_LIST);

	for( int i=0; i < list->GetCount(); i++)
	{
		ptr = (char *) list->GetItemDataPtr( i);
		delete [] ptr;
		list->SetItemDataPtr( i, NULL);
	}

	list->ResetContent();
}

void CFNTEditorDlg::OnDestroy() 
{
	ReleaseAll();

	CDialog::OnDestroy();
}

void CFNTEditorDlg::OnButtonQuit() 
{
	int		rval;
	
	if ( fnt_changed )
		rval = MessageBox(	"Attention! La fonte courante n'a pas été sauvegardée. Voulez vous tout de même continuer ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && fnt_changed)
		return;

	ReleaseAll();
	DestroyWindow();
}

void CFNTEditorDlg::OnSelchangeList() 
{
	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_FILE_NAME);
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	int n = list->GetCurSel();

	if ( n == 0)
		return;

	char * ptr = (char *) list->GetItemDataPtr( n);

	if ( strcmp( ptr, "*") == 0)
		edit->SetWindowText( "");
	else
		edit->SetWindowText( ptr);

	edit->SetFocus();
}

void CFNTEditorDlg::OnChangeEditFileName() 
{
	char	buffer[MAX_PATH];

	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_FILE_NAME);
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	int n = list->GetCurSel();
	char * ptr = (char *) list->GetItemDataPtr( n);

	edit->GetWindowText( buffer, MAX_PATH);

	if ( strlen( buffer) == 0)
		strcpy( buffer, "*");
	
	strcpy( ptr, buffer);

	sprintf( buffer, "%d - (%c) : %s", n, char(n), ptr);
	list->DeleteString( n);
	list->InsertString( n, buffer);
	list->SetItemDataPtr( n, ptr);
	list->SetCurSel( n);

	change();
}

void CFNTEditorDlg::OnButtonBrowse() 
{
	CFileDialog load_box (TRUE, NULL, NULL, NULL, "Fichiers bitmaps (*.BMP)|*.bmp|Tous les fichiers (*.*)|*.*||", NULL);
	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_FILE_NAME);

	if ( load_box.DoModal() != IDOK)
		return;

	edit->SetWindowText( load_box.GetPathName());
}

void CFNTEditorDlg::OnChangeEditLine() 
{
	char	buffer[30];	

	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_LINE);

	edit->GetWindowText( buffer, 30);
	
	if ( strlen(buffer) == 0)
		hauteur_ligne = 0;
	else
		hauteur_ligne = atoi( buffer);
		
	change();
}

void CFNTEditorDlg::OnChangeEditSpaceSize() 
{
	char	buffer[30];	

	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_SPACE_SIZE);

	edit->GetWindowText( buffer, 30);
	
	if ( strlen(buffer) == 0)
		largeur_espace = 0;
	else
		largeur_espace = atoi( buffer);

	change();
}

void CFNTEditorDlg::OnButtonLoad() 
{
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	
	// Choisit le nom du fichier
	//

	CFileDialog load_box( TRUE, "fnt", NULL, 0, "Fichiers FNT (*.fnt)|*.fnt|Tous les fichiers (*.*)|*.*||", NULL);
	

	if ( load_box.DoModal() != IDOK)
		return;

	LoadFNT( load_box.GetPathName());

	fnt_name = load_box.GetFileName();
	fnt_changed = FALSE;
	MetAJourTitre();
}

void CFNTEditorDlg::LoadFNT( const char * fic_name)
{
	char		buffer[MAX_PATH];
	char *		ptr;
	ifstream	fic;

	CListBox *list = (CListBox *) GetDlgItem( IDC_LIST);
	CEdit * edit_l = (CEdit *) GetDlgItem( IDC_EDIT_SPACE_SIZE);
	CEdit * edit_h = (CEdit *) GetDlgItem( IDC_EDIT_LINE);

	fic.open( fic_name);

	if ( fic.is_open() == 0)
	{
		MessageBox( "Impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	// Taille espaces/sauts de ligne
	//
	fic>>largeur_espace;
	fic>>hauteur_ligne;

	sprintf( buffer, "%d", largeur_espace);
	edit_l->SetWindowText( buffer);

	sprintf( buffer, "%d", hauteur_ligne);
	edit_h->SetWindowText( buffer);


	// Pour finit la ligne
	fic.getline( buffer, MAX_PATH);

	// Charge les noms des images
	//
	for ( int i=1; i < list->GetCount(); i++)
	{
		ptr = (char *) list->GetItemDataPtr( i);
		fic.getline( ptr, MAX_PATH);
		sprintf( buffer, "%d - (%c) : %s", i, char(i), ptr);
		list->DeleteString( i);
		list->InsertString( i, buffer);
		list->SetItemDataPtr( i, ptr);
	}
}

void CFNTEditorDlg::OnButtonSave() 
{
	ofstream	fic;
	char *		ptr;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	
	// Choisit le nom du fichier
	//
	CFileDialog save_box( FALSE, "fnt", fnt_name, 0, "Fichiers FNT (*.fnt)|*.fnt|Tous les fichiers (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;

	fic.open( save_box.GetPathName());

	if ( fic.is_open() == 0)
	{
		MessageBox( "Impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	int n = list->GetCount();

	fic<<largeur_espace<<endl;
	fic<<hauteur_ligne<<endl;

	for ( int i=1; i < n; i++)
	{
		ptr = (char *) list->GetItemDataPtr( i);
		fic<<ptr<<endl;
	}

	fic.close();
	fnt_changed = FALSE;
	fnt_name = save_box.GetFileName();
	MetAJourTitre();
}


void CFNTEditorDlg::OnButtonBidon() 
{
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_FILE_NAME);

	int n = list->GetCurSel();

	if ( n < (list->GetCount() -1))
		list->SetCurSel( n+1);

	OnSelchangeList();

	edit->SetFocus();
}



void CFNTEditorDlg::CreateFNT()
{
	char	buffer[20];
	char *	ptr;

	CListBox * list = (CListBox*) GetDlgItem( IDC_LIST);
	CEdit * edit_l = (CEdit *) GetDlgItem( IDC_EDIT_SPACE_SIZE);
	CEdit * edit_h = (CEdit *) GetDlgItem( IDC_EDIT_LINE);

	// Ze init of ze list
	//

	list->InsertString( 0, "0 - (NULL)");
	ptr = new char[MAX_PATH];
	ptr[0] = '*';
	ptr[1] = '\0';
	list->SetItemDataPtr( 0, ptr);

	for ( int i=1; i < 256; i++)
	{
		sprintf( buffer, "%d - (%c) : *", i, char(i));
		list->InsertString( i, buffer);
		ptr = new char[MAX_PATH];
		ptr[0] = '*';
		ptr[1] = '\0';
		list->SetItemDataPtr( i, ptr);
	}
	
	// Largeur / hauteur
	//
	largeur_espace = 0;
	hauteur_ligne = 0;

	edit_l->SetWindowText( "0");
	edit_h->SetWindowText( "0");
}

void CFNTEditorDlg::OnButtonNew() 
{
	int rval;
	
	if ( fnt_changed )
		rval = MessageBox(	"Attention! La fonte courante n'a pas été sauvegardée. Voulez vous tout de même en créer une nouvelle ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);

	if ( rval == IDOK || !fnt_changed)
	{
		ReleaseAll();
		CreateFNT();

		fnt_changed = FALSE;
		fnt_name = "Sans titre.fnt";
		MetAJourTitre();
	}
}

void CFNTEditorDlg::MetAJourTitre()
{
	CString tmp = "LOADED FNT Editor - ";
	tmp += fnt_name;

	if ( fnt_changed)
	{
		tmp = tmp + "*";
	}

	SetWindowText( tmp);
}


void CFNTEditorDlg::change()
{
	fnt_changed = TRUE;
	MetAJourTitre();
}

void CFNTEditorDlg::OnButtonAbout() 
{
	CAboutDlg	about;

	about.DoModal();
}

void CFNTEditorDlg::OnButtonCompile() 
{
	HBITMAP		tmp_hbm;
	HDC			hdc;
	int			fh;
	char *		ptr;
	int			taille;
	BITMAP		bm;
	void *		ptr_lgx;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);

	
	// Choisit le nom du fichier
	//
	CFileDialog save_box( FALSE, "lft", NULL, 0, "Fichiers LFT (*.lft)|*.lft|Tous les fichiers (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;

	fh = _open( save_box.GetPathName(), _O_WRONLY | _O_BINARY | _O_CREAT);

	if ( fh == -1)
	{
		MessageBox("Impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	bar->SetRange32( 0, 255);
	bar->SetStep( 1);
	bar->SetPos( 0);

	_write( fh, &hauteur_ligne, sizeof(hauteur_ligne));
	_write( fh, &largeur_espace, sizeof(largeur_espace));

	for ( int i=1; i < 256; i++)
	{
		ptr = (char *) list->GetItemDataPtr( i);

		if ( strcmp( ptr, "*") == 0)
		{
			taille = 0;
			_write( fh, &taille, sizeof(taille));
		}
		else
		{
			tmp_hbm = (HBITMAP)LoadImage(NULL, ptr, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

			if ( tmp_hbm == NULL)
			{
				MessageBox( "Image inaccessible", NULL, MB_ICONERROR);
				_close( fh);
				return;
			}

			// Récupère le HDC de l'image
			//
			hdc = CreateCompatibleDC( NULL);

			if ( hdc == NULL)
			{
				MessageBox( "CreateDC Error!", NULL, MB_ICONERROR);
				_close( fh);
				return;
			}

			SelectObject( hdc, tmp_hbm);
			GetObject( tmp_hbm, sizeof(bm), &bm);

			taille = createLGX_1( hdc, bm.bmWidth, bm.bmHeight, ptr_lgx);

			_write( fh, &taille, sizeof(taille));
			_write(  fh, ptr_lgx, taille);

			free( ptr_lgx);
			DeleteDC( hdc);
			DeleteObject( tmp_hbm);
		}

		bar->StepIt();
	}

	bar->SetPos( 0);
	_close( fh);

}
