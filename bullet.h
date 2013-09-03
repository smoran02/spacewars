#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QImage>
#include "spaceship.h"

class Bullet
{

    public:
	Bullet();
	~Bullet();

    public:
	QRect getRect();
	QImage &getImage();
	virtual void move() = 0;
	bool offScreen();
	QRect rect;
	QImage image;
};

class GoodBullet : public Bullet
{
	public:
		GoodBullet(int, int);
		~GoodBullet();
		void move();
};

class BadBullet : public Bullet
{
	public:
		BadBullet(int, int);
		~BadBullet();
		void move();
};

class BossBullet1 : public Bullet
{
	public:
		BossBullet1(int, int);
		~BossBullet1();
		void move();
};

class BossBullet2 : public Bullet
{
	public:
		BossBullet2(int, int);
		~BossBullet2();
		void move();
};

class BossBullet3 : public Bullet
{
	public:
		BossBullet3(int, int);
		~BossBullet3();
		void move();
};

class BossBullet4 : public Bullet
{
	public:
		BossBullet4(int, int);
		~BossBullet4();
		void move();
};

class BossBullet5 : public Bullet
{
	public:
		BossBullet5(int, int);
		~BossBullet5();
		void move();
};

class AimBullet : public Bullet
{
	public:
		AimBullet(int, int, Spaceship*);
		~AimBullet();
		void move();

	private:
		int aimX, aimY;
};


#endif