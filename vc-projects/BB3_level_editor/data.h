#include <afx.h>

struct ENNEMI
{
	int		id;
	int		x;
	int		y;
	int		sens;
};

struct GEN_ENNEMI
{
	int		id;
	int		x;
	int		y;
	int		sens;
	int		capacite;
	int		periode;
	bool	tmp;
};

struct FOND_ANIME
{
	int		id;
	int		x;
	int		y;
};

struct LOCK
{
	int		x;
	int		condition;
	int		flag;
	int		valeur;
};

struct HOLD_FIRE
{
	int		x;
	int		flag;
	int		valeur;
};

struct FORCE_SCROLL
{
	int		x;
	int		speed;
};


struct RPG
{
	int		x;
	int		num;
	int		flag;
	int		val;
	int		cond;
};

struct FLAG
{
	int		x;
	int		num;
	int		val;
};

struct TEXTE
{
	int		x;
	int		cond;
	int		flag;
	int		val;
	int		ntxt;
};

struct SON
{
	int		x;
	int		flag;
	int		val;
	int		sbk;
	int		num;
};

struct METEO
{
	int		x;
	int		type;
	int		intensite;
};

struct OVERKILL
{
	int		x;
	int		id_en;
	int		duree;
};

struct LOAD_DYNA
{
	int		x;
	int		id;
	char	fic[20];
};

struct MUSIC
{
	int		x;
	int		num;
	int		play;
};

struct GBONUS
{
	int		x;
	int		type;	// 0: Armes seulement
	int		periode;// 1: La totale
};

struct TURRET
{
	int		id;
	int		x;
	int		y;
	int		dir;
};

struct BONUS
{
	int		x;
	int		y;
	int		type;
};