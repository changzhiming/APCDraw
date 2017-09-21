#ifndef APIXMAPANIMATION_H
#define APIXMAPANIMATION_H

#include <QWidget>

namespace Ui {
class APixmapAnimation;
}
class TPixmap;
class APixmapAnimation : public QWidget
{
    Q_OBJECT

public:
    explicit APixmapAnimation(TPixmap *pixmap, QWidget *parent = 0);
    ~APixmapAnimation();
    void save();
private slots:
    void on_pushButtonSelecPixamaptPath_clicked();

private:
    Ui::APixmapAnimation *ui;
    TPixmap *m_pixmap = nullptr;
};

#endif // APIXMAPANIMATION_H
