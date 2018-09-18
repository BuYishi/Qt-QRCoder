#include "Widget.h"
#include "ui_Widget.h"
#include "qrencode/qrencode.h"
#include <QMessageBox>
#include <QPainter>
#include <QtDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_encodeButton_clicked()
{

    QString textToEncode = ui->textToEncodeTextEdit->toPlainText();
    if (textToEncode.isEmpty())
        textToEncode = ui->textToEncodeTextEdit->placeholderText();
//    int size, const unsigned char *data, int version, QRecLevel level
    const QByteArray &byteArray = textToEncode.toUtf8();
    const char *data = byteArray.constData();
    qDebug() << data;
    QRcode *qrcode = QRcode_encodeData(strlen(data), reinterpret_cast<const unsigned char *>(data), 0, QR_ECLEVEL_M);
    if (Q_NULLPTR == qrcode)
        QMessageBox::critical(this, "Error", "无法生成二维码，错误未知");
    else
    {
        QPixmap pixmap(100, 100);
        QPainter painter(&pixmap);
        QRectF *rect = new QRectF[qrcode->width * qrcode->width];
        for (int y = 0; y < qrcode->width; ++y)
        {
            for (int x = 0; x < qrcode->width; ++x)
            {
                if (qrcode->data[qrcode->width * y + x] & 1)
                    ;
            }
        }
//        ui->encodedLabel->setPixmap();
        qDebug() << qrcode->width;
        delete[] rect;
    }
}
