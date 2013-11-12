// BB3_level_editorDlg.h : header file
//

#if !defined(AFX_BB3_LEVEL_EDITORDLG_H__D9A8CEE6_4D23_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_BB3_LEVEL_EDITORDLG_H__D9A8CEE6_4D23_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream.h>

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorDlg dialog

class CBB3_level_editorDlg : public CDialog
{
public:
	void AfficheBonus();
	void AfficheStart();
	void AfficheTurret();
	void AfficheGBonus();
	void AfficheMusic();
	void AfficheLoadDyn();
	void AfficheOverKill();
	void AfficheMeteo();
	void AfficheSons();
	void AfficheTextes();
	void AfficheFlags();
	void AfficheRPG();
	void AfficheForceScroll();
	void AfficheHoldFire();
	void AfficheLock();
	bool LoadPremierPlan();
	void AffichePremierPlan();
	void AfficheMiFonds();
	bool LoadMiFonds();


	// Inside the editor
	//
	HBITMAP	bmp_fleche[2];	// Fleches ennemis
	HBITMAP	bmp_Gfleche[2];	// Fleches générateurs
	HBITMAP bmp_tourelle;	// Tourelle
	int		cur_offset;		// Offset courant

	// Souris
	//
	int		ymouse;			// Coordonnées de la souris (fenêtre entière, pas Frame)
	int		xmouse;
	bool	in_zone;		// Pointeur dans la zone d'édition
	BOOL	lmb_down;		// TRUE si le bouton gauche de la souris est enfoncé
	BOOL	rmb_down;		// idem bouton droit
	BOOL	already_clicked;// Permet de savoir si le click a déjà été pris en compte
							// TRUE = plus à s'en occuper. (évite de placer 10.000 ennemis en 1 click)

	// Nom des trucs à charger
	//
	CString			gfx_decor_name;	// Nom du .GFX contenant les decors
	CString			gfx_niveau_name;
	CString			gfx_ennemis_name;
	CString			sbk_niveau_name;
	CString			sbk_music_name;
	CString			rpg_niveau_name;
	CString			gfx_rpg_name;

	// Décors / taille
	//
	HBITMAP *		scr_decor;		// Tableau de BITMAP pour les decors
	int				nb_scr_decor;	// nombre de types de décors
	int *			num_decor;		// 'Tiles' du niveau
	int				level_size;		// Taille du niveau en pixels
	int				scr_level_size;	// Taille du niveau en écrans

	// Plateformes & co
	//
	int **			y_plat;			// Hauteur des plateformes
	bool **			murs_opaque;	// Murs opaques (8x8)
	bool **			murs_sang;		// Murs sanglants (8x8)

	// Ennemis
	//
	HBITMAP *		bmp_ennemis;	// Tableau de BITMAP pour les ennemis
	char **			noms_ennemis;	// Tableau de chaines pour les noms des ennemis
	int				nb_ennemis;		// Nombre de type d'ennemis
	int *			id_ennemis;		// Identifiant pour les ennemis

	// Fonds animés
	//
	HBITMAP *		bmp_fonds_animes;	// Tableau de BITMAP
	char **			noms_fonds_animes;	// Noms des fonds animés
	int				nb_fonds_animes;	// Nombre de fons animés
	int *			id_fonds_animes;	// Identifiants des fonds animés

	// Mi-fonds
	//
	HBITMAP *		bmp_mi_fonds;	// Tableau de BITMAP
	char **			noms_mi_fonds;	// Noms des fonds animés
	int				nb_mi_fonds;	// Nombre de fons animés
	int *			id_mi_fonds;	// Identifiant des mi fonds

	// Premier plan
	//
	HBITMAP *		bmp_premier_plan;	// Tableau de BITMAP
	char **			noms_premier_plan;	// Noms des 1 plan
	int				nb_premier_plan;	// Nombre de 1 plan
	int *			id_premier_plan;	// Identifiants des fonds animés

	// Coordonnées de départ
	//
	int				xstart1;	// Joueur 1
	int				ystart1;
	int				xstart2;	// Joueur 2
	int				ystart2;

	// Conditions de victoire
	//
	int				xvictory;
	int				vflag1;
	int				vval1;
	int				vflag2;
	int				vval2;

