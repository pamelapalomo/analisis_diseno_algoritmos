#include "minebutton.h"

MineButton::MineButton(QWidget *parent):QPushButton(parent)
{
}

void MineButton::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::RightButton) emit rightClicked();
    else if(e->button()==Qt::LeftButton) emit clicked();
}
