#include "bullet.h"

Bullet::Bullet()
{
	
}

Bullet::~Bullet()
{

}

QRect Bullet::getRect()
{
	return rect;
}

QImage &Bullet::getImage()
{
	return image;
}

bool Bullet::offScreen()
{
	//returns true if the bullet is offscreen
	if (rect.bottom() <= 0 || rect.top() >= 800)
		return true;
	else
		return false;
}

GoodBullet::GoodBullet(int x, int y)
{
	//load the image for the spaceship bullet
	image.load("goodbullet.png");
	
	//set the bullet rectangle above the spaceship
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y);
	rect.setTop(y - 20);
	rect.setHeight(20);
	rect.setWidth(4);
}

void GoodBullet::move()
{
	//move the bullet up the screen
	//used for the player controlled spaceship
	rect.moveTo(rect.left(), (rect.top() - 8));
}

BadBullet::BadBullet(int x, int y)
{
	//load the image for the badguy bullet
	image.load("bullet.png");
	
	//set the bullet rectangle below the badguy
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(4);
}

void BadBullet::move()
{
	//move the bullet down the screen
	//used for the badguys
	rect.moveTo(rect.left(), (rect.top() + 4));
}

BossBullet1::BossBullet1(int x, int y)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
}

void BossBullet1::move()
{
	rect.moveTo(rect.left() - 4, rect.top() + 4);
}

BossBullet2::BossBullet2(int x, int y)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
}

void BossBullet2::move()
{
	//move the boss bullet in the correct direction
	rect.moveTo(rect.left(), rect.top() + 4);
}

BossBullet3::BossBullet3(int x, int y)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
}

void BossBullet3::move()
{
	//move the bullet in the correct direction
	rect.moveTo(rect.left() + 4, rect.top() + 4);
}

BossBullet4::BossBullet4(int x, int y)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
}

void BossBullet4::move()
{
	//move the boss bullet in the correct direction
	rect.moveTo(rect.left() + 2, rect.top() + 4);
}

BossBullet5::BossBullet5(int x, int y)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
}

void BossBullet5::move()
{
	//move the boss bullet in the correct direction
	rect.moveTo(rect.left() - 2, rect.top() + 4);
}

AimBullet::AimBullet(int x, int y, Spaceship* spaceship)
{
	//load the image for the boss bullet
	image.load("bossbullet.png");

	//set the bullet rectangles below the boss
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(20);
	QPoint center = spaceship->rect.center();
	aimX = center.x();
	aimY = center.y();
}

AimBullet::~AimBullet()
{

}

void AimBullet::move()
{
	//move the bullet to the players location at the time of the bullet being shot
	QPoint bulletCenter = this->rect.center();
	int x = bulletCenter.x();
	int y = bulletCenter.y();

	if (x < aimX && y < aimY)
	{
		rect.moveTo(rect.left() + 1, rect.top() + 1);
	}
	else if (x > aimX && y < aimY)
	{
		rect.moveTo(rect.left() - 1, rect.top() + 1);
	}
	else if (x < aimX && y > aimY)
	{
		rect.moveTo(rect.left() + 1, rect.top() - 1);
	}
	else if (x > aimX && y > aimY)
	{
		rect.moveTo(rect.left() - 1, rect.top() + 1);
	}
	else if (x > aimX && y == aimY)
	{
		rect.moveTo(rect.left() - 1, rect.top());
	}
	else if (x < aimX && y == aimY)
	{
		rect.moveTo(rect.left() - 1, rect.top());
	}
	else if (x == aimX && y > aimY)
	{
		rect.moveTo(rect.left(), rect.top() - 1);
	}
	else if (x == aimX && y < aimY)
	{
		rect.moveTo(rect.left(), rect.top() + 1);
	}

	if ((x == aimX && y == aimY))
		delete this;
}