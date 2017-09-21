#ifndef ASHOWINFOANIMATION_H
#define ASHOWINFOANIMATION_H

#include <QWidget>

namespace Ui {
class AShowInfoAnimation;
}

class AShowInfoAnimation : public QWidget
{
    Q_OBJECT

public:
    explicit AShowInfoAnimation(QString info, QWidget *parent = 0);
    ~AShowInfoAnimation();

private:
    Ui::AShowInfoAnimation *ui;
};

#endif // ASHOWINFOANIMATION_H
