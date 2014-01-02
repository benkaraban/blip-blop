/******************************************************************
*
* 
*		----------------
*		  Input.h
*		----------------
*			
*		Classe Input
*
*
*		La Classe Input représente toutes les entrées :
*
*		 - Clavier
*
*
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _BENINPUT_
#define _BENINPUT_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <dinput.h>

//-----------------------------------------------------------------------------
//		Constantes pour les entrées
//-----------------------------------------------------------------------------

#define	BINPUT_KEYB		1		// On peut utiliser le clavier
#define BINPUT_JOY		2		// On peut utiliser un joystick

#define MAX_JOY			5		// Nombre maximal de joystick pouvant être gérés

#define	JOY_UP			10
#define	JOY_DOWN		11
#define	JOY_LEFT		12
#define	JOY_RIGHT		13


//-----------------------------------------------------------------------------
//		Définition de la classe Input
//-----------------------------------------------------------------------------

class Input
{
private:
	IDirectInput8 *			dinput;
	IDirectInputDevice8 *	dikeyb;
	IDirectInputDevice8 *	dijoy[MAX_JOY];

	int				n_joy;
	DIJOYSTATE		js[MAX_JOY];
	char 			buffer[256];
	unsigned int	aliastab[256];

public:
	Input();
	~Input();

	int scanKey( unsigned int k) const;

	inline int scanAlias(int a) const { return (scanKey(aliastab[a])); };
	inline unsigned int getAlias(int n) const { return aliastab[n]; };

	IDirectInput8 * di() const;
	int		nbJoy() const { return n_joy; };
	bool	open(HWND wh, HINSTANCE inst, int flags = BINPUT_KEYB|BINPUT_JOY, int cl = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
	void	setAlias(int a, unsigned int val);
	
	unsigned int		waitKey();
	
	void	waitClean();
	void	update();
	void	close();
	bool	anyKeyPressed();
	bool	reAcquire();

	friend BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
};

//-----------------------------------------------------------------------------
//		Déclaration d'un objet 'in' global
//-----------------------------------------------------------------------------

#ifndef BENINPUT_CPP_FILE
	extern Input		in;
#endif

#endif