#ifndef DICOMREADER_H
#define DICOMREADER_H

#include <DicomStructs.h>


class QString;


class DicomReader
{
public:
    static DicomSet *readSet(const QString &dicomFolder);
    static DicomSingle *readSingle(const QString &filePath);
};

#endif  // DICOMREADER_H
