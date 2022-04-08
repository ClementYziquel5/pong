#include "../headers/scene.h"

// Déclaration de la fonction qui positionne et colorise les scores
void set_score_display(QGraphicsTextItem *,int );


// Déclaration de la fonction qui positionne et le message de victoire
void display_win_msg(QGraphicsTextItem *,int );

/* Constructeur */
Scene::Scene(QObject *parent) : QGraphicsScene(parent){
  // Créer les joueurs et la balle
  ball = new Ball();
  player_l = new Player ();
  player_l->setBrush(Qt::darkBlue);
  player_r = new Player ();
  player_r->setBrush(Qt::darkRed);

  // Créer l'affichage des scores
  score_r = new QGraphicsTextItem(QString::number(player_r->getScore()));
  score_l = new QGraphicsTextItem(QString::number(player_l->getScore()));
  win_msg = new QGraphicsTextItem();

  set_score_display(score_l,1);
  set_score_display(score_r,2);

  // Délimitation de la zone dejeu
  top    = new QGraphicsLineItem(-375,-275,375,-275);
  bottom = new QGraphicsLineItem(-375,275,375,275);
  right  = new QGraphicsLineItem(375,-275,375,275);
  left   = new QGraphicsLineItem(-375,-275,-375,275);
  middle_line = new QGraphicsLineItem(0,-275,0,275);
  slot_light_mode(false);

  // Sound effects
  ball_impact = new QMediaPlayer;
  ball_impact->setMedia(QUrl::fromLocalFile("/home/isen/c++/qt/Pong/audio/pong.mp3"));
  ball_impact->setVolume(100);

  player_losing = new QMediaPlayer;
  player_losing->setMedia(QUrl::fromLocalFile("/home/isen/c++/qt/Pong/audio/bong.mp3"));
  player_losing->setVolume(100);

  win_sound = new QMediaPlayer;
  win_sound->setMedia(QUrl::fromLocalFile("/home/isen/c++/qt/Pong/audio/win.mp3"));
  win_sound->setVolume(100);

  // Ajout des élémnts dans la scène
  this->addItem(player_l);
  this->addItem(player_r);
  this->addItem(top);
  this->addItem(bottom);
  this->addItem(right);
  this->addItem(left);
  this->addItem(middle_line);
  this->addItem(ball);
  this->addItem(score_l);
  this->addItem(score_r);
  this->addItem(win_msg);
  win_msg->hide();

  fps = 60;

  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(slot_update()));
  timer->start(fps);
  srand(time(NULL));
  to_play = rand()%2+1; // 1: ball vers player_r; 2: ball vers player_l

  // Mise en place des éléments
  slot_reset();

}


/* Destructeur */
Scene::~Scene(){

}

/* Lancer la partie quand le joueur appuie sur le bouton start */
void Scene::slot_start(){
  ball->start_ball(to_play,fps);
}


void Scene::slot_update(){
  /* Faire bouger les joueurs */
  if(player_l->getKeyUp()){
    player_l->setPos(player_l->x(),player_l->y()-Player::getSpeed());
  }
  if(player_l->getKeyDown()){
    player_l->setPos(player_l->x(),player_l->y()+Player::getSpeed());
  }
  if(player_r->getKeyUp()){
    player_r->setPos(player_r->x(),player_r->y()-Player::getSpeed());
  }
  if(player_r->getKeyDown()){
    player_r->setPos(player_r->x(),player_r->y()+Player::getSpeed());
  }

  /* Joueur à la limite du terrain */
  while( player_l->collidesWithItem(bottom) ){
    player_l->setPos(player_l->x(),player_l->y()-1);
  }
  while(player_l->collidesWithItem(top)){
    player_l->setPos(player_l->x(),player_l->y()+1);
  }
  while(player_r->collidesWithItem(bottom) ){
    player_r->setPos(player_r->x(),player_r->y()-1);
  }
  while(player_r->collidesWithItem(top)){
    player_r->setPos(player_r->x(),player_r->y()+1);
  }

  /* Faire bouger la balle */
  if (ball->collidesWithItem(top) || ball->collidesWithItem(bottom)){
    ball->setSpeedY(-ball->getSpeedY());
    ball_impact->play();
  }else if(ball->collidesWithItem(player_l)){
    /* Accélération et changement de direction */
    ball->getNewAngle(player_l,2);
    ball_impact->play();
  }else if(ball->collidesWithItem(player_r)){
    /* Accélération et changement de direction */
    ball->getNewAngle(player_r,1);
    ball_impact->play();
  }else if(ball->x()<(player_l->x())){ // player_r gagne
    /* Reset et changement de direction de départ */
    player_r->increment_score();
    player_r->getScore()<Settings::getScoreToWin() ? player_losing->play() : win_sound->play();
    reset_pos_items();
    to_play = 1;
  }else if( ball->x()>player_r->x()){ // player_l gagne
    /* Reset et changement de direction de départ */
    player_l->increment_score();
    player_l->getScore()<Settings::getScoreToWin() ? player_losing->play() : win_sound->play();
    reset_pos_items();
    to_play = 2;
  }
  /* Bouger la balle aux nouvelles coordonnées */
  ball->setPos(ball->x()+ball->getSpeedX(),ball->y()+ball->getSpeedY());
}


