#include "myviewfinder.h"
#include <QVideoRendererControl>
#include <QPainter>
#include <QPaintEvent>

myViewFinder::myViewFinder(QWidget *parent)
    : QWidget(parent)
{
    camera = new QCamera;

    surface = new myVideoSurface(this);

    pix = new QImage();

    frames = 0;

    decoder = new QZXing();
    decoder->setDecoder(QZXing::DecoderFormat_QR_CODE);

    QVideoRendererControl *control = camera->service()->requestControl<QVideoRendererControl *>();
    if(control){
        control->setSurface(surface);
    }

    QObject::connect(surface, SIGNAL(newImage(QImage)), SLOT(getImage(QImage)));

    camera->start();
}

void myViewFinder::getImage(QImage img) {
    *pix = img;

    if(frames%15 == 0) {
        QString result = decoder->decodeImage(img);
        if(result > "") {
            emit detectedQRCode(result);
        }
    }

    update();
    frames++;
}

void myViewFinder::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    if(!pix)
        return;
    if(!pix->isNull() && this->geometry().width() != 0 && this->geometry().height() != 0
                    && pix->width() != 0 && pix->height() != 0)
    {
            QRect pixR(event->rect());
            int w0 = pix->rect().width(),
                h0 = pix->rect().height(),
                w1 = event->rect().width(),
                h1 = event->rect().height();
            double scale = 1;
            if(w0*h1 >= w1*h0) {
                scale = (double)w1/(double)w0;
            }else {
                scale = (double)h1/(double)h0;
            }
            pixR.setWidth(pix->width()*scale);
            pixR.setHeight(pix->height()*scale);
            painter.save();
            painter.drawImage(pixR, *pix);
            painter.restore();
    }
}

myViewFinder::~myViewFinder()
{
    camera->unload();
    delete camera;
    delete pix;
}
