// BB3_level_editorDlg.cpp : implementation file
//
#include "stdafx.h"
#include "BB3_level_editor.h"
#include "BB3_level_editorDlg.h"
#include "const.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorDlg dialog

CBB3_level_editorDlg::CBB3_level_editorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBB3_level_editorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBB3_level_editorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBB3_level_editorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBB3_level_editorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBB3_level_editorDlg, CDialog)
	//{{AFX_MSG_MAP(CBB3_level_editorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TOOL, OnSelchangeComboTool)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT_ARG3, OnChangeEditArg3)
	ON_CBN_EDITCHANGE(IDC_COMBO_ARG1, OnEditchangeComboArg1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAuto)
	ON_BN_CLICKED(IDC_CHECK_MURS_OPAK, OnCheckMursOpak)
	ON_BN_CLICKED(IDC_CHECK_MURS_SANG, OnCheckMursSang)
	ON_BN_CLICKED(IDC_CHECK_PLAT, OnCheckPlat)
	ON_BN_CLICKED(IDC_CHECK_ENNEMIS, OnCheckEnnemis)
	ON_BN_CLICKED(IDC_CHECK_GENENNEMIS, OnCheckGenennemis)
	ON_BN_CLICKED(IDC_CHECK_FONDANIME, OnCheckFondanime)
	ON_BN_CLICKED(IDC_CHECK_MIFOND, OnCheckMifond)
	ON_BN_CLICKED(IDC_CHECK_PREMIER_PLAN, OnCheckPremierPlan)
	ON_BN_CLICKED(IDC_CHECK_LOCK, OnCheckLock)
	ON_CBN_SELCHANGE(IDC_COMBO_ARG1, OnSelchangeComboArg1)
	ON_BN_CLICKED(IDC_CHECK_HOLD_FIRE, OnCheckHoldFire)
	ON_BN_CLICKED(IDC_CHECK_FORCE_SCROLL, OnCheckForceScroll)
	ON_BN_CLICKED(IDC_CHECK_RPG, OnCheckRpg)
	ON_BN_CLICKED(IDC_CHECK_FLAG, OnCheckFlag)
	ON_BN_CLICKED(IDC_CHECK_TEXT, OnCheckText)
	ON_BN_CLICKED(IDC_CHECK_SON, OnCheckSon)
	ON_BN_CLICKED(IDC_CHECK_METEO, OnCheckMeteo)
	ON_BN_CLICKED(IDC_CHECK_OVERKILL, OnCheckOverkill)
	ON_BN_CLICKED(IDC_CHECK_LOAD_DYNA, OnCheckLoadDyna)
	ON_BN_CLICKED(IDC_CHECK_GBONUS, OnCheckGbonus)
	ON_BN_CLICKED(IDC_CHECK_TURRET, OnCheckTurret)
	ON_CBN_SELCHANGE(IDC_COMBO_ARG2, OnSelchangeComboArg2)
	ON_EN_CHANGE(IDC_EDIT_ARG4, OnChangeEditArg4)
	ON_BN_CLICKED(IDC_CHECK_START, OnCheckStart)
	ON_BN_CLICKED(IDC_CHECK_VICTORY, OnCheckVictory)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_BN_CLICKED(IDC_CHECK_BONUS, OnCheckBonus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorDlg message handlers

BOOL CBB3_level_editorDlg::OnInitDialog()
{
	CButton * check_auto = (CButton *) GetDlgItem( IDC_CHECK_AUTO);
	CButton * check_plat = (CButton *) GetDlgItem( IDC_CHECK_PLAT);
	CButton * check_mSang = (CButton *) GetDlgItem( IDC_CHECK_MURS_SANG);
	CButton * check_mOpak = (CButton *) GetDlgItem( IDC_CHECK_MURS_OPAK);
	CButton * check_enn = (CButton *) GetDlgItem( IDC_CHECK_ENNEMIS);
	CButton * check_gEnn = (CButton *) GetDlgItem( IDC_CHECK_GENENNEMIS);
	CButton * check_fondAnime = (CButton *) GetDlgItem( IDC_CHECK_FONDANIME);
	CButton * check_miFonds = (CButton *) GetDlgItem( IDC_CHECK_MIFOND);
	CButton * check_1plan = (CButton *) GetDlgItem( IDC_CHECK_PREMIER_PLAN);
	CButton * check_lock = (CButton *) GetDlgItem( IDC_CHECK_LOCK);
	CButton * check_holdfire = (CButton *) GetDlgItem( IDC_CHECK_HOLD_FIRE);
	CButton * check_forcescroll = (CButton *) GetDlgItem( IDC_CHECK_FORCE_SCROLL);
	CButton * check_rpg = (CButton *) GetDlgItem( IDC_CHECK_RPG);
	CButton * check_flag = (CButton *) GetDlgItem( IDC_CHECK_FLAG);
	CButton * check_text = (CButton *) GetDlgItem( IDC_CHECK_TEXT);
	CButton * check_son = (CButton *) GetDlgItem( IDC_CHECK_SON);
	CButton * check_meteo = (CButton *) GetDlgItem( IDC_CHECK_METEO);
	CButton * check_okill = (CButton *) GetDlgItem( IDC_CHECK_OVERKILL);
	CButton * check_load_d = (CButton *) GetDlgItem( IDC_CHECK_LOAD_DYNA);
	CButton * check_gbonus = (CButton *) GetDlgItem( IDC_CHECK_GBONUS);
	CButton * check_turret = (CButton *) GetDlgItem( IDC_CHECK_TURRET);
	CButton * check_start = (CButton *) GetDlgItem( IDC_CHECK_START);
	CButton * check_victory = (CButton *) GetDlgItem( IDC_CHECK_VICTORY);
	CButton * check_bonus = (CButton *) GetDlgItem( IDC_CHECK_BONUS);

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	


	//	Les pointeurs à NULL
	//
	y_plat		= NULL;
	scr_decor	= NULL;
	num_decor	= NULL;
	murs_opaque = NULL;
	murs_sang	= NULL;


	// Autres variables
	//
	cur_offset	= 0;
	lmb_down	= FALSE;


	// Les noms des GFX
	//
	gfx_decor_name = "";


	// Chargement des décors
	//
	if ( !LoadDecor())
		MessageBox("Impossible de charger le fichier 'bbe_decors.ini'", NULL, MB_ICONERROR);


	// Chargement des ennemis
	//
	if ( !LoadEnnemis())
		MessageBox("Impossible de charger le fichier 'bbe_ennemis.ini'", NULL, MB_ICONERROR);


	// Chargement des fonds animes
	//
	if ( !LoadFondsAnimes())
		MessageBox("Impossible de charger le fichier 'bbe_fondsanimes.ini'", NULL, MB_ICONERROR);


	// Chargement des mi fonds
	//
	if ( !LoadMiFonds())
		MessageBox("Impossible de charger le fichier 'bbe_mifonds.ini'", NULL, MB_ICONERROR);


	// Chargement des mi fonds
	//
	if ( !LoadPremierPlan())
		MessageBox("Impossible de charger le fichier 'bbe_1plan.ini'", NULL, MB_ICONERROR);


	// Charge les fleches et la "tourelle"
	//
	bmp_fleche[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), "FLECHE_GAUCHE", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	bmp_fleche[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), "FLECHE_DROITE", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	bmp_Gfleche[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), "FLECHE_G_GAUCHE", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	bmp_Gfleche[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), "FLECHE_G_DROITE", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	bmp_tourelle = (HBITMAP)LoadImage(GetModuleHandle(NULL), "TOURELLE", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);


	// Initialise les plateformes
	//
	for ( int i=0; i < level_size; i++)
		for ( int j=0; j < NB_MAX_PLAT; j++)
			y_plat[j][i] = 0xFFFF;

	// Conditions de victoire
	//
	xvictory = 0;
	vflag1 = 0;
	vval1 = 0;
	vflag2 = 0;
	vval2 = 0;

	
	// Met en auto par défaut
	//
	check_auto->SetCheck( 1);

	check_plat->EnableWindow( FALSE);
	check_mSang->EnableWindow( FALSE);
	check_mOpak->EnableWindow( FALSE);
	check_enn->EnableWindow( FALSE);
	check_gEnn->EnableWindow( FALSE);
	check_fondAnime->EnableWindow( FALSE);
	check_miFonds->EnableWindow( FALSE);
	check_1plan->EnableWindow( FALSE);
	check_lock->EnableWindow( FALSE);
	check_holdfire->EnableWindow( FALSE);
	check_forcescroll->EnableWindow( FALSE);
	check_rpg->EnableWindow( FALSE);
	check_flag->EnableWindow( FALSE);
	check_text->EnableWindow( FALSE);
	check_son->EnableWindow( FALSE);
	check_meteo->EnableWindow( FALSE);
	check_okill->EnableWindow( FALSE);
	check_load_d->EnableWindow( FALSE);
	check_gbonus->EnableWindow( FALSE);
	check_turret->EnableWindow( FALSE);
	check_start->EnableWindow( FALSE);
	check_victory->EnableWindow( FALSE);
	check_bonus->EnableWindow( FALSE);


	// Blah!
	//
	AfficheTout();

	OnButtonLoad();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBB3_level_editorDlg::OnPaint() 
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

	AfficheTout();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBB3_level_editorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBB3_level_editorDlg::OnSelchangeComboTool() 
{
	int		cur_tool;
	int		i;
	char	buffer[100];

	CComboBox * tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CComboBox * arg2 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG2);
	CStatic * txt1 = (CStatic *) GetDlgItem( IDC_STATIC_ARG1);
	CStatic * txt2 = (CStatic *) GetDlgItem( IDC_STATIC_ARG2);
	CStatic * txt3 = (CStatic *) GetDlgItem( IDC_STATIC_ARG3);
	CStatic * txt4 = (CStatic *) GetDlgItem( IDC_STATIC_ARG4);
	CEdit * arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);
	CEdit * arg4 = (CEdit *) GetDlgItem( IDC_EDIT_ARG4);
	
	
	cur_tool = tool->GetCurSel();

	arg1->ResetContent();
	arg2->ResetContent();
	arg3->SetWindowText("");
	arg4->SetWindowText("");

	txt1->SetWindowText( "");
	txt2->SetWindowText( "");
	txt3->SetWindowText( "");
	txt4->SetWindowText( "");

	switch( cur_tool)
	{
	case TOOL_PLATEFORME:

		arg1->InsertString( 0, "0 - rouge");
		arg1->InsertString( 1, "1 - verte");
		arg1->InsertString( 2, "2 - bleue");
		arg1->InsertString( 3, "3 - jaune");
		arg1->InsertString( 4, "4 - violet");
		arg1->InsertString( 5, "5 - bleu clair (G)");
		arg1->InsertString( 6, "6 - orange (G)");
		arg1->InsertString( 7, "7 - violet (G)");

		for ( i=0; i < TOOL_PLAT_LARGEUR_MAX; i++)
		{
			sprintf( buffer, "%d", i+1);
			arg2->InsertString( i, buffer);
		}

		txt1->SetWindowText( "numéro");
		txt2->SetWindowText( "taille pinceau");
		
		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( TRUE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);

		break;

	case TOOL_LOAD_INIT:

		arg1->InsertString( TOOL_LOAD_INIT_FOND, "PBK du fond");
		arg1->InsertString( TOOL_LOAD_INIT_PBK, "PBK du niveau");
		arg1->InsertString( TOOL_LOAD_INIT_PBK_ENN, "PBK des ennemis");
		arg1->InsertString( TOOL_LOAD_INIT_PBK_RPG, "PBK pour les RPG");
		arg1->InsertString( TOOL_LOAD_INIT_RPG, "Fichier RPG");
		arg1->InsertString( TOOL_LOAD_INIT_SBK, "SBK des ennemis");
		arg1->InsertString( TOOL_LOAD_INIT_MUSICBK, "MBK des musiques");

		arg3->SetWindowText( gfx_decor_name);

		txt1->SetWindowText( "fichier pour");
		txt3->SetWindowText( "nommé");

		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( TRUE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		OnEditchangeComboArg1();

		break;

	case TOOL_MUR_OPAQUE:
	case TOOL_MUR_SANG:

		arg1->EnableWindow( FALSE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		break;

	case TOOL_ENNEMIS:

		for ( i=0; i < nb_ennemis; i++)
			arg1->InsertString( i, noms_ennemis[i]);

		arg2->InsertString( 0, "Gauche");
		arg2->InsertString( 1, "Droite");

		txt1->SetWindowText( "de type");
		txt2->SetWindowText( "de direction");

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);

		break;

	case TOOL_GEN_ENNEMIS:
	case TOOL_GEN_ENNEMIS_TMP:

		for ( i=0; i < nb_ennemis; i++)
			arg1->InsertString( i, noms_ennemis[i]);

		arg2->InsertString( 0, "Gauche");
		arg2->InsertString( 1, "Droite");

		txt1->SetWindowText( "de type");
		txt2->SetWindowText( "de direction");
		txt3->SetWindowText( "de capacité");
		txt4->SetWindowText( "de période");

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow();
		arg4->EnableWindow();

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);
		arg3->SetWindowText( "10");
		arg4->SetWindowText( "100");

		break;

	case TOOL_FOND_ANIME:

		for ( i=0; i < nb_fonds_animes; i++)
			arg1->InsertString( i, noms_fonds_animes[i]);

		txt1->SetWindowText( "de type");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);

		break;

	case TOOL_MI_FONDS:

		for ( i=0; i < nb_mi_fonds; i++)
			arg1->InsertString( i, noms_mi_fonds[i]);

		txt1->SetWindowText( "de type");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);

		break;

	case TOOL_PREMIER_PLAN:

		for ( i=0; i < nb_premier_plan; i++)
			arg1->InsertString( i, noms_premier_plan[i]);

		txt1->SetWindowText( "de type");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);

		break;

	case TOOL_LOCK:

		arg1->InsertString( 0, "Plus d'ennemis");
		arg1->InsertString( 1, "Plus de générateurs");
		arg1->InsertString( 2, "Flag");
		arg1->InsertString( 3, "Flag >=");
		arg1->SetCurSel( 0);

		txt1->SetWindowText( "reprend si");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		break;

	case TOOL_HOLD_FIRE:

		for ( i=0; i < 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg1->InsertString( i, buffer);
		}

		arg1->SetCurSel( 0);
		arg3->SetWindowText( "1");

		txt1->SetWindowText( "reprend si flag");
		txt3->SetWindowText( "vaut");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow();
		arg4->EnableWindow( FALSE);

		break;

	case TOOL_FORCE_SCROLL:

		arg4->SetWindowText( "0");

		txt4->SetWindowText( "vitesse");

		arg1->EnableWindow( FALSE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow();

		break;

	case TOOL_RPG:

		for ( i=0; i <= 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg1->InsertString( i, buffer);
		}

		arg2->InsertString( 0, "Sans condition");
		arg2->InsertString( 1, "Seulement si");

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);

		txt1->SetWindowText( "numéro");

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		break;

	case TOOL_FLAG:
		for ( i=0; i <= 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg1->InsertString( i, buffer);
		}

		for ( i=0; i <= 1000; i++)
		{
			sprintf( buffer, "%d", i);
			arg2->InsertString( i, buffer);
		}

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);

		txt1->SetWindowText( "numéro");
		txt2->SetWindowText( "à la valeur");

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);
		break;

	case TOOL_TEXT:

		arg1->InsertString( 0, "Sans condition");
		arg1->InsertString( 1, "Seulement si");
		arg1->InsertString( 2, "Seulement si >=");

		arg1->SetCurSel( 0);
		txt4->SetWindowText( "texte :");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow();
		break;

	case TOOL_SON:

		for ( i=0; i < NB_SBK; i++)
			arg1->InsertString( i, sbk_name[i]);

		for ( i=0; i <= 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg2->InsertString( i, buffer);
		}

		arg1->SetCurSel( 0);
		arg2->SetCurSel( 0);

		txt1->SetWindowText( "dans SBK");
		txt2->SetWindowText( "si flag");
		txt3->SetWindowText( "est égal à");
		txt4->SetWindowText( "numéro son :");

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow();
		arg4->EnableWindow();
		break;

	case TOOL_METEO:

		for ( i=0; i < NB_METEO; i++)
			arg1->InsertString( i, meteo_name[i]);

		arg1->SetCurSel( 0);
		arg3->SetWindowText( "0");

		txt1->SetWindowText( "de type");
		txt2->SetWindowText( "");
		txt3->SetWindowText( "d'intensité");
		txt4->SetWindowText( "");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow();
		arg4->EnableWindow( FALSE);
		break;

	case TOOL_OVERKILL:

		for ( i=0; i < nb_ennemis; i++)
			arg1->InsertString( i, noms_ennemis[i]);

		arg1->SetCurSel( 0);
		arg3->SetWindowText( "200");

		txt1->SetWindowText( "ennemis de type");
		txt2->SetWindowText( "");
		txt3->SetWindowText( "durée");
		txt4->SetWindowText( "");

		arg1->EnableWindow();
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow();
		arg4->EnableWindow( FALSE);
		break;

	case TOOL_LOAD_DYNA:

		arg1->InsertString( TOOL_LOAD_DYNA_PBK, "PBK du niveau");
		arg1->InsertString( TOOL_LOAD_DYNA_PBK_ENN, "PBK des ennemis");
		arg1->InsertString( TOOL_LOAD_DYNA_PBK_TMP, "PBK temporaire");
		arg1->InsertString( TOOL_LOAD_DYNA_SBK_ENN, "SBK des ennemis");
		arg1->InsertString( TOOL_LOAD_DYNA_SBK_TMP, "SBK temporaire");
		arg1->InsertString( TOOL_LOAD_DYNA_MUSICBK, "MBK des musiques");

		txt1->SetWindowText( "fichier pour");
		txt3->SetWindowText( "nommé");

		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( TRUE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		OnEditchangeComboArg1();

		break;

	case TOOL_MUSIC:

		arg1->InsertString( 0, "Stoppe");
		arg1->InsertString( 1, "Joue");

		for ( i=0; i <= 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg2->InsertString( i, buffer);
		}

		txt1->SetWindowText( "action :");
		txt2->SetWindowText( "musique numéro");

		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( TRUE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 1);
		arg2->SetCurSel( 0);
		OnEditchangeComboArg1();

		break;

	case TOOL_GBONUS:

		arg1->InsertString( 0, "Armes seulement");
		arg1->InsertString( 1, "La totale");
		arg3->SetWindowText( "500");

		txt1->SetWindowText( "de type");
		txt3->SetWindowText( "de periode");

		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( TRUE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		OnEditchangeComboArg1();

		break;

	case TOOL_TURRET:

		for ( i=0; i < 8; i++)
		{
			sprintf( buffer, "%d", i);
			arg1->InsertString( i, buffer);
		}

		for ( i=0; i <= 100; i++)
		{
			sprintf( buffer, "%d", i);
			arg2->InsertString( i, buffer);
		}

		txt1->SetWindowText( "direction :");
		txt2->SetWindowText( "ID:");

		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( TRUE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);

		arg1->SetCurSel( 0);
		OnEditchangeComboArg1();

		break;

	case TOOL_START1:
	case TOOL_START2:
		arg1->EnableWindow( FALSE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);
		break;

	case TOOL_VICTORY:
		
		for ( i=0; i <= 10; i++)
		{
			sprintf( buffer, "%d", i);
			arg1->InsertString( i, buffer);
			arg2->InsertString( i, buffer);
		}

		txt1->SetWindowText( "si flag numéro ");
		txt2->SetWindowText( "vaut");
		txt3->SetWindowText( "et flag numéro");
		txt4->SetWindowText( "vaut");

		arg1->SetCurSel( vflag1);
		arg2->SetCurSel( vval1);

		sprintf( buffer, "%d", vflag2);
		arg3->SetWindowText( buffer);

		sprintf( buffer, "%d", vval2);
		arg4->SetWindowText( buffer);

		arg1->EnableWindow();
		arg2->EnableWindow();
		arg3->EnableWindow();
		arg4->EnableWindow();
		break;

	case TOOL_BONUS:
		for ( i=0; i < NB_BONUS; i++)
		{
			arg1->InsertString( i, bonus_name[i]);
		}

		txt1->SetWindowText( "de type");

		arg1->SetCurSel( 0);
		arg1->EnableWindow( TRUE);
		arg2->EnableWindow( FALSE);
		arg3->EnableWindow( FALSE);
		arg4->EnableWindow( FALSE);
		break;
	}

	OnCheckAuto();
}

