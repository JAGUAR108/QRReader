#include "myvideosurface.h"

myVideoSurface::myVideoSurface(QObject *parent) : QAbstractVideoSurface(parent)
{
    //Очистка формата
    m_imageFormat = QImage::Format_Invalid;
}
//Данный метод определяет, какие форматы кадров
//поддерживаются нашим video surface'ом,
//для нашей задачи этого будет достаточно
QList<QVideoFrame::PixelFormat> myVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
            return QList<QVideoFrame::PixelFormat>()
                    << QVideoFrame::Format_RGB32
                    << QVideoFrame::Format_ARGB32
                    << QVideoFrame::Format_ARGB32_Premultiplied
                    << QVideoFrame::Format_RGB565
                    << QVideoFrame::Format_RGB555;
        } else {
            return QList<QVideoFrame::PixelFormat>();
        }
}
//Наш самый важный метод.
//Здесь, получая кадр с камеры в объекте QVideoFrame,
//мы должны переконвертировать его в объект QImage и передать в видоискатель
bool myVideoSurface::present(const QVideoFrame &frame)
{
    m_frame = frame;
    //Проверяем, соответствует ли текущий формат входящего кадра
    //формату, установленному для текущего surface'а.
    //В нашем случае текущий формат устанавливает сама камера,
    //так что по идее будет соответствовать всегда
    if(surfaceFormat().pixelFormat() != m_frame.pixelFormat() ||
            surfaceFormat().frameSize() != m_frame.size()) {
            stop();
            return false;
        } else {
            //Создаем из фрейма QImage...
            if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {
                QImage image(
                     m_frame.bits(),
                     m_frame.width(),
                     m_frame.height(),
                     m_frame.bytesPerLine(),
                     QVideoFrame::imageFormatFromPixelFormat(m_frame.pixelFormat()));
                //... и передаем его в видоискатель
                emit newImage(image);
            }
            return true;
        }
}
