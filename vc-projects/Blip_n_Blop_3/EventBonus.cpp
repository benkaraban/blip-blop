
#include "eventbonus.h"
#include "bonuspm.h"
#include "bonusfusil.h"
#include "bonuslaser.h"
#include "bonusbeer.h"
#include "bonusinvincible.h"
#include "bonustonneau.h"
#include "bonusvache.h"
#include "bonuslf.h"

void EventBonus::doEvent()
{
	Bonus * bonus;

	switch (type) {
		case BPM:
			bonus = new BonusPM();
			break;

		case BFUSIL:
			bonus = new BonusFusil();
			break;

		case BLF:
			bonus = new BonusLF();
			break;

		case BLASER:
			bonus = new BonusLaser();
			break;

		case BBEER:
			bonus = new BonusBeer();
			break;

		case BINV:
			bonus = new BonusInvincible();
			break;

		case BTONNO:
			bonus = new BonusTonneau();
			break;

		case BCOW:
			bonus = new BonusVache();
			break;

		default:
			bonus = NULL;
			debug << "Unknown bonus type\n";
			break;
	}

	if (bonus != NULL) {
		bonus->x = x;
		bonus->y = y;

		list_bonus.ajoute((void*) bonus);
	}
}