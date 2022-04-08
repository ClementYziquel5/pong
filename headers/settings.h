#ifndef SETTINGS_H
#define SETTINGS_H

class Settings{
  private:
    static const int player_width    = 7;
    static const int player_height   = 70;
    static const int player_speed    = 20;

    static const int ball_width      = 20;
    static const int ball_height     = 20;
    static const int ball_speed_init = 7;

    static const int score_to_win    = 5;

  public:
    static int getPlayerWidth() {return player_width;}
    static int getPlayerHeight() {return player_height;}
    static int getPlayerSpeed() {return player_speed;}

    static int getBallWidth() {return ball_width;}
    static int getBallHeight() {return ball_height;}
    static int getBallSpeed() {return ball_speed_init;}


    static int getScoreToWin() {return score_to_win;}
};

#endif
