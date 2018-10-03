#ifndef PLAYGAMEPUSHBUTTON_HPP
#define PLAYGAMEPUSHBUTTON_HPP

#include <QPushButton>

class PlayGamePushButton final : public QPushButton
{
    Q_OBJECT
  public:
    explicit PlayGamePushButton(QWidget *parent = nullptr);

  public:
    void setIsClickAble(bool isClickAble);

  private:
    bool m_isClickAble;

  signals:

  public slots:

};

#endif // PLAYGAMEPUSHBUTTON_HPP
