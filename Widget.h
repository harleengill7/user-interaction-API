#ifndef WIDGET_H
#define WIDGET_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <stdio.h>
#include <iostream>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QDesktopServices>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{

 Q_OBJECT

public:

    QImage image[100000];
    QJsonArray myArray;
    int n;
    QString Img;

    // Member vars
    void paintEvent(QPaintEvent *evt);

    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;

private slots:
    void managerFinished(QNetworkReply *reply);
    void imageLoaded(QNetworkReply *reply);

};
#endif // WIDGET.H
