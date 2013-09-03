#include "powerup.h"
#include <stdlib.h>
using namespace std;

PowerUp::PowerUp(string iS)
{
	QString filename = QString::fromStdString(iS);
	image.load(filename);
	rect = image.rect();

	int rLocation = rand() % 12 + 1;
	switch(rLocation)
	{
		case 1:
			rect.moveTo(rand() % 350 - 100, -200);
			direction = rand() % 2 + 1;
			break;
		case 2:
			rect.moveTo(rand() % 300 + 250, -200);
			direction = rand() % 3 + 1;
			break;
			case 3:
				rect.moveTo(rand() % 350 + 550, -200);
				direction = rand() % 2 + 2;
				break;
			case 4:
				rect.moveTo(900, rand() % 300 - 100);
				direction = rand() % 2 + 3;
				break;
			case 5:
				rect.moveTo(900, rand() % 300 + 200);
				direction = rand() % 3 + 3;
				break;
			case 6:
				rect.moveTo(900, rand() % 300 + 500);
				direction = rand() % 2 + 4;
				break;
			case 7:
				rect.moveTo(rand() % 350 + 550, 800);
				direction = rand() % 2 + 5;
				break;
			case 8:
				rect.moveTo(rand() % 300 + 250, 800);
				direction = rand() % 3 + 5;
				break;
			case 9:
				rect.moveTo(rand() % 350 - 100, 800);
				direction = rand() % 2 + 6;
				break;
			case 10:
				rect.moveTo(-100, rand() % 300 + 500);
				direction = rand() % 2 + 7;
				break;
			case 11:
				rect.moveTo(-100, rand() % 300 + 200);
				direction = rand() % 3 + 7; 
				if (direction == 9)
					direction = 1;
				break;
			case 12:
				rect.moveTo(-100, rand() % 300 - 100);
				direction = rand() % 2 + 8;
				if (direction == 9)
					direction = 1;
				break;
		}
}

PowerUp::~PowerUp()
{

}

PowerUp* PowerUp::create()
{
	int random = rand() % 6 + 1;
	PowerUp * ret = 0;
	switch(random)
	{
	case 1:
		ret = new ExtraLife("extralife.png");
		break;
	case 2: 
		ret = new LostLife("bitthedust.png");
		break;
	case 3:
		ret = new Bomb("hiroshima.png");
		break;
	case 4:
		ret = new ScoreBonus("madcheddar.png");
		break;
	case 5:
		ret = new ScoreMinus("badforthebankroll.png");
		break;
	case 6:
		ret = new RandomUp("johnnychan.png");
		break;
	}
	return ret;
}

QRect PowerUp::getRect()
{
	return rect;
}

QImage &PowerUp::getImage()
{
	return image;
}

void PowerUp::move()
{
	switch(direction)
	{
		//move down right
		case 1:
			rect.moveTo(rect.left() + 2, rect.top() + 2);
			break;
		//move down
		case 2:
			rect.moveTo(rect.left(), rect.top() + 2);
			break;
		//move down left
		case 3:
			rect.moveTo(rect.left() - 2, rect.top() + 2);
			break;
		//move left
		case 4:
			rect.moveTo(rect.left() - 2, rect.top());
			break;
		//move up left
		case 5:
			rect.moveTo(rect.left() - 2, rect.top() - 2);
			break;
		//move up
		case 6:
			rect.moveTo(rect.left(), rect.top() - 2);
			break;
		//move up right
		case 7:
			rect.moveTo(rect.left() + 2, rect.top() - 2);
			break;
		//move right
		case 8:
			rect.moveTo(rect.left() + 2, rect.top());
	}
}

bool PowerUp::offScreen()
{
	if (rect.left() < -200 || rect.right() > 1000)
		return true;
	else if (rect.top() < -200 || rect.bottom() > 1000)
		return true;
	else
		return false;
}

bool PowerUp::isActive()
{
	return active;
}

void PowerUp::setActive(bool d)
{
	active = d;
}

void ExtraLife::trigger(SpaceWars * game)
{
	game->setLives(game->getLives() + 1);
}

void ExtraLife::move()
{
	PowerUp::move();
}

void LostLife::trigger(SpaceWars* game)
{
	game->setLives(game->getLives() - 1);
	if (game->getLives() == 0)
		game->setReportInfo(TRUE);
}

void LostLife::move()
{
	PowerUp::move();
}

void Bomb::trigger(SpaceWars* game)
{
	game->setBombs(game->getBombs() + 1);
}

void Bomb::move()
{
	PowerUp::move();
}

void ScoreBonus::trigger(SpaceWars* game)
{
	game->setScore(game->getScore() + 20);
}

void ScoreBonus::move()
{
	PowerUp::move();
}

void ScoreMinus::trigger(SpaceWars* game)
{
	game->setScore(game->getScore() - 20);
}

void ScoreMinus::move()
{
	PowerUp::move();
}

void RandomUp::trigger(SpaceWars* game)
{
	int random = rand() % 5 + 1;
	switch(random)
	{
		case 1:
			game->setLives(game->getLives() + 1);
			break;
		case 2:
			game->setLives(game->getLives() - 1);
			break;
		case 3:
			game->setBombs(game->getBombs() + 1);
			break;
		case 4:
			game->setScore(game->getScore() - 20);
			break;
		case 5:
			game->setScore(game->getScore() + 20);
			break;
	}
}

void RandomUp::move()
{
	PowerUp::move();
}
