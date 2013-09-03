#include "badguy.h"
#include <stdlib.h>

Badguy::Badguy()
{
	//set the exploded flag to false for each badguy that is created
	setExploded(FALSE);
	setBadguyHit(FALSE);
	setBadguyExploding(FALSE);
	hitsToKill = 1;
	hitCounter = 0;
	levelBoss = FALSE;
}

Badguy::~Badguy()
{

}

Badguy* Badguy::create()
{
	//switch to randomly select the badguy to create
	int random = rand() % 5 + 1;
	Badguy* badguy = 0;
	switch(random)
	{
		case 1:
		{
			badguy = new B1();
			badguy->setType(1);
			break;
		}
		case 2:
		{
			badguy = new B2();
			badguy->setType(2);
			break;
		}
		case 3:
		{
			badguy = new B3();
			badguy->setType(3);
			break;
		}
		case 4:
		{
			badguy = new B4();
			badguy->setType(4);
			break;
		}
		case 5:
		{
			badguy = new B5();
			badguy->setType(5);
			break;
		}
	}	
	return badguy;
}

Badguy* Badguy::create(int t)
{
	//switch based on first badguy type to create remaining badguys
	Badguy* badguy = 0;
	switch(t)
	{
		case 1:
		{
			badguy = new B1();
			badguy->setType(1);
			break;
		}
		case 2:
		{
			badguy = new B2();
			badguy->setType(2);
			break;
		}
		case 3:
		{
			badguy = new B3();
			badguy->setType(3);
			break;
		}
		case 4:
		{
			badguy = new B4();
			badguy->setType(4);
			break;
		}
		case 5:
		{
			badguy = new B5();
			badguy->setType(5);
			break;
		}
	}
	return badguy;
}

void Badguy::changeImage(int timesHit)
{

}

void Badguy::setLocation()
{
	//set default location
	rect.moveTo(335, -200);
}

void Badguy::setExploded(bool b)
{
	//set the exploded flag
	badguyExploded = b;
}

bool Badguy::isExploded()
{
	//return the exploded flag
	return badguyExploded;
}

bool Badguy::offScreen()
{
	//returns true if the badguy is out of bounds
	//otherwise return false
	if (rect.bottom() < -500)
		return true;
	else if (rect.top() > 1300)
		return true;
	else if (rect.left() < -500)
		return true;
	else if (rect.right() > 1200)
		return true;
	else
		return false;
}

void Badguy::setActive(bool d)
{
	//set the badguy to active
	active = d;
}

bool Badguy::isActive()
{
	//return whether or not the badguy is active
	return active;
}

//lots of getters and setters
bool Badguy::isBoss()
{
	return levelBoss;
}

void Badguy::setBadguyHit(bool bgH)
{
	badguyHit = bgH;
}

bool Badguy::getBadguyHit()
{
	return badguyHit;
}

void Badguy::setBadguyExploding(bool bE)
{
	badguyExploding = bE;
}

bool Badguy::getBadguyExploding()
{
	return badguyExploding;
}

void Badguy::setTimerBadguyHit(int timer)
{
	timerBadguyHit = timer;
}

int Badguy::getTimerBadguyHit()
{
	return timerBadguyHit;
}

void Badguy::setExplosionIndex(int eI)
{
	explosionIndex = eI;
}

int Badguy::getExplosionIndex()
{
	return explosionIndex;
}

void Badguy::setHitCounter(int hC)
{
	hitCounter = hC;
}

int Badguy::getHitCounter()
{
	return hitCounter;
}

void Badguy::setHitsToKill(int hTK)
{
	hitsToKill = hTK;
}

int Badguy::getHitsToKill()
{
	return hitsToKill;
}

void Badguy::setLevelBoss(bool lB)
{
	levelBoss = lB;
}

void Badguy::setDirection(int d)
{
	direction = d;
}

int Badguy::getDirection()
{
	return direction;
}

void Badguy::setX(int fX)
{
	x = fX;
}

int Badguy::getX()
{
	return x;
}

void Badguy::setY(int fY)
{
	y = fY;
}

int Badguy::getY()
{
	return y;
}

void Badguy::setType(int t)
{
	type = t;
}

int Badguy::getType()
{
	return type;
}

QRect Badguy::getRect()
{
	return rect;
}

QImage &Badguy::getImage()
{
	return image;
}

