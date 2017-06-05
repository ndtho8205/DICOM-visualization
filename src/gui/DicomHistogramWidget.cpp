#include "DicomHistogramWidget.h"

#include <QGraphicsLayout>
#include <QDebug>

DicomHistogramWidget::DicomHistogramWidget(QWidget *parent) : QChartView(parent)
{
    m_xRangeMin = 0;
    m_xRangeMax = 255;
    m_yRangeMin = 0;
    m_yRangeMax = 0;

    m_series0 = new QLineSeries();
    m_series1 = new QLineSeries();
    *m_series1 << QPointF(0, 0) << QPointF(255, 0);

    QAreaSeries *series = new QAreaSeries(m_series0, m_series1);
    QPen         seriesPen(QColor(33, 33, 33));
    seriesPen.setWidth(3);
    series->setPen(seriesPen);
    series->setBrush(QBrush(QColor(105, 105, 105)));


    QPen rangePen(QColor(242, 49, 49, 186));

    m_rangeLeft0           = new QLineSeries();
    m_rangeLeft1           = new QLineSeries();
    QAreaSeries *rangeLeft = new QAreaSeries(m_rangeLeft0, m_rangeLeft1);
    rangeLeft->setPen(rangePen);
    rangeLeft->setBrush(QBrush(QColor(243, 63, 63, 100)));

    m_rangeRight0           = new QLineSeries();
    m_rangeRight1           = new QLineSeries();
    QAreaSeries *rangeRight = new QAreaSeries(m_rangeRight0, m_rangeRight1);
    rangeRight->setPen(rangePen);
    rangeRight->setBrush(QBrush(QColor(243, 63, 63, 100)));



    m_chart = new QChart();
    m_chart->addSeries(series);
    m_chart->addSeries(rangeLeft);
    m_chart->addSeries(rangeRight);
    m_chart->legend()->hide();
    m_chart->createDefaultAxes();
    m_chart->axisX()->setVisible(false);
    m_chart->axisY()->setVisible(false);
    m_chart->layout()->setContentsMargins(0, 0, 0, 0);
    m_chart->setMargins(QMargins(0, 0, 0, 0));
    m_chart->setBackgroundRoundness(0);

    setChart(m_chart);
    setRenderHint(QPainter::Antialiasing);
    setContentsMargins(0, 0, 0, 0);
}

void DicomHistogramWidget::loadData(uint64_t *data)
{
    if (!data)
        return;

    m_data = data;

    m_series0->clear();
    m_rangeLeft0->clear();
    m_rangeLeft1->clear();
    m_rangeRight0->clear();
    m_rangeRight1->clear();
    m_yRangeMax = 0;

    for (int i = 0; i < 256; ++i) {
        *m_series0 << QPointF(i, m_data[i]);
        if (m_data[i] > m_yRangeMax)
            m_yRangeMax = m_data[i];
    }

    draw();

    emit dataLoaded();
}

void DicomHistogramWidget::changeSelectedRange(int lower, int upper)
{
    m_rangeLeft0->clear();
    m_rangeLeft1->clear();

    m_rangeRight0->clear();
    m_rangeRight1->clear();

    *m_rangeLeft0 << QPointF(0, m_yRangeMax) << QPointF(lower, m_yRangeMax);
    *m_rangeLeft1 << QPointF(0, 0) << QPointF(lower, 0);
    *m_rangeRight0 << QPointF(upper, m_yRangeMax) << QPointF(m_xRangeMax, m_yRangeMax);
    *m_rangeRight1 << QPointF(upper, 0) << QPointF(m_xRangeMax, 0);

    update();
}

//
// ---------------------------------------------------------------------------
//

void DicomHistogramWidget::draw()
{
    m_chart->axisX()->setRange(m_xRangeMin, m_xRangeMax);
    m_chart->axisY()->setRange(m_yRangeMin, m_yRangeMax);
    update();
}
