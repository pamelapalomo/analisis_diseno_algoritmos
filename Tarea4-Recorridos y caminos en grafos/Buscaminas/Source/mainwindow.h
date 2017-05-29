#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "engine.h"
#include "minebutton.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QSignalMapper>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Engine* _engine;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QWidget *horizontalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumberCounter;
    QGridLayout *gridLayout;
    MineButton*** _mineButton;
    QPushButton* newGameButton;
    bool partida_perdida;
    int altura, anchura, n_banderas, n_minas;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void cambiarBoton(int,int);
    void colocarBandera(int,int);
    void mostrarVentanaResultado();

private:
    Ui::MainWindow *ui;

public slots:
    void revelarCelda(int,int);
    void reset();
};

#endif // MAINWINDOW_H
