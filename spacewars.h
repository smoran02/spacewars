#ifndef SPACEWARS_H
#define SPACEWARS_H

#include "bullet.h"
#include "spaceship.h"
#include "badguy.h"
#include "linkedlist.h"
#include <QWidget>
#include <QKeyEvent>
#include <list>
using namespace std;

class PowerUp;

class SpaceWars : public QWidget
{
   Q_OBJECT

   public:
	SpaceWars(QWidget *parent = 0);
	~SpaceWars();

   public:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
	void keyPressEvent(QKeyEvent *event);
	
	void moveGoodBullet();
	void moveBadBullet();
	void moveBossBullet();
	void moveBullets();

	void explodeBomb();

	void checkBulletsCollision();
	bool checkGoodShipHit();
	bool checkBadShipHit(Badguy* b);
	bool checkSpaceshipCollision(Badguy* b);
	bool checkPowerUpCollision();
	void checkPowerUp();
	void checkCollisions(bool& spaceshipHit);

	void explodeBadguy(Badguy* b);
	void explodeSpaceship();

	bool checkBadguyTimers(int, Badguy* &b);
	void killTimers();
	void startTimers();

	void makeBadGuys();
	void deleteBadGuys();
	void makeBoss();

	void startGame();
	void pauseGame();
	void restartGame();
 	void victory();
	void continueGame();

	void setLives(int l);
	int getLives();
	void setScore(int s);
	int getScore();
	void setBombs(int b);
	int getBombs();
	void setReportInfo(bool);
	int getLevel();

	void deleteBullets();
	void deleteBadBullets();

	int updateScore(int);

   private:
	Spaceship *spaceship;
	int timerId;
	int timerBadguy;
	int timerBadguyBullet;
	int timerBadguyMove;
	int timerSpaceshipHit;
	int timerPowerUp;
	int timerPowerUpMove;
	int timerBoss;
	int timerGoodBullets;
	int spaceshipIndex;
	int previousBadguy;
	int badguyType;
	int bombs;
	int lives;
	int score;
	int level;
	int highScore;
	unsigned int bulletCounter;
	unsigned int lastShotTime;
	bool spaceshipExploding;
	bool spaceshipExploded;
	bool gameOver;
	bool gameWon;
	bool gameStarted;
	bool paused;
	bool reportInfo;
	bool gameStarting;
	bool levelChange;
	bool displayUnloggedMenu;
	bool displayLoggedMenu;

	PowerUp* powerUp;
	list<Bullet*> bullets;
	list<Bullet*> badguyBullets;
	Badguy* badguys[3];
	LinkedList<Badguy*> badguyList;

};

#endif