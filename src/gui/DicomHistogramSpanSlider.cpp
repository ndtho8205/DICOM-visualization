#include "DicomHistogramSpanSlider.h"


DicomHistogramSpanSlider::DicomHistogramSpanSlider(QWidget *parent) : QxtSpanSlider(parent)
{
    setMinimum(0);
    setMaximum(255);
    reset();
}

void DicomHistogramSpanSlider::reset()
{
    setLowerPosition(0);
    setUpperPosition(255);
    setLowerValue(0);
    setUpperValue(255);
}
