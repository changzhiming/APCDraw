#include "awindowproperty.h"
#include "ui_awindowproperty.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "aglobal.h"
#include "drawCore/Scene/Scene.h"
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>

AWindowProperty::AWindowProperty(TScene *scene, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AWindowProperty), m_scene(scene)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);

    setWindowModality(Qt::WindowModal);

    ui->comboBoxBrushStyle->addItem(tr("Qt::NoBrush"), (int)Qt::NoBrush);
    ui->comboBoxBrushStyle->addItem(tr("Qt::SolidPattern"),  (int)Qt::SolidPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense1Pattern"), (int)Qt::Dense1Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense2Pattern"), (int)Qt::Dense2Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense3Pattern"), (int)Qt::Dense3Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense4Pattern"), (int) Qt::Dense4Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense5Pattern"), (int)Qt::Dense5Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense6Pattern"), (int)Qt::Dense6Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::Dense7Pattern"), (int)Qt::Dense7Pattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::HorPattern"), (int)Qt::HorPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::VerPattern"), (int)Qt::VerPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::CrossPattern"), (int)Qt::CrossPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::BDiagPattern"), (int)Qt::BDiagPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::FDiagPattern"), (int)Qt::FDiagPattern);
    ui->comboBoxBrushStyle->addItem(tr("Qt::DiagCrossPattern"), (int)Qt::DiagCrossPattern);

    IF_TRUE_RUN(!scene, return)
    setWindowSize(QApplication::desktop()->width(), QApplication::desktop()->height());
    IF_TRUE_RUN(m_scene->sceneRect().width() || m_scene->sceneRect().height(), setWindowSize(m_scene->sceneRect().width(), m_scene->sceneRect().height()))
    setWidowName(m_scene->fGetName());
    setBrush(m_scene->backgroundBrush());
}

AWindowProperty::~AWindowProperty()
{
    delete ui;
}

void AWindowProperty::setWindowSize(qreal width, qreal height)
{
    ui->lineEditWidth->setText(QString::number(width));
    ui->lineEditHeight->setText(QString::number(height));
}
void AWindowProperty::setWidowName(const QString &name)
{
    ui->lineEditWindowName->setText(name);
}
void AWindowProperty::setBrush(const QBrush &brush)
{
    QPalette palette = ui->pushButtonBackground->palette();
    palette.setColor(QPalette::Button, brush.color());
    ui->pushButtonBackground->setPalette(palette);

    ui->comboBoxBrushStyle->setCurrentIndex(brush.style());
}

void AWindowProperty::setAllWindowName(const QStringList &windowNamelist)
{
    m_allWindowName = windowNamelist;
}
void AWindowProperty::closeEvent(QCloseEvent *event)
{
    IF_TRUE_RUN(!m_ok && !m_cancle, emit cancle(m_scene))
    event->accept();
}

void AWindowProperty::on_pushButtonBackground_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("选择窗体背景色"));
    if(color.isValid()) {
        QPalette palette = ui->pushButtonBackground->palette();
        palette.setColor(QPalette::Button, color);
        ui->pushButtonBackground->setPalette(palette);
    }
}

void AWindowProperty::on_pushButtonOk_clicked()
{
    if(ui->lineEditWindowName->text().isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("窗体名不能为空"), tr("确定"));
        return;
    }
    if(m_allWindowName.contains(ui->lineEditWindowName->text())) {
        QMessageBox::warning(this, tr("错误"), tr("窗体名已经存在"), tr("确定"));
        return;
    }
    QBrush brush;
    if(ui->lineEditBackPixmap->text().isEmpty()) {
        brush.setColor(ui->pushButtonBackground->palette().color(QPalette::Button));
        brush.setStyle((Qt::BrushStyle)ui->comboBoxBrushStyle->currentIndex());
    } else {
        brush.setColor(ui->pushButtonBackground->palette().color(QPalette::Button));
        brush.setTexture(QPixmap(ui->lineEditBackPixmap->text()).scaled(ui->lineEditWidth->text().toInt(), ui->lineEditHeight->text().toInt()));
    }
    m_scene->fSetName(ui->lineEditWindowName->text());
    m_scene->setBackgroundBrush(brush);
    m_scene->setSceneRect(0, 0, ui->lineEditWidth->text().toInt(), ui->lineEditHeight->text().toInt());
    m_ok = true;
    emit okSave(m_scene);
    close();
}

void AWindowProperty::on_pushButtonCancle_clicked()
{
    m_cancle = true;
    emit cancle(m_scene);
    close();
}

void AWindowProperty::on_pushButtonSelectBackPixmap_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开背景图片"), "", tr("*.png *.jpg"));
    ui->lineEditBackPixmap->setText(fileName);
}
