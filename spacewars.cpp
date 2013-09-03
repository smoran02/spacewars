#include "spacewars.h"
#include <QPainter>
#include <QApplication>
#include <list>
#include <stdlib.h>
#include "powerup.h"
#include "database.h"

SpaceWars::SpaceWars(QWidget *parent)
    : QWidget(parent)
{

  //set the initial flag conditions
  gameOver = FALSE;
  gameWon = FALSE;
  paused = FALSE;
  gameStarted = FALSE;
  reportInfo = FALSE;
  gameStarting = TRUE;
  levelChange = FALSE;
  displayUnloggedMenu = TRUE;
  level = 1;
  highScore = 0;
  score = 0;

  //create a spaceship object
  spaceship = new Spaceship();
  
  //create the initial 3 badguys
  makeBadGuys();
}

SpaceWars::~SpaceWars()
{
	//deallocate memory for the spaceship
	delete spaceship;
}

void SpaceWars::makeBadGuys()
{
	//pick a random number of badguys to spawn
	int numberBadGuys = rand() % 2 + 3;

	//create variables to control the spawning of all badguys after the initial one
	int nextX = 0, nextY = 0;
	int lastType;

	//create the appropriate number of badguys
	for (int i=0; i < numberBadGuys; i++)
	{
		Badguy* badguy = NULL;

		//create the initial badguy
		if (i == 0)
		{
			badguy = Badguy::create();
			lastType = badguy->getType();
			badguy->setActive(FALSE);
		}

		//create all additional badguys based on the location and type of the first one
		else
		{
			badguy = Badguy::create(lastType);
			badguy->setActive(FALSE);
		}

		//set the location of all badguys
		if (i == 0)
			badguy->setFirstLocation();
		else
			badguy->setLocation(nextX, nextY);

		//add all badguys to the list
		badguyList.push_front(badguy);
		nextX = badguy->getX();
		nextY = badguy->getY();
	}

	lastType = 0;
	
	//create a power up
	powerUp = PowerUp::create();
	powerUp->setActive(TRUE);
}

void SpaceWars::makeBoss()
{
	//create the boss
	Badguy* boss;
	if (level == 1)
		boss = new Boss();
	else if (level == 2)
		boss = new Boss2();
	else
		boss = new Boss3();

	boss->setActive(TRUE);

	boss->setLocation();

	//add the boss to the list
	badguyList.push_front(boss);
	boss->setBadguyExploding(FALSE);
}

void SpaceWars::deleteBadGuys()
{
	while(!badguyList.empty())
	{
		badguyList.remove();
	}
}

