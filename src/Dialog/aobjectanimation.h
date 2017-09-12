#ifndef AOBJECTANIMATION_H
#define AOBJECTANIMATION_H

#include <QDialog>
class TItemEx;
namespace Ui {
class AObjectAnimation;
class APixmaptAnimation;
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
    Ui::APixmaptAnimation *ui_pixmap = nullptr;
    QWidget *m_pixmapWidget = nullptr;

    TItemEx *m_item;
};

#endif // AOBJECTANIMATION_H
