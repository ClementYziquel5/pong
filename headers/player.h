#ifndef PLAYER_H
#define PLAYER_H

#include <QApplication>
#include <QGraphicsRectItem>
#include "MainWindow.h"
#include "scene.h"
#include "settings.h"



class Player:public QObject,public QGraphicsRectItem{
  Q_OBJECT
  private:
    int score; // Score du joueur
    bool key_up; // true si pressée, false sinon
    bool key_down; // true si pressée, false sinon

  public:
    /* Constructeur/Destructeur */
    Player();
    ~Player();

    /* Getters/Setters */
    bool getKeyUp() const {return key_up;}
    bool getKeyDown() const {return key_down;}
    void setKeyUp(bool key_status){key_up=key_status;}
    void setKeyDown(bool key_status){key_down=key_status;}
    static int getSpeed() {return Settings::getPlayerSpeed();}
    int getScore() const {return score;}
    void setScore(int sc) {score=sc;}

    /* Autres Méthodes */
    void increment_score() {score++;}
};

#endif
