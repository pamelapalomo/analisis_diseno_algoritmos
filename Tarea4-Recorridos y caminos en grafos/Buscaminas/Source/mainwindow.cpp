#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Iniciar juego
    altura=16;
    anchura=30;
    n_minas=99;
    partida_perdida=false;
    int n_banderas=0;
    partida_perdida=false;
    n_banderas=0;
    _engine=new Engine(altura,anchura,n_minas);

    //Generar ventana
    ui->setupUi(this);
    this->resize(800,700);
    this->setWindowTitle("Buscaminas: 99 minas");

    centralWidget=new QWidget(this);
    verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setGeometry(QRect(20,50,760,600));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setSpacing(30);

    //Agregar contador de minas
    lcdNumberCounter=new QLCDNumber(verticalLayoutWidget);
    verticalLayout->addWidget(lcdNumberCounter);
    lcdNumberCounter->display(n_banderas);

    //Agregar tablero
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    _mineButton =new MineButton**[altura];
    for(int i=0;i<altura;i++){
        _mineButton[i]=new MineButton*[anchura];
        for(int j=0;j<anchura;j++){
            _mineButton[i][j]=new MineButton(verticalLayoutWidget);
            _mineButton[i][j]->setFixedSize(25,25);
            gridLayout->addWidget(_mineButton[i][j], i,j, 1, 1);

            //Color de los botones
            QPalette pal = _mineButton[i][j]->palette();
            pal.setColor(QPalette::Button, QColor(Qt::lightGray));
            _mineButton[i][j]->setAutoFillBackground(true);
            _mineButton[i][j]->setPalette(pal);
            _mineButton[i][j]->update();

            //Acciones de los botones
            connect(_mineButton[i][j], &MineButton::clicked, [this,i,j](){revelarCelda(i,j);});
            connect(_mineButton[i][j], &MineButton::rightClicked, [this,i,j](){colocarBandera(i,j);});
        }
    }
    verticalLayout->addLayout(gridLayout);

    //Agregar boton para iniciar un juego nuevo
    newGameButton = new QPushButton(verticalLayoutWidget);
    newGameButton->setText("Nuevo juego");
    connect(newGameButton, &QPushButton::clicked, [this](){reset();});
    verticalLayout->addWidget(newGameButton);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::revelarCelda(int i,int j){
    //Si el juego ha terminado, la celda tiene una bandera o la celda esta revelada no se hace nada
    if(partida_perdida || _engine->partidaGanada() || _engine->tieneBandera(i,j) || _engine->estaRevelada(i,j)) return;

    //Si la celda tiene una mina, se pierde el juego
    if(_engine->getMinas(i,j)==-1){
        cambiarBoton(i,j);
        partida_perdida=true;
        mostrarVentanaResultado();
        return;
    }

    //Si la celda no contiene minas, se ejecuta el algoritmo de busqueda
    if(_engine->getMinas(i,j)>-1){
        list<pair<int,int> > celdas_reveladas=_engine->destaparCeldas(i,j);
        for(list<pair<int,int> >::iterator it=celdas_reveladas.begin();it!=celdas_reveladas.end();it++) cambiarBoton(it->first,it->second);
        if(_engine->partidaGanada()) mostrarVentanaResultado();
        return;
    }

}

void MainWindow::cambiarBoton(int i, int j){
    //Si la celda tiene una mina, revelar todas las minas
    if(_engine->getMinas(i,j)==-1){
        QPalette pal = _mineButton[i][j]->palette();
        pal.setColor(QPalette::Button, QColor(Qt::red));
        _mineButton[i][j]->setAutoFillBackground(true);
        _mineButton[i][j]->setPalette(pal);
        _mineButton[i][j]->update();

        //Revelar el resto de las minas
        QPixmap pixmap1("imagenes/mina.png");
        QIcon ButtonIcon1(pixmap1);
        QPixmap pixmap2("imagenes/check.png");
        QIcon ButtonIcon2(pixmap2);
        QPixmap pixmap3("imagenes/cross.png");
        QIcon ButtonIcon3(pixmap3);
        for(int ii=0;ii<altura;ii++){
            for(int jj=0;jj<anchura;jj++){
                if(_engine->getMinas(ii,jj)==-1){
                    if(_engine->tieneBandera(ii,jj)) _mineButton[ii][jj]->setIcon(ButtonIcon2);
                    else _mineButton[ii][jj]->setIcon(ButtonIcon1);
                }
                else if(_engine->tieneBandera(ii,jj)) _mineButton[ii][jj]->setIcon(ButtonIcon3);
                _mineButton[ii][jj]->setIconSize(QSize(20,20));
            }
        }

        return;
    }

    //Si la celda contiene un numero mayor que cero, revelar el numero
    if(_engine->getMinas(i,j)>0){
        _mineButton[i][j]->setText(QString::number(_engine->getMinas(i,j)));
        return;
    }

    //Si la celda tiene un cero, cambiar de color
    QPalette pal = _mineButton[i][j]->palette();
    pal.setColor(QPalette::Button, QColor(Qt::darkGray));
    _mineButton[i][j]->setAutoFillBackground(true);
    _mineButton[i][j]->setPalette(pal);
    _mineButton[i][j]->update();
}

void MainWindow::colocarBandera(int i, int j){
    //Si la celda esta revelada, no se hace nada
    if(_engine->estaRevelada(i,j)) return;

    //Si la celda tiene una bandera, se coloca un signo de interrogacion
    if(_engine->tieneBandera(i,j)){
        _engine->quitarBandera(i,j);
        QPixmap pixmap("imagenes/question.png");
        QIcon ButtonIcon(pixmap);
        _mineButton[i][j]->setIcon(ButtonIcon);
        _mineButton[i][j]->setIconSize(QSize(20,20));
        return;
    }

    //Si la celda tiene un signo de interrogacion, se quita
    if(_engine->tieneInterrogacion(i,j)){
        _engine->quitarInterrogacion(i,j);
        n_banderas--;
        lcdNumberCounter->display(n_banderas);
        _mineButton[i][j]->setIcon(QIcon());
        return;
    }

    //Si la celda no tiene una bandera, se coloca una
    _engine->ponerBandera(i,j);
    QPixmap pixmap("imagenes/bandera.png");
    QIcon ButtonIcon(pixmap);
    _mineButton[i][j]->setIcon(ButtonIcon);
    _mineButton[i][j]->setIconSize(QSize(20,20));
    n_banderas++;
    lcdNumberCounter->display(n_banderas);
}

void MainWindow::mostrarVentanaResultado(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Resultado");
    if(partida_perdida) msgBox.setText("¡Has perdido!");
    else msgBox.setText("¡Has ganado!");
    msgBox.exec();
}

void MainWindow::reset(){
    //Crear un nuevo juego
    delete _engine;
    _engine=new Engine(altura, anchura, n_minas);
    partida_perdida=false;

    //Reiniciar el contador de minas
    n_banderas=0;
    lcdNumberCounter->display(n_banderas);

    //Restaurar botones
    for(int i=0;i<altura;i++){
        for(int j=0;j<anchura;j++){
            _mineButton[i][j]->setIcon(QIcon());
            _mineButton[i][j]->setText(QString());
            QPalette pal = _mineButton[i][j]->palette();
            pal.setColor(QPalette::Button, QColor(Qt::lightGray));
            _mineButton[i][j]->setAutoFillBackground(true);
            _mineButton[i][j]->setPalette(pal);
            _mineButton[i][j]->update();
        }
    }
}