void SpaceWars::paintEvent(QPaintEvent *event)
{
	//create a QPainter object to paint in the window
	QPainter painter(this);

	//the first time the game starts, print the instructions to the screen
	if (gameStarting)
	{
		QColor *color = new QColor("white");
		painter.setPen(*color);
		painter.setFont(QFont("Chicago", 15));
		painter.drawText(250,200, "W, A, S, D to move");
		painter.drawText(250,250, "space to shoot");
		painter.drawText(250,300, "F to use bomb");
		painter.drawText(250,350, "Avoid enemy bullets and spaceships");
		painter.drawText(250,400, "Kill bosses to advance levels");
		painter.drawText(250,450, "Beat the third level to win");
		painter.drawText(250,500, "Powerups may help you");
		painter.drawText(250,550, "Press M to start a level");
		painter.drawText(250,600, "Q to quit");
		//gameStarting = FALSE;
	}

	//if the level should be changed, change it
	else if (levelChange)
	{
		//stop all timers
		killTimers();

		//print a message to alert the user to a new level coming up
		QColor *color = new QColor("white");
		painter.setPen(*color);
		painter.setFont(QFont("Chicago", 15));
		if (level == 2)
			painter.drawText(330,200,"Level Two");
		else if (level == 3)
			painter.drawText(330,200, "Level Three");
		else if (level > 3)
		{
			//if the level is 4, the user has won and take appropriate action
			victory();
			QColor *color = new QColor("white");
			painter.setPen(*color);
			painter.setFont(QFont("Chicago", 15));
			painter.drawText(340, 300, "YOU WIN!!");
			painter.drawText(290, 330, "Hit 'M' to start new game");
			reportInfo = FALSE;
			gameStarted = FALSE;
			deleteBadGuys();
			deleteBullets();
			deleteBadBullets();
			makeBadGuys();
		}
	}

	else
	{
	//create a white pen to write in the window
	//write the lives and score in the window
	QColor *color = new QColor("white");
	painter.setPen(*color);
    painter.setFont(QFont("Chicago", 11)); 
	QString int_score = QString::number(score);
	QString int_lives = QString::number(lives);
	QString int_bombs = QString::number(bombs);
	QString int_level = QString::number(level);

	painter.drawText(610, 15, "Lives: ");
	if (lives > -1)
		painter.drawText(655, 15, int_lives);

	painter.drawText(690, 32, "Level: ");
	painter.drawText(735, 32, int_level);

	painter.drawText(715, 15, "$");
	if (score >= -500)
		painter.drawText(725, 15, int_score);

	painter.drawText(598, 32, "Bombs: ");
	if (bombs > -1)
		painter.drawText(655, 32, int_bombs);
	
	//draw the spaceship
	painter.drawImage(spaceship->getRect(), 
        	spaceship->getImage());

	//draw any active powerups
	if (powerUp->isActive())
	{
		painter.drawImage(powerUp->getRect(),
			powerUp->getImage());
	}

	//draw the spaceship's bullets
	list<Bullet*>::iterator bulletIterator;
	for (bulletIterator = bullets.begin(); bulletIterator != bullets.end(); bulletIterator++)
	{
		painter.drawImage((*bulletIterator)->getRect(), (*bulletIterator)->getImage());
	}

	
	//if the badguys are active, draw them
	Node<Badguy*>* b = badguyList.getFirst();
	while (b != NULL)
	{
		if (b->data->isActive())
		{
			painter.drawImage(b->data->getRect(), b->data->getImage());
		}

		//draw the badguy's bullets
		list<Bullet*>::iterator badguyIterator;
		for (badguyIterator = badguyBullets.begin(); badguyIterator != badguyBullets.end(); badguyIterator++)
		{
			painter.drawImage((*badguyIterator)->getRect(), (*badguyIterator)->getImage());
		}
		b = b->next;
	}
	if (reportInfo)
	//if the flag for the spaceship being hit is true
	{
		QPalette sample_palette;
		sample_palette.setColor(QPalette::WindowText, Qt::white);

		//write a message to alert the player to the loss of one life if he has lives remaining
		QColor *color = new QColor("white");
		painter.setPen(*color);
        painter.setFont(QFont("Chicago", 15)); 
        painter.setCompositionMode(QPainter::CompositionMode_Source);
		
		//if the player is out of lives, end the game
		if (lives <= 0)
		{	
			QColor *color = new QColor("white");
			painter.setPen(*color);
		    painter.setFont(QFont("Chicago", 15)); 
			painter.setCompositionMode(QPainter::CompositionMode_Source);
			killTimers();
			reportInfo = FALSE;
			painter.drawText(340, 300, "Game Over!");
			painter.drawText(290, 330, "Hit 'M' to start new game");
		}
		else
		{
			painter.drawText(350, 300, "Lost a Life!");
			painter.drawText(290, 330, "Hit 'R' to continue game");
		}
	}
	}
}

