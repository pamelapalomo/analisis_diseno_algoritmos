#ifndef WINDOW_H
#define WINDOW_H


class QPushButton;
class Window : public QWidget
{
 public:
  explicit Window(QWidget *parent = 0);
 private:
 QPushButton *m_button;
};

#endif // WINDOW_H
