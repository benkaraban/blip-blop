// GFX_EditorDlg.cpp : implementation file
//
#include "stdafx.h"
#include "GFX_Editor.h"
#include "GFX_EditorDlg.h"
#include "infos.h"

#include "Utils.h"
#include "BMPUtils.h"

#include "Log.h"

#define NB_MAX_PIC	5000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char dummy[MAX_PATH];


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
// CGFX_EditorDlg dialog

CGFX_EditorDlg::CGFX_EditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGFX_EditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGFX_EditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	animating = FALSE;

	Log::Clear();
}

void CGFX_EditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGFX_EditorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGFX_EditorDlg, CDialog)
	//{{AFX_MSG_MAP(CGFX_EditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUPP, OnButtonSupp)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_ZOOM, OnSelchangeComboZoom)
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_NEW_PBK, OnButtonNewPbk)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_COMPILE, OnButtonCompile)
	ON_CBN_SELCHANGE(IDC_COMBO_PAK, OnSelchangeComboPak)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON_HTML, OnButtonHtml)
	ON_BN_CLICKED(IDC_BUTTON_ANIM, OnButtonAnim)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BIMPORTGFX, &CGFX_EditorDlg::OnBnClickedBimportgfx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGFX_EditorDlg message handlers

BOOL CGFX_EditorDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here

	CComboBox * combo = (CComboBox*) GetDlgItem( IDC_COMBO_ZOOM);
	CEdit * edit_delai = (CEdit *) GetDlgItem( IDC_EDIT_DELAI_ANIM);

	combo->SetCurSel( combo->FindString( 0, "1x"));

	edit_delai->SetWindowText( "100");

	pbk_changed = FALSE;
	pbk_name = "Untitled.pbk";


	metAJourTitre();

	if ( cmd_line.GetLength() > 0)
	{
		cmd_line = cmd_line.Right( cmd_line.GetLength() - 1);
		cmd_line = cmd_line.Left( cmd_line.GetLength() - 1);
		LoadPBK( LPCSTR(cmd_line));
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGFX_EditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGFX_EditorDlg::OnPaint() 
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

		DisplayImage();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGFX_EditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGFX_EditorDlg::OnButtonAdd() 
{
	const int BUFFER_SIZE = MAX_PATH*1000;

	static int	cpt = 0;
	CString		str;
	int			rang;
	GFXPIC *	pic;
	char *		fic;
	int			i;
	POSITION	pos;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	CFileDialog load_box (TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "Bitmap Images (*.BMP)|*.bmp|All the files (*.*)|*.*||", NULL);

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


		pic = new GFXPIC;
		pic->file = str;	// Pour le chemin complet
		pic->xspot = 0;
		pic->yspot = 0;
		pic->compression = 1;

		// Grumpf! On est obligé d'extraire le nom du fichier lui même à la main

		i = str.GetLength()-1;

		while ( str[i] != '\\' && i > 0)
			i--;

		str = str.Right( str.GetLength()-(i+1));


		rang = list->AddString( str);
		list->SetItemDataPtr( rang, (void*) pic);

	}

	delete [] fic;
	change();
}

void CGFX_EditorDlg::OnButtonSupp() 
{
	int		i;
	int		tab[NB_MAX_PIC];
	int		nb_sel;
	GFXPIC *	pic;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	nb_sel = list->GetSelItems( NB_MAX_PIC, tab);

	for ( i=0; i<list->GetCount(); i++)
	if ( list->GetSel(i) > 0)
	{
		pic = (GFXPIC *) list->GetItemDataPtr( i);
		delete pic;

		list->DeleteString( i--);
	}

	DisplayImage( TRUE);
	change();
}

void CGFX_EditorDlg::OnButtonInsert() 
{
	const int BUFFER_SIZE = MAX_PATH*1000;

	static int	cpt = 0;
	CString		str;
	int			rang;
	GFXPIC *	pic;
	char *		fic;
	char		sep[] = "*";
	int			i;
	POSITION	pos;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	CFileDialog load_box (TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "Bitmap Images (*.BMP)|*.bmp|All the files (*.*)|*.*||", NULL);

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


		pic = new GFXPIC;
		pic->file = str;	// Pour le chemin complet
		pic->xspot = 0;
		pic->yspot = 0;
		pic->compression = 1;

		// Grumpf! On est obligé d'extraire le nom du fichier lui même à la main

		i = str.GetLength()-1;

		while ( str[i] != '\\' && i > 0)
			i--;

		str = str.Right( str.GetLength()-(i+1));


		rang = list->InsertString( rang+1, str);
		list->SetItemDataPtr( rang, (void*) pic);

	}

	delete [] fic;

	change();

}

