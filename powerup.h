#ifndef POWERUP_H
#define POWERUP_H

#include "spacewars.h"
#include <QRect>
#include <QImage>
#include <string>
using namespace std;


class PowerUp
{
	public:
		PowerUp(string iS);
		~PowerUp();

	public:
		QRect getRect();
		QImage &getImage();
		virtual void move();
		virtual void trigger(SpaceWars * game) = 0;
		static PowerUp* create();
		bool offScreen();
		bool isActive();
		void setActive(bool);
		void setImageString(string iS);
		QRect rect;
		QImage image;
		int direction;
		string imageString;

	private:
		bool active;

};


class ExtraLife : public PowerUp
{
	public:
		ExtraLife(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};

class LostLife : public PowerUp
{
	public:
		LostLife(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};

class Bomb : public PowerUp
{
	public:
		Bomb(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};

class ScoreBonus : public PowerUp
{
	public:
		ScoreBonus(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};

class ScoreMinus : public PowerUp
{
	public:
		ScoreMinus(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};

class RandomUp : public PowerUp
{
	public:
		RandomUp(string s) : PowerUp(s) { }
		void move();
		void trigger(SpaceWars* game);
};



#endif