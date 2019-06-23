/******************************************************************
*
*
*		----------------
*		  Input.cpp
*		----------------
*
*		Classe Input
*
*
*		La Classe Input représente toutes les entrées :
*
*		 - Clavier
*		 - Joystick
*
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#define BENINPUT_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <cstring>

#include "graphics.h"
#include "input.h"
#include "ben_debug.h"

//-----------------------------------------------------------------------------
//		Déclaration REELLE de l'objet 'in' global
//-----------------------------------------------------------------------------

Input		in;

//-----------------------------------------------------------------------------
// Nom: Input::Input() - CONSTRUCTEUR -
// Desc: Met à NULL les valeurs susceptibles de foirer
//-----------------------------------------------------------------------------

Input::Input() : n_joy(0)
{
	memset(buffer, 0, 256);
	memset(specialsbuffer, 0, 0xFFF);
}

Input::~Input()
{

}



//-----------------------------------------------------------------------------
// Nom: Input::open(HWND, HINSTANCE, int, int)
// Desc: Ouvre BINPUT
//-----------------------------------------------------------------------------

bool Input::open(int flags)
{

	SDL_JoystickEventState(SDL_TRUE);

	this->n_joy = SDL_NumJoysticks();

	for (int i = 0; i < n_joy; i++)
	{
		js[i].handle = SDL_JoystickOpen(i);
		strcpy(this->js[i].name, SDL_JoystickName(js[i].handle));

		memset(this->js[i].buttons, 0, sizeof(this->js[i].buttons));
		memset(&this->js[i].directions, 0, sizeof(this->js[i].directions));
	}

	/*if (dinput != NULL) {
		debug << "Input::open->DINPUT déjà initialisé!\n";
		return false;
	}

	if (DirectInput8Create(inst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL) != DI_OK) {
		debug << "Input::open->Ne peut pas ouvrir DINPUT\n";
		dinput = NULL;
		return false;
	}


	if (flags & BINPUT_KEYB) {
		if (dinput->CreateDevice(GUID_SysKeyboard, (LPDIRECTINPUTDEVICE8A *)&dikeyb, NULL) != DI_OK) {
			debug << "Input::open->Ne peut pas créer le clavier!\n";
			dikeyb = NULL;
			return false;
		} else {
			if (dikeyb->SetDataFormat(&c_dfDIKeyboard) != DI_OK) {
				debug << "Input::open->Ne peut pas initialiser le clavier (set data)\n";
				dikeyb->Release();
				dikeyb = NULL;
				return false;
			} else {
				if (dikeyb->SetCooperativeLevel(wh, cl) != DI_OK) {
					debug << "Input::open->Ne peut pas règler le coop du clavier\n";
					dikeyb->Release();
					dikeyb = NULL;
					return false;
				} else
					dikeyb->Acquire();
			}
		}
	}

	// Associe le joystick
	//
	if (flags & BINPUT_JOY) {
		if (dinput->EnumDevices(DI8DEVTYPE_GAMEPAD, EnumJoysticksCallback, this, DIEDFL_ATTACHEDONLY) != DI_OK) {
			debug << "Cannot enumerate joysticks\n";
		} else {
			debug << n_joy << " joystick(s) found\n";

			for (int i = 0; i < n_joy; i++) {
				if (dijoy[i] != NULL) {
					if (dijoy[i]->SetDataFormat(&c_dfDIJoystick) != DI_OK) {
						debug << "Cannot initialise joystick " << i << "\n";
						dijoy[i]->Release();
						dijoy[i] = NULL;
					} else {
						if (dijoy[i]->SetCooperativeLevel(wh, DISCL_EXCLUSIVE | DISCL_FOREGROUND) != DI_OK) {
							debug << "Cannot set priority level of joystick " << i << "\n";
							dijoy[i]->Release();
							dijoy[i] = NULL;
						} else {
							DIPROPRANGE diprg;

							diprg.diph.dwSize       = sizeof(diprg);
							diprg.diph.dwHeaderSize = sizeof(diprg.diph);
							diprg.diph.dwObj        = DIJOFS_X;
							diprg.diph.dwHow        = DIPH_BYOFFSET;
							diprg.lMin              = -1000;
							diprg.lMax              = +1000;

							dijoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

							diprg.diph.dwObj        = DIJOFS_Y;
							dijoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

							DIPROPDWORD dipdw;

							dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
							dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
							dipdw.diph.dwHow        = DIPH_BYOFFSET;
							dipdw.dwData            = 5000;

							dipdw.diph.dwObj         = DIJOFS_X;
							dijoy[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

							dipdw.diph.dwObj = DIJOFS_Y;
							dijoy[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);


							if (dijoy[i]->Acquire() != DI_OK) {
								debug << "Cannot get joystick " << i << "\n";
							}
						}
					}
				}
			}
		}
	}*/

	return true;
}