B1::B1()
{
	//load the correct image for badguy type one
	image.load("badguy.png");
	
	rect = image.rect();

}

void B1::setFirstLocation()
{
	//set the first spawn location
	int randomX = rand() % 100 + 200;
	int randomY = rand() % 200 - 200;
	rect.moveTo(randomX, randomY);
	setX(randomX);
	setY(randomY);
}

void B1::setLocation(int x, int y)
{
	//set remaining spawn locations based off the previous one
	rect.moveTo(x + 150, y);
	setX(x + 150);
	setY(y);
}

void B1::move(Spaceship* spaceship)
{
	//move the badguy straight down the screen
	rect.moveTo(rect.left(), rect.top() + 2);
}

B2::B2()
{
	//load the correct image for badguy type two
	image.load("badguy2.png");
	
	rect = image.rect();
}

void B2::setFirstLocation()
{
	//set first spawn
	int random = rand() % 300 + 200;
	int r = rand() % 2 + 1;
	if (r == 1)
	{
		rect.moveTo(-100, random);
		setX(-100);
		setY(random);
		setDirection(1);
	}
	else
	{
		rect.moveTo(800, random);
		setX(800);
		setY(random);
		setDirection(2);
	}
}

void B2::setLocation(int x, int y)
{
	//set all other spawns
		if (x > 500)
		{
			rect.moveTo(x + 100, y - 100);
			setX(x + 100);
			setY(y - 100);
			setDirection(2);
		}
		else 
		{
			rect.moveTo(x - 100, y - 100);
			setX(x - 100);
			setY(y - 100);
			setDirection(1);
		}
}

void B2::move(Spaceship* spaceship)
{
	//move the badguy to the right
	if (getDirection() == 1)
		rect.moveTo(rect.left() + 2, (rect.top()));
	//move the badguy to the left
	else
		rect.moveTo(rect.left() - 2, (rect.top()));
}

B3::B3()
{
	//load the correct image for badguy type three
	image.load("badguy3.png");
	
	rect = image.rect();
}

void B3::setFirstLocation()
{
	//set first spawn
	int randomX, randomY;
	int r = rand() % 2 + 1;
	if (r == 1)
	{
		randomX = rand() % 200 + 600;
		randomY = rand() % 200 - 200;
		rect.moveTo(randomX, randomY);
		setDirection(1);
		setX(randomX);
		setY(randomY);
	}
	else
	{
		randomX = rand() % 200 - 100;
		randomY = rand() % 200 - 200;
		rect.moveTo(randomX, randomY);
		setDirection(2);
		setX(randomX);
		setY(randomY);
	}
}

void B3::setLocation(int x, int y)
{
	//set all other spawns
	if (x < 400)
	{
		rect.moveTo(x - 100, y - 100);
		setX(x - 100);
		setY(y - 100);
		setDirection(2);
	}
	else
	{
		rect.moveTo(x + 100, y - 100);
		setX(x + 100);
		setY(y - 100);
		setDirection(1);
	}
}

void B3::move(Spaceship* spaceship)
{
	//move the badguy diagonally down and left
	if (getDirection() == 1)
		rect.moveTo(rect.left() - 2, (rect.top() + 2));
	//move the badguy diagonally down and right
	else
		rect.moveTo(rect.left() + 2, (rect.top() + 2));
}

B4::B4()
{
	//load image and set rect
	image.load("badguy4.png");
	rect = image.rect();
}

void B4::setFirstLocation()
{
	//set first location
	int rLocation = rand() % 12 + 1;
	switch(rLocation)
	{
		case 1:
			rect.moveTo(rand() % 350 - 100, -200);
			break;
		case 2:
			rect.moveTo(rand() % 300 + 250, -200);
			break;
		case 3:
			rect.moveTo(rand() % 350 + 550, -200);
			break;
		case 4:
			rect.moveTo(900, rand() % 300 - 100);
			break;
		case 5:
			rect.moveTo(900, rand() % 300 + 200);
			break;
		case 6:
			rect.moveTo(900, rand() % 300 + 500);
			break;
		case 7:
			rect.moveTo(rand() % 350 + 550, 800);
			break;
		case 8:
			rect.moveTo(rand() % 300 + 250, 800);
			break;
		case 9:
			rect.moveTo(rand() % 350 - 100, 800);
			break;
		case 10:
			rect.moveTo(-100, rand() % 300 + 500);
			break;
		case 11:
			rect.moveTo(-100, rand() % 300 + 200);
			break;
		case 12:
			rect.moveTo(-100, rand() % 300 - 100);
			break;
	}
	setX(rect.left());
	setY(rect.top());
}

