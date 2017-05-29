#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton:public QPushButton
{
    Q_OBJECT
public:
    explicit MineButton(QWidget *parent=0);
private slots:
    void mousePressEvent(QMouseEvent *);
signals:
    void rightClicked();
};

#endif // MINEBUTTON_H