//-----------------------------------------------------------------------------
// Nom: Input::update()
// Desc: Met à jour les entrées
//-----------------------------------------------------------------------------

void Input::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){

		if (e.type == SDL_QUIT)
		{
			app_killed = true;
			//exit(0);
		}	

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym < 255)
			{
				buffer[e.key.keysym.sym] = 1;
			}
			else
				specialsbuffer[e.key.keysym.sym & 0xFFF] = 1;
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym < 255)
			{
				buffer[e.key.keysym.sym] = 0;
			}
			else
				specialsbuffer[e.key.keysym.sym & 0xFFF] = 0;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			js[e.jbutton.which].buttons[e.jbutton.button] = 1;
		}
		if (e.type == SDL_JOYBUTTONUP)
		{
			js[e.jbutton.which].buttons[e.jbutton.button] = 0;
		}
		if (e.type == SDL_JOYHATMOTION)
		{
			js[e.jhat.which].directions.down = false;
			js[e.jhat.which].directions.right = false;
			js[e.jhat.which].directions.left = false;
			js[e.jhat.which].directions.up = false;

			if (e.jhat.hat & SDL_HAT_UP)
				js[e.jhat.which].directions.up = true;
			if (e.jhat.hat & SDL_HAT_LEFT)
				js[e.jhat.which].directions.left = true;
			if (e.jhat.hat & SDL_HAT_RIGHT)
				js[e.jhat.which].directions.right = true;
			if (e.jhat.hat & SDL_HAT_DOWN)
				js[e.jhat.which].directions.down = true;
		}

		if (e.type == SDL_JOYAXISMOTION)
		{
		
			/* Horizontal movement */

			if (e.jaxis.axis == 0)
			{
				if (e.jaxis.value < -DEAD_ZONE)
				{
					js[e.jhat.which].directions.left = 1;
					js[e.jhat.which].directions.right = 0;
				}

				else if (e.jaxis.value > DEAD_ZONE)
				{
					js[e.jhat.which].directions.right = 1;
					js[e.jhat.which].directions.left = 0;
				}

				else
				{
					js[e.jhat.which].directions.left = 0;
					js[e.jhat.which].directions.right = 0;
				}
			}

			/* Vertical movement */

			if (e.jaxis.axis == 1)
			{
				if (e.jaxis.value < -DEAD_ZONE)
				{
					js[e.jhat.which].directions.up = 1;
					js[e.jhat.which].directions.down = 0;
				}

				else if (e.jaxis.value > DEAD_ZONE)
				{
					js[e.jhat.which].directions.down = 1;
					js[e.jhat.which].directions.up = 0;
				}

				else
				{
					js[e.jhat.which].directions.up = 0;
					js[e.jhat.which].directions.down = 0;
				}
			}
		}

	}
	/*if (dikeyb != NULL)
		dikeyb->GetDeviceState(sizeof(buffer), (void *)&buffer);

	for (int i = 0; i < n_joy; i++) {
		if (dijoy[i] != NULL) {
			dijoy[i]->Poll();
			dijoy[i]->GetDeviceState(sizeof(DIJOYSTATE), (void*) &js[i]);
		}
	}*/
}

