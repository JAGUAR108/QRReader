#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class myVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    myVideoSurface(QObject *parent = 0);
    bool present(const QVideoFrame &frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType
                                                          handleType=QAbstractVideoBuffer::NoHandle ) const;

private:
    QVideoFrame m_frame;
    QImage::Format m_imageFormat;
    QVideoSurfaceFormat m_videoFormat;

signals:
    void newImage(QImage img);
};

#endif // MYVIDEOSURFACE_H
