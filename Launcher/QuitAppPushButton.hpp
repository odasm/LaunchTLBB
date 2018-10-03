#ifndef QUITAPPPUSHBUTTON_HPP
#define QUITAPPPUSHBUTTON_HPP

#include <QPushButton>

class QuitAppPushButton final : public QPushButton
{
    Q_OBJECT
  public:
    explicit QuitAppPushButton(QWidget *parent = nullptr);

  signals:

  public slots:
};

#endif // QUITAPPPUSHBUTTON_HPP
