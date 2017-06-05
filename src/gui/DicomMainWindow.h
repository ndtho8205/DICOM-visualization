#ifndef DICOMMAINWINDOW_H
#define DICOMMAINWINDOW_H

#include <QMainWindow>


namespace Ui {
    class DicomMainWindow;
}

class DicomMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DicomMainWindow(QWidget *parent = 0);
    ~DicomMainWindow();

public slots:
    void openFolder();
    void quit();

    void resetStatus();
    void changeStatus(const QString &text);
    void startProgressing();
    void changeProcessingRange(int minimum, int maximum);
    void setProgressingValue(int value);
    void stopProgressing();

private slots:
    void on_okButton_clicked();

signals:
    void textureAlphaRangeChanged(int lower, int upper);

private:
    Ui::DicomMainWindow *ui;
};

#endif  // DICOMMAINWINDOW_H
