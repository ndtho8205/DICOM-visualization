#ifndef DICOMHISTOGRAMWIDGET_H
#define DICOMHISTOGRAMWIDGET_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

#include <Vector2.h>

QT_CHARTS_USE_NAMESPACE


class DicomHistogramWidget : public QChartView
{
    Q_OBJECT

public:
    explicit DicomHistogramWidget(QWidget *parent = 0);

signals:
    void dataLoaded();

public slots:
    void loadData(std::uint64_t *data);
    void changeSelectedRange(int lower, int upper);

private:
    void draw();

    std::uint8_t  m_xCurrentRangeMin;
    std::uint8_t  m_xCurrentRangeMax;
    std::uint64_t m_yCurrentRangeMin;
    std::uint64_t m_yCurrentRangeMax;

    std::uint8_t m_xRangeMin;
    std::uint8_t m_xRangeMax;
    quint64      m_yRangeMin;
    quint64      m_yRangeMax;

    std::uint64_t *m_data;
    QChart *       m_chart = nullptr;

    QLineSeries *m_series0 = nullptr;
    QLineSeries *m_series1 = nullptr;

    QLineSeries *m_rangeLeft0 = nullptr;
    QLineSeries *m_rangeLeft1 = nullptr;

    QLineSeries *m_rangeRight0 = nullptr;
    QLineSeries *m_rangeRight1 = nullptr;
};

#endif  // DICOMHISTOGRAMWIDGET_H
