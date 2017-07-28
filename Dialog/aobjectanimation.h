#ifndef AOBJECTANIMATION_H
#define AOBJECTANIMATION_H

#include <QDialog>
#include "drawCore/Item/ItemEx.h"

namespace Ui {
class AObjectAnimation;
}

class AObjectAnimation : public QDialog
{
    Q_OBJECT

public:
    explicit AObjectAnimation(TItemEx *item, QWidget *parent = 0);
    ~AObjectAnimation();
private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonLineColor_clicked();

    void on_pushButtonBrushColor_clicked();

private:
    Ui::AObjectAnimation *ui;
    TItemEx *m_item;
};

#endif // AOBJECTANIMATION_H
