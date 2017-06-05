#ifndef DICOMLOGICCLASS_H
#define DICOMLOGICCLASS_H

#include <QObject>


//
// Singleton Pattern
//

class DicomLogicClass : public QObject
{
    Q_OBJECT

public:
    static DicomLogicClass &getInstance()
    {
        static DicomLogicClass instance;
        return instance;
    }

    DicomLogicClass(DicomLogicClass const &) = delete;
    DicomLogicClass(DicomLogicClass &&)      = delete;
    DicomLogicClass &operator=(DicomLogicClass const &) = delete;
    DicomLogicClass &operator=(DicomLogicClass &&) = delete;


protected:
    explicit DicomLogicClass(QObject *parent = 0);

signals:
    void statusReset();
    void statusChanged(const QString &);
    void progressingStart();
    void progressingRangeChanged(int minimum, int maximum);
    void progressingValueChanged(int value);
    void progressingDone();

public slots:
    void resetStatus();
    void changeStatus(const QString &text);
    void startProgressing();
    void changeProgressingRange(int minimum, int maximum);
    void increaseProgressingValue(int delta = 1);
    void setProgressingValue(int value);
    void stopProgressing();

private:
    int m_value;
};

#endif  // DICOMLOGICCLASS_H
