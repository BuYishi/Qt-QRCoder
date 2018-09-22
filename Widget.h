#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QMenu;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_encodeButton_clicked();
    void on_encodedLabel_customContextMenuRequested(const QPoint &pos);
    void on_copyAction_triggered();
    void on_saveAction_triggered();

    void on_decodeButton_clicked();

private:
    Ui::Widget *ui;
    QMenu *menu;
    QPixmap qrcodePixmap;
};

#endif // WIDGET_H
