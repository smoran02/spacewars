
#include "spacewars.h"
#include "powerup.h"
#include <list>

void SpaceWars::checkBulletsCollision()
{
	list<Bullet*>::iterator i = bullets.begin();

	//iterate through list, checking for intersections between good and bad bullets
	while (i != bullets.end())
	{
		list<Bullet*>::iterator j = badguyBullets.begin();
		bool bullet_collision = false;

		while (j != badguyBullets.end() && i != bullets.end())
		{
			if ((*i)->rect.intersects((*j)->rect))
			{
				bullet_collision = true;
				list<Bullet*>::iterator del = i;
				i++;
				delete (*del);
				bullets.erase(del);
					
				list<Bullet*>::iterator delj = j;
				j++;
				delete (*delj);
				badguyBullets.erase(delj);
			}
			else
				j++;
		}

		

		if (!bullet_collision)
			i++;
	}
}


bool SpaceWars::checkGoodShipHit()
{
	bool hit = false;

	//iterate through list, checking to see if spaceship is hit
	list<Bullet*>::iterator j = badguyBullets.begin();

	while (j != badguyBullets.end())
	{
		if ((*j)->rect.intersects(spaceship->rect))
		{
			hit = TRUE;

			list<Bullet*>::iterator delj = j;
			j++;
			delete (*delj);
			badguyBullets.erase(delj);
		}
				
		else
			j++;
	}

	
	return hit;
}



bool SpaceWars::checkBadShipHit(Badguy* badguy)
{
	bool hit = false;

	//iterate through list, checking to see if badguys got hit
	list<Bullet*>::iterator i = bullets.begin();

	while (i != bullets.end())
	{
		if ((*i)->rect.intersects(badguy->rect))
		{	
			badguy->setHitCounter(badguy->getHitCounter() + 1);
			if (badguy->isBoss())
			{
				badguy->changeImage(badguy->getHitCounter());
			}
			if (badguy->getHitCounter() == badguy->getHitsToKill())
				hit = true;

			list<Bullet*>::iterator del = i;
			i++;
			delete (*del);
			bullets.erase(del);
		}

		else
			i++;
	}
	
	return hit;
}

//check to see if player spaceship collided with a badguy's ship
bool SpaceWars::checkSpaceshipCollision(Badguy* badguy)
{
	bool collision = false;

	if (badguy->rect.intersects(spaceship->rect))
		collision = true;

	return collision;
}

//check to see if player collides with a powerup
bool SpaceWars::checkPowerUpCollision()
{
	bool collision = false;

	if (powerUp->rect.intersects(spaceship->rect))
	{
		collision = true;
	
	}
	return collision;
}

//check to see which collisions occured and set appropriate flags
void SpaceWars::checkCollisions(bool& spaceshipHit)
{
	if (!bullets.empty() && !badguyBullets.empty())
		checkBulletsCollision();

	if (!badguyBullets.empty())
		spaceshipHit = checkGoodShipHit();

	if (!bullets.empty())
	{
		Node<Badguy*>* b = badguyList.getFirst();
		while (b != 0)
		{
			if (b->data->isActive())
				b->data->setBadguyHit(checkBadShipHit(b->data));
			b = b->next;
		}
	}

	Node<Badguy*>* b = badguyList.getFirst();
	while (b != 0)
	{
		if (b->data->isActive())
		{
			if (checkSpaceshipCollision(b->data))
			{
				spaceshipHit = true;
				b->data->setBadguyHit(true);
			}
		}
		b = b->next;
	}
}
