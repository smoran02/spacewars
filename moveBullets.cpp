
#include "spacewars.h"

#include <list>


void SpaceWars::moveGoodBullet()
{
	//increment through list, moving or deleting bullets
	list<Bullet*>::iterator i = bullets.begin();

	while (i != bullets.end())
	{
		(*i)->move();

		//delete any bullets that are out of bounds
		if ((*i)->offScreen())
		{
			list<Bullet*>::iterator del = i;
			i++;
			bullets.erase(del);
		}
		else
		{
			i++;
		}
	}
}


void SpaceWars::moveBadBullet()
{
	//incremement through list, moving or deleting bullets
	list<Bullet*>::iterator j = badguyBullets.begin();

	while (j != badguyBullets.end())
	{
		(*j)->move();

		//delete any bullets that are out of bounds
		if ((*j)->offScreen())
		{
			list<Bullet*>::iterator del = j;
			j++;
			badguyBullets.erase(del);
		}
		else
		{
			j++;
		}
	}
}

void SpaceWars::moveBullets()
{
	//move any spaceship bullets that exist
	if (!bullets.empty())
		moveGoodBullet();

	//move any badguy bullets that exist
	if (!badguyBullets.empty())
		moveBadBullet();
}
