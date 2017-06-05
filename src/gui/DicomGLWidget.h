#ifndef DICOMGLWIDGET_H
#define DICOMGLWIDGET_H

#include <QOpenGLWidget>

#include <DicomStructs.h>
#include <DicomVolumeRenderer.h>
#include <DicomCameraController.h>



class DicomGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit DicomGLWidget(QWidget *parent = 0);
    ~DicomGLWidget();

    void loadDicomData(const QString &dicomDir);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void changeTextureAlphaRange(int lower, int upper);

signals:
    void dataLoaded(std::uint64_t *);

private:
    void drawAxis();

    DicomVolumeRenderer * m_volumeRenderer;
    DicomCameraController m_cameraController;

    Vec2d m_mousePressPosition;
};

#endif  // DICOMGLWIDGET_H
