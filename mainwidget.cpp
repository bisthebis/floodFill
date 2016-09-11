#include "mainwidget.h"
#include <QDebug>

//Black : Wall
//White : nothing
//Red : flooded

QRgb red = QColor(255, 0, 0).rgb();
QRgb black = QColor(0, 0, 0).rgb();
QRgb white = QColor(255, 255, 255).rgb();


mainWidget::mainWidget(QWidget *parent)
    : QGraphicsView(parent), timer(this)


{
    img = new QImage(50, 50, QImage::Format_RGB32);
    img->fill(white);

    buffer = new QImage(50, 50, QImage::Format_RGB32);
    buffer->fill(white);

    setFixedSize(1000, 1000);
    scale(20, 20);
    pixmap = scene.addPixmap(QPixmap::fromImage(*img));

    for (int i = -15; i < 16; ++i)
    {
        img->setPixel(25 + i, 20, black);
    }

    for (int j = -15; j < 25; ++j)
    {
        img->setPixel(24, 20 + j, black);
        img->setPixel(26, 20 + j, black);
        img->setPixel(10, 20 + j, black);
        img->setPixel(40, 20 + j, black);
    }

    img->setPixel(25, 20, white);
    img->setPixel(25, 25, red);
    //img->setPixel(27, 25, Qt::GlobalColor::red);

    updatePixmap();

    connect(&timer, &QTimer::timeout, this, &mainWidget::tick);

    timer.setInterval(50);
    timer.start(300);



    setScene(&scene);
}

mainWidget::~mainWidget()
{
    delete img;
    delete buffer;
}

void mainWidget::updatePixmap()
{
    pixmap->setPixmap(QPixmap::fromImage(*img));
}


//helper
void switchPixelIfInRangeAndWhite(QImage* target, int x, int y)
{
    if (x >= 0
        && y >=0
        && x < target->width()
        && y < target->height()
        && target->pixel(x, y) == white)
        target->setPixel(x, y, red);
}

void mainWidget::tick()
{
    *buffer = *img;
    qDebug() << "Tick";
    for (int y = 0; y < 50; ++y)
    {
        for (int x = 0; x < 50; ++x)
        {
            if (img->pixel(x, y) == red)
            {
                switchPixelIfInRangeAndWhite(buffer, x, y+1);
                switchPixelIfInRangeAndWhite(buffer, x, y-1);
                switchPixelIfInRangeAndWhite(buffer, x+1, y);
                switchPixelIfInRangeAndWhite(buffer, x-1, y);


            }
        }
    }

    if (*img == *buffer)
        qDebug() << "End !";
    *img = *buffer;
    updatePixmap();
}