bool CBB3_level_editorDlg::LoadDecor()
{
	ifstream	fic;
	char		buffer[100];

	CScrollBar * barre = (CScrollBar *) GetDlgItem( IDC_SCROLLBAR);


	fic.open( "bbe_ndecors.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>scr_level_size;
	level_size = scr_level_size * 640;

	if ( level_size <= 0)
	{
		fic.close();
		return false;
	}

	num_decor = new int[scr_level_size];

	for ( int i=0; i < scr_level_size; i++)
		fic>>num_decor[i];

	fic.close();


	fic.open( "bbe_decors.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>nb_scr_decor;

	scr_decor = new HBITMAP[nb_scr_decor];

	if ( scr_decor == NULL)
	{
		fic.close();
		return false;
	}

	//
	//	Alloue la place pour les plateformes
	//
	y_plat = new int * [NB_MAX_PLAT];

	for ( i=0; i < NB_MAX_PLAT; i++)
	{
		y_plat[i] = new int[level_size];

		for ( int j=0; j < level_size; j++)
			y_plat[i][j] = 0xFFFF;
	}

	//
	// Alloue la place pour les murs opaques
	//
	int	ls8 = level_size / 8;
	murs_opaque = new bool * [60];	// 60 = 480/8

	for ( i=0; i < 60; i++)
	{
		murs_opaque[i] = new bool[ls8];

		for ( int j=0; j < ls8; j++)
			murs_opaque[i][j] = false;
	}

	//
	// Alloue la place pour les murs opaques
	//
	murs_sang = new bool * [60];	// 60 = 480/8

	for ( i=0; i < 60; i++)
	{
		murs_sang[i] = new bool[ls8];

		for ( int j=0; j < ls8; j++)
			murs_sang[i][j] = false;
	}


	//
	//	Charge les images
	//
	for ( i=0; i < nb_scr_decor; i++)
	{
		fic>>buffer;

		scr_decor[i] = (HBITMAP)LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( scr_decor[i] == NULL)
		{
			char buffer2[200];
			sprintf( buffer2, "Impossible de charger %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONERROR);
			fic.close();
			return false;
		}
	}

	barre->SetScrollRange( 0, level_size - 640);

	fic.close();
	return true;
}

void CBB3_level_editorDlg::OnClose() 
{
	ReleaseAll();
	
	CDialog::OnClose();
}

void CBB3_level_editorDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	static rem_pos;

	int		min;
	int		max;
	int		space;

	pScrollBar->GetScrollRange( &min, &max);
	space = (max - min)/(scr_level_size-1);

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

	cur_offset = pScrollBar->GetScrollPos();


	AfficheTout();

}

void CBB3_level_editorDlg::AfficheTout()
{
	int		cur_tool;

	CComboBox * tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CButton * check_plat = (CButton *) GetDlgItem( IDC_CHECK_PLAT);
	CButton * check_mSang = (CButton *) GetDlgItem( IDC_CHECK_MURS_SANG);
	CButton * check_mOpak = (CButton *) GetDlgItem( IDC_CHECK_MURS_OPAK);
	CButton * check_enn = (CButton *) GetDlgItem( IDC_CHECK_ENNEMIS);
	CButton * check_gEnn = (CButton *) GetDlgItem( IDC_CHECK_GENENNEMIS);
	CButton * check_fondAnime = (CButton *) GetDlgItem( IDC_CHECK_FONDANIME);
	CButton * check_miFonds = (CButton *) GetDlgItem( IDC_CHECK_MIFOND);
	CButton * check_1plan = (CButton *) GetDlgItem( IDC_CHECK_PREMIER_PLAN);
	CButton * check_lock = (CButton *) GetDlgItem( IDC_CHECK_LOCK);
	CButton * check_holdfire = (CButton *) GetDlgItem( IDC_CHECK_HOLD_FIRE);
	CButton * check_forcescroll = (CButton *) GetDlgItem( IDC_CHECK_FORCE_SCROLL);
	CButton * check_rpg = (CButton *) GetDlgItem( IDC_CHECK_RPG);
	CButton * check_flag = (CButton *) GetDlgItem( IDC_CHECK_FLAG);
	CButton * check_text = (CButton *) GetDlgItem( IDC_CHECK_TEXT);
	CButton * check_son = (CButton *) GetDlgItem( IDC_CHECK_SON);
	CButton * check_meteo = (CButton *) GetDlgItem( IDC_CHECK_METEO);
	CButton * check_okill = (CButton *) GetDlgItem( IDC_CHECK_OVERKILL);
	CButton * check_load_d = (CButton *) GetDlgItem( IDC_CHECK_LOAD_DYNA);
	CButton * check_gbonus = (CButton *) GetDlgItem( IDC_CHECK_GBONUS);
	CButton * check_turret = (CButton *) GetDlgItem( IDC_CHECK_TURRET);
	CButton * check_start = (CButton *) GetDlgItem( IDC_CHECK_START);
	CButton * check_victory = (CButton *) GetDlgItem( IDC_CHECK_VICTORY);
	CButton * check_bonus = (CButton *) GetDlgItem( IDC_CHECK_BONUS);

	cur_tool = tool->GetCurSel();

	AfficheFond();	// Toujours

	if ( check_fondAnime->GetCheck())
		AfficheFondsAnimes();

	if ( check_mOpak->GetCheck())
		AfficheMursOpaques();

	if ( check_miFonds->GetCheck())
		AfficheMiFonds();

	if ( check_enn->GetCheck())
		AfficheEnnemis();

	if ( check_gEnn->GetCheck())
		AfficheGenerateursEnnemis();

	if ( check_plat->GetCheck())
		AffichePlateformes();

	if ( check_mSang->GetCheck())
		AfficheMursSang();

	if ( check_1plan->GetCheck())
		AffichePremierPlan();

	if ( check_lock->GetCheck())
		AfficheLock();

	if ( check_holdfire->GetCheck())
		AfficheHoldFire();

	if ( check_forcescroll->GetCheck())
		AfficheForceScroll();

	if ( check_rpg->GetCheck())
		AfficheRPG();

	if ( check_flag->GetCheck())
		AfficheFlags();

	if ( check_text->GetCheck())
		AfficheTextes();

	if ( check_son->GetCheck())
	{
		AfficheSons();
		AfficheMusic();
	}

	if ( check_meteo->GetCheck())
		AfficheMeteo();

	if ( check_okill->GetCheck())
		AfficheOverKill();

	if ( check_load_d->GetCheck())
		AfficheLoadDyn();

	if ( check_gbonus->GetCheck())
		AfficheGBonus();

	if ( check_turret->GetCheck())
		AfficheTurret();

	if ( check_victory->GetCheck())
		AfficheVictory();
	
	if ( check_start->GetCheck())
		AfficheStart();

	if ( check_bonus->GetCheck())
		AfficheBonus();
}

void CBB3_level_editorDlg::AfficheFond()
{
	int		scr1;
	int		scr2;
	int		reste;

	CDC *	dc;
	HDC		hdc1;
	HDC		hdc2;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	//
	// Calcule les rares trucs à calculer
	//
	scr1  = cur_offset / 640;
	reste = cur_offset % 640;
	scr2  = scr1 + 1;

	//
	// On récupère les DC et autres HDC...
	//
	dc = frame->GetDC();

	hdc1 = CreateCompatibleDC( NULL);
	SelectObject( hdc1, scr_decor[num_decor[scr1]]);

	if ( scr1 >= scr_level_size - 1)
	{
		BitBlt( dc->m_hDC, 1, 1, 640, 480, hdc1, 0, 0, SRCCOPY);
	}
	else if ( num_decor[scr1] == num_decor[scr2])
	{
		BitBlt( dc->m_hDC, 1, 1, 640-reste, 480, hdc1, reste, 0, SRCCOPY);
		BitBlt( dc->m_hDC, 641-reste, 1, reste, 480, hdc1, 0, 0, SRCCOPY);
	}
	else
	{

		hdc2 = CreateCompatibleDC( NULL);
		SelectObject( hdc2, scr_decor[num_decor[scr2]]);

		BitBlt( dc->m_hDC, 1, 1, 640-reste, 480, hdc1, reste, 0, SRCCOPY);
		BitBlt( dc->m_hDC, 641-reste, 1, reste, 480, hdc2, 0, 0, SRCCOPY);


		DeleteDC( hdc2);
	}

	//
	// Free the malloc! ;)
	//
	DeleteDC( hdc1);
	frame->ReleaseDC( dc);

}

void CBB3_level_editorDlg::ReleaseAll()
{
	// Les plateformes
	//
	if ( y_plat != NULL)
	{
		for ( int i=0; i < NB_MAX_PLAT; i++)
			delete [] y_plat[i];

		delete [] y_plat;
		y_plat = NULL;
	}

	// Les murs opaques
	//
	if ( murs_opaque != NULL)
	{
		for ( int i=0; i < 60; i++)
			delete [] murs_opaque[i];

		delete [] murs_opaque;
		murs_opaque = NULL;
	}

	// Les murs sanglants
	//
	if ( murs_sang != NULL)
	{
		for ( int i=0; i < 60; i++)
			delete [] murs_sang[i];

		delete [] murs_sang;
		murs_sang = NULL;
	}

	// Les décors
	//
	if ( scr_decor != NULL)
	{
		for ( int i=0; i < scr_level_size; i++)
			DeleteObject( scr_decor[i]);

		delete [] scr_decor;
		scr_decor = NULL;
	}

	// Les BMP des ennemis
	//
	if ( bmp_ennemis != NULL)
	{
		for ( int i=0; i < nb_ennemis; i++)
			DeleteObject( bmp_ennemis[i]);

		delete [] bmp_ennemis;
		bmp_ennemis = NULL;
	}

	// Les noms des ennemis
	//
	if ( noms_ennemis != NULL)
	{
		for ( int i=0; i < nb_ennemis; i++)
			delete [] noms_ennemis[i];

		delete [] noms_ennemis;
		noms_ennemis = NULL;
	}

	// Les BMP des fonds_animes
	//
	if ( bmp_fonds_animes != NULL)
	{
		for ( int i=0; i < nb_fonds_animes; i++)
			DeleteObject( bmp_fonds_animes[i]);

		delete [] bmp_fonds_animes;
		bmp_fonds_animes = NULL;
	}

	// Les BMP des mi fonds
	//
	if ( bmp_mi_fonds != NULL)
	{
		for ( int i=0; i < nb_mi_fonds; i++)
			DeleteObject( bmp_mi_fonds[i]);

		delete [] bmp_mi_fonds;
		bmp_mi_fonds = NULL;
	}

	// Les noms des mi_fonds
	//
	if ( noms_mi_fonds != NULL)
	{
		for ( int i=0; i < nb_mi_fonds; i++)
			delete [] noms_mi_fonds[i];

		delete [] noms_mi_fonds;
		noms_mi_fonds = NULL;
	}

	// Les noms des fonds_animes
	//
	if ( noms_fonds_animes != NULL)
	{
		for ( int i=0; i < nb_fonds_animes; i++)
			delete [] noms_fonds_animes[i];

		delete [] noms_fonds_animes;
		noms_fonds_animes = NULL;
	}

	// Les BMP des premiers plans
	//
	if ( bmp_premier_plan != NULL)
	{
		for ( int i=0; i < nb_premier_plan; i++)
			DeleteObject( bmp_premier_plan[i]);

		delete [] bmp_premier_plan;
		bmp_premier_plan = NULL;
	}

	// Les noms des premier_plan
	//
	if ( noms_premier_plan != NULL)
	{
		for ( int i=0; i < nb_premier_plan; i++)
			delete [] noms_premier_plan[i];

		delete [] noms_premier_plan;
		noms_premier_plan = NULL;
	}

	delete [] num_decor;
	delete [] id_ennemis;
	delete [] id_fonds_animes;
	delete [] id_premier_plan;
	delete [] id_mi_fonds;

	// Les listes
	//
	list_ennemis.vide();
	list_genEnnemis.vide();
	list_fonds_animes.vide();
	list_mi_fonds.vide();
	list_premier_plan.vide();
	list_lock.vide();
	list_hold_fire.vide();
	list_force_scroll.vide();
	list_rpg.vide();
	list_flag.vide();
	list_txt.vide();
	list_son.vide();
	list_meteo.vide();
	list_okill.vide();
	list_load_dyna.vide();
	list_music.vide();
	list_gbonus.vide();
	list_turret.vide();
	list_bonus.vide();
}

void CBB3_level_editorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if ( scr_decor != NULL)
	{
		delete [] scr_decor;
		scr_decor = NULL;
	}
}

void CBB3_level_editorDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	char	buffer[100];
	
	CStatic * txt_coord = (CStatic *) GetDlgItem( IDC_STATIC_COORD);


	xmouse = point.x;
	ymouse = point.y;


	//
	// Cas 1 : souris hors de la zone d'édition
	//
	if ( xmouse < 121 || xmouse > 760 ||
		 ymouse < 32  || ymouse > 511)
	{
		sprintf( buffer, "-");
		lmb_down = FALSE;
		rmb_down = FALSE;

		if ( in_zone)
		{
			AfficheTout();
			in_zone = false;
		}
	}
	else	// Cas 2 : en plein dedans!
	{
		int	x = xmouse - 121 + cur_offset;
		int y = ymouse - 32;

		sprintf( buffer, "(%d,%d)", x, y);

		MakeAction( x, y);
		in_zone = true;
	}

	txt_coord->SetWindowText( buffer);
	
	CDialog::OnMouseMove(nFlags, point);
}

