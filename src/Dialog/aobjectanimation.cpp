#include "aobjectanimation.h"
#include "ui_aobjectanimation.h"
#include "itemProperty/apixmapanimation.h"
#include "drawCore/Graphics/GraphicsPub.h"
#include "drawCore/Plot/plotpub.h"
#include "jsdesignwidget.h"
#include <QMessageBox>
#include <QColorDialog>
#include "ageneralfunction.h"
#include "adrawmainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include "ui/ashowinfoanimation.h"

AObjectAnimation::AObjectAnimation(TItemEx *item, QWidget *parent) : QDialog(parent), ui(new Ui::AObjectAnimation), m_item(item)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);

    setWindowModality(Qt::WindowModal);
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

    ui->comboBoxBrushStyle->setCurrentIndex(item->fGetBackGroundStyle());

    ui->lineEditDeviceAddr->setInputMask("hhh");
    ui->comboBoxDeviceName->setCurrentText(m_item->fGetDeviceName());
    ui->lineEditDeviceAddr->setText(QString::number(m_item->fGetRegisterAddr()));
    ui->comboBoxDeviceType->setCurrentIndex(m_item->fGetRegisterType());

    palette = ui->labelBrushColor->palette();
    palette.setColor(QPalette::Window, item->fGetBackGroundColor());
    ui->labelBrushColor->setPalette(palette);
    ui->spinBoxBrushAlpha->setValue(item->fGetBackGroundColor().alpha());

    //Pixmap
    TPixmap *t_pixmap = qobject_cast<TPixmap *>(m_item);
    if(t_pixmap) {
        m_pixmap = new APixmapAnimation(t_pixmap, this);
        ui->tabWidget->addTab(m_pixmap, "图片");
    }
}


AObjectAnimation::~AObjectAnimation()
{
    if(ui) delete ui;
}
void AObjectAnimation::setAllDeviceName(QStringList alldeviceName)
{
    ui->comboBoxDeviceName->addItems(alldeviceName);
    ui->comboBoxDeviceName->setCurrentText(m_item->fGetDeviceName());
}

void AObjectAnimation::ItemSave()
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
    //device
    m_item->fSetDeviceName(ui->comboBoxDeviceName->currentText());
    m_item->fSetRegisterAddr(ui->lineEditDeviceAddr->text().toInt());
    m_item->fSetRegisterType(ui->comboBoxDeviceType->currentIndex());

}

void AObjectAnimation::on_pushButtonOk_clicked()
{
    ItemSave();     //ItemEx
    if(m_pixmap)
        m_pixmap->save();  //Pixmap
    AShowInfoAnimation *info = new AShowInfoAnimation("保存成功");
    info->show();
    close();
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

void AObjectAnimation::on_pushButtonLeftAction_clicked()
{
    JSDesignWidget * jsDesignWidget = new JSDesignWidget(m_item->fGetName() + qobject_cast<QPushButton *>(sender())->text(), this);
    jsDesignWidget->addJSWidget(tr("鼠标按压"), m_item->fGetMousePressJS());
    jsDesignWidget->addJSWidget(tr("鼠标双击"), m_item->fGetMouseDoublicJS());
    jsDesignWidget->addJSWidget(tr("鼠标释放"), m_item->fGetMouseRelease());

    connect(jsDesignWidget, &JSDesignWidget::okData, [this](QMap<QString, QString> jsmap){
        IF_TRUE_RUN(jsmap.contains(tr("鼠标按压")), m_item->fSetMousePressJS(jsmap.value(tr("鼠标按压"))))
        IF_TRUE_RUN(jsmap.contains(tr("鼠标双击")), m_item->fSetMouseDoublicJS(jsmap.value(tr("鼠标双击"))))
        IF_TRUE_RUN(jsmap.contains(tr("鼠标释放")), m_item->fSetMouseRelease(jsmap.value(tr("鼠标释放"))))
    });
    jsDesignWidget->show();
}


void AObjectAnimation::on_pushButtonRightAction_clicked()
{
    JSDesignWidget * jsDesignWidget = new JSDesignWidget(m_item->fGetName() + qobject_cast<QPushButton *>(sender())->text(), this);
    jsDesignWidget->addJSWidget(tr("鼠标按压"), m_item->fGetMouseMenu());
    jsDesignWidget->addJSWidget(tr("鼠标双击"));
    jsDesignWidget->addJSWidget(tr("鼠标释放"));

    connect(jsDesignWidget, &JSDesignWidget::okData, [this](QMap<QString, QString> jsmap){
        IF_TRUE_RUN(jsmap.contains(tr("鼠标按压")), m_item->fSetMouseMenu(jsmap.value(tr("鼠标按压"))))
    });
    jsDesignWidget->show();
}

void AObjectAnimation::on_pushButtonMouseAction_clicked()
{
    JSDesignWidget * jsDesignWidget = new JSDesignWidget(m_item->fGetName() + qobject_cast<QPushButton *>(sender())->text(), this);
    jsDesignWidget->addJSWidget(tr("鼠标进入"), m_item->fGetMouseEnterJS());
    jsDesignWidget->addJSWidget(tr("鼠标移动"), m_item->fGetMouseMove());
    jsDesignWidget->addJSWidget(tr("鼠标离开"), m_item->fGetMouseLeaveJS());

    connect(jsDesignWidget, &JSDesignWidget::okData, [this](QMap<QString, QString> jsmap){
        IF_TRUE_RUN(jsmap.contains(tr("鼠标进入")), m_item->fSetMouseEnterJS(jsmap.value(tr("鼠标进入"))))
        IF_TRUE_RUN(jsmap.contains(tr("鼠标移动")), m_item->fSetMouseMove(jsmap.value(tr("鼠标移动"))))
        IF_TRUE_RUN(jsmap.contains(tr("鼠标离开")), m_item->fSetMouseLeaveJS(jsmap.value(tr("鼠标离开"))))
    });
    jsDesignWidget->show();
}

