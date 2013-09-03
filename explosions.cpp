#include "spacewars.h"
#include "powerup.h"
#include <QPainter>
#include <list>
#include <stdlib.h>
#include "linkedlist.h"


void SpaceWars::explodeSpaceship()
{
		//increment counting variable to control which explosion image is displayed
		spaceshipIndex++;

		//switch to display exploding images in correct order
		switch(spaceshipIndex)
		{
		case 2:
			{
			QPoint center = spaceship->rect.center();
			spaceship->image.load("explosiontwo.png");
			spaceship->rect = spaceship->image.rect();
			spaceship->rect.moveCenter(center);
			break;
			}

		case 3:
			{
			QPoint center = spaceship->rect.center();
			spaceship->image.load("explosionthree.png");
			spaceship->rect = spaceship->image.rect();
			spaceship->rect.moveCenter(center);
			break;
			}

		case 4:
			{
			QPoint center = spaceship->rect.center();
			spaceship->image.load("explosionfour.png");
			spaceship->rect = spaceship->image.rect();
			spaceship->rect.moveCenter(center);
			break;
			}

		case 5:
			{
			QPoint center = spaceship->rect.center();
			spaceship->image.load("explosionfour.png");
			spaceship->rect = spaceship->image.rect();
			spaceship->rect.moveCenter(center);
			break;
			}

		default:
			//kill timers
			killTimers();
			killTimer(timerSpaceshipHit);

			//spaceship is done exploding, set to false
			spaceshipExploding = FALSE;
			spaceshipExploded = TRUE;

			powerUp->setActive(FALSE);

			Node<Badguy*>* b = badguyList.getFirst();
			while (b != NULL)
			{
				if (b->data->getBadguyExploding())
					killTimer(b->data->getTimerBadguyHit());
				b->data->setActive(FALSE);
				b = b->next;
			}

			bullets.clear();
			badguyBullets.clear();

			//set flag to go to lost a life screen
			//subtract a life
			reportInfo = true;
			lives--;
			
		}
}


void SpaceWars::explodeBadguy(Badguy* b)
{
	//increment variable to control which explosion image is displayed
	b->setExplosionIndex(b->getExplosionIndex() + 1);
	
	//switch to display exploding images in correct order
	switch(b->getExplosionIndex())
	{
	case 2:
		{
		QPoint center = b->rect.center();
		b->image.load("explosiontwo.png");
		b->rect = b->image.rect();
		b->rect.moveCenter(center);
		break;
		}

	case 3:
		{
		QPoint center = b->rect.center();
		b->image.load("explosionthree.png");
		b->rect = b->image.rect();
		b->rect.moveCenter(center);
		break;
		}

	case 4:
		{
		QPoint center = b->rect.center();
		b->image.load("explosionfour.png");
		b->rect = b->image.rect();
		b->rect.moveCenter(center);
		break;
		}

	case 5:
		{
		QPoint center = b->rect.center();
		b->image.load("explosionfour.png");
		b->rect = b->image.rect();
		b->rect.moveCenter(center);
		break;
		}

	default:
		killTimer(b->getTimerBadguyHit());
		b->setBadguyExploding(FALSE);
		b->setActive(FALSE);
		
		if (b->isBoss())
		{
			score +=50;
			level++;
			levelChange = TRUE;
			killTimers();
			deleteBadGuys();
			badguyBullets.clear();
			bullets.clear();
			spaceship->resetState();
		}
		else
		{
			//add score for destroying a badguy
			score += 5;
		}
		
		//set flag, badguy is now exploded
		b->setExploded(TRUE);

	}
}