void CBB3_level_editorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	lmb_down = TRUE;
	already_clicked = FALSE;

	if ( !(xmouse < 121 || xmouse > 760 ||
		 ymouse < 32  || ymouse > 511))
	{
		MakeAction( xmouse - 121 + cur_offset, ymouse - 32);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CBB3_level_editorDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	lmb_down = FALSE;
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CBB3_level_editorDlg::AffichePlateformes()
{
	CDC *	dc;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	dc = frame->GetDC();

	for ( int x=cur_offset; x < cur_offset + 640; x++)
	{
		int x_frame = x - cur_offset;

		for ( int i=0; i < NB_MAX_PLAT; i++)
		{
			if ( y_plat[i][x] > 0 && y_plat[i][x] < 480)
				dc->SetPixel( x_frame+1, y_plat[i][x]+1, col_plat[i]);
		}
	}


	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::MakeAction( int x, int y)
{
	int		n_plat;
	int		l_plat;

	int		min;
	int		max;

	int		cur_tool;
	int		i;
	char	buffer[100];

	ENNEMI *		ennemi;
	GEN_ENNEMI *	g_ennemi;
	FOND_ANIME *	fanime;
	LOCK *			lock;
	HOLD_FIRE *		hold_fire;
	FORCE_SCROLL *	force_scroll;
	RPG *			rpg;
	FLAG *			flag;
	TEXTE *			txt;
	SON *			son;
	METEO *			meteo;
	OVERKILL *		okill;
	LOAD_DYNA *		load_dyna;
	MUSIC *			music;
	GBONUS *		gbonus;
	TURRET *		turret;
	BONUS *			bonus;

	
	CComboBox * tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CComboBox * arg2 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG2);
	CEdit * arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);
	CEdit * arg4 = (CEdit *) GetDlgItem( IDC_EDIT_ARG4);
	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	cur_tool = tool->GetCurSel();


	if ( lmb_down) // ------------------- Bouton GAUCHE -----------------
	{
		switch( cur_tool)
		{
		case TOOL_PLATEFORME:
			n_plat = arg1->GetCurSel();
			l_plat = arg2->GetCurSel() + 1;

			min = x - (l_plat-1);
			max = x + l_plat;

			if ( min < 0) min = 0;
			if ( max >= level_size) max = level_size - 1;

			for ( i=min; i < max; i++)
				y_plat[n_plat][i] = y;

			AfficheTout();
			break;

		case TOOL_MUR_OPAQUE:
			murs_opaque[y/8][x/8] = true;
			AfficheTout();
			break;

		case TOOL_MUR_SANG:
			murs_sang[y/8][x/8] = true;
			AfficheTout();
			break;

		case TOOL_ENNEMIS:
			if ( already_clicked)
				break;

			ennemi = new ENNEMI;
			ennemi->id = arg1->GetCurSel();
			ennemi->x = x;
			ennemi->y = y;
			ennemi->sens = arg2->GetCurSel();
			
			list_ennemis.ajoute( (void*) ennemi);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_GEN_ENNEMIS:
		case TOOL_GEN_ENNEMIS_TMP:
			if ( already_clicked)
				break;

			g_ennemi = new GEN_ENNEMI;
			g_ennemi->id = arg1->GetCurSel();
			g_ennemi->x = x;
			g_ennemi->y = y;
			g_ennemi->sens = arg2->GetCurSel();
			
			if ( cur_tool == TOOL_GEN_ENNEMIS)
				g_ennemi->tmp = false;
			else
				g_ennemi->tmp = true;
			
			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de capacité spécifiée. Considérée comme 10", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "10");
				g_ennemi->capacite = 10;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &(g_ennemi->capacite));

			arg4->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de periode spécifiée. Considérée comme 75", NULL, MB_ICONWARNING);
				arg4->SetWindowText( "75");
				g_ennemi->periode = 75;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &(g_ennemi->periode));
			
			list_genEnnemis.ajoute( (void*) g_ennemi);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_FOND_ANIME:
			if ( already_clicked)
				break;

			fanime = new FOND_ANIME;
			fanime->id = arg1->GetCurSel();
			fanime->x = x;
			fanime->y = y;
			
			list_fonds_animes.ajoute( (void*) fanime);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_MI_FONDS:
			if ( already_clicked)
				break;

			fanime = new FOND_ANIME;
			fanime->id = arg1->GetCurSel();
			fanime->x = x;
			fanime->y = y;
			
			list_mi_fonds.ajoute( (void*) fanime);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_PREMIER_PLAN:
			if ( already_clicked)
				break;

			fanime = new FOND_ANIME;
			fanime->id = arg1->GetCurSel();
			fanime->x = x;
			fanime->y = y;
			
			list_premier_plan.ajoute( (void*) fanime);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_LOCK:
			if ( already_clicked)
				break;

			lock = new LOCK;
			lock->x = x;
			lock->condition = arg1->GetCurSel();

			if ( lock->condition == TOOL_LOCK_FLAG || lock->condition == TOOL_LOCK_FLAG2)
			{
				lock->flag = arg2->GetCurSel();

				arg3->GetWindowText( buffer, 20);
				if ( strlen(buffer) == 0)
				{
					MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
					arg3->SetWindowText( "1");
					lock->valeur = 1;
					lmb_down = FALSE;
				}
				else
					sscanf( buffer, "%d", &(lock->valeur));
			}
			
			list_lock.ajoute( (void*) lock);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_HOLD_FIRE:
			if ( already_clicked)
				break;

			hold_fire = new HOLD_FIRE;
			hold_fire->x = x;
			hold_fire->flag = arg1->GetCurSel();

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "1");
				hold_fire->valeur = 1;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &hold_fire->valeur);
			
			list_hold_fire.ajoute( (void*) hold_fire);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_FORCE_SCROLL:
			if ( already_clicked)
				break;

			force_scroll = new FORCE_SCROLL;
			force_scroll->x = x;
			arg4->GetWindowText( buffer, 20);
			sscanf( buffer, "%d", &force_scroll->speed);
			
			list_force_scroll.ajoute( (void*) force_scroll);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_RPG:
			if ( already_clicked)
				break;

			rpg = new RPG;
			rpg->x = x;
			rpg->num = arg1->GetCurSel();
			rpg->cond = arg2->GetCurSel();

			if ( rpg->cond)
			{
				arg3->GetWindowText( buffer, 20);
				
				if ( strlen(buffer) == 0)
				{
					MessageBox( "Pas de flag spécifié. Considéré comme 0", NULL, MB_ICONWARNING);
					arg3->SetWindowText( "0");
					rpg->val = 0;
					lmb_down = FALSE;
				}
				else
				{
					sscanf( buffer, "%d", &rpg->flag);
				}

				arg4->GetWindowText( buffer, 20);
				
				if ( strlen(buffer) == 0)
				{
					MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
					arg4->SetWindowText( "1");
					rpg->val = 1;
					lmb_down = FALSE;
				}
				else
				{
					sscanf( buffer, "%d", &rpg->val);
				}
			}

			list_rpg.ajoute( (void*) rpg);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_FLAG:
			if ( already_clicked)
				break;

			flag = new FLAG;
			flag->x = x;
			flag->num = arg1->GetCurSel();
			flag->val = arg2->GetCurSel();

			list_flag.ajoute( (void*) flag);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_TEXT:
			if ( already_clicked)
				break;

			txt = new TEXTE;
			txt->x = x;
			txt->cond = arg1->GetCurSel();

			arg4->GetWindowText( buffer, 20);
			
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de numéro de texte spécifié. Considéré comme 0", NULL, MB_ICONWARNING);
				arg4->SetWindowText( "0");
				txt->ntxt = 0;
				lmb_down = FALSE;
			}
			else
			{
				sscanf( buffer, "%d", &txt->ntxt);
			}

			if ( txt->cond)
			{
				txt->flag = arg2->GetCurSel();
				arg3->GetWindowText( buffer, 20);
				
				if ( strlen(buffer) == 0)
				{
					MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
					arg3->SetWindowText( "1");
					txt->val = 1;
					lmb_down = FALSE;
				}
				else
				{
					sscanf( buffer, "%d", &txt->val);
				}
			}

			list_txt.ajoute( (void*) txt);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_SON:
			if ( already_clicked)
				break;

			son = new SON;
			son->x = x;
			son->sbk = arg1->GetCurSel();
			son->flag = arg2->GetCurSel();

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "1");
				son->val = 1;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &son->val);

			arg4->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de numéro spécifiée. Considérée comme 0", NULL, MB_ICONWARNING);
				arg4->SetWindowText( "0");
				son->num = 0;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &son->num);

			list_son.ajoute( (void*) son);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_METEO:
			if ( already_clicked)
				break;

			meteo = new METEO;
			meteo->x = x;
			meteo->type = arg1->GetCurSel();

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de valeur spécifiée. Considérée comme 1", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "1");
				meteo->intensite = 1;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &meteo->intensite);


			list_meteo.ajoute( (void*) meteo);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_OVERKILL:
			if ( already_clicked)
				break;

			okill = new OVERKILL;
			okill->x = x;
			okill->id_en = arg1->GetCurSel();

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de valeur spécifiée. Considérée comme 200", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "200");
				okill->duree = 200;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &okill->duree);

			list_okill.ajoute( (void*) okill);
			AfficheTout();
			already_clicked = TRUE;
			break;
		
		case TOOL_LOAD_DYNA:
			if ( already_clicked)
				break;

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de nom de fichier spécifié.", NULL, MB_ICONERROR);
				lmb_down = FALSE;
				break;
			}

			load_dyna = new LOAD_DYNA;
			load_dyna->x = x;
			load_dyna->id = arg1->GetCurSel();

			strcpy( load_dyna->fic, buffer);

			list_load_dyna.ajoute( (void*) load_dyna);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_MUSIC:
			if ( already_clicked)
				break;

			music = new MUSIC;
			music->x = x;
			music->play = arg1->GetCurSel();
			music->num = arg2->GetCurSel();

			list_music.ajoute( (void*) music);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_GBONUS:
			if ( already_clicked)
				break;

			gbonus = new GBONUS;
			gbonus->x = x;
			gbonus->type = arg1->GetCurSel();

			arg3->GetWindowText( buffer, 20);
			if ( strlen(buffer) == 0)
			{
				MessageBox( "Pas de valeur spécifiée. Considérée comme 500", NULL, MB_ICONWARNING);
				arg3->SetWindowText( "500");
				gbonus->periode = 500;
				lmb_down = FALSE;
			}
			else
				sscanf( buffer, "%d", &gbonus->periode);
			
			list_gbonus.ajoute( (void*) gbonus);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_TURRET:
			if ( already_clicked)
				break;

			turret = new TURRET;
			turret->dir = arg1->GetCurSel();
			turret->x = x;
			turret->y = y;
			turret->id = arg2->GetCurSel();
			
			list_turret.ajoute( (void*) turret);
			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_START1:
			xstart1 = x;
			ystart1 = y;
			AfficheTout();
			break;

		case TOOL_START2:
			xstart2 = x;
			ystart2 = y;
			AfficheTout();
			break;

		case TOOL_VICTORY:
			xvictory = x;
			AfficheTout();
			break;

		case TOOL_BONUS:
			if ( already_clicked)
				break;

			bonus = new BONUS;
			bonus->x = x;
			bonus->y = y;
			bonus->type = arg1->GetCurSel();

			list_bonus.ajoute( (void*) bonus);
			AfficheTout();
			already_clicked = TRUE;
			break;
		}
	}
	else if ( rmb_down) // ------------------- Bouton DROIT -----------------
	{
		switch( cur_tool)
		{
		case TOOL_PLATEFORME:
			n_plat = arg1->GetCurSel();
			l_plat = arg2->GetCurSel() + 1;

			min = x - (l_plat-1);
			max = x + l_plat;

			if ( min < 0) min = 0;
			if ( max >= level_size) max = level_size - 1;

			for ( i=min; i < max; i++)
				y_plat[n_plat][i] = 0xFFFF;

			AfficheTout();
			break;

		case TOOL_MUR_OPAQUE:
			murs_opaque[y/8][x/8] = false;
			AfficheTout();
			break;

		case TOOL_MUR_SANG:
			murs_sang[y/8][x/8] = false;
			AfficheTout();
			break;


		case TOOL_ENNEMIS:
			if ( already_clicked)
				break;

			list_ennemis.start();

			while( !list_ennemis.fin())
			{
				ennemi = (ENNEMI*) list_ennemis.info();

				if ( IsClicked( x, y, bmp_ennemis[ennemi->id], ennemi->x, ennemi->y, true))
					list_ennemis.supprime();
				else
					list_ennemis.suivant();
			}

			AfficheTout();
			break;

		case TOOL_GEN_ENNEMIS:
		case TOOL_GEN_ENNEMIS_TMP:
			if ( already_clicked)
				break;

			list_genEnnemis.start();

			while( !list_genEnnemis.fin())
			{
				g_ennemi = (GEN_ENNEMI*) list_genEnnemis.info();

				if ( IsClicked( x, y, bmp_ennemis[g_ennemi->id], g_ennemi->x, g_ennemi->y, true))
					list_genEnnemis.supprime();
				else
					list_genEnnemis.suivant();
			}

			AfficheTout();
			break;

		case TOOL_FOND_ANIME:
			if ( already_clicked)
				break;

			list_fonds_animes.start();

			while( !list_fonds_animes.fin())
			{
				fanime = (FOND_ANIME*) list_fonds_animes.info();

				if ( IsClicked( x, y, bmp_fonds_animes[fanime->id], fanime->x, fanime->y, false))
					list_fonds_animes.supprime();
				else
					list_fonds_animes.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_MI_FONDS:
			if ( already_clicked)
				break;

			list_mi_fonds.start();

			while( !list_mi_fonds.fin())
			{
				fanime = (FOND_ANIME*) list_mi_fonds.info();

				if ( IsClicked( x, y, bmp_mi_fonds[fanime->id], fanime->x, fanime->y, false))
					list_mi_fonds.supprime();
				else
					list_mi_fonds.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_PREMIER_PLAN:
			if ( already_clicked)
				break;

			list_premier_plan.start();

			while( !list_premier_plan.fin())
			{
				fanime = (FOND_ANIME*) list_premier_plan.info();

				if ( IsClicked( x, y, bmp_premier_plan[fanime->id], fanime->x, fanime->y, false))
					list_premier_plan.supprime();
				else
					list_premier_plan.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_LOCK:
			if ( already_clicked)
				break;

			list_lock.start();

			while( !list_lock.fin())
			{
				lock = (LOCK*) list_lock.info();

				if ( x > (lock->x - 10) && x < (lock->x + 10))
					list_lock.supprime();
				else
					list_lock.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_HOLD_FIRE:
			if ( already_clicked)
				break;

			list_hold_fire.start();

			while( !list_hold_fire.fin())
			{
				hold_fire = (HOLD_FIRE*) list_hold_fire.info();

				if ( x > (hold_fire->x - 10) && x < (hold_fire->x + 10))
					list_hold_fire.supprime();
				else
					list_hold_fire.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_FORCE_SCROLL:
			if ( already_clicked)
				break;

			list_force_scroll.start();

			while( !list_force_scroll.fin())
			{
				force_scroll = (FORCE_SCROLL*) list_force_scroll.info();

				if ( x > (force_scroll->x - 10) && x < (force_scroll->x + 10))
					list_force_scroll.supprime();
				else
					list_force_scroll.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_RPG:
			if ( already_clicked)
				break;

			list_rpg.start();

			while( !list_rpg.fin())
			{
				rpg = (RPG*) list_rpg.info();

				if ( x > (rpg->x - 10) && x < (rpg->x + 10))
					list_rpg.supprime();
				else
					list_rpg.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_FLAG:
			if ( already_clicked)
				break;

			list_flag.start();

			while( !list_flag.fin())
			{
				flag = (FLAG*) list_flag.info();

				if ( x > (flag->x - 10) && x < (flag->x + 10))
					list_flag.supprime();
				else
					list_flag.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_TEXT:
			if ( already_clicked)
				break;

			list_txt.start();

			while( !list_txt.fin())
			{
				txt = (TEXTE*) list_txt.info();

				if ( x > (txt->x - 10) && x < (txt->x + 10))
					list_txt.supprime();
				else
					list_txt.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_SON:
			if ( already_clicked)
				break;

			list_son.start();

			while( !list_son.fin())
			{
				son = (SON*) list_son.info();

				if ( x > (son->x - 10) && x < (son->x + 10))
					list_son.supprime();
				else
					list_son.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_METEO:
			if ( already_clicked)
				break;

			list_meteo.start();

			while( !list_meteo.fin())
			{
				meteo = (METEO*) list_meteo.info();

				if ( x > (meteo->x - 10) && x < (meteo->x + 10))
					list_meteo.supprime();
				else
					list_meteo.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_OVERKILL:
			if ( already_clicked)
				break;

			list_okill.start();

			while( !list_okill.fin())
			{
				okill = (OVERKILL*) list_okill.info();

				if ( x > (okill->x - 10) && x < (okill->x + 10))
					list_okill.supprime();
				else
					list_okill.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_LOAD_DYNA:
			if ( already_clicked)
				break;

			list_load_dyna.start();

			while( !list_load_dyna.fin())
			{
				load_dyna = (LOAD_DYNA*) list_load_dyna.info();

				if ( x > (load_dyna->x - 10) && x < (load_dyna->x + 10))
					list_load_dyna.supprime();
				else
					list_load_dyna.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_MUSIC:
			if ( already_clicked)
				break;

			list_music.start();

			while( !list_music.fin())
			{
				music = (MUSIC*) list_music.info();

				if ( x > (music->x - 10) && x < (music->x + 10))
					list_music.supprime();
				else
					list_music.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_GBONUS:
			if ( already_clicked)
				break;

			list_gbonus.start();

			while( !list_gbonus.fin())
			{
				gbonus = (GBONUS*) list_gbonus.info();

				if ( x > (gbonus->x - 10) && x < (gbonus->x + 10))
					list_gbonus.supprime();
				else
					list_gbonus.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_TURRET:
			if ( already_clicked)
				break;

			list_turret.start();

			while( !list_turret.fin())
			{
				turret = (TURRET*) list_turret.info();

				if ( IsClicked( x, y, bmp_tourelle, turret->x, turret->y, true))
					list_turret.supprime();
				else
					list_turret.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;

		case TOOL_BONUS:
			if ( already_clicked)
				break;

			list_bonus.start();

			while( !list_bonus.fin())
			{
				bonus = (BONUS*) list_bonus.info();

				if ( x > bonus->x-10 && x < bonus->x+10 && y > bonus->y-10 && y < bonus->y+10)
					list_bonus.supprime();
				else
					list_bonus.suivant();
			}

			AfficheTout();
			already_clicked = TRUE;
			break;
		}
	}
	else // ------------------- aucun bouton -----------------
	{
		switch( cur_tool)
		{
		case TOOL_FOND_ANIME:
			AfficheTout();
			ClippedBlit( bmp_fonds_animes[arg1->GetCurSel()], x, y, false, false, true);
			break;

		case TOOL_MI_FONDS:
			AfficheTout();
			ClippedBlit( bmp_mi_fonds[arg1->GetCurSel()], x, y, false, false, true);
			break;

		case TOOL_PREMIER_PLAN:
			AfficheTout();
			ClippedBlit( bmp_premier_plan[arg1->GetCurSel()], x, y, false, false, true);
			break;
		}
	}

}

void CBB3_level_editorDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	rmb_down = TRUE;
	already_clicked = FALSE;

	if ( !(xmouse < 121 || xmouse > 760 ||
		 ymouse < 32  || ymouse > 511))
	{
		MakeAction( xmouse - 121 + cur_offset, ymouse - 32);
	}

	CDialog::OnRButtonDown(nFlags, point);
}

void CBB3_level_editorDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	rmb_down = FALSE;
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CBB3_level_editorDlg::OnChangeEditArg3() 
{
	int		cur_tool;
	int		arg1;
	char	buffer[40];

	
	CComboBox * d_tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * d_arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CEdit * d_arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);

	cur_tool = d_tool->GetCurSel();
	arg1 = d_arg1->GetCurSel();
	
	switch( cur_tool)
	{
	case TOOL_LOAD_INIT:

		switch( arg1)
		{
		case TOOL_LOAD_INIT_FOND:
			d_arg3->GetWindowText( gfx_decor_name);
			break;
		case TOOL_LOAD_INIT_PBK:
			d_arg3->GetWindowText( gfx_niveau_name);
			break;
		case TOOL_LOAD_INIT_PBK_ENN:
			d_arg3->GetWindowText( gfx_ennemis_name);
			break;
		case TOOL_LOAD_INIT_PBK_RPG:
			d_arg3->GetWindowText( gfx_rpg_name);
			break;
		case TOOL_LOAD_INIT_RPG:
			d_arg3->GetWindowText( rpg_niveau_name);
			break;
		case TOOL_LOAD_INIT_SBK:
			d_arg3->GetWindowText( sbk_niveau_name);
			break;
		case TOOL_LOAD_INIT_MUSICBK:
			d_arg3->GetWindowText( sbk_music_name);
			break;
		}
		break;

	case TOOL_VICTORY:
		d_arg3->GetWindowText( buffer, 20);
		if ( strlen( buffer) > 0)
			vflag2 = atoi( buffer);
		break;
	}
}

void CBB3_level_editorDlg::OnEditchangeComboArg1() 
{
}

void CBB3_level_editorDlg::OnButtonSave() 
{
	int		fic;
	char	buffer[100];

	if ( gfx_decor_name.GetLength() == 0)
	{
		MessageBox( "ERREUR : pas de nom de GFX pour les décors", NULL, MB_ICONERROR);
		return;
	}

	CFileDialog save_box (FALSE, "lvl", NULL, 0, "Fichiers level (*.LVL)|*.lvl|Tous les fichiers (*.*)|*.*||", NULL);

	save_box.DoModal();

	if ( (fic=_open( save_box.GetPathName(), _O_WRONLY | _O_BINARY | _O_TRUNC | _O_CREAT, _S_IREAD | _S_IWRITE)) == -1)
	{
		MessageBox( "ERREUR : impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	
	// Nom du fichier GFX pour les décors
	//
	strcpy( buffer, LPCSTR(gfx_decor_name));
	_write( fic, buffer, 20);


	// Nom du fichier GFX pour le niveau
	//
	strcpy( buffer, LPCSTR(gfx_niveau_name));
	_write( fic, buffer, 20);

	
	// Nom du fichier GFX pour les ennemis
	//
	strcpy( buffer, LPCSTR(gfx_ennemis_name));
	_write( fic, buffer, 20);


	// Nom du fichier SFX pour le niveau
	//
	strcpy( buffer, LPCSTR(sbk_niveau_name));
	_write( fic, buffer, 20);


	// Nom du fichier SFX pour les musiques
	//
	strcpy( buffer, LPCSTR(sbk_music_name));
	_write( fic, buffer, 20);


	// Nom du fichier RPG
	//
	strcpy( buffer, LPCSTR(rpg_niveau_name));
	_write( fic, buffer, 20);


	// Nom du fichier GFX pour les RPGS
	//
	strcpy( buffer, LPCSTR(gfx_rpg_name));
	_write( fic, buffer, 20);


	// Décors
	//
	_write( fic, &scr_level_size, sizeof(scr_level_size));
	for ( int i=0; i < scr_level_size; i++)
		_write( fic, &num_decor[i], sizeof(int));

	// Positions de départ des joueurs
	//
	_write( fic, &xstart1, sizeof(xstart1));
	_write( fic, &ystart1, sizeof(ystart1));
	_write( fic, &xstart2, sizeof(xstart2));
	_write( fic, &ystart2, sizeof(ystart2));
	
	// Conditions de victoire
	//
	_write( fic, &xvictory, sizeof(xvictory));
	_write( fic, &vflag1, sizeof(vflag1));
	_write( fic, &vval1, sizeof(vval1));
	_write( fic, &vflag2, sizeof(vflag2));
	_write( fic, &vval2, sizeof(vval2));

	// Plateformes
	//
	for ( i=0; i < NB_MAX_PLAT; i++)
		_write( fic, y_plat[i], level_size*sizeof(int));

	
	// Murs opaques
	//
	for ( i=0; i < 60; i++)
		_write( fic, murs_opaque[i], (level_size/8)*sizeof(bool));

	
	// Murs sanglants
	//
	for ( i=0; i < 60; i++)
		_write( fic, murs_sang[i], (level_size/8)*sizeof(bool));

	//------------------------------------------------
	// Là, ça devient chaud! -> Liste des Events
	//

	SuperListe		list_events;
	FICEVENT *		event;
	ENNEMI *		ennemi;
	GEN_ENNEMI *	gennemi;
	FOND_ANIME *	fond;
	LOCK *			lock;
	HOLD_FIRE *		hold_fire;
	FORCE_SCROLL *	force_scroll;
	RPG *			rpg;
	FLAG *			flag;
	TEXTE *			txt;
	SON *			son;
	METEO *			meteo;
	OVERKILL *		okill;
	LOAD_DYNA *		load_dyna;
	MUSIC *			music;
	GBONUS *		gbonus;
	TURRET *		turret;
	BONUS *			bonus;


	// Les ennemis
	//
	list_ennemis.start();

	while( !list_ennemis.fin())
	{
		ennemi = (ENNEMI*) list_ennemis.info();

		event = new FICEVENT;

		if ( ennemi->sens == 0)
			event->x_activation = ennemi->x - 750;
		else
			event->x_activation = ennemi->x + 50;

		event->event_id = EVENTID_ENNEMI;
		event->id = id_ennemis[ennemi->id];
		event->x = ennemi->x;
		event->y = ennemi->y;
		event->sens = ennemi->sens;

		list_events.ajoute( (void*) event);
		list_ennemis.suivant();
	}

	// Les générateurs d'ennemis
	//
	list_genEnnemis.start();

	while( !list_genEnnemis.fin())
	{
		gennemi = (GEN_ENNEMI*) list_genEnnemis.info();

		event = new FICEVENT;

		if ( gennemi->sens == 0 || !gennemi->tmp)
			event->x_activation = gennemi->x - 800;
		else
			event->x_activation = gennemi->x + 50;

		event->event_id = EVENTID_ENNEMI_GENERATOR;
		event->id = id_ennemis[gennemi->id];
		event->x = gennemi->x;
		event->y = gennemi->y;
		event->sens = gennemi->sens;
		event->capacite = gennemi->capacite;
		event->periode = gennemi->periode;
		event->tmp = gennemi->tmp;

		list_events.ajoute( (void*) event);
		list_genEnnemis.suivant();
	}


	// Les fonds animés
	//
	list_fonds_animes.start();

	while( !list_fonds_animes.fin())
	{
		fond = (FOND_ANIME*) list_fonds_animes.info();

		event = new FICEVENT;

		event->event_id = EVENTID_FOND_ANIME;
		event->x_activation = fond->x - 740;
		event->id = id_fonds_animes[fond->id];
		event->x = fond->x;
		event->y = fond->y;

		list_events.ajoute( (void*) event);
		list_fonds_animes.suivant();
	}


	// Les mi-fonds
	//
	list_mi_fonds.start();

	while( !list_mi_fonds.fin())
	{
		fond = (FOND_ANIME*) list_mi_fonds.info();

		event = new FICEVENT;

		event->event_id = EVENTID_MIFOND;
		event->x_activation = fond->x - 660;
		event->id = id_mi_fonds[fond->id];
		event->x = fond->x;
		event->y = fond->y;
		event->capacite = fond->id; // Le terme "capacité" est bidon, c'est juste pour que l'éditeur de niveau puisse recharger le schnuff

		list_events.ajoute( (void*) event);
		list_mi_fonds.suivant();
	}


	// Les premiers plans
	//
	list_premier_plan.start();

	while( !list_premier_plan.fin())
	{
		fond = (FOND_ANIME*) list_premier_plan.info();

		event = new FICEVENT;

		event->event_id = EVENTID_PREMIER_PLAN;
		event->x_activation = fond->x - 740;
		event->id = id_premier_plan[fond->id];
		event->x = fond->x;
		event->y = fond->y;
		event->capacite = fond->id; // Le terme "capacité" est bidon, c'est juste pour que l'éditeur de niveau puisse recharger le schnuff

		list_events.ajoute( (void*) event);
		list_premier_plan.suivant();
	}

	// Les locks
	//
	list_lock.start();

	while( !list_lock.fin())
	{
		lock = (LOCK*) list_lock.info();

		event = new FICEVENT;

		event->event_id = EVENTID_LOCK;
		event->x_activation = lock->x;
		event->cond = lock->condition;
		event->flag = lock->flag;
		event->val = lock->valeur;

		list_events.ajoute( (void*) event);
		list_lock.suivant();
	}

	// Les hold fire
	//
	list_hold_fire.start();

	while( !list_hold_fire.fin())
	{
		hold_fire = (HOLD_FIRE*) list_hold_fire.info();

		event = new FICEVENT;

		event->event_id = EVENTID_HOLD_FIRE;
		event->x_activation = hold_fire->x;
		event->flag = hold_fire->flag;
		event->val = hold_fire->valeur;

		list_events.ajoute( (void*) event);
		list_hold_fire.suivant();
	}

	// Les force scroll
	//
	list_force_scroll.start();

	while( !list_force_scroll.fin())
	{
		force_scroll = (FORCE_SCROLL*) list_force_scroll.info();

		event = new FICEVENT;

		event->event_id = EVENTID_FORCE_SCROLL;
		event->x_activation = force_scroll->x;
		event->speed = force_scroll->speed;

		list_events.ajoute( (void*) event);
		list_force_scroll.suivant();
	}

	// Les phases RPG
	//
	list_rpg.start();

	while( !list_rpg.fin())
	{
		rpg = (RPG*) list_rpg.info();

		event = new FICEVENT;

		event->event_id = EVENTID_RPG;
		event->x_activation = rpg->x;
		event->id = rpg->num;
		event->cond = rpg->cond;
		event->flag = rpg->flag;
		event->val = rpg->val;

		list_events.ajoute( (void*) event);
		list_rpg.suivant();
	}

	// Les FLAGS
	//
	list_flag.start();

	while( !list_flag.fin())
	{
		flag = (FLAG*) list_flag.info();

		event = new FICEVENT;

		event->event_id = EVENTID_FLAG;
		event->x_activation = flag->x;
		event->flag = flag->num;
		event->val = flag->val;

		list_events.ajoute( (void*) event);
		list_flag.suivant();
	}

	// Les textes
	//
	list_txt.start();

	while( !list_txt.fin())
	{
		txt = (TEXTE*) list_txt.info();

		event = new FICEVENT;

		event->event_id = EVENTID_TEXT;
		event->x_activation = txt->x;
		event->cond = txt->cond;
		event->flag = txt->flag;
		event->val = txt->val;
		event->n_txt = txt->ntxt;

		list_events.ajoute( (void*) event);
		list_txt.suivant();
	}

	// Les sons
	//
	list_son.start();

	while( !list_son.fin())
	{
		son = (SON*) list_son.info();

		event = new FICEVENT;

		event->event_id = EVENTID_SON;
		event->x_activation = son->x;
		event->n_sbk = son->sbk;
		event->flag = son->flag;
		event->val = son->val;
		event->id = son->num;

		list_events.ajoute( (void*) event);
		list_son.suivant();
	}

	// Les effets meteo
	//
	list_meteo.start();

	while( !list_meteo.fin())
	{
		meteo = (METEO*) list_meteo.info();

		event = new FICEVENT;

		event->event_id = EVENTID_METEO;
		event->x_activation = meteo->x;
		event->id = meteo->type;
		event->intensite = meteo->intensite;

		list_events.ajoute( (void*) event);
		list_meteo.suivant();
	}

	// Les overkills!
	//
	list_okill.start();

	while( !list_okill.fin())
	{
		okill = (OVERKILL*) list_okill.info();

		event = new FICEVENT;

		event->event_id = EVENTID_OVERKILL;
		event->x_activation = okill->x;
		event->duree = okill->duree;
		event->id = okill->id_en;

		list_events.ajoute( (void*) event);
		list_okill.suivant();
	}

	// Les chargements dynamiques
	//
	list_load_dyna.start();

	while( !list_load_dyna.fin())
	{
		load_dyna = (LOAD_DYNA*) list_load_dyna.info();

		event = new FICEVENT;

		event->event_id = EVENTID_DYNAMIC_LOAD;
		event->x_activation = load_dyna->x;
		event->id = load_dyna->id;
		strcpy( event->fic, load_dyna->fic);

		list_events.ajoute( (void*) event);
		list_load_dyna.suivant();
	}

	// Les musiques
	//
	list_music.start();

	while( !list_music.fin())
	{
		music = (MUSIC*) list_music.info();

		event = new FICEVENT;

		event->event_id = EVENTID_MUSIC;
		event->x_activation = music->x;
		event->id = music->num;
		event->play = music->play;

		list_events.ajoute( (void*) event);
		list_music.suivant();
	}

	// Les générateurs de bonus
	//
	list_gbonus.start();

	while( !list_gbonus.fin())
	{
		gbonus = (GBONUS*) list_gbonus.info();

		event = new FICEVENT;

		event->event_id = EVENTID_BONUS_GENERATOR;
		event->x_activation = gbonus->x;
		event->id = gbonus->type;
		event->periode = gbonus->periode;

		list_events.ajoute( (void*) event);
		list_gbonus.suivant();
	}

	// Les tourelles
	//
	list_turret.start();

	while( !list_turret.fin())
	{
		turret = (TURRET*) list_turret.info();

		event = new FICEVENT;

		event->event_id = EVENTID_TURRET;
		event->x_activation = turret->x - 740;
		event->x = turret->x;
		event->y = turret->y;
		event->dir = turret->dir;
		event->id = turret->id;

		list_events.ajoute( (void*) event);
		list_turret.suivant();
	}

	// Les bonus
	//
	list_bonus.start();

	while( !list_bonus.fin())
	{
		bonus = (BONUS*) list_bonus.info();

		event = new FICEVENT;

		event->event_id = EVENTID_BONUS;
		event->x_activation = bonus->x - 740;
		event->x = bonus->x;
		event->y = bonus->y;
		event->id = bonus->type;

		list_events.ajoute( (void*) event);
		list_bonus.suivant();
	}

	// Sauvegarde la taille de la liste
	//
	int	taille = list_events.taille();
	_write( fic, &taille, sizeof(int));

	// Sauvegarde la liste elle même
	//
	list_events.trier( trier_events);
	list_events.start();

	while( !list_events.fin())
	{
		event = (FICEVENT*) list_events.info();
		_write( fic, (void*)event, sizeof(FICEVENT));
		list_events.suivant();
	}

	list_events.vide();
	_close( fic);
}

void CBB3_level_editorDlg::OnButtonLoad() 
{
	int		fic;
	char	buffer[100];


	CFileDialog load_box (TRUE, "lvl", NULL, 0, "Fichiers level (*.LVL)|*.lvl|Tous les fichiers (*.*)|*.*||", NULL);

	if ( load_box.DoModal() != IDOK)
		return;

	if ( (fic=_open( load_box.GetPathName(), _O_RDONLY | _O_BINARY)) == -1)
	{
		MessageBox( "ERREUR : impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	list_ennemis.vide();
	list_genEnnemis.vide();
	list_fonds_animes.vide();
	list_mi_fonds.vide();
	list_premier_plan.vide();
	list_lock.vide();
	list_hold_fire.vide();
	list_force_scroll.vide();
	list_rpg.vide();
	list_flag.vide();
	list_txt.vide();
	list_son.vide();
	list_meteo.vide();
	list_okill.vide();
	list_load_dyna.vide();
	list_music.vide();
	list_gbonus.vide();
	list_turret.vide();
	
	// Nom du fichier GFX pour les décors
	//
	_read( fic, buffer, 20);
	gfx_decor_name = buffer;

	
	// Nom du fichier GFX pour le niveau
	//
	_read( fic, buffer, 20);
	gfx_niveau_name = buffer;

	
	// Nom du fichier GFX pour les ennemis
	//
	_read( fic, buffer, 20);
	gfx_ennemis_name = buffer;

	
	// Nom du fichier SBK pour le niveau
	//
	_read( fic, buffer, 20);
	sbk_niveau_name = buffer;

	
	// Nom du fichier SBK pour les musiques 
	//
	_read( fic, buffer, 20);
	sbk_music_name = buffer;

	
	// Nom du fichier RPG pour le niveau 
	//
	_read( fic, buffer, 20);
	rpg_niveau_name = buffer;

	
	// Nom du fichier GFX pour les RPG
	//
	_read( fic, buffer, 20);
	gfx_rpg_name = buffer;


	// Décors
	//
	_read( fic, &scr_level_size, sizeof(scr_level_size));

	level_size = 640 * scr_level_size;

	if ( num_decor != NULL)
		delete [] num_decor;

	num_decor = new int[scr_level_size];

	for ( int i=0; i < scr_level_size; i++)
		_read( fic, &num_decor[i], sizeof(int));

	// Positions de départ des joueurs
	//
	_read( fic, &xstart1, sizeof(xstart1));
	_read( fic, &ystart1, sizeof(ystart1));
	_read( fic, &xstart2, sizeof(xstart2));
	_read( fic, &ystart2, sizeof(ystart2));
	
	// Conditions de victoire
	//
	_read( fic, &xvictory, sizeof(xvictory));
	_read( fic, &vflag1, sizeof(vflag1));
	_read( fic, &vval1, sizeof(vval1));
	_read( fic, &vflag2, sizeof(vflag2));
	_read( fic, &vval2, sizeof(vval2));
	
	// Plateformes
	//
	for ( i=0; i < NB_MAX_PLAT; i++)
		_read( fic, y_plat[i], level_size*sizeof(int));
		
	
	// Murs opaques
	//
	for ( i=0; i < 60; i++)
		_read( fic, murs_opaque[i], (level_size/8)*sizeof(bool));

	
	// Murs sanglants
	//
	for ( i=0; i < 60; i++)
		_read( fic, murs_sang[i], (level_size/8)*sizeof(bool));

	// Nombre d'évenements
	//
	int				nb_events;
	FICEVENT *		event = new FICEVENT;
	ENNEMI *		ennemi;
	GEN_ENNEMI *	gennemi;
	FOND_ANIME *	fond;
	LOCK *			lock;
	HOLD_FIRE *		hold;
	FORCE_SCROLL *	scroll;
	RPG *			rpg;
	FLAG *			flag;
	TEXTE *			txt;
	SON *			son;
	METEO *			meteo;
	OVERKILL *		okill;
	LOAD_DYNA *		load_dyna;
	MUSIC *			music;
	GBONUS *		gbonus;
	TURRET *		turret;
	BONUS *			bonus;

	_read( fic, &nb_events, sizeof(nb_events));

	// Les évenements
	//
	for ( i=0; i < nb_events; i++)
	{
		_read( fic, (void*)event, sizeof(FICEVENT));
		
		switch(event->event_id)
		{
		case EVENTID_ENNEMI:
			ennemi = new ENNEMI;
			ennemi->id = event->id-id_ennemis[0];
			ennemi->x = event->x;
			ennemi->y = event->y;
			ennemi->sens = event->sens;

			list_ennemis.ajoute( (void*) ennemi);
			break;

		case EVENTID_ENNEMI_GENERATOR:
			gennemi = new GEN_ENNEMI;
			gennemi->id = event->id-id_ennemis[0];
			gennemi->x = event->x;
			gennemi->y = event->y;
			gennemi->sens = event->sens;
			gennemi->capacite = event->capacite;
			gennemi->periode = event->periode;
			gennemi->tmp = event->tmp;

			list_genEnnemis.ajoute( (void*) gennemi);
			break;

		case EVENTID_FOND_ANIME:
			fond = new FOND_ANIME;
			fond->id = event->id-id_fonds_animes[0];
			fond->x = event->x;
			fond->y = event->y;

			list_fonds_animes.ajoute( (void*) fond);
			break;

		case EVENTID_MIFOND:
			fond = new FOND_ANIME;
			fond->id = event->capacite;
			fond->x = event->x;
			fond->y = event->y;

			list_mi_fonds.ajoute( (void*) fond);
			break;

		case EVENTID_PREMIER_PLAN:
			fond = new FOND_ANIME;
			fond->id = event->capacite;
			fond->x = event->x;
			fond->y = event->y;

			list_premier_plan.ajoute( (void*) fond);
			break;

		case EVENTID_LOCK:
			lock = new LOCK;
			lock->x = event->x_activation;
			lock->condition = event->cond;
			lock->flag = event->flag;
			lock->valeur = event->val;

			list_lock.ajoute( (void*) lock);
			break;

		case EVENTID_HOLD_FIRE:
			hold = new HOLD_FIRE;
			hold->x = event->x_activation;
			hold->flag = event->flag;
			hold->valeur = event->val;

			list_hold_fire.ajoute( (void*) hold);
			break;

		case EVENTID_FORCE_SCROLL:
			scroll = new FORCE_SCROLL;
			scroll->x = event->x_activation;
			scroll->speed = event->speed;

			list_force_scroll.ajoute( (void*) scroll);
			break;

		case EVENTID_RPG:
			rpg = new RPG;
			rpg->x = event->x_activation;
			rpg->cond = event->cond;
			rpg->num = event->id;
			rpg->flag = event->flag;
			rpg->val = event->val;

			list_rpg.ajoute( (void*) rpg);
			break;

		case EVENTID_FLAG:
			flag = new FLAG;
			flag->x = event->x_activation;
			flag->num = event->flag;
			flag->val = event->val;

			list_flag.ajoute( (void*) flag);
			break;

		case EVENTID_TEXT:
			txt = new TEXTE;
			txt->x = event->x_activation;
			txt->ntxt = event->n_txt;
			txt->cond = event->cond;
			txt->flag = event->flag;
			txt->val = event->val;

			list_txt.ajoute( (void*) txt);
			break;

		case EVENTID_SON:
			son = new SON;
			son->x = event->x_activation;
			son->sbk = event->n_sbk;
			son->num = event->id;
			son->flag = event->flag;
			son->val = event->val;

			list_son.ajoute( (void*) son);
			break;

		case EVENTID_METEO:
			meteo = new METEO;
			meteo->x = event->x_activation;
			meteo->type = event->id;
			meteo->intensite = event->intensite;

			list_meteo.ajoute( (void*) meteo);
			break;

		case EVENTID_OVERKILL:
			okill = new OVERKILL;
			okill->x = event->x_activation;
			okill->id_en = event->id;
			okill->duree = event->duree;

			list_okill.ajoute( (void*) okill);
			break;

		case EVENTID_DYNAMIC_LOAD:
			load_dyna = new LOAD_DYNA;
			load_dyna->x = event->x_activation;
			load_dyna->id = event->id;
			strcpy( load_dyna->fic, event->fic);

			list_load_dyna.ajoute( (void*) load_dyna);
			break;

		case EVENTID_MUSIC:
			music = new MUSIC;
			music->x = event->x_activation;
			music->num = event->id;
			music->play = event->play;

			list_music.ajoute( (void*) music);
			break;

		case EVENTID_BONUS_GENERATOR:
			gbonus = new GBONUS;
			gbonus->x = event->x_activation;
			gbonus->type = event->id;
			gbonus->periode = event->periode;

			list_gbonus.ajoute( (void*) gbonus);
			break;

		case EVENTID_TURRET:
			turret = new TURRET;
			turret->id = event->id;
			turret->x = event->x;
			turret->y = event->y;
			turret->dir = event->dir;

			list_turret.ajoute( (void*) turret);
			break;

		case EVENTID_BONUS:
			bonus = new BONUS;
			bonus->x = event->x;
			bonus->y = event->y;
			bonus->type = event->id;

			list_bonus.ajoute( (void*) bonus);
			break;
		}
	}

	delete event;
	_close( fic);
	OnSelchangeComboTool();
	
}

void CBB3_level_editorDlg::AfficheMursOpaques()
{
	CDC *	dc;
	CPen	pen(PS_SOLID, 1, RGB( 255, 0, 0));

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	dc = frame->GetDC();
	dc->SelectObject( &pen);

	int	decal = cur_offset % 8;
	int	xi = cur_offset + 7;
	int	xe;

	xi /= 8;

	if ( decal == 0)
		xe = xi + 80;
	else
		xe = xi + 79;

	decal++;

	for ( int y=0; y < 60; y++)
	{
		for ( int x=xi; x < xe; x++)
		{
			if ( murs_opaque[y][x] )
			{
				int top		= y * 8 + 1;
				int left	= (x * 8)-cur_offset+1;

				dc->MoveTo( left, top);
				dc->LineTo( left + 8, top + 8);

				left += 8;

				dc->MoveTo( left, top);
				dc->LineTo( left - 8, top + 8);
			}
		}
	}

	frame->ReleaseDC( dc);

}



void CBB3_level_editorDlg::AfficheMursSang()
{
	CDC *	dc;
	CPen	pen(PS_SOLID, 1, RGB( 255, 255, 0));

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	dc = frame->GetDC();
	dc->SelectObject( &pen);

	int	decal = cur_offset % 8;
	int	xi = cur_offset + 7;
	int	xe;

	xi /= 8;

	if ( decal == 0)
		xe = xi + 80;
	else
		xe = xi + 79;

	decal++;

	for ( int y=0; y < 60; y++)
	{
		for ( int x=xi; x < xe; x++)
		{
			if ( murs_sang[y][x] )
			{
				int top		= y * 8 + 1;
				int left	= (x * 8)-cur_offset+1;

				dc->MoveTo( left, top + 4);
				dc->LineTo( left + 8, top + 4);

				dc->MoveTo( left + 4, top);
				dc->LineTo( left + 4, top + 8);
			}
		}
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckAuto() 
{
	CButton * check_auto = (CButton *) GetDlgItem( IDC_CHECK_AUTO);
	CButton * check_plat = (CButton *) GetDlgItem( IDC_CHECK_PLAT);
	CButton * check_mSang = (CButton *) GetDlgItem( IDC_CHECK_MURS_SANG);
	CButton * check_mOpak = (CButton *) GetDlgItem( IDC_CHECK_MURS_OPAK);
	CButton * check_enn = (CButton *) GetDlgItem( IDC_CHECK_ENNEMIS);
	CButton * check_gEnn = (CButton *) GetDlgItem( IDC_CHECK_GENENNEMIS);
	CButton * check_fondAnime = (CButton *) GetDlgItem( IDC_CHECK_FONDANIME);
	CButton * check_miFonds = (CButton *) GetDlgItem( IDC_CHECK_MIFOND);
	CButton * check_1plan = (CButton *) GetDlgItem( IDC_CHECK_PREMIER_PLAN);
	CButton * check_lock = (CButton *) GetDlgItem( IDC_CHECK_LOCK);
	CButton * check_holdfire = (CButton *) GetDlgItem( IDC_CHECK_HOLD_FIRE);
	CButton * check_forcescroll = (CButton *) GetDlgItem( IDC_CHECK_FORCE_SCROLL);
	CButton * check_rpg = (CButton *) GetDlgItem( IDC_CHECK_RPG);
	CButton * check_flag = (CButton *) GetDlgItem( IDC_CHECK_FLAG);
	CButton * check_text = (CButton *) GetDlgItem( IDC_CHECK_TEXT);
	CButton * check_son = (CButton *) GetDlgItem( IDC_CHECK_SON);
	CButton * check_meteo = (CButton *) GetDlgItem( IDC_CHECK_METEO);
	CButton * check_okill = (CButton *) GetDlgItem( IDC_CHECK_OVERKILL);
	CButton * check_load_d = (CButton *) GetDlgItem( IDC_CHECK_LOAD_DYNA);
	CButton * check_gbonus = (CButton *) GetDlgItem( IDC_CHECK_GBONUS);
	CButton * check_turret = (CButton *) GetDlgItem( IDC_CHECK_TURRET);
	CButton * check_start = (CButton *) GetDlgItem( IDC_CHECK_START);
	CButton * check_victory = (CButton *) GetDlgItem( IDC_CHECK_VICTORY);
	CButton * check_bonus = (CButton *) GetDlgItem( IDC_CHECK_BONUS);

	// Mode automatique
	//
	if ( check_auto->GetCheck() == 1)
	{
		check_plat->EnableWindow( FALSE);
		check_mSang->EnableWindow( FALSE);
		check_mOpak->EnableWindow( FALSE);
		check_enn->EnableWindow( FALSE);
		check_gEnn->EnableWindow( FALSE);
		check_fondAnime->EnableWindow( FALSE);
		check_miFonds->EnableWindow( FALSE);
		check_1plan->EnableWindow( FALSE);
		check_lock->EnableWindow( FALSE);
		check_holdfire->EnableWindow( FALSE);
		check_forcescroll->EnableWindow( FALSE);
		check_rpg->EnableWindow( FALSE);
		check_flag->EnableWindow( FALSE);
		check_text->EnableWindow( FALSE);
		check_son->EnableWindow( FALSE);
		check_meteo->EnableWindow( FALSE);
		check_okill->EnableWindow( FALSE);
		check_load_d->EnableWindow( FALSE);
		check_gbonus->EnableWindow( FALSE);
		check_turret->EnableWindow( FALSE);
		check_start->EnableWindow( FALSE);
		check_victory->EnableWindow( FALSE);
		check_bonus->EnableWindow( FALSE);

		ManageAutoShow();
		AfficheTout();
	}
	else // Mode manuel
	{
		check_plat->EnableWindow();
		check_mSang->EnableWindow();
		check_mOpak->EnableWindow();
		check_enn->EnableWindow();
		check_gEnn->EnableWindow();
		check_fondAnime->EnableWindow();
		check_miFonds->EnableWindow();
		check_1plan->EnableWindow();
		check_lock->EnableWindow();
		check_holdfire->EnableWindow();
		check_forcescroll->EnableWindow();
		check_rpg->EnableWindow();
		check_flag->EnableWindow();
		check_text->EnableWindow();
		check_son->EnableWindow();
		check_meteo->EnableWindow();
		check_okill->EnableWindow();
		check_load_d->EnableWindow();
		check_gbonus->EnableWindow();
		check_turret->EnableWindow();
		check_start->EnableWindow();
		check_victory->EnableWindow();
		check_bonus->EnableWindow();
	}
}

void CBB3_level_editorDlg::ManageAutoShow()
{
	int		cur_tool;

	CComboBox * tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CButton * check_plat = (CButton *) GetDlgItem( IDC_CHECK_PLAT);
	CButton * check_mSang = (CButton *) GetDlgItem( IDC_CHECK_MURS_SANG);
	CButton * check_mOpak = (CButton *) GetDlgItem( IDC_CHECK_MURS_OPAK);
	CButton * check_enn = (CButton *) GetDlgItem( IDC_CHECK_ENNEMIS);
	CButton * check_gEnn = (CButton *) GetDlgItem( IDC_CHECK_GENENNEMIS);
	CButton * check_fondAnime = (CButton *) GetDlgItem( IDC_CHECK_FONDANIME);
	CButton * check_miFonds = (CButton *) GetDlgItem( IDC_CHECK_MIFOND);
	CButton * check_1plan = (CButton *) GetDlgItem( IDC_CHECK_PREMIER_PLAN);
	CButton * check_lock = (CButton *) GetDlgItem( IDC_CHECK_LOCK);
	CButton * check_holdfire = (CButton *) GetDlgItem( IDC_CHECK_HOLD_FIRE);
	CButton * check_forcescroll = (CButton *) GetDlgItem( IDC_CHECK_FORCE_SCROLL);
	CButton * check_rpg = (CButton *) GetDlgItem( IDC_CHECK_RPG);
	CButton * check_flag = (CButton *) GetDlgItem( IDC_CHECK_FLAG);
	CButton * check_text = (CButton *) GetDlgItem( IDC_CHECK_TEXT);
	CButton * check_son = (CButton *) GetDlgItem( IDC_CHECK_SON);
	CButton * check_meteo = (CButton *) GetDlgItem( IDC_CHECK_METEO);
	CButton * check_okill = (CButton *) GetDlgItem( IDC_CHECK_OVERKILL);
	CButton * check_load_d = (CButton *) GetDlgItem( IDC_CHECK_LOAD_DYNA);
	CButton * check_gbonus = (CButton *) GetDlgItem( IDC_CHECK_GBONUS);
	CButton * check_turret = (CButton *) GetDlgItem( IDC_CHECK_TURRET);
	CButton * check_start = (CButton *) GetDlgItem( IDC_CHECK_START);
	CButton * check_victory = (CButton *) GetDlgItem( IDC_CHECK_VICTORY);
	CButton * check_bonus = (CButton *) GetDlgItem( IDC_CHECK_BONUS);

	cur_tool = tool->GetCurSel();

	check_plat->SetCheck( 0);
	check_mSang->SetCheck( 0);
	check_mOpak->SetCheck( 0);
	check_gEnn->SetCheck( 0);
	check_enn->SetCheck( 0);
	check_fondAnime->SetCheck( 0);
	check_miFonds->SetCheck( 0);
	check_1plan->SetCheck( 0);
	check_lock->SetCheck( 0);
	check_holdfire->SetCheck( 0);
	check_forcescroll->SetCheck( 0);
	check_rpg->SetCheck( 0);
	check_flag->SetCheck( 0);
	check_text->SetCheck( 0);
	check_son->SetCheck( 0);
	check_meteo->SetCheck( 0);
	check_okill->SetCheck( 0);
	check_load_d->SetCheck( 0);
	check_gbonus->SetCheck( 0);
	check_turret->SetCheck( 0);
	check_start->SetCheck( 0);
	check_victory->SetCheck( 0);
	check_bonus->SetCheck( 0);

	switch( cur_tool)
	{
	case TOOL_PLATEFORME:
		check_plat->SetCheck( 1);
		break;

	case TOOL_MUR_OPAQUE:
		check_mOpak->SetCheck( 1);
		break;

	case TOOL_MUR_SANG:
		check_mSang->SetCheck( 1);
		break;

	case TOOL_ENNEMIS:
		check_enn->SetCheck( 1);
		break;

	case TOOL_GEN_ENNEMIS:
	case TOOL_GEN_ENNEMIS_TMP:
		check_gEnn->SetCheck( 1);
		break;

	case TOOL_FOND_ANIME:
		check_fondAnime->SetCheck( 1);
		break;

	case TOOL_MI_FONDS:
		check_miFonds->SetCheck( 1);
		break;

	case TOOL_PREMIER_PLAN:
		check_1plan->SetCheck( 1);
		break;

	case TOOL_LOCK:
		check_lock->SetCheck( 1);
		break;

	case TOOL_HOLD_FIRE:
		check_holdfire->SetCheck( 1);
		break;

	case TOOL_FORCE_SCROLL:
		check_forcescroll->SetCheck( 1);
		break;

	case TOOL_RPG:
		check_rpg->SetCheck( 1);
		break;

	case TOOL_FLAG:
		check_flag->SetCheck( 1);
		break;

	case TOOL_TEXT:
		check_text->SetCheck( 1);
		break;

	case TOOL_SON:
	case TOOL_MUSIC:
		check_son->SetCheck( 1);
		break;

	case TOOL_METEO:
		check_meteo->SetCheck( 1);
		break;

	case TOOL_OVERKILL:
		check_okill->SetCheck( 1);
		break;

	case TOOL_LOAD_DYNA:
		check_load_d->SetCheck( 1);
		break;

	case TOOL_GBONUS:
		check_gbonus->SetCheck( 1);
		break;

	case TOOL_TURRET:
		check_turret->SetCheck( 1);
		break;

	case TOOL_VICTORY:
		check_victory->SetCheck( 1);
		break;

	case TOOL_START1:
	case TOOL_START2:
		check_start->SetCheck( 1);
		break;

	case TOOL_BONUS:
		check_bonus->SetCheck( 1);
	default:
		break;
	}

}

void CBB3_level_editorDlg::OnCheckMursOpak() 
{
	AfficheTout();
}

void CBB3_level_editorDlg::OnCheckMursSang() 
{
	AfficheTout();
}

void CBB3_level_editorDlg::OnCheckPlat() 
{
	AfficheTout();
}

bool CBB3_level_editorDlg::LoadEnnemis()
{
	ifstream	fic;
	char		buffer[100];

	fic.open( "bbe_ennemis.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>nb_ennemis;

	bmp_ennemis = new HBITMAP[nb_ennemis];
	noms_ennemis = new char * [nb_ennemis];
	id_ennemis = new int[nb_ennemis];

	fic.getline( buffer, 200);	// Bidon -> Ligne suivante

	for ( int i=0; i < nb_ennemis; i++)
	{
		fic>>id_ennemis[i];
		fic.getline( buffer, 200, '*'); // Nom de l'ennemi

		noms_ennemis[i] = new char[strlen(buffer)+1];
		strcpy( noms_ennemis[i], buffer);


		fic.getline( buffer, 200);
		bmp_ennemis[i] = (HBITMAP)LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( bmp_ennemis[i] == NULL)
		{
			char buffer2[200];
			sprintf( buffer2, "Impossible de charger %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONERROR);
			fic.close();
			return false;
		}
	}

	fic.close();
	return true;
}



void CBB3_level_editorDlg::AfficheEnnemis()
{
	ENNEMI *	ennemi;
	int			x;
	int			y;

	list_ennemis.start();

	while( !list_ennemis.fin() )
	{

		ennemi = (ENNEMI*) list_ennemis.info();

		x = ennemi->x;
		y = ennemi->y;

		ClippedBlit( bmp_ennemis[ennemi->id], x, y, true);
		ClippedBlit( bmp_fleche[ennemi->sens], x, y, true);
		list_ennemis.suivant();
	}
}

void CBB3_level_editorDlg::ClippedBlit(const HBITMAP &bmp, int x1, int y1, bool spoted, bool trans, bool xored, unsigned int col_rect)
{
	BITMAP	bm;
	CDC *	dc;
	HDC		hdc;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	dc = frame->GetDC();
ASSERT(dc != NULL);
	hdc = CreateCompatibleDC( NULL);
ASSERT(hdc != NULL);
	SelectObject( hdc, bmp);
	
ASSERT(GetObject( bmp, sizeof(bm), &bm));
	// Prend en compte l'offset
	//
	x1 -= cur_offset;

	// "point chaud" bidon (en bas au milieu)
	//
	if ( spoted)
	{
		x1 -= bm.bmWidth / 2;
		y1 -= bm.bmHeight;
	}

	int x2 = x1 + bm.bmWidth;
	int y2 = y1 + bm.bmHeight;

	// Totalement en dehors de la zone
	//
	if ( x2 < 0 || x1 > 639 || y2 < 0 || y1 > 479)
	{
		DeleteDC( hdc);
		frame->ReleaseDC( dc);
		return;
	}

	int im_x1 = 0;
	int im_y1 = 0;
	int im_x2 = bm.bmWidth - 1;
	int im_y2 = bm.bmHeight - 1;


	if ( x1 < 0)
	{
		im_x1 += (-x1);
		x1 = 0;
	}

	if ( x2 > 639)
	{
		im_x2 -= (x2-639);
	}

	if ( y1 < 0)
	{
		im_y1 += (-y1);
		y1 = 0;
	}

	if ( y2 > 479)
	{
		im_y2 -= (y2-479);
	}

	x1 += 1; // En raison des rebords
	y1 += 1;
	
	im_x2++; // Pour le blit
	im_y2++;


	if ( xored)
		BitBlt( dc->m_hDC, x1, y1, im_x2-im_x1, im_y2-im_y1, hdc, im_x1, im_y1, SRCINVERT);
	else if ( trans)
		BitBlt( dc->m_hDC, x1, y1, im_x2-im_x1, im_y2-im_y1, hdc, im_x1, im_y1, SRCAND);
	else
		BitBlt( dc->m_hDC, x1, y1, im_x2-im_x1, im_y2-im_y1, hdc, im_x1, im_y1, SRCCOPY);

	CPen	pen( PS_DASH, 1, col_rect);

	if ( col_rect != RGB( 0, 0, 0))
	{
		int xx = x1 + im_x2-im_x1 + 1;
		int yy = y1 + im_y2-im_y1 + 1;

		if ( xx > 639) xx = 639;
		if ( yy > 479) yy = 479;

		dc->SelectObject( &pen);
		dc->SetBkMode( TRANSPARENT);

		dc->MoveTo( x1, y1);
		dc->LineTo( xx, y1);
		dc->LineTo( xx, yy);
		dc->LineTo( x1, yy);
		dc->LineTo( x1, y1);
	}

	DeleteDC( hdc);
	frame->ReleaseDC( dc);
}

bool CBB3_level_editorDlg::IsClicked(int xc, int yc, const HBITMAP &bmp, int x1, int y1, bool spoted)
{
	BITMAP	bm;
	HDC		hdc;

	hdc = CreateCompatibleDC( NULL);
	SelectObject( hdc, bmp);
	GetObject( bmp, sizeof(bm), &bm);

	if ( spoted)
	{
		x1 -= bm.bmWidth / 2;
		y1 -= bm.bmHeight;
	}

	int x2 = x1 + bm.bmWidth;
	int y2 = y1 + bm.bmHeight;

	DeleteObject( hdc);

	if ( xc < x1 || xc > x2 || yc < y1 || yc > y2)
		return false;
	
	return true;
}

void CBB3_level_editorDlg::AfficheGenerateursEnnemis()
{
	char			buffer[100];
	CDC *			dc;
	GEN_ENNEMI *	g_ennemi;
	CFont			font;
	RECT			r;
	int				x;
	int				y;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 255, 0));
	dc->SelectObject( &font);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_genEnnemis.start();

	while( !list_genEnnemis.fin() )
	{

		g_ennemi = (GEN_ENNEMI*) list_genEnnemis.info();

		x = g_ennemi->x;
		y = g_ennemi->y;

		ClippedBlit( bmp_ennemis[g_ennemi->id], x, y, true);
		ClippedBlit( bmp_Gfleche[g_ennemi->sens], x, y, true);

		x -= cur_offset;

		sprintf( buffer, "C:%d", g_ennemi->capacite);
		dc->ExtTextOut( x+20, y-24, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		sprintf( buffer, "P:%d", g_ennemi->periode);
		dc->ExtTextOut( x+20, y-12, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		if ( g_ennemi->tmp)
		{
			sprintf( buffer, "TMP");
			dc->ExtTextOut( x+20, y-36, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_genEnnemis.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckEnnemis() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckGenennemis() 
{
	AfficheTout();	
}

bool CBB3_level_editorDlg::LoadFondsAnimes()
{
	ifstream	fic;
	char		buffer[100];

	fic.open( "bbe_fondsanimes.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>nb_fonds_animes;

	bmp_fonds_animes = new HBITMAP[nb_fonds_animes];
	noms_fonds_animes = new char * [nb_fonds_animes];
	id_fonds_animes = new int[nb_fonds_animes];

	fic.getline( buffer, 200);	// Bidon -> Ligne suivante
 
	for ( int i=0; i < nb_fonds_animes; i++)
	{
		fic>>id_fonds_animes[i];

		fic.getline( buffer, 200, '*'); // Nom du fond animé


		noms_fonds_animes[i] = new char[strlen(buffer)+1];
		strcpy( noms_fonds_animes[i], buffer);


		fic.getline( buffer, 200);

		bmp_fonds_animes[i] = (HBITMAP)LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( bmp_fonds_animes[i] == NULL)
		{
			char buffer2[200];
			sprintf( buffer2, "Impossible de charger %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONERROR);
			fic.close();
			return false;
		}
	}

	fic.close();

	return true;

}

void CBB3_level_editorDlg::AfficheFondsAnimes()
{
	FOND_ANIME *fanime;
	int			x;
	int			y;

	list_fonds_animes.start();

	while( !list_fonds_animes.fin() )
	{

		fanime = (FOND_ANIME*) list_fonds_animes.info();

		x = fanime->x;
		y = fanime->y;

		ClippedBlit( bmp_fonds_animes[fanime->id], x, y, false, false, false, RGB( 0, 0, 255));
		list_fonds_animes.suivant();
	}
}

void CBB3_level_editorDlg::OnCheckFondanime() 
{
	AfficheTout();
}

bool CBB3_level_editorDlg::LoadMiFonds()
{
	ifstream	fic;
	char		buffer[100];

	fic.open( "bbe_mifonds.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>nb_mi_fonds;

	bmp_mi_fonds = new HBITMAP[nb_mi_fonds];
	noms_mi_fonds = new char * [nb_mi_fonds];
	id_mi_fonds = new int[nb_mi_fonds];

	fic.getline( buffer, 200);	// Bidon -> Ligne suivante
 
	for ( int i=0; i < nb_mi_fonds; i++)
	{
		fic>>id_mi_fonds[i];

		fic.getline( buffer, 200, '*'); // Nom de l'ennemi

		noms_mi_fonds[i] = new char[strlen(buffer)+1];
		strcpy( noms_mi_fonds[i], buffer);

		fic.getline( buffer, 200);

		bmp_mi_fonds[i] = (HBITMAP)LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( bmp_mi_fonds[i] == NULL)
		{
			char buffer2[200];
			sprintf( buffer2, "Impossible de charger %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONERROR);
			fic.close();
			return false;
		}
	}

	fic.close();
	return true;
}

void CBB3_level_editorDlg::AfficheMiFonds()
{
	FOND_ANIME *fanime;
	int			x;
	int			y;

	list_mi_fonds.start();

	while( !list_mi_fonds.fin() )
	{

		fanime = (FOND_ANIME*) list_mi_fonds.info();

		x = fanime->x;
		y = fanime->y;

		ClippedBlit( bmp_mi_fonds[fanime->id], x, y, false, false, false, RGB( 0, 255, 0));
		list_mi_fonds.suivant();
	}
}

void CBB3_level_editorDlg::OnCheckMifond() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckPremierPlan() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AffichePremierPlan()
{
	FOND_ANIME *fanime;
	int			x;
	int			y;

	list_premier_plan.start();

	while( !list_premier_plan.fin() )
	{

		fanime = (FOND_ANIME*) list_premier_plan.info();

		x = fanime->x;
		y = fanime->y;

		ClippedBlit( bmp_premier_plan[fanime->id], x, y, false, true, false, RGB( 0, 255, 0));
		list_premier_plan.suivant();
	}
}

bool CBB3_level_editorDlg::LoadPremierPlan()
{
	ifstream	fic;
	char		buffer[100];

	fic.open( "bbe_1plan.ini", ios::in | ios::nocreate);

	if ( fic.is_open() == 0)
		return false;

	fic>>nb_premier_plan;

	bmp_premier_plan = new HBITMAP[nb_premier_plan];
	noms_premier_plan = new char * [nb_premier_plan];
	id_premier_plan = new int[nb_premier_plan];

	fic.getline( buffer, 200);	// Bidon -> Ligne suivante
 
	for ( int i=0; i < nb_premier_plan; i++)
	{
		fic>>id_premier_plan[i];

		fic.getline( buffer, 200, '*');


		noms_premier_plan[i] = new char[strlen(buffer)+1];
		strcpy( noms_premier_plan[i], buffer);


		fic.getline( buffer, 200);

		bmp_premier_plan[i] = (HBITMAP)LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );

		if ( bmp_premier_plan[i] == NULL)
		{
			char buffer2[200];
			sprintf( buffer2, "Impossible de charger %s", buffer);
			MessageBox( buffer2, NULL, MB_ICONERROR);
			fic.close();
			return false;
		}
	}

	fic.close();
	return true;
}

void CBB3_level_editorDlg::OnCheckLock() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnSelchangeComboArg1() 
{
	char	buffer[100];
	int		cur_tool;
	int		arg1;

	CStatic * txt1 = (CStatic *) GetDlgItem( IDC_STATIC_ARG1);
	CStatic * txt2 = (CStatic *) GetDlgItem( IDC_STATIC_ARG2);
	CStatic * txt3 = (CStatic *) GetDlgItem( IDC_STATIC_ARG3);
	CStatic * txt4 = (CStatic *) GetDlgItem( IDC_STATIC_ARG4);
	CComboBox * d_tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * d_arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CComboBox * d_arg2 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG2);
	CEdit * d_arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);
	CEdit * d_arg4 = (CEdit *) GetDlgItem( IDC_EDIT_ARG4);

	cur_tool = d_tool->GetCurSel();
	arg1 = d_arg1->GetCurSel();

	switch( cur_tool)
	{
	case TOOL_LOAD_INIT:

		switch( arg1)
		{
		case TOOL_LOAD_INIT_FOND:
			d_arg3->SetWindowText( gfx_decor_name);
			break;
		case TOOL_LOAD_INIT_PBK:
			d_arg3->SetWindowText( gfx_niveau_name);
			break;
		case TOOL_LOAD_INIT_PBK_ENN:
			d_arg3->SetWindowText( gfx_ennemis_name);
			break;
		case TOOL_LOAD_INIT_PBK_RPG:
			d_arg3->SetWindowText( gfx_rpg_name);
			break;
		case TOOL_LOAD_INIT_SBK:
			d_arg3->SetWindowText( sbk_niveau_name);
			break;
		case TOOL_LOAD_INIT_RPG:
			d_arg3->SetWindowText( rpg_niveau_name);
			break;
		case TOOL_LOAD_INIT_MUSICBK:
			d_arg3->SetWindowText( sbk_music_name);
			break;
		}
		break;

	case TOOL_LOCK:

		switch( arg1)
		{
		case TOOL_LOCK_PLUS_DENNEMI:
		case TOOL_LOCK_PLUS_DE_GEN:
			
			d_arg2->ResetContent();
			d_arg3->SetWindowText( "");
			txt2->SetWindowText( "");
			txt3->SetWindowText( "");

			d_arg2->EnableWindow( FALSE);
			d_arg3->EnableWindow( FALSE);
			
			break;

		case TOOL_LOCK_FLAG:
		case TOOL_LOCK_FLAG2:

			d_arg2->ResetContent();

			for ( int i=0; i < 10; i++)
			{
				sprintf( buffer, "%d", i);
				d_arg2->InsertString( i, buffer);
			}

			d_arg2->SetCurSel( 0);
			d_arg3->SetWindowText( "1");

			txt2->SetWindowText( "numéro");

			if ( arg1 == TOOL_LOCK_FLAG2)
				txt3->SetWindowText( ">=");
			else
				txt3->SetWindowText( "est égal à");

			d_arg2->EnableWindow();
			d_arg3->EnableWindow();
			break;
		}
		break;

	case TOOL_TEXT:

		switch( arg1)
		{
		case TOOL_TEXT_NO_COND:

			d_arg2->ResetContent();
			d_arg3->SetWindowText( "");

			txt2->SetWindowText( "");
			txt3->SetWindowText( "");

			d_arg2->EnableWindow( FALSE);
			d_arg3->EnableWindow( FALSE);
			break;

		case TOOL_TEXT_COND:
		case TOOL_TEXT_COND2:

			for ( int i=0; i <= 10; i++)
			{
				sprintf( buffer, "%d", i);
				d_arg2->InsertString( i, buffer);
			}

			d_arg2->SetCurSel( 0);
			
			txt2->SetWindowText( "le flag");

			if ( arg1 == TOOL_TEXT_COND2)
				txt3->SetWindowText( ">=");
			else
				txt3->SetWindowText( "est égal à");

			d_arg2->EnableWindow();
			d_arg3->EnableWindow();
		}
		break;

	case TOOL_VICTORY:
		vflag1 = d_arg1->GetCurSel();
		break;
	}

}

void CBB3_level_editorDlg::AfficheLock()
{
	char		buffer[100];
	LOCK *		lock;
	CDC *		dc;
	int			x;
	RECT		r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 255, 0, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 0, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_lock.start();

	while( !list_lock.fin())
	{
		lock = (LOCK*) list_lock.info();

		x = lock->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			if ( lock->condition == TOOL_LOCK_FLAG)
			{
				sprintf( buffer, "Flag:%d", lock->flag);
				ASSERT(strlen(buffer));
				dc->ExtTextOut( x+3, 17, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

				sprintf( buffer, "Val:%d", lock->valeur);
				ASSERT(strlen(buffer));
				dc->ExtTextOut( x+3, 29, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
			else if ( lock->condition == TOOL_LOCK_FLAG2)
			{
				sprintf( buffer, "Flag:%d", lock->flag);
				ASSERT(strlen(buffer));
				dc->ExtTextOut( x+3, 17, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

				sprintf( buffer, "Val>=:%d", lock->valeur);
				ASSERT(strlen(buffer));
				dc->ExtTextOut( x+3, 29, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}

			else if ( lock->condition == TOOL_LOCK_PLUS_DENNEMI)
			{
				sprintf( buffer, "No ennemi");
				dc->ExtTextOut( x+3, 17, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
			else if ( lock->condition == TOOL_LOCK_PLUS_DE_GEN)
			{
				sprintf( buffer, "No generateur");
				dc->ExtTextOut( x+3, 17, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
		
			sprintf(buffer, "Lock");
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);
			dc->ExtTextOut( x+3, 5, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_lock.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::AfficheHoldFire()
{
	char		buffer[100];
	HOLD_FIRE *	hold_fire;
	CDC *		dc;
	int			x;
	RECT		r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 255, 255, 0));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 255, 0));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_hold_fire.start();

	while( !list_hold_fire.fin())
	{
		hold_fire = (HOLD_FIRE*) list_hold_fire.info();

		x = hold_fire->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
		
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Hold Fire");
			dc->ExtTextOut( x+3, 41, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Flag:%d", hold_fire->flag);
			dc->ExtTextOut( x+3, 53, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Val:%d", hold_fire->valeur);
			dc->ExtTextOut( x+3, 65, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_hold_fire.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckHoldFire() 
{
	AfficheTout();
}

void CBB3_level_editorDlg::AfficheForceScroll()
{
	char			buffer[100];
	FORCE_SCROLL*	force_scroll;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 255, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 255, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_force_scroll.start();

	while( !list_force_scroll.fin())
	{
		force_scroll = (FORCE_SCROLL*) list_force_scroll.info();

		x = force_scroll->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
		
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Force Scroll");
			dc->ExtTextOut( x+3, 135, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Speed:%d", force_scroll->speed);
			dc->ExtTextOut( x+3, 147, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_force_scroll.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckForceScroll() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckRpg() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheRPG()
{
	char			buffer[100];
	RPG *			rpg;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 0, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 0, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_rpg.start();

	while( !list_rpg.fin())
	{
		rpg = (RPG*) list_rpg.info();

		x = rpg->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
		
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "RPG");
			dc->ExtTextOut( x+3, 77, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Num:%d", rpg->num);
			dc->ExtTextOut( x+3, 89, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			if ( rpg->cond)
			{
				sprintf( buffer, "Flag:%d", rpg->flag);
				dc->ExtTextOut( x+3, 101, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

				sprintf( buffer, "Val:%d", rpg->val);
				dc->ExtTextOut( x+3, 113, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
		}

		list_rpg.suivant();
	}

	frame->ReleaseDC( dc);

}

void CBB3_level_editorDlg::AfficheFlags()
{
	char			buffer[100];
	FLAG *			flag;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 255, 0, 0));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 0, 0));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_flag.start();

	while( !list_flag.fin())
	{
		flag = (FLAG*) list_flag.info();

		x = flag->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Set");
			dc->ExtTextOut( x+3, 159, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Flag:%d", flag->num);
			dc->ExtTextOut( x+3, 171, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Val:%d", flag->val);
			dc->ExtTextOut( x+3, 183, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_flag.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckFlag() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckText() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheTextes()
{
	char			buffer[100];
	TEXTE *			txt;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 255, 0, 128));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 0, 128));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_txt.start();

	while( !list_txt.fin())
	{
		txt = (TEXTE*) list_txt.info();

		x = txt->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Txt");
			dc->ExtTextOut( x+3, 195, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Ntxt:%d", txt->ntxt);
			dc->ExtTextOut( x+3, 207, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			if ( txt->cond == TOOL_TEXT_COND)
			{
				sprintf( buffer, "Flag:%d", txt->flag);
				dc->ExtTextOut( x+3, 219, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

				sprintf( buffer, "Val:%d", txt->val);
				dc->ExtTextOut( x+3, 231, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
			else if ( txt->cond == TOOL_TEXT_COND2)
			{
				sprintf( buffer, "Flag:%d", txt->flag);
				dc->ExtTextOut( x+3, 219, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

				sprintf( buffer, "Val>=:%d", txt->val);
				dc->ExtTextOut( x+3, 231, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
			}
		}

		list_txt.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckSon() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheSons()
{
	char			buffer[100];
	SON *			son;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 128, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 128, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_son.start();

	while( !list_son.fin())
	{
		son = (SON*) list_son.info();

		x = son->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Son");
			dc->ExtTextOut( x+3, 279, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "SBK:%s", sbk_name[son->sbk]);
			dc->ExtTextOut( x+3, 291, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Num:%d", son->num);
			dc->ExtTextOut( x+3, 303, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Flag:%d", son->flag);
			dc->ExtTextOut( x+3, 315, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Val:%d", son->val);
			dc->ExtTextOut( x+3, 327, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_son.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckMeteo() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheMeteo()
{
	char			buffer[100];
	METEO *			meteo;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 128, 0, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 128, 0, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_meteo.start();

	while( !list_meteo.fin())
	{
		meteo = (METEO*) list_meteo.info();

		x = meteo->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Meteo");
			dc->ExtTextOut( x+3, 243, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Type:%s", meteo_name[meteo->type]);
			dc->ExtTextOut( x+3, 255, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Int:%d", meteo->intensite);
			dc->ExtTextOut( x+3, 267, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		}

		list_meteo.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::AfficheOverKill()
{
	char			buffer[100];
	OVERKILL *		okill;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 128, 255, 0));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 128, 255, 0));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	
	list_okill.start();

	while( !list_okill.fin())
	{
		okill = (OVERKILL*) list_okill.info();

		ASSERT(okill);

		x = okill->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "OverKill!");
			dc->ExtTextOut( x+3, 339, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Type:%s", noms_ennemis[okill->id_en]);
			dc->ExtTextOut( x+3, 351, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Duree:%d", okill->duree);
			dc->ExtTextOut( x+3, 363, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		}

		list_okill.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckOverkill() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckLoadDyna() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheLoadDyn()
{
	char			buffer[100];
	LOAD_DYNA *		load_dyna;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 150, 250, 150));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 150, 250, 150));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	
	list_load_dyna.start();

	while( !list_load_dyna.fin())
	{
		load_dyna = (LOAD_DYNA*) list_load_dyna.info();

		x = load_dyna->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Chargement Dynamique");
			dc->ExtTextOut( x+3, 375, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			switch( load_dyna->id)
			{
			case TOOL_LOAD_DYNA_PBK:
				strcpy( buffer, "PBK niveau");
				break;
			case TOOL_LOAD_DYNA_PBK_ENN:
				strcpy( buffer, "PBK ennemis");
				break;
			case TOOL_LOAD_DYNA_PBK_TMP:
				strcpy( buffer, "PBK temporaire");
				break;
			case TOOL_LOAD_DYNA_SBK_ENN:
				strcpy( buffer, "SBK ennemis");
				break;
			case TOOL_LOAD_DYNA_SBK_TMP:
				strcpy( buffer, "SBK temporaire");
				break;
			case TOOL_LOAD_DYNA_MUSICBK:
				strcpy( buffer, "SBK musique");
				break;
			}

			dc->ExtTextOut( x+3, 387, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Fichier:%s", load_dyna->fic);
			dc->ExtTextOut( x+3, 399, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_load_dyna.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::AfficheMusic()
{
	char			buffer[100];
	MUSIC *			music;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 128, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 128, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_music.start();

	while( !list_music.fin())
	{
		music = (MUSIC*) list_music.info();

		x = music->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Music");
			dc->ExtTextOut( x+3, 410, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Play:%d", music->play);
			dc->ExtTextOut( x+3, 422, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Num:%d", music->num);
			dc->ExtTextOut( x+3, 435, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_music.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::AfficheGBonus()
{
	char			buffer[100];
	GBONUS *		gbonus;
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 128, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 128, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_gbonus.start();

	while( !list_gbonus.fin())
	{
		gbonus = (GBONUS*) list_gbonus.info();

		x = gbonus->x - cur_offset + 1;

		if ( x > 0 && x < 640)
		{
			dc->MoveTo( x, 1);
			dc->LineTo( x, 480);

			sprintf( buffer, "Gen. bonus");
			dc->ExtTextOut( x+3, 447, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			if ( gbonus->type == 0)
				strcpy( buffer, "Armes");
			else
				strcpy( buffer, "Tous");

			dc->ExtTextOut( x+3, 459, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

			sprintf( buffer, "Periode:%d", gbonus->periode);
			dc->ExtTextOut( x+3, 471, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
		}

		list_gbonus.suivant();
	}

	frame->ReleaseDC( dc);

}

void CBB3_level_editorDlg::OnCheckGbonus() 
{
	AfficheTout();
}

void CBB3_level_editorDlg::AfficheTurret()
{
	TURRET *		turret;
	int				x;
	int				y;
	char			buffer[100];
	CDC *			dc;
	CFont			font;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 255, 0));
	dc->SelectObject( &font);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_turret.start();

	while( !list_turret.fin() )
	{

		turret = (TURRET*) list_turret.info();

		x = turret->x;
		y = turret->y;

		ClippedBlit( bmp_tourelle, x, y, true, true);
	
		x -= cur_offset;

		sprintf( buffer, "ID:%d", turret->id);
		dc->ExtTextOut( x+20, y-24, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		sprintf( buffer, "Dir:%d", turret->dir);
		dc->ExtTextOut( x+20, y-12, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);

		list_turret.suivant();
	}

	frame->ReleaseDC( dc);
}

void CBB3_level_editorDlg::OnCheckTurret() 
{
	AfficheTout();
}

void CBB3_level_editorDlg::OnSelchangeComboArg2() 
{
	int		cur_tool;
	int		arg2;

	CStatic * txt1 = (CStatic *) GetDlgItem( IDC_STATIC_ARG1);
	CStatic * txt2 = (CStatic *) GetDlgItem( IDC_STATIC_ARG2);
	CStatic * txt3 = (CStatic *) GetDlgItem( IDC_STATIC_ARG3);
	CStatic * txt4 = (CStatic *) GetDlgItem( IDC_STATIC_ARG4);
	CComboBox * d_tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * d_arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CComboBox * d_arg2 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG2);
	CEdit * d_arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);
	CEdit * d_arg4 = (CEdit *) GetDlgItem( IDC_EDIT_ARG4);

	cur_tool = d_tool->GetCurSel();
	arg2 = d_arg2->GetCurSel();

	switch ( cur_tool)
	{
	case TOOL_RPG:

		switch( arg2)
		{
		case TOOL_RPG_NO_COND:

			d_arg3->SetWindowText( "");
			d_arg4->SetWindowText( "");

			txt3->SetWindowText( "");
			txt4->SetWindowText( "");

			d_arg3->EnableWindow( FALSE);
			d_arg4->EnableWindow( FALSE);
			break;

		case TOOL_RPG_COND:

			d_arg3->SetWindowText( "0");
			d_arg4->SetWindowText( "0");
			
			txt3->SetWindowText( "le flag");
			txt4->SetWindowText( "est égal à");

			d_arg3->EnableWindow();
			d_arg4->EnableWindow();
			break;
		}
		break;

	case TOOL_VICTORY:
		vval1 = d_arg2->GetCurSel();
		break;
	}
}

// Permet de trier dans l'ordre DECROISSANT
//
int trier_events( const void * a, const void * b)
{
	FICEVENT * p1;
	FICEVENT * p2;

	p1 = (FICEVENT*) a;
	p2 = (FICEVENT*) b;

	if ( p1->x_activation < p2->x_activation)
		return 1;
	else
		return -1;
}


void CBB3_level_editorDlg::AfficheVictory()
{
	char			buffer[100];
	CDC *			dc;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 0, 128, 255));
	CFont	font;

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 0, 128, 255));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	int x = xvictory - cur_offset + 1;

	if ( x > 0 && x < 640)
	{
		dc->MoveTo( x, 1);
		dc->LineTo( x, 480);
		sprintf( buffer, "Victory!");
		dc->ExtTextOut( x+3, 10, ETO_CLIPPED, &r, buffer, strlen(buffer), NULL);
	}

	frame->ReleaseDC( dc);

}

void CBB3_level_editorDlg::OnChangeEditArg4() 
{
	int		cur_tool;
	int		arg1;
	char	buffer[40];

	
	CComboBox * d_tool = (CComboBox *) GetDlgItem( IDC_COMBO_TOOL);
	CComboBox * d_arg1 = (CComboBox *) GetDlgItem( IDC_COMBO_ARG1);
	CEdit * d_arg3 = (CEdit *) GetDlgItem( IDC_EDIT_ARG3);
	CEdit * d_arg4 = (CEdit *) GetDlgItem( IDC_EDIT_ARG4);

	cur_tool = d_tool->GetCurSel();
	arg1 = d_arg1->GetCurSel();
	
	switch( cur_tool)
	{
	case TOOL_VICTORY:
		d_arg4->GetWindowText( buffer, 20);
		if ( strlen( buffer) > 0)
			vval2 = atoi( buffer);
		break;
	}

	
}


void CBB3_level_editorDlg::AfficheStart()
{
	CDC *			dc;
	int				x;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen1( PS_SOLID, 1, RGB( 0, 0, 255));
	CPen	pen2( PS_SOLID, 1, RGB( 255, 0, 0));


	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SelectObject( &pen1);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	x = xstart1 - cur_offset;

	if ( x > 0 && x < 640)
	{
		dc->MoveTo( x, 1);
		dc->LineTo( x, 480);

		dc->MoveTo( 0, ystart1);
		dc->LineTo( 640, ystart1);
	}

	dc->SelectObject( &pen2);
	x = xstart2 - cur_offset;

	if ( x > 0 && x < 640)
	{
		dc->MoveTo( x, 1);
		dc->LineTo( x, 480);

		dc->MoveTo( 0, ystart2);
		dc->LineTo( 640, ystart2);
	}

	frame->ReleaseDC( dc);
}


void CBB3_level_editorDlg::OnCheckStart() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnCheckVictory() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::OnButtonImport() 
{	
	int		tmp_scr_size;
	int		tmp_size;
	int		fic;
	char	buffer[100];
	CString	str;

//	CEdit * edit = (CEdit*) GetDlgItem( IDC_EDIT_IMPORT);


	CFileDialog load_box (TRUE, "lvl", NULL, 0, "Fichiers level (*.LVL)|*.lvl|Tous les fichiers (*.*)|*.*||", NULL);

	load_box.DoModal();

	if ( (fic=_open( load_box.GetPathName(), _O_RDONLY | _O_BINARY)) == -1)
	{
		MessageBox( "ERREUR : impossible d'ouvrir le fichier", NULL, MB_ICONERROR);
		return;
	}

	list_ennemis.vide();
	list_genEnnemis.vide();
	list_fonds_animes.vide();
	list_mi_fonds.vide();
	list_premier_plan.vide();
	list_lock.vide();
	list_hold_fire.vide();
	list_force_scroll.vide();
	list_rpg.vide();
	list_flag.vide();
	list_txt.vide();
	list_son.vide();
	list_meteo.vide();
	list_okill.vide();
	list_load_dyna.vide();
	list_music.vide();
	list_gbonus.vide();
	list_turret.vide();
	
	// Nom du fichier GFX pour les décors
	//
	_read( fic, buffer, 20);
	gfx_decor_name = buffer;

	
	// Nom du fichier GFX pour le niveau
	//
	_read( fic, buffer, 20);
	gfx_niveau_name = buffer;

	
	// Nom du fichier GFX pour les ennemis
	//
	_read( fic, buffer, 20);
	gfx_ennemis_name = buffer;

	
	// Nom du fichier SBK pour le niveau
	//
	_read( fic, buffer, 20);
	sbk_niveau_name = buffer;

	
	// Nom du fichier SBK pour les musiques 
	//
	_read( fic, buffer, 20);
	sbk_music_name = buffer;

	
	// Nom du fichier RPG pour le niveau 
	//
	_read( fic, buffer, 20);
	rpg_niveau_name = buffer;

	
	// Nom du fichier GFX pour les RPG
	//
	_read( fic, buffer, 20);
	gfx_rpg_name = buffer;


	// Décors
	//
	_read( fic, &tmp_scr_size, sizeof(tmp_scr_size));

	tmp_size = tmp_scr_size * 640;

	level_size = 640 * scr_level_size;

	if ( num_decor == NULL)
		num_decor = new int[scr_level_size];

	for ( int i=0; i < tmp_scr_size; i++)
		_read( fic, &num_decor[i], sizeof(int));


	// Positions de départ des joueurs
	//
	_read( fic, &xstart1, sizeof(xstart1));
	_read( fic, &ystart1, sizeof(ystart1));
	_read( fic, &xstart2, sizeof(xstart2));
	_read( fic, &ystart2, sizeof(ystart2));
	
	// Conditions de victoire
	//
	_read( fic, &xvictory, sizeof(xvictory));
	_read( fic, &vflag1, sizeof(vflag1));
	_read( fic, &vval1, sizeof(vval1));
	_read( fic, &vflag2, sizeof(vflag2));
	_read( fic, &vval2, sizeof(vval2));
	
	// Plateformes
	//
	for ( i=0; i < NB_MAX_PLAT; i++)
		_read( fic, y_plat[i], tmp_size*sizeof(int));
		
	
	// Murs opaques
	//
	for ( i=0; i < 60; i++)
		_read( fic, murs_opaque[i], (tmp_size/8)*sizeof(bool));

	
	// Murs sanglants
	//
	for ( i=0; i < 60; i++)
		_read( fic, murs_sang[i], (tmp_size/8)*sizeof(bool));

	// Nombre d'évenements
	//
	int				nb_events;
	FICEVENT *		event = new FICEVENT;
	ENNEMI *		ennemi;
	GEN_ENNEMI *	gennemi;
	FOND_ANIME *	fond;
	LOCK *			lock;
	HOLD_FIRE *		hold;
	FORCE_SCROLL *	scroll;
	RPG *			rpg;
	FLAG *			flag;
	TEXTE *			txt;
	SON *			son;
	METEO *			meteo;
	OVERKILL *		okill;
	LOAD_DYNA *		load_dyna;
	MUSIC *			music;
	GBONUS *		gbonus;
	TURRET *		turret;
	BONUS *			bonus;

	_read( fic, &nb_events, sizeof(nb_events));

	// Les évenements
	//
	for ( i=0; i < nb_events; i++)
	{
		_read( fic, (void*)event, sizeof(FICEVENT));
		
		switch(event->event_id)
		{
		case EVENTID_ENNEMI:
			ennemi = new ENNEMI;
			ennemi->id = event->id-id_ennemis[0];
			ennemi->x = event->x;
			ennemi->y = event->y;
			ennemi->sens = event->sens;

			list_ennemis.ajoute( (void*) ennemi);
			break;

		case EVENTID_ENNEMI_GENERATOR:
			gennemi = new GEN_ENNEMI;
			gennemi->id = event->id-id_ennemis[0];
			gennemi->x = event->x;
			gennemi->y = event->y;
			gennemi->sens = event->sens;
			gennemi->capacite = event->capacite;
			gennemi->periode = event->periode;
			gennemi->tmp = event->tmp;

			list_genEnnemis.ajoute( (void*) gennemi);
			break;

		case EVENTID_FOND_ANIME:
			fond = new FOND_ANIME;
			fond->id = event->id-id_fonds_animes[0];
			fond->x = event->x;
			fond->y = event->y;

			list_fonds_animes.ajoute( (void*) fond);
			break;

		case EVENTID_MIFOND:
			fond = new FOND_ANIME;
			fond->id = event->capacite;
			fond->x = event->x;
			fond->y = event->y;

			list_mi_fonds.ajoute( (void*) fond);
			break;

		case EVENTID_PREMIER_PLAN:
			fond = new FOND_ANIME;
			fond->id = event->capacite;
			fond->x = event->x;
			fond->y = event->y;

			list_premier_plan.ajoute( (void*) fond);
			break;

		case EVENTID_LOCK:
			lock = new LOCK;
			lock->x = event->x_activation;
			lock->condition = event->cond;
			lock->flag = event->flag;
			lock->valeur = event->val;

			list_lock.ajoute( (void*) lock);
			break;

		case EVENTID_HOLD_FIRE:
			hold = new HOLD_FIRE;
			hold->x = event->x_activation;
			hold->flag = event->flag;
			hold->valeur = event->val;

			list_hold_fire.ajoute( (void*) hold);
			break;

		case EVENTID_FORCE_SCROLL:
			scroll = new FORCE_SCROLL;
			scroll->x = event->x_activation;
			scroll->speed = event->speed;

			list_force_scroll.ajoute( (void*) scroll);
			break;

		case EVENTID_RPG:
			rpg = new RPG;
			rpg->x = event->x_activation;
			rpg->cond = event->cond;
			rpg->num = event->id;
			rpg->flag = event->flag;
			rpg->val = event->val;

			list_rpg.ajoute( (void*) rpg);
			break;

		case EVENTID_FLAG:
			flag = new FLAG;
			flag->x = event->x_activation;
			flag->num = event->flag;
			flag->val = event->val;

			list_flag.ajoute( (void*) flag);
			break;

		case EVENTID_TEXT:
			txt = new TEXTE;
			txt->x = event->x_activation;
			txt->ntxt = event->n_txt;
			txt->cond = event->cond;
			txt->flag = event->flag;
			txt->val = event->val;

			list_txt.ajoute( (void*) txt);
			break;

		case EVENTID_SON:
			son = new SON;
			son->x = event->x_activation;
			son->sbk = event->n_sbk;
			son->num = event->id;
			son->flag = event->flag;
			son->val = event->val;

			list_son.ajoute( (void*) son);
			break;

		case EVENTID_METEO:
			meteo = new METEO;
			meteo->x = event->x_activation;
			meteo->type = event->id;
			meteo->intensite = event->intensite;

			list_meteo.ajoute( (void*) meteo);
			break;

		case EVENTID_OVERKILL:
			okill = new OVERKILL;
			okill->x = event->x_activation;
			okill->id_en = event->id;
			okill->duree = event->duree;

			list_okill.ajoute( (void*) okill);
			break;

		case EVENTID_DYNAMIC_LOAD:
			load_dyna = new LOAD_DYNA;
			load_dyna->x = event->x_activation;
			load_dyna->id = event->id;
			strcpy( load_dyna->fic, event->fic);

			list_load_dyna.ajoute( (void*) load_dyna);
			break;

		case EVENTID_MUSIC:
			music = new MUSIC;
			music->x = event->x_activation;
			music->num = event->id;
			music->play = event->play;

			list_music.ajoute( (void*) music);
			break;

		case EVENTID_BONUS_GENERATOR:
			gbonus = new GBONUS;
			gbonus->x = event->x_activation;
			gbonus->type = event->id;
			gbonus->periode = event->periode;

			list_gbonus.ajoute( (void*) gbonus);
			break;

		case EVENTID_TURRET:
			turret = new TURRET;
			turret->x = event->x;
			turret->y = event->y;
			turret->dir = event->dir;

			list_turret.ajoute( (void*) turret);
			break;

		case EVENTID_BONUS:
			bonus = new BONUS;
			bonus->x = event->x;
			bonus->y = event->y;
			bonus->type = event->id;

			list_bonus.ajoute( (void*) bonus);
			break;
		}
	}

	delete event;
	_close( fic);
	OnSelchangeComboTool();
	
}

void CBB3_level_editorDlg::OnCheckBonus() 
{
	AfficheTout();	
}

void CBB3_level_editorDlg::AfficheBonus() 
{
	BONUS *			bonus;
	int				x;
	int				y;
	CDC *			dc;
	CFont			font;
	RECT			r;

	CFrameWnd * frame = (CFrameWnd *) GetDlgItem( IDC_FRAME);

	CPen	pen( PS_SOLID, 1, RGB( 255, 0, 0));

	font.CreateFont( 12, 5, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	dc = frame->GetDC();
	dc->SetBkMode( TRANSPARENT);
	dc->SetTextColor( RGB( 255, 0, 0));
	dc->SelectObject( &font);
	dc->SelectObject( &pen);

	r.top	= 1;
	r.bottom= 480;
	r.left	= 1;
	r.right	= 640;

	list_bonus.start();

	while( !list_bonus.fin() )
	{

		bonus = (BONUS*) list_bonus.info();

		x = bonus->x;
		y = bonus->y;

		x -= cur_offset;

		if ( x > 20 && x < 620)
		{
			dc->MoveTo( x, y-10);
			dc->LineTo( x, y+10);

			dc->MoveTo( x-10, y);
			dc->LineTo( x+10, y);

			dc->ExtTextOut( x+20, y-12, ETO_CLIPPED, &r, bonus_name[bonus->type], strlen(bonus_name[bonus->type]), NULL);
		}

		list_bonus.suivant();
	}

	frame->ReleaseDC( dc);
}