void SpaceWars::timerEvent(QTimerEvent *e)
{
	//create a badguy for the explosion timer control
	Badguy* badguyTimerControl;

	if (e->timerId() == timerId)
	{
		//increment variable to control bullet firing rate
		bulletCounter++;

		if (gameWon == FALSE)
		{
			//move any bullets in the list
			if (!bullets.empty())
				moveGoodBullet();
		}

		//move the bullets
		if (gameWon == FALSE)
		{
			if (!badguyBullets.empty())
				moveBadBullet();
		}

		//create a flag for each ship to know if it is hit or not
		bool spaceshipHit = FALSE;

		//check to see if a collision has occured
		checkCollisions(spaceshipHit);

		//check to see if the spaceship collided with a powerup
		checkPowerUp();

		//if the spaceship is hit, explode it
		if (spaceshipHit && !spaceshipExploding)
		{
			spaceshipExploding = TRUE;
			timerSpaceshipHit = startTimer(100);
			QPoint center = spaceship->rect.center();
			spaceship->image.load("explosionone.png");
			spaceship->rect = spaceship->image.rect();
			spaceship->rect.moveCenter(center);
			spaceshipIndex = 1;
		}

		//traverse the list, exploding any bad guys that are hit
		Node<Badguy*>* b = badguyList.getFirst();
		while (b != NULL)
		{
			if (b->data->getBadguyHit() && !(b->data->getBadguyExploding()) && b->data->isActive())
			{
				b->data->setBadguyExploding(TRUE);
				b->data->setTimerBadguyHit(startTimer(40));
				QPoint center = b->data->rect.center();
				b->data->image.load("explosionone.png");
				b->data->rect = b->data->image.rect();
				b->data->rect.moveCenter(center);
				b->data->setExplosionIndex(1);
			}
			b = b->next;
		}

		//move the powerup if it is active
		if (powerUp->isActive())
			powerUp->move();

		//start at the beginning of the list, and traverse it moving all active badguys
		b = badguyList.getFirst();
		while (b != NULL)
		{
			if (b->data->isActive())
 				b->data->move(spaceship);

			if (b->data->offScreen())
			{
				b->data->setActive(FALSE);
			}	
			b = b->next;
		}
	}

	//if spaceship is hit, explode it
	else if (e->timerId() == timerSpaceshipHit)
	{
		explodeSpaceship();
	}

	//if any of the badguys are hit, explode them
	else if (checkBadguyTimers(e->timerId(), badguyTimerControl))
	{
		explodeBadguy(badguyTimerControl);
	}

	else if (e->timerId() == timerBadguy)
	{		
		//delete any remaining offscreen badguys
		deleteBadGuys();
		
		//make a new set of badguys
		makeBadGuys();

		//traverse the list, setting all badguys to active
		Node<Badguy*>* b = badguyList.getFirst();
		while (b != NULL)
		{
			b->data->setActive(TRUE);
			b = b->next;
		}
	}

	else if (e->timerId() == timerBadguyBullet)
	{
		//return the first badguy in the list to traverse the list for the shooting of the badguy bullets
		Node<Badguy*>* b = badguyList.getFirst();
		if (!b->data->isExploded() && !b->data->getBadguyExploding())
		{
			while (b != NULL)
			{
				if (b->data->isActive() && !(b->data->isBoss()))
				{
					//if the badguy is not a boss, add a normal badguy bullet to the list at the correct location
					Bullet *badguyBullet = new BadBullet((b->data->rect.left() + b->data->rect.right()) / 2 , b->data->rect.bottom());
	  				badguyBullets.push_back(badguyBullet);
				}
				else if (level == 3 && b->data->isActive() && b->data->isBoss())
				{
					//for the level 3 boss, use five of the split firing bullets
					Bullet *bossBullet1 = new BossBullet1((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet1);
					Bullet *bossBullet2 = new BossBullet2((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet2);
					Bullet *bossBullet3 = new BossBullet3((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet3);
					Bullet *bossBullet4 = new BossBullet4((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet4);
					Bullet *bossBullet5 = new BossBullet5((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet5);
				}
				else if (level == 2 && b->data->isActive() && b->data->isBoss())
				{
					//for the level 2 boss, use three of the split firing bullets
					Bullet *bossBullet1 = new BossBullet1((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet1);
					Bullet *bossBullet2 = new BossBullet2((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet2);
					Bullet *bossBullet3 = new BossBullet3((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom());
					badguyBullets.push_back(bossBullet3);
				}
				else if (level == 1 && b->data->isActive() && b->data->isBoss())
				{
					//for level 1, use one aimbullet only!
					Bullet *bossBullet1 = new AimBullet((b->data->rect.left() + b->data->rect.right()) / 2, b->data->rect.bottom(), spaceship);
					badguyBullets.push_back(bossBullet1);
				}
				b = b->next;
			}
		}

	}


	

	else if (e->timerId() == timerPowerUp)
	{
		//assign the randomly selected pointer 
		powerUp = PowerUp::create();
		powerUp->setActive(TRUE);
	}

	else if (e->timerId() == timerBoss)
	{
		//kill badguy and boss spawning timers, create the boss
		killTimer(timerBadguy);
		killTimer(timerBoss);
		makeBoss();
	}

	repaint();
}


void SpaceWars::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
       {  
		int x = spaceship->getRect().x();
		if (!spaceshipExploding && !spaceshipExploded)
		{
			for (int i=1; i<=12; i++)
				spaceship->moveLeft(x--);
		}
        break;
       }
    case Qt::Key_D:
		{ 
		int x = spaceship->getRect().x();
        if (!spaceshipExploding && !spaceshipExploded)
		{
			for (int i=1; i<=12; i++)
				spaceship->moveRight(x++);
        }
        break;
		}
    case Qt::Key_W:
        { 
          int y = spaceship->getRect().y();
          if (!spaceshipExploding && !spaceshipExploded)
		  {
			  for (int i=1; i<=12; i++)
				spaceship->moveUp(y--);
		  }
        }
	break;
    case Qt::Key_S:
        { 
		 int y = spaceship->getRect().y();
		 if (!spaceshipExploding && !spaceshipExploded)
		 {
			for (int i=1; i<=12; i++)
				spaceship->moveDown(y++);
		 }
        }
	break;
    case Qt::Key_P:
        { 
          pauseGame();
        }
        break;

	case Qt::Key_R:
		restartGame();
		break;

    case Qt::Key_Space:
        {
			if (bulletCounter - lastShotTime > 10 && !spaceshipExploding)
			{
				Bullet *bullet = new GoodBullet((spaceship->rect.left() + spaceship->rect.right()) / 2 , spaceship->rect.top());
				bullets.push_back(bullet);
				lastShotTime = bulletCounter;
			}
        }
        break;
    case Qt::Key_M:
	{
	  if (!gameStarted)
		  startGame();
	  else
	  {
		  continueGame();
	  }
	}
	break;

	case Qt::Key_F:
		{
			if (bombs > 0 && !paused && !reportInfo && !gameWon)
				explodeBomb();
		}
		break;
    case Qt::Key_Q:
        {
			if (score > highScore)
			highScore = score;
			qApp->exit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void SpaceWars::startGame()
{ 
  if (!gameStarted) {
	//move the spaceship to its initial position
    spaceship->resetState();
    
	//set background to level 1 background
	QPalette pal;
	setAutoFillBackground(TRUE);
	pal.setBrush(this->backgroundRole(), QBrush(QImage("level1.png")));
	this->setPalette(pal);

	//initialize flag and counting variables
    	gameOver = FALSE; 
	reportInfo = FALSE;
    	gameWon = FALSE; 
    	gameStarted = TRUE;
	gameStarting = FALSE;
	lives = 3;
	if (score > highScore)
		highScore = score;
	score = 0;
	bombs = 0;
	badguyType = 1;
	previousBadguy = 5;
	bulletCounter = 14;
	lastShotTime = 0;
	spaceshipExploding = FALSE;
    startTimers();
    Node<Badguy*>* b = badguyList.getFirst();
	while (b != NULL)
	{	
		b->data->setActive(TRUE); 
		b->data->setBadguyExploding(FALSE);
		b = b->next;
	}
	
  }
}

void SpaceWars::continueGame()
{
	QPalette pal;
	setAutoFillBackground(TRUE);

	if (lives == 0)
	{
			level = 1;
			if (score > highScore)
				highScore = score;
			score = 0;
			lives = 3;
	}


	//fix the background for appropriate level
	if (level == 1)
	{
		pal.setBrush(this->backgroundRole(), QBrush(QImage("level1.png")));
		this->setPalette(pal);
	}
	else if (level == 2)
	{
		pal.setBrush(this->backgroundRole(), QBrush(QImage("level2a.png")));
		this->setPalette(pal);
	}
	else
	{
		pal.setBrush(this->backgroundRole(), QBrush(QImage("level3.png")));
		this->setPalette(pal);
	}
	
	//change the necessary bools
	gameOver = FALSE; 
	gameWon = FALSE;
	gameStarted = TRUE;
	spaceshipExploding = FALSE;

	deleteBadGuys();
	deleteBullets();
	deleteBadBullets();
	delete spaceship;
	spaceship = new Spaceship();
	

	//reinitialize the bullet counters
	bulletCounter = 14;
	lastShotTime = 0;

	//restart all the timers
	startTimers();

	//make another set of bad guys
	makeBadGuys();

	//
	Node<Badguy*>* b = badguyList.getFirst();
		while (b != NULL)
		{
			b->data->setActive(TRUE); 
			b->data->setBadguyExploding(FALSE);
			b = b->next;
		}
	levelChange = FALSE;
	reportInfo = FALSE;
}

void SpaceWars::pauseGame()
{
  //if unpausing, start all the timers again
  if (paused) 
  {
    startTimers();
    paused = FALSE;
  } 
  
  //if pausing, kill all active timers
  else 
  {
    paused = TRUE;
	bulletCounter = 2;
	lastShotTime = 0;
    killTimers();
   }
}

void SpaceWars::victory()
{
	//kill all timers
	gameWon = TRUE;
	killTimers();

	deleteBadBullets();

	//set the initial flag conditions
	gameOver = FALSE;
	gameWon = FALSE;
	paused = FALSE;
	gameStarted = FALSE;
	reportInfo = FALSE;
	gameStarting = TRUE;
	levelChange = FALSE;
	level = 1;
  
	//set all badguys to inactive
	Node<Badguy*>* b = badguyList.getFirst();
	while (b != NULL)
	{
		b->data->setActive(FALSE);
		b = b->next;
	}
}

//if spaceship is hit, stop game to print a message and force keystroke to resume
void SpaceWars::restartGame()
{
	if (reportInfo)
	{
		reportInfo = false;

		//deallocate memory for current spaceship
		delete spaceship;

		//create a new spaceship
		spaceship = new Spaceship();

		//deallocate memory for all badguys
		deleteBadGuys();

		deleteBullets();
		deleteBadBullets();

		//make new bad guys in their initial positions
		makeBadGuys();

		//initialize bad guys to active and not exploding
		
		Node<Badguy*>* b = badguyList.getFirst();
		while (b != NULL)
		{
			b->data->setActive(TRUE); 
			b->data->setBadguyExploding(FALSE);
			b = b->next;
		}

		//initialize counting variables
		bulletCounter = 14;
		lastShotTime = 0;
		spaceshipExploding = FALSE;

		//start timers
		startTimers();
	}
}

void SpaceWars::explodeBomb()
{
	Node<Badguy*>* b = badguyList.getFirst();
	while (b != NULL)
	{
			if (!b->data->getBadguyExploding() && b->data->isActive() && b->data->isBoss() && (b->data->getHitCounter() + 3 < b->data->getHitsToKill()))
			{
				b->data->setHitCounter(b->data->getHitCounter() + 3);
				b->data->changeImage(b->data->getHitCounter());
			}
			else if (!(b->data->getBadguyExploding()) && b->data->isActive())
			{
				b->data->setBadguyExploding(TRUE);
				b->data->setTimerBadguyHit(startTimer(40));
				QPoint center = b->data->rect.center();
				b->data->image.load("explosionone.png");
				b->data->rect = b->data->image.rect();
				b->data->rect.moveCenter(center);
				b->data->setExplosionIndex(1);
			}
		b = b->next;
	}

	bombs--;
}

void SpaceWars::setLives(int l)
{
	lives = l;
}

int SpaceWars::getLives()
{
	return lives;
}

void SpaceWars::setScore(int s)
{
	score = s;
}

int SpaceWars::getScore()
{
	return score;
}

void SpaceWars::setBombs(int b)
{
	bombs = b;
}

int SpaceWars::getBombs()
{
	return bombs;
}

void SpaceWars::setReportInfo(bool rI)
{
	reportInfo = rI;
}

void SpaceWars::checkPowerUp()
{
	if (checkPowerUpCollision() && powerUp->isActive())
		{
			powerUp->setActive(FALSE);
			powerUp->trigger(this);			
		}

}

bool SpaceWars::checkBadguyTimers(int timerId, Badguy* &badguyTimerControl)
{
	Node<Badguy*>* b = badguyList.getFirst();
	while (b != NULL)
	{
		if (timerId == b->data->getTimerBadguyHit())
		{	
			badguyTimerControl = b->data;
			return true;
		}
		b = b->next;
	}
	return false;
}

void SpaceWars::killTimers()
{
	killTimer(timerId);
	killTimer(timerBadguy);
	killTimer(timerBadguyBullet);
	killTimer(timerPowerUp);
	killTimer(timerBoss);
}

void SpaceWars::startTimers()
{
	spaceshipExploded = FALSE;
	timerId = startTimer(20);
	timerBadguy = startTimer(13000);
	timerBadguyBullet = startTimer(1500);
	timerPowerUp = startTimer(13000);
	timerBoss = startTimer(25000);
}

void SpaceWars::deleteBullets()
{
	list<Bullet*>::iterator i = bullets.begin();
	while (i != bullets.end())
	{
		delete (*i);
		i++;
	}
	bullets.clear();
}

void SpaceWars::deleteBadBullets()
{
	list<Bullet*>::iterator i = badguyBullets.begin();
	while (i != badguyBullets.end())
	{
		delete (*i);
		i++;
	}
	badguyBullets.clear();
}

int SpaceWars::updateScore(int score)
{
	if (highScore > score)
	{
		return highScore;
	}
	else
	{
		return score;
	}
}
