#include "myvideosurface.h"

myVideoSurface::myVideoSurface(QObject *parent) : QAbstractVideoSurface(parent)
{
    m_imageFormat = QImage::Format_Invalid;
}

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

bool myVideoSurface::present(const QVideoFrame &frame)
{
    m_frame = frame;
    if(surfaceFormat().pixelFormat() != m_frame.pixelFormat() ||
            surfaceFormat().frameSize() != m_frame.size()) {
            stop();
            return false;
        } else {
            if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {

                QImage image(
                     m_frame.bits(),
                     m_frame.width(),
                     m_frame.height(),
                     m_frame.bytesPerLine(),
                     QVideoFrame::imageFormatFromPixelFormat(m_frame.pixelFormat()));
                emit newImage(image);
            }
            return true;
        }
}
