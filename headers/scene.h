#ifndef SCENE_H
#define SCENE_H

#include <QtWidgets>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <math.h>
#include "MainWindow.h"
#include "ball.h"
#include "player.h"
#include "settings.h"


class Ball;
class Player;

class Scene:public QGraphicsScene{
  Q_OBJECT
  private:
    QTimer *timer; // Timer pour refresh la scène

    Ball *ball;
    Player *player_l; // Joueur de gauche
    Player *player_r; // Joueur de droite

    QGraphicsLineItem *top; // Limite haute
    QGraphicsLineItem *bottom; // Limite basse
    QGraphicsLineItem *left; // Limite à gauche
    QGraphicsLineItem *right; // Limite à droite
    QGraphicsLineItem *middle_line; // Ligne centrale

    QMediaPlayer *ball_impact; // Son impact balle avec mur/Joueur
    QMediaPlayer *player_losing; // Son défaite d'une manche
    QMediaPlayer *win_sound;  // Son de victoire/fin de partie

    /* Affichage des scores sur la scène */
    QGraphicsTextItem *score_l;
    QGraphicsTextItem *score_r;

    QGraphicsTextItem *win_msg; // Affichage du message de victoire

    int to_play; // Pour le choix de la direction de la balle au start: 1 droite, 2 gauche
    int fps; // Nombre d'images par seconde

  public:
    /* Constructeur/Destructeur */
    Scene(QObject *parent = 0);
    ~Scene();

    /* Autres méthodes */
    void keyPressEvent(QKeyEvent*); // Touche pressée
    void keyReleaseEvent(QKeyEvent*); // Touche relachée
    void reset_pos_items();

  public slots:
    void slot_update(); // Refresh le scène aux nouvelles coordonnées pour ball et player
    void slot_pause();
    void slot_reset();
    void slot_light_mode(bool);
    void slot_start();
    void slot_manage_sound(bool);
    void slot_ball_speed(int value);
};

#endif
