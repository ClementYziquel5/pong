#include "../headers/MainWindow.h"
#include "../headers/scene.h"


/* Constructeur */
MainWindow::MainWindow(): QMainWindow(){
    //MainWidget
    main_widget = new QWidget;
    QHBoxLayout *main_layout = new QHBoxLayout;
    QVBoxLayout *control_box = new QVBoxLayout;
    main_widget->setLayout(main_layout);
    this->setCentralWidget(main_widget);
    this->setMinimumWidth(900);
    this->setMinimumHeight(600);

    // Menu zone
    fileMenu = menuBar()->addMenu(tr("&Fichier"));

    // Play zone
    scene = new Scene(this);
    scene->setBackgroundBrush(Qt::black);
    myview = new QGraphicsView(scene,this);

    // Button zone
    // Je dois créer 2 groupes distincts pour gérer les signaux/slots sur les QRadioButton
    control_box->addWidget(BuildGroupBoxControle());
    control_box->addWidget(BuildGroupBoxControle2());

    main_layout->addLayout(control_box);
    main_layout->addWidget(myview);
}


/* Desstructeur */
MainWindow::~MainWindow(){

}


/* Construire la 1ere control_box */
QGroupBox *MainWindow::BuildGroupBoxControle(){
  QGroupBox *qgb = new QGroupBox(tr("Contrôles"));

  QLabel *slider_label = new QLabel("Ball speed");
  QSlider *slider_ball_speed = new QSlider(Qt::Horizontal);
  slider_ball_speed->setSliderPosition(5*Settings::getBallSpeed());

  QRadioButton *light_mode = new QRadioButton(tr("Light mode"));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(slider_label);
  vbox->addWidget(slider_ball_speed);
  vbox->addWidget(light_mode);

  qgb->setLayout(vbox);

  connect(light_mode,SIGNAL(toggled(bool)),this,SLOT( slot_light_mode(bool)));
  connect(light_mode,SIGNAL(toggled(bool)),scene,SLOT( slot_light_mode(bool)));
  connect(slider_ball_speed,SIGNAL(valueChanged(int)),scene,SLOT(slot_ball_speed(int)));

  return qgb;
}


/* Construire la 2nde control_box */
QGroupBox *MainWindow::BuildGroupBoxControle2(){
  QGroupBox *qgb = new QGroupBox(NULL);

  QRadioButton *sound = new QRadioButton(tr("Sound off"));

  QPushButton *start_button = new QPushButton(tr("Start"));
  QPushButton *pause_button = new QPushButton(tr("Pause/Resume"));
  QPushButton *reset_button = new QPushButton(tr("Reset"));
  QPushButton *leave_button = new QPushButton(tr("Leave game"));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(sound);
  vbox->addWidget(start_button);
  vbox->addWidget(pause_button);
  vbox->addWidget(reset_button);
  vbox->addStretch(1);
  vbox->addWidget(leave_button);

  qgb->setLayout(vbox);

  connect(start_button,SIGNAL(clicked()),scene,SLOT(slot_start()));
  connect(reset_button,SIGNAL(clicked()),scene,SLOT(slot_reset()));
  connect(pause_button,SIGNAL(clicked()),scene,SLOT(slot_pause()));
  connect(leave_button,SIGNAL(clicked()),this,SLOT(slot_leave_game()));
  connect(sound,SIGNAL(toggled(bool)),scene,SLOT(slot_manage_sound(bool)));

  return qgb;
}


/* Change les couleurs pour le light/dark mode */
void MainWindow::slot_light_mode(bool isChecked){
  if(isChecked){
    scene->setBackgroundBrush(Qt::darkGray);
  }else{
    scene->setBackgroundBrush(Qt::black);
  }
}


void MainWindow::slot_leave_game(){
  this->close();
}


/* Ne fonctionne que lorsque je clic dans myview
void MainWindow::mousePressEvent(QMouseEvent *event){
  qDebug() << "ok";
  myview->setFocus();
}
*/
