#include "ashowinfoanimation.h"
#include "ui_ashowinfoanimation.h"
#include <QPropertyAnimation>
#include <QDebug>
AShowInfoAnimation::AShowInfoAnimation(QString info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AShowInfoAnimation)
{
    ui->setupUi(this);
    ui->label->setText(info);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation, &QPropertyAnimation::finished, [this](){
       close();
    });
}

AShowInfoAnimation::~AShowInfoAnimation()
{
    delete ui;
}
