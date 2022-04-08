#include "../headers/player.h"

/* Constructeur */
Player::Player():QGraphicsRectItem(0,0,Settings::getPlayerWidth(),Settings::getPlayerHeight()){
  score    = 0;
  key_up   = false;
  key_down = false;
}

/* Destructeur */
Player::~Player(){

}
