#include "DicomReader.h"

#include <QString>
#include <QDir>

#include <algorithm>
#include <vector>

#include <imebra/imebra.h>

#include <DicomLogicClass.h>



DicomSet *DicomReader::readSet(const QString &dicomFolder)
{
    DicomLogicClass &logicClass = DicomLogicClass::getInstance();

    // -----------------------------------------------------------------------

    logicClass.changeStatus("Reading DICOM data...");
    QFileInfoList dicomFileList  = QDir(dicomFolder).entryInfoList();
    int           dicomFileCount = dicomFileList.size();
    DicomSet *    dicomSet       = new DicomSet();

    logicClass.startProgressing();
    logicClass.changeProgressingRange(0, dicomFileCount);


    QString filePath;

    for (int i = 0; i < dicomFileCount; ++i) {
        filePath = dicomFileList.at(i).absoluteFilePath();
        if (QFileInfo(filePath).isFile())
            dicomSet->data.push_back(readSingle(filePath));
        logicClass.increaseProgressingValue();
    }

    std::sort(dicomSet->data.begin(),
              dicomSet->data.end(),
              [&](DicomSingle *dicomSingle1, DicomSingle *dicomSingle2) -> bool {
                  return dicomSingle1->instanceNumber < dicomSingle2->instanceNumber;
              });

    dicomSet->width  = dicomSet->data.at(0)->width;
    dicomSet->height = dicomSet->data.at(0)->height;
    dicomSet->depth  = std::uint32_t(dicomSet->data.size());

    logicClass.stopProgressing();
    logicClass.resetStatus();

    // -----------------------------------------------------------------------

    logicClass.changeStatus("Generating histogram data...");

    logicClass.startProgressing();
    logicClass.changeProgressingRange(0, int(dicomSet->depth));

    dicomSet->histogram = new std::uint64_t[256]{0};

    for (DicomSingle *dicomSingle : dicomSet->data) {
        for (std::uint8_t l : dicomSingle->luminance8) {
            ++dicomSet->histogram[l];
        }
        logicClass.increaseProgressingValue();
    }

    logicClass.stopProgressing();
    logicClass.resetStatus();


    return dicomSet;
}

DicomSingle *DicomReader::readSingle(const QString &filePath)
{
    DicomSingle *dicomSingle = new DicomSingle();

    std::unique_ptr<imebra::DataSet> dataSet(
        imebra::CodecFactory::load(filePath.toStdString(), 2048));
    std::unique_ptr<imebra::Image> image(dataSet->getImageApplyModalityTransform(0));
    std::unique_ptr<imebra::ReadingDataHandlerNumeric> dataHandler(image->getReadingDataHandler());


    std::uint32_t width  = image->getWidth();
    std::uint32_t height = image->getHeight();
    std::uint32_t instanceNumber =
        dataSet->getUnsignedLong(imebra::TagId(imebra::tagId_t::InstanceNumber_0020_0013), 0);
    int min = dataSet->getSignedLong(
        imebra::TagId(imebra::tagId_t::SmallestImagePixelValue_0028_0106), 0, -32768);
    int max = dataSet->getSignedLong(
        imebra::TagId(imebra::tagId_t::LargestImagePixelValue_0028_0107), 0, 32767);


    dicomSingle->width              = width;
    dicomSingle->height             = height;
    dicomSingle->instanceNumber     = instanceNumber;
    dicomSingle->smallestPixelValue = min;
    dicomSingle->largestPixelValue  = max;

    for (std::uint32_t y = 0; y < dicomSingle->height; ++y)
        for (std::uint32_t x = 0; x < dicomSingle->width; ++x) {
            int          luminance = dataHandler->getSignedLong(y * dicomSingle->width + x);
            std::uint8_t luminance8 =
                (max == min) ? min : std::uint8_t((luminance - min) * 255 / (max - min));
            dicomSingle->luminance.push_back(luminance);
            dicomSingle->luminance8.push_back(luminance8);
        }
    return dicomSingle;
}
