#include "DicomLogicClass.h"


DicomLogicClass::DicomLogicClass(QObject *parent) : QObject(parent)
{
    m_value = 0;
}

//
// ---------------------------------------------------------------------------
//

void DicomLogicClass::resetStatus()
{
    emit statusReset();
}

void DicomLogicClass::changeStatus(const QString &text)
{
    emit statusChanged(text);
}

void DicomLogicClass::startProgressing()
{
    emit progressingStart();
}

void DicomLogicClass::changeProgressingRange(int minimum, int maximum)
{
    m_value = minimum;
    emit progressingRangeChanged(minimum, maximum);
}

void DicomLogicClass::increaseProgressingValue(int delta)
{
    m_value += delta;
    emit progressingValueChanged(m_value);
}

void DicomLogicClass::setProgressingValue(int value)
{
    m_value = value;
    emit progressingValueChanged(value);
}

void DicomLogicClass::stopProgressing()
{
    emit progressingDone();
}
