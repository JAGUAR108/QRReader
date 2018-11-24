#ifndef MYVIEWFINDER_H
#define MYVIEWFINDER_H

#include <QWidget>
#include <QCamera>
#include <myvideosurface.h>
#include <QZXing.h>

class myViewFinder : public QWidget
{
    Q_OBJECT
public:
    explicit myViewFinder(QWidget *parent = nullptr);
    virtual ~myViewFinder();

private:
    void paintEvent(QPaintEvent *);

private:
    QCamera* camera;
    myVideoSurface *surface;
    QImage *pix;
    QZXing *decoder;
    int frames;

signals:
    void detectedQRCode(QString &result);

public slots:
    void getImage(QImage img);

};

#endif // MYVIEWFINDER_H
