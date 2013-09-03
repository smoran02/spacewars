#ifndef SPACESHIP_H
#define SPACESHIP_H


#include <QRect>
#include <QImage>

class Spaceship
{
   public:
	Spaceship();
	~Spaceship();

   public:
	void resetState();
	void moveLeft(int);
	void moveRight(int);
	void moveUp(int);
	void moveDown(int);
	QRect getRect();
	QImage &getImage();
	QRect rect;
	QImage image;
	

};


#endif