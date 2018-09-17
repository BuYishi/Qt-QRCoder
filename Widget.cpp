#include "Widget.h"
#include "ui_Widget.h"
#include <QZXing.h>
#include <zxing/WriterException.h>
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
    try
    {
        QString textToEncode = ui->textToEncodeTextEdit->toPlainText();
        if (textToEncode.isEmpty())
            textToEncode = "在此输入要编码的文本";
        //        textToEncode = ui->textToEncodeTextEdit->placeholderText();
        qDebug() << textToEncode;
        const QImage &encodedImage = QZXing::encodeData(textToEncode, QZXing::EncoderFormat_QR_CODE);
        ui->encodedLabel->setPixmap(QPixmap::fromImage(encodedImage));
    }
    catch (const zxing::WriterException *ex)
    {
        qDebug() << ex->what();
    }
}
