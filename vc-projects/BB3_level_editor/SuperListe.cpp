/******************************************************************
*
* 
*		----------------
*		   SuperListe.h
*		----------------
*			
*
*		Liste de pointeurs (void*) doublement chaînée
*		MAIS à sens unique
*
*
*		Prosper / LOADED -   V 1.0 - 28 Juin 2000
*
*
*
******************************************************************/

#ifndef NULL
	#define NULL	0
#endif

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "stdafx.h"


//-----------------------------------------------------------------------------

SuperListe::SuperListe() : tete(NULL), obs(NULL), nb_elem(0)
{
}


//-----------------------------------------------------------------------------

void SuperListe::start()
{
	obs = tete;
}

void SuperListe::suivant()
{
	if ( obs != NULL)
		obs = obs->next;
}


//-----------------------------------------------------------------------------

void SuperListe::ajoute( void * nouvo)
{
	CELLULE *	ptr;

	ptr = new CELLULE();

	ptr->data = nouvo;
	ptr->prev = NULL;
	ptr->next = tete;

	if ( tete != NULL)
		tete->prev = ptr;

	tete = ptr;

	nb_elem++;
}


//-----------------------------------------------------------------------------

void * SuperListe::supprimePorc()
{
	void *	dat;

	if ( obs == NULL)
		return NULL;


	if ( obs == tete)
	{
		CELLULE *	ptr;

		ptr = tete->next;

		dat = tete->data;
		delete tete;

		tete = obs = ptr;
		tete->prev = NULL;
	}
	else
	{
		CELLULE *	ptr_p;
		CELLULE *	ptr_n;

		ptr_p = obs->prev;
		ptr_n = obs->next;

		ptr_p->next = ptr_n;

		if ( ptr_n != NULL )
			ptr_n->prev = ptr_p;

		dat = obs->data;
		delete obs;

		obs = ptr_n;
	}

	return dat;
}

//-----------------------------------------------------------------------------

void SuperListe::supprime()
{
	if ( obs == NULL)
		return;


	if ( obs == tete)
	{
		CELLULE *	ptr;

		ptr = tete->next;

		delete tete->data;
		delete tete;

		tete = obs = ptr;

		if ( tete != NULL)
			tete->prev = NULL;
	}
	else
	{
		CELLULE *	ptr_p;
		CELLULE *	ptr_n;

		ptr_p = obs->prev;
		ptr_n = obs->next;

		ptr_p->next = ptr_n;

		if ( ptr_n != NULL )
			ptr_n->prev = ptr_p;

		delete obs->data;
		delete obs;

		obs = ptr_n;
	}
}



//-----------------------------------------------------------------------------

void * SuperListe::info()
{
	if ( obs != NULL)
		return ( obs->data );
	else
		return NULL;
}



//-----------------------------------------------------------------------------

bool SuperListe::fin()
{
	return ( obs == NULL);
}



//-----------------------------------------------------------------------------

int SuperListe::taille()
{
	return nb_elem;
}



//-----------------------------------------------------------------------------

void SuperListe::vide()
{
	CELLULE * ptr;

	ptr = tete;

	while( ptr != NULL)
	{
		tete = ptr->next;
		
		delete ptr->data;
		delete ptr;

		ptr = tete;
	}

	tete = NULL;
}



//-----------------------------------------------------------------------------

bool SuperListe::estVide()
{
	return (tete == NULL);
}


//-----------------------------------------------------------------------------

void (SuperListe::trier( int (*fonc)( const void *, const void*)))
{
	if ( tete == NULL || tete->next == NULL)
		return;

	CELLULE *	p1;
	CELLULE *	p2;

	p1 = tete;
	p2 = p1->next;


	while ( p2 != NULL)
	{
		if ( fonc( p1->data, p2->data) > 0)
		{
			if ( p1->prev != NULL)
				(p1->prev)->next = p2;
			else
				tete = p2;

			if ( p2->next != NULL)
				(p2->next)->prev = p1;

			p1->next = p2->next;
			p2->prev = p1->prev;

			p2->next = p1;
			p1->prev = p2;

			if ( p2->prev != NULL)
				p1 = p2->prev;
		}
		else
		{
			p1 = p2;
		}

		p2 = p1->next;
	}

}