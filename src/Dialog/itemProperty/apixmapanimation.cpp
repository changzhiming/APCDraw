#include "apixmapanimation.h"
#include "ui_apixmapanimation.h"
#include "drawCore/Graphics/GraphicsPub.h"
#include <QFileDialog>
APixmapAnimation::APixmapAnimation(TPixmap *pixmap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::APixmapAnimation), m_pixmap(pixmap)
{
    ui->setupUi(this);
    if(pixmap)
        ui->lineEditPixmapPath->setText(pixmap->fGetPixmapPath());
}

APixmapAnimation::~APixmapAnimation()
{
    delete ui;
}

void APixmapAnimation::on_pushButtonSelecPixamaptPath_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.jpg)"));
    if(!fileName.isEmpty())
        ui->lineEditPixmapPath->setText(fileName);
}
void APixmapAnimation::save()
{
    if(m_pixmap) {
        m_pixmap->fSetPixmapPath(ui->lineEditPixmapPath->text());
    }
}