void CGFX_EditorDlg::OnButtonUp() 
{
	int			i;
	CString		s;
	char		buff[200];
	int			select[NB_MAX_PIC];
	int			nb_sel;
	GFXPIC *	pic;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	nb_sel = list->GetSelItems( NB_MAX_PIC, select);

	if ( select[0] != 0)
	{
		for ( i=0; i < nb_sel; i++)
		{
			list->GetText( select[i], buff);
			pic = (GFXPIC *) list->GetItemDataPtr( select[i]);
			
			list->InsertString( select[i]-1, buff);
			list->SetItemDataPtr( select[i]-1, (void*)pic);

			list->DeleteString( select[i]+1);
		}
	
		for ( i=0; i < nb_sel; i++)
		{
			list->SetSel( select[i]-1);
		}
	}
	change();

}

void CGFX_EditorDlg::OnButtonDown() 
{
	int			i;
	CString		s;
	char		buff[200];
	int			select[NB_MAX_PIC];
	int			nb_sel;
	int			nb_str;
	GFXPIC *	pic;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);

	nb_sel = list->GetSelItems( NB_MAX_PIC, select);
	nb_str = list->GetCount();


	if ( (nb_sel < nb_str) && select[nb_sel-1] < nb_str-1)
	{
		for ( i = nb_sel-1; i >= 0; i--)
		{
			list->GetText( select[i], buff);
			pic = (GFXPIC *) list->GetItemDataPtr( select[i]);
			
			list->InsertString( select[i]+2, buff);
			list->SetItemDataPtr( select[i]+2, (void*)pic);

			list->DeleteString( select[i]);
		}
	
		for ( i=0; i < nb_sel; i++)
		{
			list->SetSel( select[i]+1);
		}
	}
	
	change();
}

void CGFX_EditorDlg::OnSelchangeList() 
{
	DisplayImage( TRUE, TRUE, TRUE);
}