//-----------------------------------------------------------------------------
// Nom: Input::waitKey()
// Desc: Attends que l'utilisateur tape une touche et renvoie sa valeur
//-----------------------------------------------------------------------------

unsigned int Input::waitKey()
{
	unsigned int	key = 0;

	while (1)
	{
		update();
		for (int i = 0; i < 255; i++)
		{
			if (buffer[i] != 0)
			{
				return i;
			}
		}
		for (int i = 0; i < 0xFFF; i++)
		{
			if (specialsbuffer[i] != 0)
			{
				return i | 0x40000000;
			}
		}

		for (int i = 0; i < 128; i++)
		{
			for (int k = 0; k < n_joy; k++)
			{
				if (js[k].buttons[i] == 1)
				{
					int k2 = (k + 1) * (1 << 10) + i;
					return k2;
				}
					//return (js[k].buttons[i] | (0x400));
			}
		}

		for (int k = 0; k < n_joy; k++)
		{
			if (js[k].directions.down)
			{
				int k2 = (k + 1) * (1 << 10) + JOY_DOWN;
				return k2;
			}
			if (js[k].directions.left)
			{
				int k2 = (k + 1) * (1 << 10) + JOY_LEFT;
				return k2;
			}
			if (js[k].directions.right)
			{
				int k2 = (k + 1) * (1 << 10) + JOY_RIGHT;
				return k2;
			}
			if (js[k].directions.up)
			{
				int k2 = (k + 1) * (1 << 10) + JOY_UP;
				return k2;
			}
			//return (js[k].buttons[i] | (0x400));
		}
	}
	/*unsigned int	i = 0;
	int				j;
	int				k;

	while (key == 0) {
		update();

		for (i = 0; i < 256; i++)
			if (scanKey(i))
				key = i;

		for (i = 0; i < (unsigned int)n_joy; i++) {
			k = (i + 1) * (1 << 10);

			for (j = 0; j < 14; j++)
				if (scanKey(k + j))
					key = k + j;
		}
	}*/

	return key;
}

//-----------------------------------------------------------------------------
// Nom: Input::waitClean()
// Desc: Attends qu'aucune touche ne soit enfoncée
//-----------------------------------------------------------------------------

void Input::waitClean()
{
	//Waits for all keys to be released?
	while (1)
	{
		bool j = false;
		update();
		for (int i = 0; i < 255; i++)
		{
			if (buffer[i] != 0)
			{
				j = true;
			}
		}
		for (int i = 0; i < 0xFFF; i++)
		{
			if (specialsbuffer[i] != 0)
			{
				j = true;
			}
		}

		for (int i = 0; i < 128; i++)
		{
			for (int k = 0; k < n_joy; k++)
			{
				if (js[k].buttons[i] == 1)
				{
					j = true;
				}
			}
		}

		for (int k = 0; k < n_joy; k++)
		{
			if (js[k].directions.down || js[k].directions.up || js[k].directions.left || js[k].directions.right)
			j = true;
		}

		if (!j)
			return;
	}
	/*unsigned int		i, j = 1;		// Bcoz si j = 0 alors on sort tout de suite!

	while (j) {
		update();
		j = 0;
		for (i = 0; i < 256; i++)
			j |= scanKey(i);

		for (i = 0; i < (unsigned int)n_joy; i++) {
			unsigned int k = (i + 1) * (1 << 10);

			for (int l = 0; l < 14; l++)
				j |= scanKey(k + l);
		}
	}*/

}

