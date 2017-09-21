#include "InputEdit.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

TInputEdit::TInputEdit(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :
    TWidgets(atScenePos, bounDingRect, pen, brush)
{

    fSetType(TItemFactory::InputEdit);
    mText = tr("");
    fSetFocusAble(true);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod, true);
    setAcceptHoverEvents(true);
}

TInputEdit::~TInputEdit()
{
    if(timer)
        timer->deleteLater();
}

TItem* TInputEdit::fCopy()
{
    TInputEdit *InputEdit = new TInputEdit();

    InputEdit->fCopy(this);

    return InputEdit;
}

void TInputEdit::fCopy(TInputEdit *InputEditFrom)
{
    if(NULL == InputEditFrom)
        return;

    TWidgets::fCopy(InputEditFrom);
    this->fSetText(InputEditFrom->fGetText());
}

void TInputEdit::fDraw(QPainter *painter)
{
    QFont font = painter->font();
    font.setPointSize(0.7 * (m_boundingRect.height()) + 1);
    painter->setFont(font);

    painter->save();
    if(hasFocus()) {
        painter->setPen(QPen(Qt::blue));
        painter->setBrush(Qt::white);
    }
    painter->drawRect(m_boundingRect);
    painter->restore();
    painter->drawText(m_boundingRect, Qt::AlignLeft | Qt::AlignVCenter, mText);
    if(m_showCursor) {
        QFontMetricsF fm(font);
        QRectF showCursorRect = m_boundingRect;
        showCursorRect.adjust(0, 2, fm.width(mText), -2);

        painter->drawText(showCursorRect, Qt::AlignLeft | Qt::AlignVCenter, mText + '|');
    }
}

void TInputEdit::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Backspace:
        mText = mText.left(mText.length() - 1);
        break;
    case Qt::Key_Return:
        clearFocus();
        break;
    default:
        mText += event->text();
        break;
    }

    fUpdate();
    QGraphicsItem::keyReleaseEvent(event);
}
void TInputEdit::focusInEvent(QFocusEvent *event)
{
    if(!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this](){
            m_showCursor = !m_showCursor;
            update();
        });
    }
    timer->start(1000);
    TWidgets::focusInEvent(event);
}

void TInputEdit::focusOutEvent(QFocusEvent *event)
{
    if(timer) {
        timer->stop();
        m_showCursor = false;
    }
    emit mTextChange(mText);
    TWidgets::focusOutEvent(event);
}

void TInputEdit::inputMethodEvent(QInputMethodEvent *event)
{
    mText += event->commitString();
    update();
}

QVariant TInputEdit::inputMethodQuery(Qt::InputMethodQuery query) const
{
    if(query == Qt::ImEnabled)
        return true;
    if(query == Qt::ImCursorPosition)
        return mText.size();
    return false;
}

void TInputEdit::fSetText(const QString &Text)
{
    mText = Text;
}

QString TInputEdit::fGetText()
{
    return mText;
}