	// Listes
	//
	SuperListe		list_ennemis;		// Liste d'ennemis
	SuperListe		list_genEnnemis;	// Liste de générateurs d'ennemis
	SuperListe		list_fonds_animes;	// Liste des fonds animés
	SuperListe		list_mi_fonds;		// Liste des mi_fonds
	SuperListe		list_premier_plan;	// Liste premier plan
	SuperListe		list_lock;
	SuperListe		list_hold_fire;
	SuperListe		list_force_scroll;
	SuperListe		list_rpg;
	SuperListe		list_flag;
	SuperListe		list_txt;
	SuperListe		list_son;
	SuperListe		list_meteo;
	SuperListe		list_okill;
	SuperListe		list_load_dyna;
	SuperListe		list_music;
	SuperListe		list_gbonus;
	SuperListe		list_turret;
	SuperListe		list_bonus;

	// -----------------------------------------------------
	
	bool	LoadDecor();		// Charge les décors
	bool	LoadEnnemis();		// Charge la liste des ennemis
	bool	LoadFondsAnimes();	// A ton avis ?

	void	ReleaseAll();	// On est pas des bourrins jusqu'au bout...

	void	MakeAction( int x, int y); // Fait l'action selectionnée

	void	ManageAutoShow();	// Gère le mode automatique d'affichage

	void	AfficheVictory();		// Affiche la victoire
	void	AfficheFond();			// Affiche le fond (décors)
	void	AfficheFondsAnimes();	// Affiche les fonds animés
	void	AfficheGenerateursEnnemis();	// Les générateurs
	void	AffichePlateformes();	// Affiche les plateformes
	void	AfficheMursSang();		// Affiche les murs sanglants
	void	AfficheMursOpaques();	// Affiche les murs opaques (impossibles à traverser)
	void	AfficheEnnemis();		// Affiche tous les ennemis
	void	AfficheTout();			// Affiche tout ce qui est nécessaire

	// Jolis blits propres
	//
	void ClippedBlit( const HBITMAP & bmp, int x, int y, bool spoted=false, bool trans=false, bool xored=false, unsigned int col_rect=0);


	// Retourne VRAI si le point (xc,yc) appartient à l'image définie
	// par le bitmap hbm de coordonnées (x1,y1)
	// spoted : point chaud bidon
	//
	bool IsClicked( int xc, int yc, const HBITMAP & hbm, int x1, int y1, bool spoted=false);

	
	CBB3_level_editorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBB3_level_editorDlg)
	enum { IDD = IDD_BB3_LEVEL_EDITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBB3_level_editorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBB3_level_editorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeComboTool();
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChangeEditArg3();
	afx_msg void OnEditchangeComboArg1();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	afx_msg void OnCheckAuto();
	afx_msg void OnCheckMursOpak();
	afx_msg void OnCheckMursSang();
	afx_msg void OnCheckPlat();
	afx_msg void OnCheckEnnemis();
	afx_msg void OnCheckGenennemis();
	afx_msg void OnCheckFondanime();
	afx_msg void OnCheckMifond();
	afx_msg void OnCheckPremierPlan();
	afx_msg void OnCheckLock();
	afx_msg void OnSelchangeComboArg1();
	afx_msg void OnCheckHoldFire();
	afx_msg void OnCheckForceScroll();
	afx_msg void OnCheckRpg();
	afx_msg void OnCheckFlag();
	afx_msg void OnCheckText();
	afx_msg void OnCheckSon();
	afx_msg void OnCheckMeteo();
	afx_msg void OnCheckOverkill();
	afx_msg void OnCheckLoadDyna();
	afx_msg void OnCheckGbonus();
	afx_msg void OnCheckTurret();
	afx_msg void OnSelchangeComboArg2();
	afx_msg void OnChangeEditArg4();
	afx_msg void OnCheckStart();
	afx_msg void OnCheckVictory();
	afx_msg void OnButtonImport();
	afx_msg void OnCheckBonus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//
// Nos jolies couleurs (1 par plateforme)
//
extern COLORREF col_plat[];
extern char pbk_name[][40];
extern char sbk_name[][40];
extern char meteo_name[][40];
extern char bonus_name[][40];

int trier_events( const void * a, const void * b);


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_BB3_LEVEL_EDITORDLG_H__D9A8CEE6_4D23_11D4_8760_00A024851A35__INCLUDED_)