//-----------------------------------------------------------------------------
// Nom: Input::setAlias()
// Desc: Règle la valeur d'un alias
//-----------------------------------------------------------------------------
void Input::setAlias(int a, unsigned int val)
{
	aliastab[a] = val;
}

//-----------------------------------------------------------------------------
// Nom: Input::close()
// Desc: Ferme toutes les entrées
//-----------------------------------------------------------------------------

void Input::close()
{
	/*if (dikeyb != NULL) {
		dikeyb->Unacquire();
		dikeyb->Release();
		dikeyb = NULL;
	}

	if (dinput != NULL) {
		dinput->Release();
		dinput = NULL;
	}

	for (int i = 0; i < n_joy; i++) {
		if (dijoy[i] != NULL) {
			dijoy[i]->Release();
			dijoy[i] = NULL;
		}
	}

	n_joy = 0;*/
}


//-----------------------------------------------------------------------------

bool Input::anyKeyPressed()
{
	unsigned int	i;
	unsigned int	k;
	int key = 0;

	update();
	for (int i = 0; i < 255; i++)
	{
		if (buffer[i] != 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 0xFFF; i++)
	{
		if (specialsbuffer[i] != 0)
		{
			return true;
		}
	}

	for (int i = 0; i < 128; i++)
	{
		for (int k = 0; k < n_joy; k++)
		{
			if (js[k].buttons[i] == 1)
			{
				return true;
			}
		}
	}

	for (int k = 0; k < n_joy; k++)
	{
		if (js[k].directions.down || js[k].directions.up || js[k].directions.left || js[k].directions.right)
			return true;
	}

	return false;


	/*int j;

	update();

	for (i = 0; i < 256; i++)
		if (scanKey(i))
			key = i;

	for (i = 0; i < (unsigned int)n_joy; i++) {
		k = (i + 1) * (1 << 10);

		for (j = 0; j < 14; j++)
			if (scanKey(k + j))
				key = k + j;
	}*/
}

int Input::scanKey(unsigned int k) const
{
	/*int j = (k >> 10);

	if (j == 0)
		return buffer[k] & 0x80;

	j -= 1;

	if (j < 0 || j >= n_joy)
		return 0;
	else {
		int		z = 0;
		int		k2 = k & 0x3FF;

		switch (k2) {
			case JOY_UP:
				if (js[j].lY < -200) z = 1;
				break;

			case JOY_DOWN:
				if (js[j].lY > 200) z = 1;
				break;

			case JOY_LEFT:
				if (js[j].lX < -200) z = 1;
				break;

			case JOY_RIGHT:
				if (js[j].lX > 200) z = 1;
				break;

			default:
				z = (js[j].rgbButtons[k2] & 0x80);
				break;
		}

		return z;
	}*/
	if ((k >> 10) & 0xFF > 0)
	{
		/*
		REMEMBER
		That the joystick number starts from 1, but the array starts from 0
		*/
		int	j = k >> 10 & 0xFF;
		int b = k & 0xFF;

		if (b == JOY_UP)
			return js[j - 1].directions.up;
		if (b == JOY_DOWN)
			return js[j - 1].directions.down;
		if (b == JOY_RIGHT)
			return js[j - 1].directions.right;
		if (b == JOY_LEFT)
			return js[j - 1].directions.left;

		int r = js[j-1].buttons[b];
		return r;
	}
	else if (k<255)
		return buffer[k];
	else 
		return specialsbuffer[k & 0xFFF];

	return 0;
}

//-----------------------------------------------------------------------------
// Nom: Input::waitKey()
// Desc: Attends que l'utilisateur tape une touche et renvoie sa valeur
//-----------------------------------------------------------------------------

bool Input::reAcquire()
{
	/*if (dinput == NULL)
		return false;

	if (dikeyb != NULL)
		dikeyb->Acquire();

	for (int i = 0; i < MAX_JOY; i++)
		if (dijoy[i] != NULL)
			dijoy[i]->Acquire();*/

	return true;
}
