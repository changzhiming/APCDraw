#ifndef TTEXT_H
#define TTEXT_H

#include "../Graphics/Graphics.h"

/////////////////////////////////////////////////  文字  /////////////////////////////////////////////////////
class TText : public TGraphics
{
    Q_PROPERTY(QString mText READ fGetText WRITE fSetText)
    Q_PROPERTY(QString mFontFamily READ fGetFontFamily WRITE fSetFontFamily)
    Q_PROPERTY(int mFontSize READ fGetFontSize  WRITE fSetFontSize)
    Q_PROPERTY(bool mFontBlod READ fGetFontBlod  WRITE fSetFontBlod)
    Q_PROPERTY(bool mFontItalic READ fGetFontItalic  WRITE fSetFontItalic)
    Q_PROPERTY(int mFontSpacing READ fGetFontSpacing  WRITE fSetFontSpacing)
    Q_PROPERTY(bool mFontUnderLine READ fGetFontUnderLine  WRITE fSetFontUnderLine)
    Q_PROPERTY(bool mFontStrikeOut READ fGetFontStrikeOut  WRITE fSetFontStrikeOut)

    Q_OBJECT
public:
    TText(QPointF atScenePos = QPointF(0, 0), QRectF bounDingRect = QRectF(QPointF(0, 0), QSize(40, 40)), QPen pen =QPen(Qt::black),
          QBrush brush = QBrush(Qt::white));

    virtual ~TText();
    virtual TItem *fCopy();
    virtual void fCopy(TText *TextFrom);
    virtual void fDraw(QPainter *painter);

    void fSetFontFamily(const QString &Family);
    QString fGetFontFamily() const;
    void fSetFontSize(int Size);
    int fGetFontSize() const;
    void fSetFontSpacing(int Spacing);
    int fGetFontSpacing() const;
    void fSetFontBlod(bool Blod);
    bool fGetFontBlod() const;
    void fSetFontItalic(bool Italic);
    bool fGetFontItalic() const;
    void fSetFontUnderLine(bool UnderLine);
    bool fGetFontUnderLine() const;
    void fSetFontStrikeOut(bool StrikeOut);
    bool fGetFontStrikeOut() const;

    void fSetText(const QString &Text);
    QString fGetText() const;

protected:
    QString mText;
    QString mFontFamily;
    int mFontSize;
    bool mFontBlod;
    bool mFontItalic;
    int mFontSpacing;
    bool mFontUnderLine;
    bool mFontStrikeOut;


};
#endif // TTEXT_H
