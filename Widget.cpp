#include "widget.h"
#include "ui_widget.h"
#include <QSslSocket>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

       QUrl myUrl("https://api.sampleapis.com/cartoons/cartoons2D");

       QNetworkRequest myRequest(myUrl);

       connect(manager,SIGNAL(finished(QNetworkReply*)),
                  this,SLOT(managerFinished(QNetworkReply*)));

       manager->get(myRequest);



    ui->setupUi(this);
}

void Widget::managerFinished(QNetworkReply *reply)
{
    QByteArray *myByteArray = new QByteArray();

    myByteArray->append(reply->readAll());

    QJsonDocument myJson = QJsonDocument::fromJson(*myByteArray);

    qDebug() << myJson;

    //parsing array
    QJsonArray myArray = myJson.array();
    int s = myArray.size();

    qDebug() << "\n size: " << s;
    n =0;


    qDebug() << "\n";
    for(int i=0;i<30;i++)
    {

        QJsonValue v = myArray[i]; //calling out first array

        QJsonObject obj = v.toObject(); //objects within it


        //reading objects
        QString title = obj.value("title").toString();
        qDebug() << "\n";
        qDebug() << "title" << title;

        //year - number
       int year = obj.value("year").toInt();
       qDebug() << "year" << year;


       //rating - letters
       QString rating = obj.value("rating").toString();
       qDebug() << "rating" << rating;

        //runtime - number
       int runtime_in_minutes = obj.value("runtime_in_minutes").toInt();
       qDebug() << "runtime_in_minutes" << runtime_in_minutes;

        //episodes - number
       int episodes = obj.value("episodes").toInt();
       qDebug() << "episodes" << episodes;

       n = n+1;
        //image - url
       QString image = obj.value("image").toString();
       qDebug() << "image" << image;
       //storing image urls in Img
       for(int i=0;i<s;i++)
       {
           Img = image;
       }


        //id - number
       int id = obj.value("id").toInt();
       qDebug() << "id" << id;


       QNetworkAccessManager *manager1 = new QNetworkAccessManager(this);
       QNetworkRequest imageReq(Img);
       imageReq.setAttribute(QNetworkRequest::User, QVariant(i));
       connect(manager1,SIGNAL(finished(QNetworkReply*)),this,SLOT(imageLoaded(QNetworkReply*)));
       manager1->get(imageReq);



    }

}

void Widget::imageLoaded(QNetworkReply *reply)
 {
    QNetworkRequest myRequest = reply->request();
    QVariant myVariant = myRequest.attribute(QNetworkRequest::User);
    int i = myVariant.toInt();
    image[i].loadFromData(reply->readAll());
    repaint();
 }

void Widget::paintEvent(QPaintEvent *evt)
{

    QPainter cartoon(this);
    for(int i=0; i<n/5; i++)
    {
        for(int j=0; j<5; j++)
        {
            image[i*5 +j] = image[i*5 +j].scaled(100, 100, Qt::KeepAspectRatio);
            cartoon.drawImage(i*100, j*100, image[5*i + j]);
        }
    }


}


Widget::~Widget()
{
    delete ui;
}
