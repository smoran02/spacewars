#ifndef BADGUY_H
#define BADGUY_H

#include <QRect>
#include <QImage>
#include "spaceship.h"

class Badguy
{

   public:
	Badguy();	
	~Badguy();

   public:
	bool offScreen();
	static Badguy* create();
	static Badguy* create(int);
	virtual void move(Spaceship* spaceship) = 0;
	virtual void setFirstLocation() = 0;
	virtual void setLocation(int, int) = 0;
	virtual void changeImage(int);
	void setLocation();
	void setActive(bool);
	bool isActive();
	bool isExploded();
	bool isBoss();
	void setLevelBoss(bool);
	void setExploded(bool);
	void setBadguyHit(bool);
	bool getBadguyHit();
	void setBadguyExploding(bool);
	bool getBadguyExploding();
	void setTimerBadguyHit(int);
	int getTimerBadguyHit();
	void setExplosionIndex(int);
	int getExplosionIndex();
	void setHitCounter(int);
	int getHitCounter();
	void setHitsToKill(int);
	int getHitsToKill();
	void setDirection(int);
	int getDirection();
	void setType(int);
	int getType();
	void setX(int);
	int getX();
	void setY(int);
	int getY();
	QRect getRect();
	QImage &getImage();
	QRect rect;
	QImage image;

   private:
	bool active;
	bool badguyExploded;
	bool badguyHit;
	bool levelBoss;
	int timerBadguyHit;
	int explosionIndex;
	int hitCounter;
	int hitsToKill;
	int direction;
	int x, y;
	int type;
	bool badguyExploding;
};


class B1 : public Badguy
{
	public:
		B1();
		~B1();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
};

class B2 : public Badguy
{
	public:
		B2();
		~B2();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
};

class B3 : public Badguy
{
	public:
		B3();
		~B3();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
};

class B4 : public Badguy
{
	public:
		B4();
		~B4();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
};

class B5 : public Badguy
{
	public:
		B5();
		~B5();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
};

class Boss : public Badguy
{
	public:
		Boss();
		~Boss();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
		void changeImage(int);

	private:
		int moveCount;

};

class Boss2 : public Badguy
{
	public:
		Boss2();
		~Boss2();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
		void changeImage(int);

	private:
		int moveCount;

};

class Boss3 : public Badguy
{
	public:
		Boss3();
		~Boss3();
		void move(Spaceship* spaceship);
		void setFirstLocation();
		void setLocation(int, int);
		void changeImage(int);

	private:
		int moveCount;

};

#endif