/* Pause/Resume le jeu */
void Scene::slot_pause(){
  if(ball->getMove()){
    timer->stop();
    ball->setMove(false);
  }else{
    timer->start();
    ball->setMove(true);
  }
}


/* Méthode pour pouvoir utiliser plusieurs touches du clavier
   en même temps trouvée sur le forum openclassroom:
   https://openclassrooms.com/forum/sujet/qt-appui-sur-2-touches-83520
*/

/* Récupération des touches pressées sur le clavier */
void Scene::keyPressEvent(QKeyEvent *event){
  switch (event->key()) {
    case Qt::Key_E:
      player_l->setKeyUp(true); // player_l up
      break;
    case Qt::Key_D:
      player_l->setKeyDown(true); // player_l down
      break;
    case Qt::Key_O:
      player_r->setKeyUp(true); // player_r up
      break;
    case Qt::Key_L:
      player_r->setKeyDown(true); // player_r down
      break;
    case Qt::Key_B:
      if(!ball->getMove()){
        ball->start_ball(to_play,fps); // Launch game
        win_msg->hide();
      }
      break;
    case Qt::Key_Space: // Pause
      slot_pause();
      break;
    case Qt::Key_R: // Reset le jeu
      slot_reset();
      break;
    default:
      break;
  }
}


/* Récupération des touches relachées sur le clavier */
void Scene::keyReleaseEvent (QKeyEvent *event){
  switch (event->key()) {
    case Qt::Key_E: // player_l up
      player_l->setKeyUp(false);
      break;
    case Qt::Key_D: // player_l down
      player_l->setKeyDown(false);
      break;
    case Qt::Key_O: // player_r up
      player_r->setKeyUp(false);
      break;
    case Qt::Key_L: // player_r down
      player_r->setKeyDown(false);
      break;
    default:
      break;
  }
}

/* Remise à 0 de l'affichage et des scores */
void reset_scores(Player *pl,Player *pr,QGraphicsTextItem *tl,QGraphicsTextItem *tr){
  pl->setScore(0);
  pr->setScore(0);
  tl->setPlainText(QString::number(pl->getScore()));
  tr->setPlainText(QString::number(pr->getScore()));
}


void Scene::reset_pos_items(){
  /* Mise à jour des scores */
  score_r->setPlainText(QString::number(player_r->getScore()));
  score_l->setPlainText(QString::number(player_l->getScore()));

  /* Victoire d'un joueur */
  if(player_r->getScore()==Settings::getScoreToWin() || player_l->getScore()==Settings::getScoreToWin()){
    if(player_r->getScore()==Settings::getScoreToWin()){
      display_win_msg(win_msg,2);
    }else if(player_l->getScore()==Settings::getScoreToWin()){
      display_win_msg(win_msg,1);
    }
    reset_scores(player_l,player_r,score_l,score_r);
  }
  /* Reset la postion des items */
  ball->reset_pos();
  player_l->setPos(-325-Settings::getPlayerWidth(),-Settings::getPlayerHeight()/2);
  player_r->setPos(325,-Settings::getPlayerHeight()/2);
}


/* Reset les scores et les postions des items */
void Scene::slot_reset(){
  /* Reset all positions */
  reset_pos_items();

  /* Reset score */
  reset_scores(player_l,player_r,score_l,score_r);
}


/* Changement de la couleur des limites du terrain pour le light/dark mode */
void Scene::slot_light_mode(bool isChecked){
  QPen pen;
  pen.setWidth(2);
  if(isChecked){
    pen.setBrush(Qt::black);
  }else{
    pen.setBrush(Qt::white);
  }
  top->setPen(pen);
  bottom->setPen(pen);
  right->setPen(pen);
  left->setPen(pen);
  pen.setStyle(Qt::DotLine);
  middle_line->setPen(pen);
}


/* Active ou désactive le son en fonction du bouton radio */
void Scene::slot_manage_sound(bool soundOn){
  if(soundOn){
    player_losing->setVolume(0);
    ball_impact->setVolume(0);
    win_sound->setVolume(0);
  }else{
    player_losing->setVolume(100);
    ball_impact->setVolume(100);
    win_sound->setVolume(100);
  }
}


/* Met à jour la vitesse de la balle en fonction du curseur */
void Scene::slot_ball_speed(int value){
  ball->setSpeedInit(value/(50/Settings::getBallSpeed()));
  slot_reset();
}


/* Initialisation de la fonction qui position et colorise les scores */
void set_score_display(QGraphicsTextItem *score,int side){
  QFont ft;
  ft.setPointSize(30);
  score->setFont(ft);

  QPalette pa;
  QColor *col;
  if(side==1){
    col = new QColor(Qt::darkBlue);
    score->setPos(-200, -200);
  }else{
    col = new QColor(Qt::darkRed);
    score->setPos(165, -200);
  }
  score->setDefaultTextColor(*col);
}


/* Initialisation de la fonction qui positionne et le message de victoire */
void display_win_msg(QGraphicsTextItem *msg,int side){
  QFont ft;
  ft.setPointSize(30);
  msg->setFont(ft);

  QPalette pa;
  QColor *col = new QColor(209,181,43);
  msg->setDefaultTextColor(*col);

  if(side==1){
    msg->setPlainText("Player Blue wins");
    msg->setPos(-325,-250);
  }else if(side==2){
    msg->setPlainText("Player Red wins");
    msg->setPos(25,-250);
  }
  msg->show();
}
