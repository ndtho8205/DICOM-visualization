#ifndef DICOMHISTOGRAMSPANSLIDER_H
#define DICOMHISTOGRAMSPANSLIDER_H

#include <QWidget>
#include <qxtspanslider.h>


class DicomHistogramSpanSlider : public QxtSpanSlider
{
    Q_OBJECT
public:
    explicit DicomHistogramSpanSlider(QWidget *parent = 0);

signals:

public slots:
    void reset();
};

#endif  // DICOMHISTOGRAMSPANSLIDER_H
