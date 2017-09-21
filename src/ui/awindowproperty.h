#ifndef AWINDOWPROPERTY_H
#define AWINDOWPROPERTY_H

#include <QDialog>

namespace Ui {
class AWindowProperty;
}
class TScene;
class AWindowProperty : public QDialog
{
    Q_OBJECT

public:
    explicit AWindowProperty(TScene *scene, QWidget *parent = 0);
    ~AWindowProperty();
    void setAllWindowName(const QStringList &windowNamelist);
protected:
    void setWindowSize(qreal width, qreal height);
    void setWidowName(const QString &name);
    void setBrush(const QBrush &brush);

    void closeEvent(QCloseEvent *event);
signals:
    void okSave(TScene *scene);
    void cancle(TScene *scene);
private slots:
    void on_pushButtonBackground_clicked();

    void on_pushButtonOk_clicked();

    void on_pushButtonCancle_clicked();

    void on_pushButtonSelectBackPixmap_clicked();

private:
    Ui::AWindowProperty *ui;
    QStringList m_allWindowName;

    TScene *m_scene = nullptr;
    bool m_ok = false;
    bool m_cancle = false;
};

#endif // AWINDOWPROPERTY_H
