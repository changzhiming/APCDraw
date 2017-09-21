#ifndef AOBJECTANIMATION_H
#define AOBJECTANIMATION_H

#include <QDialog>
class TItemEx;
namespace Ui {
class AObjectAnimation;
}
class APixmapAnimation;
class AObjectAnimation : public QDialog
{
    Q_OBJECT
public:
    explicit AObjectAnimation(TItemEx *item, QWidget *parent = 0);
    ~AObjectAnimation();
    void setAllDeviceName(QStringList alldeviceName);
private:
    void ItemSave();
private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonLineColor_clicked();
    void on_pushButtonBrushColor_clicked();
    void on_pushButtonLeftAction_clicked();
    void on_pushButtonRightAction_clicked();
    void on_pushButtonMouseAction_clicked();

private:
    Ui::AObjectAnimation *ui;
    APixmapAnimation *m_pixmap = nullptr;
    QWidget *m_pixmapWidget = nullptr;
    TItemEx *m_item;
};

#endif // AOBJECTANIMATION_H
