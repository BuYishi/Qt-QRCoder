#include "Widget.h"
#include "ui_Widget.h"
#include "qrencode/qrencode.h"
#include <QClipboard>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QStandardPaths>
#include <QtDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    menu(new QMenu(this))
{
    ui->setupUi(this);
    menu->addAction(ui->copyAction);
    menu->addAction(ui->saveAction);
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
        int pixmapSize = 200;
        qrcodePixmap = QPixmap(pixmapSize, pixmapSize);
        QPainter painter(&qrcodePixmap);
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, pixmapSize, pixmapSize);
        painter.setBrush(Qt::blue);
        qreal rectSize = pixmapSize * 1.0 / qrcode->width;
        for (int y = 0; y < qrcode->width; ++y)
        {
            for (int x = 0; x < qrcode->width; ++x)
            {
                if (qrcode->data[qrcode->width * y + x] & 1)
                    painter.drawRect(QRectF(x * rectSize, y * rectSize, rectSize, rectSize));
            }
        }
        ui->encodedLabel->setPixmap(qrcodePixmap);
        qDebug() << qrcode->width;
    }
}

void Widget::on_encodedLabel_customContextMenuRequested(const QPoint &pos)
{
    menu->exec(QCursor::pos());
}

void Widget::on_copyAction_triggered()
{
    QApplication::clipboard()->setPixmap(qrcodePixmap);
    QMessageBox::information(this, "Qt-QRCoder", "Copied to clipboard");
}

void Widget::on_saveAction_triggered()
{
    const QString &desktopLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filter("PNG (*.png);;JPG (*.jpg *.jpeg);;BMP (*.bmp)");
    const QString &filename = QFileDialog::getSaveFileName(this, "Save", desktopLocation, filter);
    if (!filename.isEmpty())
    {
        if (qrcodePixmap.save(filename))
            QMessageBox::information(this, "Qt-QRCoder", QString("Saved to '").append(filename).append("'"));
        else
            QMessageBox::critical(this, "Qt-QRCoder", "Failed to save\nPlease first generate a QR code");
    }
}

void Widget::on_decodeButton_clicked()
{
    QString filename(":/icon/icons/my_qrcode.jpg");
}