void CGFX_EditorDlg::OnButtonQuit() 
{
	int			rval=0;
	
	if ( pbk_changed )
		rval = MessageBox(	"Attention! Changes hasn't been saved. Do you want to continue ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && pbk_changed)
		return;


	freeMemory();
	DestroyWindow();
}

void CGFX_EditorDlg::DisplayImage( BOOL clear, BOOL reinit, BOOL reload, BOOL spotChange)
{
	int			rang;
	BITMAP		bm;
	GFXPIC *	data;
	int			x1;
	int			y1;
	int			largeur;
	int			hauteur;
	int			xs;
	int			ys;
	int			zoom;
	int			nbsel;
	HDC			hdcImage;
	CDC *		DCFrame;
	char		buffer[128];
	CString		string;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CStatic * txtSpot = (CStatic *) GetDlgItem( IDC_STATIC_HOTSPOT);
	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 
	CStatic * txtSize = (CStatic *) GetDlgItem( IDC_STATIC_PICSIZE); 
	CScrollBar * barH = (CScrollBar *) GetDlgItem( IDC_SCROLLBAR_HORIZ);
	CScrollBar * barV = (CScrollBar *) GetDlgItem( IDC_SCROLLBAR_VERT);
	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);
	CComboBox * combo = (CComboBox *) GetDlgItem( IDC_COMBO_ZOOM);
	CComboBox * combo_pak = (CComboBox *) GetDlgItem( IDC_COMBO_PAK);

	//
	// Pas de selection OU plusieurs sélections->Quitte en effaçant le schnuff
	//
	nbsel = list->GetSelCount();

	if ( nbsel != 1)
	{
		DCFrame = frame->GetDC();
		DCFrame->FillRect( CRect(1, 1, 545, 489), CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
		frame->ReleaseDC( DCFrame);

		if ( nbsel == 0)
		{
			sprintf( buffer, "Nothing Selected");
			combo_pak->SetCurSel( -1);
		}
		else
		{
			// Si il y a plusieurs images selectionnées, on regarde si elles ont toutes
			// la même compression. Si c'est le cas on l'affiche.

			int * tab_sel = new int[nbsel];
			
			list->GetSelItems( nbsel, tab_sel);



			GFXPIC *	info;
			int			i;
			int			comp;

			info = (GFXPIC *) list->GetItemDataPtr( tab_sel[0]);
			comp = info->compression;

			i = 1;	// Remarque : ici on est sûr que le tableau va AU MOINS jusqu'à 1
			
			do{
				info = (GFXPIC *) list->GetItemDataPtr( tab_sel[i]);
				i++;

			}while( i < nbsel && comp == info->compression);

			if ( comp == info->compression)
				combo_pak->SetCurSel( comp);
			else
				combo_pak->SetCurSel( -1);

			sprintf( buffer, "%d images selected", nbsel);

			delete [] tab_sel;
		}

		txtSize->SetWindowText( "-");
		txtSpot->SetWindowText( "-");
		text->SetWindowText( buffer);


		return;	
	}


	//
	// On récupère la valeur du zoom
	//
	combo->GetLBText( combo->GetCurSel(), string);
	sscanf(LPCSTR(string), "%d", &zoom);

	//
	// Récupère les données de la selection
	//
	rang = list->GetCurSel();
	data = (GFXPIC *) list->GetItemDataPtr( rang);

	//
	// Affiche la valeur de la compression
	//
	combo_pak->SetCurSel( data->compression);


	//
	// Charge l'image
	//

	if ( reload )	// On évite de la charger 10.000 fois
	{
		if ( hbm != NULL)
			DeleteObject( hbm);

		hbm = (HBITMAP)LoadImage(NULL, LPCTSTR(data->file), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( hbm == NULL)
		{
			text->SetWindowText( "Cannot load image");
			return;
		}
	}

	//
	// Récupère le HDC de l'image
	//
	hdcImage = CreateCompatibleDC( NULL);

	if ( hdcImage == NULL)
	{
		text->SetWindowText("CreateDC Error!");
		return;
	}

	//
	// Prépare le Blit (début)
	//
	SelectObject( hdcImage, hbm);
	GetObject( hbm, sizeof(bm), &bm);
	
	int	bmX = bm.bmWidth;
	int bmY = bm.bmHeight;
	int bmXz = bmX * zoom;
	int bmYz = bmY * zoom;

	sprintf( buffer, "(%d,%d)", bm.bmWidth, bm.bmHeight);
	txtSize->SetWindowText( buffer);

	DCFrame = frame->GetDC();



	//
	// Change les scrollbars SI (et seulement si!) on change d'image/de zoom
	//
	if ( reinit )
	{
		if ( bmXz > 544 )
		{
			barH->SetScrollRange( 0, (bmXz-544)/zoom);
		}
		else
			barH->SetScrollRange( 0, 0);

		if ( bmYz > 488 )
		{
			barV->SetScrollRange( 0, (bmYz-488)/zoom);
		}
		else
			barV->SetScrollRange( 0, 0);
	}

	//
	//	Efface l'ancienne image
	//
	if ( clear )
	{
		DCFrame->FillRect( CRect(1, 1, 545, 489), CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
	}

	x1 = barH->GetScrollPos();
	y1 = barV->GetScrollPos();

	//
	// Si les coordonnées du hotspot ont changé, on se référe à celles de la souris
	//
	if ( spotChange )
	{
		int		tmpX = xmouse;
		int		tmpY = ymouse;

		tmpX -= 196;	// Change de référentiel
		tmpY -= 41;

		tmpX /= zoom;	// Prend en compte le zoom
		tmpY /= zoom;

		tmpX += x1;	// Ajoute les coordonnées des scrollbars
		tmpY += y1;

		if ( tmpX >= bmX ) tmpX = bmX - 1;	// Evite de sortir de l'image
		if ( tmpY >= bmY ) tmpY = bmY - 1;

		data->xspot = tmpX;
		data->yspot = tmpY;

		pbk_changed = TRUE;
		metAJourTitre();

	}

	//
	//	Affiche les coordonnées du hotspot
	//
	sprintf( buffer, "(%d,%d)", data->xspot, data->yspot);
	txtSpot->SetWindowText( buffer);


	//
	// Prépare le Blit
	//
	largeur = 544/zoom;
	hauteur = 488/zoom;

	if ( largeur+x1 > bmX) largeur = bmX;
	if ( hauteur+y1 > bmY) hauteur = bmY;

	xs = bmXz;
	ys = bmYz;

	if ( xs > 544)
		xs = 544;

	if   ( ys > 488)
		ys = 488;



	//
	// Blitte moi la gueule!
	//
    StretchBlt(DCFrame->m_hDC, 1, 1, xs, ys, hdcImage, x1, y1, largeur, hauteur, SRCCOPY);

	//
	// And now, let's see the hot spot! =)
	//
	xs = data->xspot;	// Réutilisation des variables
	ys = data->yspot;

	xs -= x1;	// Retire les coords des scrollbars
	ys -= y1;

	xs *= zoom;	// Prend en compte le zoom
	ys *= zoom;

	xs++;		// Pour les bordures
	ys++;

	CBrush	brush( RGB(255, 255, 255));
	CPen	pen( PS_SOLID, 1, RGB( 255, 255, 255));

	DCFrame->SelectObject( brush);
	DCFrame->SelectObject( pen);
	DCFrame->SetROP2( R2_XORPEN);

	if ( zoom == 1)	// Pas de zoom => on fait des lignes
	{
		if ( xs >= 1 && xs <= 544)
		{
			DCFrame->MoveTo( xs, 1);
			DCFrame->LineTo( xs, 489);
		}

		if ( ys >= 1 && ys <= 488)
		{
			DCFrame->MoveTo( 1, ys);
			DCFrame->LineTo( 545, ys);
		}
	}
	else	// Zoom => on fait des rectangles
	{
		if ( xs >= 1 && xs <= 544)
			DCFrame->Rectangle( xs, 1, xs+zoom, 489);

		if ( ys >= 1 && ys <= 488)
			DCFrame->Rectangle( 1, ys, 545, ys+zoom);
	}

	//
	// Libère le tout
	//
	frame->ReleaseDC( DCFrame);
	DeleteDC( hdcImage);

	text->SetWindowText( "Ready");
}

void CGFX_EditorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	static int rem_pos;

	int	min;
	int	max;
	int	space;

	pScrollBar->GetScrollRange( &min, &max);
	space = (max - min)/5;

	switch ( nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos( nPos);
		rem_pos = nPos;
		break;

	case SB_LINELEFT:
		pScrollBar->SetScrollPos( --rem_pos);
		break;

	case SB_LEFT:
		pScrollBar->SetScrollPos( --rem_pos);
		break;

	case SB_LINERIGHT:
		pScrollBar->SetScrollPos( ++rem_pos);
		break;

	case SB_RIGHT:
		pScrollBar->SetScrollPos( ++rem_pos);
		break;

	case SB_PAGELEFT:
		rem_pos -= space;
		pScrollBar->SetScrollPos( rem_pos);
		break;

	case SB_PAGERIGHT:
		rem_pos += space;
		pScrollBar->SetScrollPos( rem_pos);
		break;

	case SB_ENDSCROLL:
		pScrollBar->SetScrollPos( rem_pos);
	}

	DisplayImage(TRUE);
}



void CGFX_EditorDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	static int rem_pos;

	int	min;
	int	max;
	int	space;

	pScrollBar->GetScrollRange( &min, &max);
	space = (max - min)/5;

	switch ( nSBCode)
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos( nPos);
		rem_pos = nPos;
		break;

	case SB_LINELEFT:
		pScrollBar->SetScrollPos( --rem_pos);
		break;

	case SB_LEFT:
		pScrollBar->SetScrollPos( --rem_pos);
		break;

	case SB_LINERIGHT:
		pScrollBar->SetScrollPos( ++rem_pos);
		break;

	case SB_RIGHT:
		pScrollBar->SetScrollPos( ++rem_pos);
		break;

	case SB_PAGELEFT:
		rem_pos -= space;
		pScrollBar->SetScrollPos( rem_pos);
		break;

	case SB_PAGERIGHT:
		rem_pos += space;
		pScrollBar->SetScrollPos( rem_pos);
		break;

	case SB_ENDSCROLL:
		pScrollBar->SetScrollPos( rem_pos);
	}

	DisplayImage( TRUE);
}


