// SFX EditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SFX Editor.h"
#include "SFX EditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NB_MAX_SND		5000

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
// CSFXEditorDlg dialog

CSFXEditorDlg::CSFXEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSFXEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSFXEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSFXEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSFXEditorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSFXEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CSFXEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_INS, OnButtonIns)
	ON_BN_CLICKED(IDC_BUTTON_SUPP, OnButtonSupp)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT_NB, OnChangeEditNb)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_COMPILE, OnButtonCompile)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_HTML, OnButtonHtml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFXEditorDlg message handlers

BOOL CSFXEditorDlg::OnInitDialog()
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

	// Extra init!
	OnSelchangeList();
	sbk_name = "Sans Titre.sbk";
	sbk_changed = FALSE;
	MetAJourTitre();

	if ( cmd_line.GetLength() > 0)
	{
		cmd_line = cmd_line.Right( cmd_line.GetLength() - 1);
		cmd_line = cmd_line.Left( cmd_line.GetLength() - 1);
		LoadSBK( LPCSTR(cmd_line));

		int i = cmd_line.GetLength()-1;

		while ( cmd_line[i] != '\\' && i > 0)
			i--;

		sbk_name = cmd_line.Right( cmd_line.GetLength()-(i+1));
		MetAJourTitre();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSFXEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSFXEditorDlg::OnPaint() 
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
HCURSOR CSFXEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSFXEditorDlg::OnButtonAdd() 
{
	const int BUFFER_SIZE = MAX_PATH*1000;

	static int	cpt = 0;
	CString		str;
	int			rang;
	SOUND *		snd;
	char *		fic;
	int			i;
	POSITION	pos;
	int			tfic;	// Taille fichier
	int			fh;		// Handle fichier
	char		buffer[20];


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	CFileDialog load_box (TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "Fichiers bitmaps (*.WAV)|*.wav|Tous les fichiers (*.*)|*.*||", NULL);

	fic = new char[BUFFER_SIZE];
	fic[0] = '\0';

	load_box.m_ofn.lpstrFile = fic;
	load_box.m_ofn.Flags |= OFN_ALLOWMULTISELECT;
	load_box.m_ofn.nMaxFile = BUFFER_SIZE;

	if ( load_box.DoModal() == IDCANCEL)
	{
		delete [] fic;
		return;
	}

	pos = load_box.GetStartPosition();

	while ( pos != NULL)
	{
		str = load_box.GetNextPathName( pos);

		snd = new SOUND;
		snd->file = str;
		snd->n = 1;

		// Obtient la taille du fichier
		fh = _open( LPCSTR(str), _O_RDONLY | _O_BINARY);
		
		if ( fh != -1)
		{
			tfic = _filelength( fh);
			_close( fh);
		}
		else
			tfic = 0;


		// Grumpf! On est obligé d'extraire le nom du fichier lui même à la main

		i = str.GetLength()-1;

		while ( str[i] != '\\' && i > 0)
			i--;

		str = str.Right( str.GetLength()-(i+1));

		sprintf( buffer, "  ( %d Ko)", tfic/1024);
		str += buffer;

		rang = list->AddString( str);
		list->SetItemDataPtr( rang, (void*) snd);
	}

	delete [] fic;
	change();
}

void CSFXEditorDlg::change()
{
	if ( !sbk_changed )
	{
		sbk_changed = TRUE;
		MetAJourTitre();
	}
}

void CSFXEditorDlg::FreeMemory()
{
	SOUND *		snd;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	// On vide la ListBox
	//
	if ( list->GetCount() > 0)
	{
		do {
			snd = (SOUND *) list->GetItemDataPtr( 0);
			delete snd;

		} while( list->DeleteString(0) != 0);
	}
}

void CSFXEditorDlg::OnButtonQuit() 
{
	int			rval;
	
	if ( sbk_changed )
		rval = MessageBox(	"Attention! La SBK courante n'a pas été sauvegardée. Voulez vous tout de même continuer ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && sbk_changed)
		return;

	FreeMemory();
	DestroyWindow();
}

void CSFXEditorDlg::OnDestroy() 
{
	FreeMemory();

	CDialog::OnDestroy();	
}

void CSFXEditorDlg::OnButtonIns() 
{
	const int BUFFER_SIZE = MAX_PATH*1000;

	static int	cpt = 0;
	CString		str;
	int			rang;
	SOUND *		snd;
	char *		fic;
	int			i;
	POSITION	pos;
	int			tfic;	// Taille fichier
	int			fh;		// Handle fichier
	char		buffer[20];


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	CFileDialog load_box (TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "Fichiers bitmaps (*.WAV)|*.wav|Tous les fichiers (*.*)|*.*||", NULL);

	fic = new char[BUFFER_SIZE];
	fic[0] = '\0';

	load_box.m_ofn.lpstrFile = fic;
	load_box.m_ofn.Flags |= OFN_ALLOWMULTISELECT;
	load_box.m_ofn.nMaxFile = BUFFER_SIZE;

	if ( load_box.DoModal() == IDCANCEL)
	{
		delete [] fic;
		return;
	}

	pos = load_box.GetStartPosition();
	rang = list->GetCurSel();

	while ( pos != NULL)
	{
		str = load_box.GetNextPathName( pos);

		snd = new SOUND;
		snd->file = str;
		snd->n = 1;

		// Obtient la taille du fichier
		fh = _open( LPCSTR(str), _O_RDONLY | _O_BINARY);
		
		if ( fh != -1)
		{
			tfic = _filelength( fh);
			_close( fh);
		}
		else
			tfic = 0;

		// Grumpf! On est obligé d'extraire le nom du fichier lui même à la main

		i = str.GetLength()-1;

		while ( str[i] != '\\' && i > 0)
			i--;

		str = str.Right( str.GetLength()-(i+1));

		sprintf( buffer, "  ( %d Ko)", tfic/1024);
		str += buffer;

		rang = list->InsertString( rang+1, str);
		list->SetItemDataPtr( rang, (void*) snd);
	}

	delete [] fic;
	change();	
}

void CSFXEditorDlg::OnButtonSupp() 
{
	int		i;
	int		tab[NB_MAX_SND];
	int		nb_sel;
	SOUND *	snd;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	nb_sel = list->GetSelItems( NB_MAX_SND, tab);

	for ( i=0; i<list->GetCount(); i++)
	if ( list->GetSel(i) > 0)
	{
		snd = (SOUND *) list->GetItemDataPtr( i);
		delete snd;

		list->DeleteString( i--);
	}

	change();
	OnSelchangeList();
}

void CSFXEditorDlg::OnButtonUp() 
{
	int			i;
	CString		s;
	char		buff[200];
	int			select[NB_MAX_SND];
	int			nb_sel;
	SOUND *	snd;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	nb_sel = list->GetSelItems( NB_MAX_SND, select);

	if ( select[0] != 0)
	{
		for ( i=0; i < nb_sel; i++)
		{
			list->GetText( select[i], buff);
			snd = (SOUND *) list->GetItemDataPtr( select[i]);
			
			list->InsertString( select[i]-1, buff);
			list->SetItemDataPtr( select[i]-1, (void*)snd);

			list->DeleteString( select[i]+1);
		}
	
		for ( i=0; i < nb_sel; i++)
		{
			list->SetSel( select[i]-1);
		}
	}

	change();
}

void CSFXEditorDlg::OnButtonDown() 
{
	int			i;
	CString		s;
	char		buff[200];
	int			select[NB_MAX_SND];
	int			nb_sel;
	int			nb_str;
	SOUND *	snd;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	nb_sel = list->GetSelItems( NB_MAX_SND, select);
	nb_str = list->GetCount();


	if ( (nb_sel < nb_str) && select[nb_sel-1] < nb_str-1)
	{
		for ( i = nb_sel-1; i >= 0; i--)
		{
			list->GetText( select[i], buff);
			snd = (SOUND *) list->GetItemDataPtr( select[i]);
			
			list->InsertString( select[i]+2, buff);
			list->SetItemDataPtr( select[i]+2, (void*)snd);

			list->DeleteString( select[i]);
		}
	
		for ( i=0; i < nb_sel; i++)
		{
			list->SetSel( select[i]+1);
		}
	}
	
	change();
}

void CSFXEditorDlg::OnButtonPlay() 
{
	SOUND *	snd;
	int		rang;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	rang = list->GetCurSel();
	snd = (SOUND*) list->GetItemDataPtr( rang);
	PlaySound( LPCSTR(snd->file), NULL, SND_ALIAS_ID | SND_FILENAME);
	
}

void CSFXEditorDlg::OnSelchangeList() 
{
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CButton * b_play = (CButton *) GetDlgItem( IDC_BUTTON_PLAY);
	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_NB);

	char	str[20];

	int nb_sel = list->GetSelCount();

	if ( nb_sel == 0)
	{
		edit->SetWindowText( "");
		edit->EnableWindow( FALSE);
		b_play->EnableWindow( FALSE);
	}
	else if ( nb_sel == 1)
	{
		int	rang = list->GetCurSel();

		SOUND * snd = (SOUND*) list->GetItemDataPtr( rang);
		sprintf( str, "%d", snd->n);
		edit->SetWindowText( str);
		edit->EnableWindow();
		b_play->EnableWindow();
	}
	else
	{
		edit->EnableWindow();
		b_play->EnableWindow( FALSE);
	}
}

void CSFXEditorDlg::OnChangeEditNb() 
{
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CButton * b_play = (CButton *) GetDlgItem( IDC_BUTTON_PLAY);
	CEdit * edit = (CEdit *) GetDlgItem( IDC_EDIT_NB);

	char	str[20];
	int		tab[NB_MAX_SND];
	int		nb_buff;
	SOUND *	snd;

	// Récupère la valeur
	//
	edit->GetWindowText( str, 20);
	sscanf( str, "%d", &nb_buff);

	int nb_sel = list->GetSelItems( NB_MAX_SND, tab);


	if ( nb_sel < 1)	// Pas de selection
		return;

	for ( int i=0; i < nb_sel; i++)
	{
		snd = ( SOUND *) list->GetItemDataPtr( tab[i]);
		snd->n = nb_buff;
	}


	change();
}

void CSFXEditorDlg::OnButtonNew() 
{
	int			rval;

	CEdit * edit = (CEdit*) GetDlgItem( IDC_EDIT_NB);
	
	if ( sbk_changed )
		rval = MessageBox(	"Attention! La SBK courante n'a pas été sauvegardée. Voulez vous tout de même continuer ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && sbk_changed)
		return;

	FreeMemory();
	edit->SetWindowText( "");
	edit->EnableWindow( FALSE);

	sbk_name = "Sans Titre.sbk";
	sbk_changed = FALSE;
	MetAJourTitre();
}

void CSFXEditorDlg::MetAJourTitre()
{
	CString str;

	str = "SFX Editor - " + sbk_name;

	if ( sbk_changed)
		str += "*";

	SetWindowText( LPCSTR(str));
}

void CSFXEditorDlg::OnButtonSave() 
{
	SOUND *		snd;
	ofstream	f;
	int			n;
	
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);

	CFileDialog save_box( FALSE, "sbk", sbk_name, 0, "Fichiers SBK (*.sbk)|*.sbk|Tous les fichiers (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;

	f.open( save_box.GetPathName());

	if ( f.is_open() == 0)
	{
		MessageBox( "Impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	n = list->GetCount();
	f<<n<<endl;

	bar->SetRange32( 0, n);
	bar->SetStep( 1);
	bar->SetPos( 0);

	for ( int i=0; i < n; i++)
	{
		snd = (SOUND*)list->GetItemDataPtr( i);

		f<<(snd->n)<<endl;
		f<<(snd->file)<<endl;

		bar->StepIt();
	}

	sbk_name = save_box.GetFileName();
	sbk_changed = FALSE;
	MetAJourTitre();
	f.close();
	bar->SetPos( 0);
}

void CSFXEditorDlg::OnButtonLoad() 
{
	int			rval;

	if ( sbk_changed )
		rval = MessageBox(	"Attention! La SBK courante n'a pas été sauvegardée. Voulez vous tout de même continuer ?", 
							NULL, MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && sbk_changed)
		return;


	CFileDialog load_box( TRUE, NULL, NULL, 0, "Fichiers SBK (*.sbk)|*.sbk|Tous les fichiers (*.*)|*.*||", NULL);
	
	if ( load_box.DoModal() != IDOK) // On se tire si aucun fichier selectionné
		return;

	LoadSBK( load_box.GetPathName());
	sbk_name = load_box.GetFileName();
}

void CSFXEditorDlg::OnButtonCompile() 
{
	char		buffer[200];
	SOUND *		snd;
	int			fh;
	int			nb_snd;
	int			fh_wav;
	void *		ptr;
	int			taille_wav;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	
	CFileDialog save_box( FALSE, "sfx", NULL, 0, "Fichiers SFX (*.sfx)|*.sfx|Tous les fichiers (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;

	fh = _open( save_box.GetPathName(), _O_BINARY | _O_WRONLY | _O_TRUNC | _O_CREAT, _S_IWRITE);

	if ( fh == -1)
	{
		sprintf( buffer, "Impossible d'ouvrir le fichier %s", save_box.GetPathName());
		MessageBox( buffer, NULL, MB_ICONERROR);
		return;
	}

	// Ecrit le nombre de sons
	//
	nb_snd = list->GetCount();
	_write( fh, &nb_snd, sizeof(nb_snd));


	// Initialise la progress bar
	//
	bar->SetRange32( 0, nb_snd-1);
	bar->SetStep( 1);
	bar->SetPos( 0);


	// Ecrit tous les sons
	//
	for ( int i=0; i < nb_snd; i++)
	{
		snd = (SOUND*) list->GetItemDataPtr( i);

		// Le nombre d'apparitions du son
		//
		if ( snd->n < 1)
		{
			sprintf( "Nombre de buffers nul pour %s. Considéré comme 1.", LPCSTR(snd->file));
			MessageBox( buffer, NULL, MB_ICONWARNING);
			snd->n = 1;
		}
		_write( fh, &(snd->n), sizeof(snd->n));

		// Ouvre le fichier
		//
		fh_wav = _open( LPCSTR(snd->file), _O_BINARY | _O_RDONLY);

		if ( fh_wav == -1)
		{
			sprintf( buffer, "Impossible d'ouvrir le fichier %s", LPCSTR(snd->file));
			MessageBox( buffer, NULL, MB_ICONERROR);
			_close( fh);
			return;
		}

		// Alloue la mémoire
		//
		taille_wav = _filelength( fh_wav);
		ptr = malloc( taille_wav);

		if ( ptr == NULL)
		{
			sprintf( buffer, "Pas assez de mémoire pour %s", LPCSTR(snd->file));
			MessageBox( buffer, NULL, MB_ICONERROR);
			_close( fh_wav);
			_close( fh);
			return;
		}

		// Ecrit la taille
		//
		_write( fh, &taille_wav, sizeof(taille_wav));

		// Recopie le tout
		//
		_read( fh_wav, ptr, taille_wav);
		_write( fh, ptr, taille_wav);

		// Free the malloc!
		//
		free( ptr);
		_close( fh_wav);

		// Avance la progress bar
		//
		bar->StepIt();
	}

	_close( fh);
	bar->SetPos( 0);
}

void CSFXEditorDlg::OnButtonAbout() 
{
	CAboutDlg	about;
	about.DoModal();
}

void CSFXEditorDlg::LoadSBK( const char * nom_fic)
{
	SOUND *		snd;
	ifstream	f;
	int			n;
	CString		str;
	int			rang;
	int			j;
	int			fh;
	int			tfic;

	CEdit * edit = (CEdit*) GetDlgItem( IDC_EDIT_NB);
	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	

	f.open( nom_fic);

	if ( f.is_open() == 0)
	{
		MessageBox( "Impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	FreeMemory();

	char *	buffer = new char[MAX_PATH];

	// Nombre de sons
	//
	f>>n;

	for ( int i=0; i < n; i++)
	{
		snd = new SOUND;

		f>>(snd->n);
		f.getline( buffer, MAX_PATH);
		f.getline( buffer, MAX_PATH);
		snd->file = CString( buffer);

		// Obtient la taille du fichier
		fh = _open( buffer, _O_RDONLY | _O_BINARY);
		
		if ( fh != -1)
		{
			tfic = _filelength( fh);
			_close( fh);
		}
		else
		{
			char	buffer2[200];
			sprintf( buffer2, "Attention : ne peut pas ouvrir le fichier %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONWARNING);
			tfic = 0;
		}

		// Récupère le nom court
		//
		str = snd->file;
		j = str.GetLength()-1;

		while ( str[j] != '\\' && j > 0)
			j--;

		str = str.Right( str.GetLength()-(j+1));

		// Rajoute la taille du fichier
		//
		sprintf( buffer, "  ( %d Ko)", tfic/1024);
		str += buffer;

		rang = list->AddString( str);
		list->SetItemDataPtr( rang, snd);
	}

	delete [] buffer;
	sbk_changed = FALSE;
	MetAJourTitre();

}

void CSFXEditorDlg::OnButtonHtml() 
{
	ofstream	fic;
	SOUND *		ptr;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	
	// Choisit le nom du fichier
	//
	CFileDialog save_box( FALSE, "html", NULL, 0, "Fichiers HTML (*.html, *.htm)|*.htm;*.html|Tous les fichiers (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;

	fic.open( save_box.GetPathName());

	fic<<"<HTML>"<<endl;
	fic<<"<BODY>"<<endl;
	fic<<"<p align=\"center\"><H1>"<<sbk_name<<"<br><br></h1>"<<endl;

	fic<<"<table border=\"1\">"<<endl;

	fic<<"<tr>"<<endl;
	fic<<"<td><h2>Numéro</td>"<<endl;
	fic<<"<td><h2>Non</td>"<<endl;
	fic<<"<td><h2>Nb</td>"<<endl;
	fic<<"</tr>"<<endl;

	for ( int i=0; i < list->GetCount(); i++)
	{
		ptr = (SOUND*) list->GetItemDataPtr( i);

		fic<<"<tr>"<<endl;
		fic<<"<td>"<<i<<"</td>";
		fic<<"<td>"<<(ptr->file)<<"</td>";
		fic<<"<td>"<<(ptr->n)<<"</td>";
		fic<<"</tr>"<<endl;
	}

	fic<<"</table>"<<endl;
	fic<<"</body>"<<endl;
	fic<<"</html>"<<endl;

	fic.close();
}