void B4::setLocation(int x, int y)
{
	//set other locations
	rect.moveTo(getX(), getY());
	setX(x);
	setY(y);
}

void B4::move(Spaceship* spaceship)
{
	//move to follow the player's spaceship
	QPoint center = spaceship->rect.center();
	QPoint badguyCenter = rect.center();
	if (badguyCenter.x() < center.x() && badguyCenter.y() < center.y())
	{
		rect.moveTo(rect.left() + 2, rect.top() + 2);
	}
	else if (badguyCenter.x() < center.x() && badguyCenter.y() > center.y())
	{
		rect.moveTo(rect.left() + 2, rect.top() - 2);
	}
	else if (badguyCenter.x() < center.x() && badguyCenter.y() == center.y())
	{
		rect.moveTo(rect.left() + 2, rect.top());
	}
	else if (badguyCenter.x() > center.x() && badguyCenter.y() > center.y())
	{
		rect.moveTo(rect.left() - 2, rect.top() - 2);
	}
	else if (badguyCenter.x() > center.x() && badguyCenter.y() < center.y())
	{
		rect.moveTo(rect.left() - 2, rect.top() + 2);
	}
	else if (badguyCenter.x() > center.x() && badguyCenter.y() == badguyCenter.y())
	{
		rect.moveTo(rect.left() - 2, rect.top());
	}
	else if (badguyCenter.x() == center.x() && badguyCenter.y() > center.y())
	{
		rect.moveTo(rect.left(), rect.top() - 2);
	}
	else
	{
		rect.moveTo(rect.left(), rect.top() + 2);
	}
}

B5::B5()
{
	//load image, set rect, set hits to kill to 2 to make this badguy take 2 hits to kill
	image.load("badguy5.png");
	rect = image.rect();
	setHitsToKill(2);
}

void B5::setFirstLocation()
{
	//set initial location
	int randomX, randomY;
	int random = rand() % 300 + 200;
	int r = rand() % 4 + 1;
	if (r == 1)
	{
		randomX = rand() % 200 + 600;
		randomY = rand() % 200 - 300;
		rect.moveTo(randomX, randomY);
		setDirection(1);
		setX(randomX);
		setY(randomY);
	}
	else if (r == 2)
	{
		randomX = rand() % 200 - 100;
		randomY = rand() % 200 - 300;
		rect.moveTo(randomX, randomY);
		setDirection(2);
		setX(randomX);
		setY(randomY);
	}

	else if (r == 3)
	{
		rect.moveTo(-100, random);
		setX(-100);
		setY(random);
		setDirection(3);
	}
	else
	{
		rect.moveTo(800, random);
		setX(800);
		setY(random);
		setDirection(4);
	}
}

void B5::setLocation(int x, int y)
{
	//set remaining locations
	if (x < 300 && y < 0)
	{
		rect.moveTo(x - 100, y - 100);
		setX(x - 100);
		setY(y - 100);
		setDirection(2);
	}
	else if ( x > 400 && y < 0)
	{
		rect.moveTo(x + 100, y - 100);
		setX(x + 100);
		setY(y - 100);
		setDirection(1);
	}
	else if (x > 500 && y > 200)
	{
		rect.moveTo(x + 100, y - 100);
		setX(x + 100);
		setY(y - 100);
		setDirection(4);
	}
	else 
	{
		rect.moveTo(x - 100, y - 100);
		setX(x - 100);
		setY(y - 100);
		setDirection(3);
	}
}

void B5::move(Spaceship* spaceship)
{
	//move the badguy diagonally down and left
	if (getDirection() == 1)
		rect.moveTo(rect.left() - 2, (rect.top() + 2));
	//move the badguy diagonally down and right
	else if (getDirection() == 2)
		rect.moveTo(rect.left() + 2, (rect.top() + 2));
	//move the badguy to the right
	else if (getDirection() == 3)
		rect.moveTo(rect.left() + 2, (rect.top()));
	//move the badguy to the left
	else
		rect.moveTo(rect.left() - 2, (rect.top()));

}

