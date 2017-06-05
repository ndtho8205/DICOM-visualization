#include "DicomMainWindow.h"
#include "ui_DicomMainWindow.h"

#include <QFileDialog>
#include <QDebug>

#include <DicomReader.h>
#include <DicomLogicClass.h>
#include <QProgressBar>
#include <QLabel>

DicomMainWindow::DicomMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::DicomMainWindow)
{
    ui->setupUi(this);


    ui->progressBar->setVisible(false);
    ui->statusBar->addPermanentWidget(ui->label);
    ui->statusBar->addPermanentWidget(ui->progressBar);
    ui->statusBar->setStyleSheet(
        "QStatusBar {background: #171717;} QStatusBar QLabel {color: white;}");

    connect(ui->actionOpenFiles, SIGNAL(triggered()), this, SLOT(openFiles()));
    connect(ui->actionOpenFolder, SIGNAL(triggered()), this, SLOT(openFolder()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

    connect(ui->openGLWidget,
            SIGNAL(dataLoaded(std::uint64_t *)),
            ui->graphicsView,
            SLOT(loadData(std::uint64_t *)));
    connect(ui->graphicsView, SIGNAL(dataLoaded()), ui->spanSlider, SLOT(reset()));

    connect(ui->spanSlider,
            SIGNAL(spanChanged(int, int)),
            ui->graphicsView,
            SLOT(changeSelectedRange(int, int)));
    connect(this,
            SIGNAL(textureAlphaRangeChanged(int, int)),
            ui->openGLWidget,
            SLOT(changeTextureAlphaRange(int, int)));


    DicomLogicClass &logicClass = DicomLogicClass::getInstance();
    connect(&logicClass, SIGNAL(statusReset()), this, SLOT(resetStatus()));
    connect(&logicClass,
            SIGNAL(statusChanged(const QString &)),
            this,
            SLOT(changeStatus(const QString &)));
    connect(&logicClass, SIGNAL(progressingStart()), this, SLOT(startProgressing()));
    connect(&logicClass,
            SIGNAL(progressingRangeChanged(int, int)),
            this,
            SLOT(changeProcessingRange(int, int)));
    connect(
        &logicClass, SIGNAL(progressingValueChanged(int)), this, SLOT(setProgressingValue(int)));
    connect(&logicClass, SIGNAL(progressingDone()), this, SLOT(stopProgressing()));
}

DicomMainWindow::~DicomMainWindow()
{
    delete ui;
}

//
// ---------------------------------------------------------------------------
//

void DicomMainWindow::openFolder()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->openGLWidget->loadDicomData(dir);

    //    ui->openGLWidget->loadDicomData(
    //        "/home/ndtho8205/Desktop/DICOM/data/3Dircadb1.1/MASKS_DICOM/bone");

    //    ui->openGLWidget->loadDicomData("/home/ndtho8205/Desktop/DICOM/data/3Dircadb1.1/PATIENT_DICOM");
}

void DicomMainWindow::quit()
{
}

//
// ---------------------------------------------------------------------------
//

void DicomMainWindow::resetStatus()
{
    ui->label->setText("");
}

void DicomMainWindow::changeStatus(const QString &text)
{
    ui->label->setText(text);
}

void DicomMainWindow::startProgressing()
{
    ui->progressBar->reset();
    ui->progressBar->setVisible(true);
}

void DicomMainWindow::changeProcessingRange(int minimum, int maximum)
{
    ui->progressBar->setRange(minimum, maximum);
}

void DicomMainWindow::setProgressingValue(int value)
{
    ui->progressBar->setValue(value);
}

void DicomMainWindow::stopProgressing()
{
    ui->progressBar->setVisible(false);
}

//
// ---------------------------------------------------------------------------
//

void DicomMainWindow::on_okButton_clicked()
{
    emit textureAlphaRangeChanged(ui->spanSlider->lowerValue(), ui->spanSlider->upperValue());
}
