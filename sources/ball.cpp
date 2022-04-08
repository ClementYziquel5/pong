#include "../headers/ball.h"


/* Constructeur */
Ball::Ball():QGraphicsEllipseItem(-Settings::getBallWidth()/2,-Settings::getBallHeight()/2,Settings::getBallWidth(),Settings::getBallHeight()){
  this->setBrush(Qt::white);
  this->setSpeedInit(Settings::getBallSpeed());
}

/* Desstructeur */
Ball::~Ball(){

}

/* Remettre la balle à sa position centrale et avec des paramètres nuls */
void Ball::reset_pos(){
  this->setSpeedX(0);
  this->setSpeedY(0);
  this->setPos(0,0);
  this->setSpeed(Settings::getBallSpeed());
  this->setMove(false);
}

/* Fonction pour lancer ball dans une direction aléatoire avec la vitesse speed */
void Ball::start_ball(int to_play,int fps){
  move=true;
  srand(time(NULL));
  float angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  angle       = (angle * 2 * M_PI / 3) - M_PI / 3;
  /* Vitesse constante au début malgré les fps qui varient */
  speed = (speed_init*fps/30);
  this->setSpeedY(speed * sin(angle));
  if (to_play == 2){
    this->setSpeedX(-speed * cos(angle));
  }else{
    this->setSpeedX(speed * cos(angle));
  }
}

/* Calculer le nouvel angle de la balle après collision avec un player */
/* Méthode extraite de
   https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
*/
void Ball::getNewAngle(Player* p,int to_play){
  float diff_y = (p->y() + Settings::getPlayerHeight()/2) - this->y();
  diff_y       = diff_y / (Settings::getPlayerHeight()/2);
  float angle  = diff_y * 50; // Angle max=50°

  /* Augmenter la vitesse de la ball */
  speed = speed*105/100;

  // Asssigner le nouvel angle
  this->setSpeedY(-speed * sin(angle*M_PI/180));
  if (to_play == 2){
    this->setSpeedX(speed * cos(angle*M_PI/180));
  }else{
    this->setSpeedX(-speed * cos(angle*M_PI/180));
  }}