Boss::Boss()
{
	//load boss image, set hits to kill to 5
	image.load("boss15.png");
	rect = image.rect();
	setHitsToKill(5);
	setLevelBoss(TRUE);
	moveCount = 0;
}

Boss::~Boss()
{
	
}

void Boss::move(Spaceship* spaceship)
{
	//move the boss in a bosslike pattern
	if (rect.top() < 100)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if (rect.left() > 100 && moveCount == 0)
	{
		rect.moveTo(rect.left() - 2, rect.top());
		if (rect.left() == 101)
			moveCount = 1;
	}
	else if (rect.left() < 570 && moveCount == 1)
	{
		rect.moveTo(rect.left() + 2, rect.top());
		if (rect.left() == 569)
			moveCount = 0;
	}

}

void Boss::changeImage(int timesHit)
{
	//change the image of the boss based on the number of times it has been hit to simulate health bars
	switch(timesHit)
	{
		case 1: 
			image.load("boss14.png");
			break;
		case 2:
			image.load("boss13.png");
			break;
		case 3:
			image.load("boss12.png");
			break;
		case 4:
			image.load("boss11.png");
			break;
	}
}

//dont need these, but wanted to have pure virtual functions in class
void Boss::setFirstLocation()
{

}

void Boss::setLocation(int x, int y)
{

}

Boss2::Boss2()
{
	image.load("boss2.png");
	rect = image.rect();
	setHitsToKill(10);
	setLevelBoss(TRUE);
	moveCount = 0;
}

Boss2::~Boss2()
{
	
}

void Boss2::move(Spaceship* spaceship)
{
	if (rect.top() < 100)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if (rect.left() > 100 && moveCount == 0)
	{
		rect.moveTo(rect.left() - 2, rect.top());
		if (rect.left() == 101)
			moveCount = 1;
	}
	else if (rect.left() < 570 && moveCount == 1)
	{
		rect.moveTo(rect.left() + 2, rect.top());
		if (rect.left() == 569)
			moveCount = 0;
	}

}

void Boss2::changeImage(int timesHit)
{
	switch(timesHit)
	{
		case 1: 
			image.load("boss29.png");
			break;
		case 2:
			image.load("boss28.png");
			break;
		case 3:
			image.load("boss27.png");
			break;
		case 4:
			image.load("boss26.png");
			break;
		case 5:
			image.load("boss25.png");
			break;
		case 6:
			image.load("boss24.png");
			break;
		case 7:
			image.load("boss23.png");
			break;
		case 8:
			image.load("boss22.png");
			break;
		case 9:
			image.load("boss21.png");
			break;
	}
}

void Boss2::setFirstLocation()
{

}

void Boss2::setLocation(int x, int y)
{

}

Boss3::Boss3()
{
	image.load("boss316.png");
	rect = image.rect();
	setHitsToKill(16);
	setLevelBoss(TRUE);
	moveCount = 0;
}

Boss3::~Boss3()
{
	
}

void Boss3::move(Spaceship* spaceship)
{
	if (rect.top() < 100)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if (rect.left() > 100 && moveCount == 0)
	{
		rect.moveTo(rect.left() - 2, rect.top());
		if (rect.left() == 101)
			moveCount = 1;
	}
	else if (rect.left() < 570 && moveCount == 1)
	{
		rect.moveTo(rect.left() + 2, rect.top());
		if (rect.left() == 569)
			moveCount = 0;
	}

}

void Boss3::changeImage(int timesHit)
{
	switch(timesHit)
	{
		case 1: 
			image.load("boss315.png");
			break;
		case 2:
			image.load("boss314.png");
			break;
		case 3:
			image.load("boss313.png");
			break;
		case 4:
			image.load("boss312.png");
			break;
		case 5:
			image.load("boss311.png");
			break;
		case 6:
			image.load("boss310.png");
			break;
		case 7:
			image.load("boss39.png");
			break;
		case 8:
			image.load("boss38.png");
			break;
		case 9:
			image.load("boss37.png");
			break;
		case 10:
			image.load("boss36.png");
			break;
		case 11:
			image.load("boss35.png");
			break;
		case 12:
			image.load("boss34.png");
			break;
		case 13:
			image.load("boss33.png");
			break;
		case 14:
			image.load("boss32.png");
			break;
		case 15:
			image.load("boss31.png");
			break;
	}
}

void Boss3::setFirstLocation()
{

}

void Boss3::setLocation(int x, int y)
{

}