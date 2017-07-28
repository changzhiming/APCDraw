#include "aobjectanimation.h"
#include "ui_aobjectanimation.h"

#include "jsdesignwidget.h"
#include <QMessageBox>
#include <QColorDialog>

AObjectAnimation::AObjectAnimation(TItemEx *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AObjectAnimation), m_item(item)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);
    //初始化参数
    ui->lineEditObjname->setText(item->objectName());
    ui->lineEditHintText->setText(item->toolTip());
    ui->lineEditName->setText(item->fGetName());

    ui->doubleSpinBoxStartX->setValue(item->pos().x());
    ui->doubleSpinBoxStartY->setValue(item->pos().y());
    ui->doubleSpinBoxWidth->setValue(item->fGetBoundingRect().width());
    ui->doubleSpinBoxHeight->setValue(item->fGetBoundingRect().height());
    ui->spinBoxLayerZ->setValue(item->zValue());
    ui->spinBoxRotationAngle->setValue(item->fGetRotateAngle());

    ui->comboBoxLineStyle->setIconSize(QSize(100, 20));
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleNoPen.png")), tr("Qt::NoPen"),(int)Qt::NoPen);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleSolidLine.png")), "Qt::SolidLine", (int)Qt::SolidLine);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleDashLine.png")), "Qt::DashLine", (int)Qt::DashLine);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleDotLine.png")), "Qt::DotLine", (int)Qt::DotLine);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleDashDotLine.png")),"Qt::DashDotLine",  (int)Qt::DashDotLine);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleDashDotDotLine.png")), "Qt::DashDotDotLine",  (int)Qt::DashDotDotLine);
    ui->comboBoxLineStyle->addItem(QIcon(tr("://image/line/StyleCustomDashLine.png")), "Qt::CustomDashLine",(int)Qt::CustomDashLine);
    ui->comboBoxLineStyle->setCurrentIndex(item->fGetLineStyle());

    ui->spinBoxLineWidth->setValue(item->fGetLineWidth());
    QPalette palette = ui->labelLineColor->palette();
    palette.setColor(QPalette::Window, item->fGetLineColor());
    ui->labelLineColor->setPalette(palette);

    ui->spinBoxLineAlpha->setValue(item->fGetLineColor().alpha());
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
//    ui->comboBoxBrushStyle->addItem(tr("Qt::LinearGradientPattern"), (int)Qt::LinearGradientPattern);
//    ui->comboBoxBrushStyle->addItem(tr("Qt::RadialGradientPattern"), (int)Qt::RadialGradientPattern);
//    ui->comboBoxBrushStyle->addItem(tr("Qt::ConicalGradientPattern"), (int)Qt::ConicalGradientPattern);
    ui->comboBoxBrushStyle->setCurrentIndex(item->fGetBackGroundStyle());

    palette = ui->labelBrushColor->palette();
    palette.setColor(QPalette::Window, item->fGetBackGroundColor());
    ui->labelBrushColor->setPalette(palette);
    ui->spinBoxBrushAlpha->setValue(item->fGetBackGroundColor().alpha());

    connect(ui->pushButtonLeftAction, &QPushButton::clicked, [=](){
        JSDesignWidget * jsDesignWidget = new JSDesignWidget(item);
        jsDesignWidget->show();
    });
}

AObjectAnimation::~AObjectAnimation()
{
    delete ui;
}


void AObjectAnimation::on_pushButtonOk_clicked()
{
    m_item->setObjectName(ui->lineEditObjname->text());
    m_item->setToolTip(ui->lineEditHintText->text());
    m_item->fSetName(ui->lineEditName->text());
    m_item->setPos(ui->doubleSpinBoxStartX->value(), ui->doubleSpinBoxStartY->value());
    m_item->fSetBoundingWidthHeight(ui->doubleSpinBoxWidth->value(), ui->doubleSpinBoxHeight->value());
    m_item->setZValue(ui->spinBoxLayerZ->value());
    m_item->fSetRotateAngle(ui->spinBoxRotationAngle->value());

    m_item->fSetLineStyle(ui->comboBoxLineStyle->currentData().toInt());
    m_item->fSetLineWidth(ui->spinBoxLineWidth->value());
    m_item->fSetLineColor(ui->labelLineColor->palette().color(QPalette::Background));
    m_item->fSetLineAlpha(ui->spinBoxLineAlpha->value());

    m_item->fSetBackGroundStyle(ui->comboBoxBrushStyle->currentData().toInt());
    m_item->fSetBackGroundColor(ui->labelBrushColor->palette().color(QPalette::Background));
    m_item->fSetBackGroundAlpha(ui->spinBoxBrushAlpha->value());
}

void AObjectAnimation::on_pushButtonClose_clicked()
{
    close();
}

void AObjectAnimation::on_pushButtonLineColor_clicked()
{
    QColor t_color = QColorDialog::getColor(m_item->fGetLineColor(), this);
    QPalette palette = ui->labelLineColor->palette();
    palette.setColor(QPalette::Background, t_color);
    ui->labelLineColor->setPalette(palette);
}

void AObjectAnimation::on_pushButtonBrushColor_clicked()
{
    QColor t_color = QColorDialog::getColor(m_item->fGetBackGroundColor(), this);
    QPalette palette = ui->labelBrushColor->palette();
    palette.setColor(QPalette::Background, t_color);
    ui->labelBrushColor->setPalette(palette);
}