void CGFX_EditorDlg::OnSelchangeComboZoom() 
{
	DisplayImage( TRUE, TRUE);	
	
}

void CGFX_EditorDlg::OnClose() 
{
	int			rval=0;
	
	if ( pbk_changed )
		rval = MessageBox(	"Attention! Changes hasn't been saved. Do you want to continue ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && pbk_changed)
		return;


	freeMemory();
	CDialog::OnClose();
}

void CGFX_EditorDlg::freeMemory()
{
	GFXPIC *	pic=0;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);


	// On vide la ListBox
	//
	if ( list->GetCount() > 0)
	{
		do {
			pic = (GFXPIC *) list->GetItemDataPtr( 0);
			delete pic;

		} while( list->DeleteString(0) != 0);
	}

	// Et le HBM
	//
	if ( hbm != NULL)
	{
		DeleteObject( hbm);
		hbm = NULL;
	}

}


void CGFX_EditorDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	xmouse = point.x;
	ymouse = point.y;

	CDialog::OnMouseMove(nFlags, point);
}

void CGFX_EditorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{

	if ( xmouse >= 196 && xmouse <= 741 &&
		 ymouse >= 41  && ymouse <= 533 && !animating)
	{
		DisplayImage( TRUE, FALSE, FALSE, TRUE);
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CGFX_EditorDlg::OnButtonNewPbk() 
{

	int rval=0;
	
	if ( pbk_changed )
		rval = MessageBox(	"Attention! Changes hasn't been saved. Do you want to continue ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);

	if ( rval == IDOK || !pbk_changed)
	{
		freeMemory();
		DisplayImage();

		pbk_changed = FALSE;
		pbk_name = "Untitled.pbk";
		metAJourTitre();
	}
}

void CGFX_EditorDlg::metAJourTitre()
{
	CString tmp = "LOADED GFX Editor - ";
	tmp += pbk_name;

	if ( pbk_changed)
	{
		tmp += "*";
	}

	SetWindowText( tmp);

}

void CGFX_EditorDlg::change()
{
	if ( !pbk_changed )
	{
		pbk_changed = TRUE;
		metAJourTitre();
	}

}

void CGFX_EditorDlg::OnButtonSave() 
{
	GFXPIC *	info;
	ofstream	fic;	
	char *		buffer;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 

	int	n = list->GetCount();

	if ( n == 0)	// Liste vide -> on se casse
		return;

	//
	// Choisit le nom du fichier
	//
	CFileDialog load_box( FALSE, "pbk", pbk_name, 0, "PBK Files (*.pbk)|*.pbk|All the files (*.*)|*.*||", NULL);

	if ( load_box.DoModal() != IDOK)
		return;

	buffer = new char[40];

	bar->SetRange32( 0, n);
	bar->SetStep( 1);
	bar->SetPos( 0);

	fic.open( load_box.GetPathName());
	fic<<n<<endl;

	for ( int i=0; i < n; i++)
	{
		sprintf( buffer, "Image Backup %d/%d", i+1, n);
		text->SetWindowText( buffer);

		info = (GFXPIC *) list->GetItemDataPtr( i);

		fic<<(info->xspot)<<' ';
		fic<<(info->yspot)<<' ';
		fic<<(info->compression)<<endl;
		fic<<(info->file);
		fic<<endl;

		bar->StepIt();
	}

	bar->SetPos( 0);
	pbk_name = load_box.GetFileName();
	pbk_changed = FALSE;
	metAJourTitre();
	delete [] buffer;
	fic.close();

}

void CGFX_EditorDlg::OnButtonLoad() 
{
	int			rval = 0;
	
	if ( pbk_changed )
		rval = MessageBox(	"Attention! Changes hasn't been saved. Do you want to continue ?", 
							NULL,
							MB_OKCANCEL | MB_ICONEXCLAMATION);
	if ( rval != IDOK && pbk_changed)
		return;
	
	//
	// Choisit le nom du fichier
	//
	CFileDialog load_box( TRUE, "pbk", NULL, 0, "PBK Files (*.pbk)|*.pbk|All the files (*.*)|*.*||", NULL);

	if ( load_box.DoModal() != IDOK)
		return;

	LoadPBK( load_box.GetPathName());

	pbk_name = load_box.GetFileName();
}

void CGFX_EditorDlg::OnButtonCompile() 
{
	GFXPIC *	info;
	int			i;
	int			n;
	CString		str;
	FILE *		fic;
	HDC			hdcImage;
	HBITMAP		tmp_hbm;
	BITMAP		bm;
	void *		ptr;
	int			taille;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 

	//
	// Choisit le nom du fichier
	//
	CFileDialog save_box( FALSE, "gfx", NULL, 0, "GFX Files (*.gfx)|*.gfx|All the files (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;


	fic = fopen( save_box.GetPathName(), "wb");
	if ( fic == NULL)
	{
		MessageBox( "Unable to write file", NULL, MB_OK | MB_ICONERROR);
		return;
	}


	n = list->GetCount();
	fwrite( &n, sizeof(n), 1, fic);		// Nombre d'images


	bar->SetRange32( 0, n);
	bar->SetStep( 1);
	bar->SetPos( 0);

	for ( i=0; i < n; i++)
	{
		info = (GFXPIC *) list->GetItemDataPtr( i);

		fwrite(&(info->xspot), sizeof(info->xspot), 1, fic);	// Point chaud
		fwrite(&(info->yspot), sizeof(info->yspot), 1, fic);

		// Charge l'image

		tmp_hbm = (HBITMAP)LoadImage(NULL, LPCTSTR(info->file), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if ( tmp_hbm == NULL)
		{
			text->SetWindowText( "Cannot load image");
			return;
		}

		//
		// Récupère le HDC de l'image
		//
		hdcImage = CreateCompatibleDC( NULL);

		if ( hdcImage == NULL)
		{
			text->SetWindowText("CreateDC Error!");
			return;
		}

		//
		// Prépare le Blit (début)
		//
		SelectObject( hdcImage, tmp_hbm);
		GetObject( tmp_hbm, sizeof(bm), &bm);

		if ( info->compression == 0)
		{
			taille = createLGX_0( hdcImage, bm.bmWidth, bm.bmHeight, ptr);
		}
		else // if ( info->compression == 1)
		{
			taille = createLGX_1( hdcImage, bm.bmWidth, bm.bmHeight, ptr);
		}

		if ( taille == 0)
		{
			MessageBox( "Error converting LGX", NULL, MB_OK | MB_ICONERROR);
			return;
		}

		fwrite( &taille, sizeof(taille), 1, fic);	// Taille du fichier LGX
		fwrite( ptr, 1, taille, fic);				// Fichier LGX

		bar->StepIt();
		free( ptr);
		DeleteDC( hdcImage);
		DeleteObject( tmp_hbm);
	}


	fclose( fic);
	bar->SetPos( 0);
}


void CGFX_EditorDlg::OnSelchangeComboPak() 
{
	int		nb_sel;
	int		tab[NB_MAX_PIC];
	int		type_pak;
	GFXPIC *info;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CComboBox * combo_pak = (CComboBox *) GetDlgItem( IDC_COMBO_PAK);

	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 

	nb_sel = list->GetSelItems( NB_MAX_PIC, tab);

	type_pak = combo_pak->GetCurSel();

	if ( nb_sel < 1)	// Pas de selection
		return;

	for ( int i=0; i < nb_sel; i++)
	{
		info = ( GFXPIC *) list->GetItemDataPtr( tab[i]);
		info->compression = type_pak;
	}

		
	change();
}

void CGFX_EditorDlg::OnButtonAbout() 
{
	CAboutDlg	about;

	about.DoModal();
}

void CGFX_EditorDlg::OnButtonHtml() 
{
	ofstream	fic;	
	CString		str;
	GFXPIC *	ptr;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 

	// Choisit le nom du fichier
	//
	CFileDialog save_box( FALSE, "html", NULL, 0, "HTML Files (*.html, *.htm)|*.htm;*.html|All the files (*.*)|*.*||", NULL);

	if ( save_box.DoModal() != IDOK)
		return;
	
	fic.open( save_box.GetPathName());

	fic<<"<HTML>"<<endl;
	fic<<"<BODY>"<<endl;
	fic<<"<p align=\"center\"><H1>"<<pbk_name<<"<br><br></h1>"<<endl;

	fic<<"<table border=\"1\">"<<endl;

	fic<<"<tr>"<<endl;
	fic<<"<td><h2>Number</td>"<<endl;
	fic<<"<td><h2>Image</td>"<<endl;
	fic<<"<td><h2>Name</td>"<<endl;
	fic<<"<td width=\"300\"><h2>Description</td>"<<endl;
	fic<<"</tr>"<<endl;

	int	n = list->GetCount();

	for ( int i=0; i < n; i++)
	{
		fic<<"<tr>"<<endl;

		fic<<"<td><h2>"<<i<<"</td>"<<endl;

		list->GetText( i, str);
		ptr = (GFXPIC*) list->GetItemDataPtr( i);

		fic<<"<td><img src=\""<<ptr->file<<"\"></td>"<<endl;
		fic<<"<td>"<<str<<"</td>"<<endl;
		fic<<"<td>&nbsp</td>"<<endl;
		fic<<"</tr>"<<endl;

	}

	fic<<"</table>"<<endl<<endl;
	fic<<"</body>"<<endl;
	fic<<"</html>"<<endl;

	fic.close();

}

void CGFX_EditorDlg::OnButtonAnim() 
{
	GFXPIC *	info;
	CDC *		dc;
	CString		string;
	int			anim_delay;

	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CButton * anim = (CButton *) GetDlgItem( IDC_BUTTON_ANIM);
	CButton * up = (CButton *) GetDlgItem( IDC_BUTTON_UP);
	CButton * down = (CButton *) GetDlgItem( IDC_BUTTON_DOWN);
	CButton * add = (CButton *) GetDlgItem( IDC_BUTTON_ADD);
	CButton * insert = (CButton *) GetDlgItem( IDC_BUTTON_INSERT);
	CButton * supp = (CButton *) GetDlgItem( IDC_BUTTON_SUPP);

	CButton * m_new = (CButton *) GetDlgItem( IDC_BUTTON_NEW_PBK);
	CButton * m_load = (CButton *) GetDlgItem( IDC_BUTTON_LOAD);
	CButton * m_save = (CButton *) GetDlgItem( IDC_BUTTON_SAVE);
	CButton * m_comp = (CButton *) GetDlgItem( IDC_BUTTON_COMPILE);
	CButton * m_about = (CButton *) GetDlgItem( IDC_BUTTON_ABOUT);
	CButton * m_html = (CButton *) GetDlgItem( IDC_BUTTON_HTML);
	CButton * m_quit = (CButton *) GetDlgItem( IDC_BUTTON_QUIT);

	CComboBox * combo = (CComboBox *) GetDlgItem( IDC_COMBO_ZOOM);
	CComboBox * combo_pak = (CComboBox *) GetDlgItem( IDC_COMBO_PAK);
	CFrameWnd * fond = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CEdit * edit_delai = (CEdit *) GetDlgItem( IDC_EDIT_DELAI_ANIM);

	if ( !animating )
	{
		nb_anim = list->GetSelItems( MAX_ANIM, anim_pix);

		edit_delai->GetWindowText( string);

		if ( string.GetLength() == 0)
		{
			MessageBox("You forgot to specify an animation time", NULL, MB_ICONERROR);
			return;
		}
		
		sscanf( LPCSTR(string), "%d", &anim_delay);
		
		if ( nb_anim == 0)
		{
			return;
		}

		up->EnableWindow( FALSE);
		down->EnableWindow( FALSE);
		add->EnableWindow( FALSE);
		insert->EnableWindow( FALSE);
		supp->EnableWindow( FALSE);
		list->EnableWindow( FALSE);
		combo->EnableWindow( FALSE);
		combo_pak->EnableWindow( FALSE);
		m_new->EnableWindow( FALSE);
		m_load->EnableWindow( FALSE);
		m_save->EnableWindow( FALSE);
		m_comp->EnableWindow( FALSE);
		m_about->EnableWindow( FALSE);
		m_html->EnableWindow( FALSE);
		m_quit->EnableWindow( FALSE);
		edit_delai->EnableWindow( FALSE);

		anim->SetWindowText("Stop");


		
		frame = 0;
		
		anim_bmp = new HBITMAP[nb_anim];

		for ( int i=0; i < nb_anim; i++)
		{
			info = (GFXPIC *) list->GetItemDataPtr( anim_pix[i]);

			anim_bmp[i] = (HBITMAP)LoadImage(NULL, LPCTSTR(info->file), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		}

		dc = fond->GetDC();
		dc->FillRect( CRect(1, 1, 545, 489), CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
		
		SetTimer( 24, anim_delay, NULL);
		animating = TRUE;
	}
	else
	{
		up->EnableWindow();
		down->EnableWindow();
		add->EnableWindow();
		insert->EnableWindow();
		supp->EnableWindow();
		list->EnableWindow();
		combo->EnableWindow();
		combo_pak->EnableWindow();
		m_new->EnableWindow();
		m_load->EnableWindow();
		m_save->EnableWindow();
		m_comp->EnableWindow();
		m_about->EnableWindow();
		m_html->EnableWindow();
		m_quit->EnableWindow();
		edit_delai->EnableWindow();

		anim->SetWindowText("Animate");

		DisplayImage( TRUE, TRUE, FALSE, FALSE);

		KillTimer( 24);

		for ( int i=0; i < nb_anim; i++)
			DeleteObject( anim_bmp[i]);

		delete [] anim_bmp;
		animating = FALSE;
	}

}

void CGFX_EditorDlg::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 24 && animating)	// Timer de l'animation
	{
		GFXPIC *	info;
		CDC *		dc;
		HDC			hdcImage;
		BITMAP		bm;
		int			xi;
		int			yi;
	
		CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
		CFrameWnd * fond = (CFrameWnd *) GetDlgItem( IDC_FRAME);

		frame++;
		frame %= nb_anim;
		
		info = (GFXPIC *) list->GetItemDataPtr( anim_pix[frame]);

		hdcImage = CreateCompatibleDC( NULL);


		if ( hdcImage == NULL)
			return;

		SelectObject( hdcImage, anim_bmp[frame]);
		GetObject( anim_bmp[frame], sizeof(bm), &bm);

		dc = fond->GetDC();
	
		int	bmX = bm.bmWidth;
		int bmY = bm.bmHeight;

		int	x = 272 - (info->xspot);
		int y = 244 - (info->yspot);

		if ( x > 1)
			xi = 0;
		else
		{
			xi = - (x - 1);
			x = 1;
		}

		if ( y > 1)
			yi = 0;
		else
		{
			yi = - (y - 1);
			y = 1;
		}

		if ( (bmX - info->xspot) > 272)
			bmX = 272;

		if ( (bmY - info->yspot) > 244)
			bmY = 244;

		BitBlt( dc->m_hDC, x, y, bmX, bmY, hdcImage, xi, yi, SRCCOPY);

		DeleteDC( hdcImage);
		fond->ReleaseDC( dc);
	}

	CDialog::OnTimer(nIDEvent);
}

void CGFX_EditorDlg::LoadPBK(const char *nom_fic)
{

	GFXPIC *	info;
	ifstream	fic;	
	char *		buffer;
	int			j;
	int			n;
	CString		str;


	CListBox * list = (CListBox *) GetDlgItem( IDC_LIST);
	CProgressCtrl * bar = (CProgressCtrl *) GetDlgItem( IDC_PROGRESS);
	CStatic * text = (CStatic *) GetDlgItem( IDC_STATIC_STATE); 


	fic.open( nom_fic, ios::in /*| ios::nocreate*/);
	if ( fic.is_open() == 0)
		return;

	freeMemory();

	buffer = new char[MAX_PATH];


	fic>>n;


	bar->SetRange32( 0, n);
	bar->SetStep( 1);
	bar->SetPos( 0);


	for ( int i=0; i < n; i++)
	{
		sprintf( buffer, "Loading image %d/%d", i+1, n);
		text->SetWindowText( buffer);

		info = new GFXPIC;

		fic>>(info->xspot);
		fic>>(info->yspot);
		fic>>(info->compression);
		fic.getline( buffer, MAX_PATH);
		fic.getline( buffer, MAX_PATH);

		info->file = CString( buffer);

		//
		// Récupère le nom court
		//
		str = info->file;
		j = str.GetLength()-1;

		while ( str[j] != '\\' && j > 0)
			j--;

		str = str.Right( str.GetLength()-(j+1));

		j = list->AddString( str);
		list->SetItemDataPtr( j, (void *) info);


		bar->StepIt();
	}

	str = nom_fic;
	j = str.GetLength()-1;

	while ( str[j] != '\\' && j > 0)
		j--;

	pbk_name = str.Right( str.GetLength()-(j+1));

	bar->SetPos( 0);
	pbk_changed = FALSE;
	metAJourTitre();
	delete [] buffer;
	fic.close();

}



void CGFX_EditorDlg::OnBnClickedBimportgfx()
{
	const int BUFFER_SIZE = MAX_PATH * 1000;

	static int	cpt = 0;
	CString		str;
	int			rang;
	GFXPIC *	pic;
	char *		fic;
	char		sep[] = "*";
	int			i;
	POSITION	pos;
	char buffer[MAX_PATH];


	CListBox * list = (CListBox *)GetDlgItem(IDC_LIST);
	memset(buffer, 0, sizeof(buffer));


	CFileDialog load_box(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, "GFX Images (*.GFX)|*.gfx|All the files (*.*)|*.*||", NULL);

	fic = new char[BUFFER_SIZE];
	fic[0] = '\0';

	load_box.m_ofn.lpstrFile = fic;
	load_box.m_ofn.nMaxFile = BUFFER_SIZE;

	if (load_box.DoModal() == IDCANCEL)
	{
		delete[] fic;
		return;
	}
	pos = load_box.GetStartPosition();

	rang = list->GetCurSel();

	str = load_box.GetNextPathName(pos);
	for (int i = 0; i < str.GetLength(); i++)
	{
		buffer[i] = str[i];
	}

	unpackGFX(buffer);

	/*pic = new GFXPIC;
	pic->file = str;	// Pour le chemin complet
	pic->xspot = 0;
	pic->yspot = 0;
	pic->compression = 1;


	// Grumpf! On est obligé d'extraire le nom du fichier lui même à la main

	i = str.GetLength() - 1;

	while (str[i] != '\\' && i > 0)
		i--;

	str = str.Right(str.GetLength() - (i + 1));


	rang = list->InsertString(rang + 1, str);
	list->SetItemDataPtr(rang, (void*)pic);*/


	delete[] fic;

	change();
}

void CGFX_EditorDlg::unpackGFX(char* path)
{
	ifstream file;

	unsigned int countImages=0;

	if (!dirExists("import_temp"))
	{
		CreateDirectory("import_temp", NULL);
	}

	file.open(path, ios::binary);

	file.read((char*)&countImages, 4);
	Log::Debug << "Loading GFX file." << endl << "Images found:" << (int)countImages << endl;

	for (int i = 0; i < countImages; i++)
	{
		struct
		{
			int cx, cy;
			int size;
		} record;

		char *buffer = 0;
		file.read((char*)&record, sizeof(record));

		Log::Debug << "Reading image " << i << "\nData size: " << record.size << " byte \nCenter X: " << record.cx << "\nCenter Y: " << record.cy << endl;

		buffer = new char[record.size];
		file.read((char*)buffer, record.size);

		LGX_HEADER *header = (LGX_HEADER*)buffer;

		Log::Debug << "( " << header->xsize << "w - " << header->ysize << "h )" << endl;

		/*if (header->version == 0)
		{*/
			char fName[256];
			_splitpath(path, dummy, dummy, fName, dummy);

			char path[256];

			if (strlen(fName) > 0)
			{
				if (!dirExists(string("import_temp/")+fName))
					CreateDirectory((string("import_temp/") + fName).c_str(), NULL);
				sprintf(path, "import_temp/%s/%d.bmp", fName, i);
			}
			else
			{
				sprintf(path, "import_temp/%d.bmp", i);
			}

			unsigned char *buff2;
			
			if (header->version == 0)
				buff2 = convertLGX0ToRGB(((unsigned char*)buffer) + sizeof(LGX_HEADER), record.size - sizeof(LGX_HEADER));
			else
				buff2 = convertLGX1ToRGB(((unsigned char*)buffer) + sizeof(LGX_HEADER), record.size - sizeof(LGX_HEADER),header->xsize,header->ysize);

			long BMPbufferSize = 0;
			BYTE* buff3 = ConvertRGBToBMPBuffer(buff2, header->xsize, header->ysize, &BMPbufferSize);
			SaveBMP(buff3, header->xsize, header->ysize, BMPbufferSize, path);



			GFXPIC *pic = new GFXPIC;
			pic->file = path;	// Pour le chemin complet
			pic->xspot = record.cx;
			pic->yspot = record.cy;
			pic->compression = 1;

			CListBox * list = (CListBox *)GetDlgItem(IDC_LIST);
			int rang = list->GetCurSel();
			/*if (rang == -1)
				rang = 0;*/
			rang = list->AddString(path);
			list->SetItemDataPtr(rang, (void*)pic);

			delete buff2;
			delete buff3;
		/*}*/

		delete buffer;
		
	}

}