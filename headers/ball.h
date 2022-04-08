#ifndef BALL_H
#define BALL_H

#include <QApplication>
#include <QGraphicsRectItem>
#include "MainWindow.h"
#include "scene.h"
#include "settings.h"
#include "player.h"

class Player;

class Ball:public QObject,public QGraphicsEllipseItem{
  Q_OBJECT
  private:
    float speed_x; // Vitesse en x
    float speed_y; // Vitesse en y
    float speed;
    float speed_init;
    bool move; // true si jeu en cours, false si jeu en pause

  public:
    /* Constructeur/Destructeur */
    Ball();
    ~Ball();

    /* Getters/Setters */
    float getSpeedX() const { return speed_x;}
    float getSpeedY() const { return speed_y;}
    bool getMove() const {return move;}
    void setSpeed(float ball_speed){ speed = ball_speed;}
    void setSpeedInit(float ball_speed){ speed_init = ball_speed;}
    void setSpeedX(float speed){ this->speed_x = speed;}
    void setSpeedY(float speed){ this->speed_y = speed;}
    void setMove(bool mov) { move=mov;}
    void getNewAngle(Player*,int);

    /* Autres Méthodes */
    void reset_pos();
    void start_ball(int,int);
};

#endif
