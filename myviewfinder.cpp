#include "myviewfinder.h"
#include <QVideoRendererControl>
#include <QPainter>
#include <QPaintEvent>

myViewFinder::myViewFinder(QWidget *parent)
    : QWidget(parent)
{
    //Инициализируем камеру
    camera = new QCamera;
    //Создаем наш video surface
    surface = new myVideoSurface(this);
    //Инициализируем текущий фрейм пустым изображением
    pix = new QImage();
    //Обнуляем счётчик кадров
    frames = 0;
    //Создаём декодер кадров, с помощью которого мы будем расшифровывать QR код
    decoder = new QZXing();
    //Устанавливаем формат расшифровки
    decoder->setDecoder(QZXing::DecoderFormat_QR_CODE);
    //---Данный код подключает в качестве обработчика
    //---фреймов наш video surface
    QVideoRendererControl *control = camera->service()->requestControl<QVideoRendererControl *>();
    if(control){
        control->setSurface(surface);
    }
    //Создаём пару сигнал-слот для передачи изображения из нашего surface в текущий видоискатель
    QObject::connect(surface, SIGNAL(newImage(QImage)), SLOT(getImage(QImage)));
    //Включаем камеру, фреймы автоматически начнут передаваться
    //в myVideoSurface после инициализации устройства
    camera->start();
}
//Именно сюда приходит каждый фрейм с камеры,
//преобразованный в QImage
void myViewFinder::getImage(QImage img) {
    //Сохраняем изображение...
    *pix = img;
    //Каждый 15 кадр мы будем пытаться декодировать изображение
    //и отправлять результат в главное окно, если QR код найден и успешно расшифрован
    if(frames%15 == 0) {
        QString result = decoder->decodeImage(img);
        if(result > "") {
            emit detectedQRCode(result);
        }
    }
    //и перерисовываем видоискатель.
    //Результатом выполнения update()
    //будет асинхронный вызов paintEvent()
    //текущего виджета
    update();
    //увеличиваем счётчик кадров
    frames++;
}

void myViewFinder::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    if(!pix)
        return;
    //Проверяем корректность полученного изображения
    if(!pix->isNull() && this->geometry().width() != 0 && this->geometry().height() != 0
                    && pix->width() != 0 && pix->height() != 0)
    {
            //Определяем область рисования и следим за тем,
            //чтобы изображение не растянулось при изменении размеров окна
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
            //... и рисуем
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
