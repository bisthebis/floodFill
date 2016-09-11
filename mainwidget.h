#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QImage>
#include <QPixmap>

class mainWidget : public QGraphicsView
{
    Q_OBJECT

    public:
        mainWidget(QWidget *parent = 0);
        ~mainWidget();

    public slots:
        void updatePixmap();
        void tick();

    private:
        QImage* img;
        QImage* buffer;
        QGraphicsScene scene;
        QGraphicsPixmapItem* pixmap;
        QTimer timer;

};

#endif // MAINWIDGET_H
