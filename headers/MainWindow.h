#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSlider>

#include "settings.h"


class MainWindow: public QMainWindow{
  Q_OBJECT
  public:
    /* Constructeur/Destructeur */
    MainWindow();
    ~MainWindow();

    /* Autres méthodes */
    QGroupBox *BuildGroupBoxControle();
    QGroupBox *BuildGroupBoxControle2();


  public slots:
    void slot_light_mode(bool);
    void slot_leave_game();

  private:
    QWidget *main_widget;
    QMenu *fileMenu;
    QGraphicsScene *scene;
    QGraphicsView *myview;
};

#endif
