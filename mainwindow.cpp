#include "mainwindow.h"
#include "tablemodel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QStatusBar>
#include <QFileDialog>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>

#include "unzip.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSize s(800, 600);
    MainWindow::setWindowTitle(":: MiniZipView ::");
    MainWindow::setFixedSize(s);

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    tableView = new QTableView(parent);
    tableView->setModel(model = new Tablemodel(this));
    tableView->setColumnWidth(0, 300);
    tableView->setColumnWidth(1, 137);
    tableView->setColumnWidth(2, 137);
    tableView->verticalHeader()->setVisible(false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *secondLayout = new QHBoxLayout;
    QHBoxLayout *thirdLayout = new QHBoxLayout;
    QVBoxLayout *btnLayout = new QVBoxLayout;

    btnLayout->setAlignment(Qt::AlignTop);
    btnLayout->setContentsMargins(0, 20, 0, 0);
    btnLayout->setSpacing(5);

    widget->setLayout(mainLayout);

    QGroupBox* grbArchContent = new QGroupBox(parent);
    grbArchContent->setTitle(tr("Содержание архива"));
    grbArchContent->setAlignment(Qt::AlignLeft);
    grbArchContent->setFixedSize(600, 550);
    grbArchContent->setLayout(thirdLayout);

    thirdLayout->addWidget(tableView);
    secondLayout->addWidget(grbArchContent);
    mainLayout->addLayout(secondLayout);

    QPushButton *btnOpenArch = new QPushButton(parent);
    btnOpenArch->setText(tr("Открыть архив"));
    btnOpenArch->setFixedHeight(40);
    connect(btnOpenArch, &QPushButton::clicked, this, &MainWindow::slotOpenFile);

    QPushButton *btnExit = new QPushButton(parent);
    btnExit->setText(tr("Выход"));
    btnExit->setFixedHeight(40);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::slotExitProgram);

    secondLayout->addLayout(btnLayout);
    btnLayout->addWidget(btnOpenArch);
    btnLayout->addWidget(btnExit);

    QStatusBar *statusBar = new QStatusBar(parent);
    statusLabel = new QLabel(statusBar);
    statusBar->addWidget(statusLabel);
    mainLayout->addWidget(statusBar);
}

void MainWindow::OpenArch(const QString &pathToArch)
{
    int rValue;
    const int maxPath = 250;
    unzFile unzfile = unzOpen(pathToArch.toStdString().c_str());
    unz_global_info *unzGlobalInfo = new unz_global_info;

    if(unzfile != NULL){
        rValue = unzGetGlobalInfo(unzfile, unzGlobalInfo);

        if(rValue == UNZ_OK){
            statusLabel->setText("Архив содержит " + QString::number(unzGlobalInfo->number_entry) + " файл(а)ов");

            unz_file_info *fileInfo = new unz_file_info;
            char zipName[maxPath] = { 0 };
            char extraField[maxPath] = { 0 };
            char comment[maxPath] = { 0 };

            for(int i = 0; i < unzGlobalInfo->number_entry; ++i){
                rValue = unzGetCurrentFileInfo(unzfile, fileInfo, zipName, maxPath, extraField, maxPath, comment, maxPath);

                if(rValue == UNZ_OK){
                    #if defined(Q_OS_LINUX)
                        model->appendData(pathToArch + "/" + zipName, ChoosingUnitMeasure(fileInfo->compressed_size), ChoosingUnitMeasure(fileInfo->uncompressed_size));
                    #elif defined(Q_OS_WIN)
                        model->appendData(pathToArch + "\" + zipName, ChoosingUnitMeasure(fileInfo->compressed_size), ChoosingUnitMeasure(fileInfo->uncompressed_size));
                    #endif
                }

                unzGoToNextFile(unzfile);
            }
        }

    }else{
        QMessageBox::critical(this, tr("Ошибка!"), tr("Возникла ошибка при открытии архива"), QMessageBox::Ok);
        return;
    }

    unzClose(unzfile);
}

QString MainWindow::ChoosingUnitMeasure(const int &value)
{
    QString answer;

    if(value > 0 && value > 1073741824){
        answer = QString::number(value / 1024 / 1024 / 1024) + tr(" Гб");
    }else if(value > 0 && value > 1050000){
        answer = QString::number(value / 1024 / 1024) + tr(" Мб");
    }else if(value > 0 && value > 1024){
        answer = QString::number(value / 1024) + tr(" Кб");
    }else if(value > 0 && value < 1024){
        answer = QString::number(value) + tr(" Байт");
    }

    return answer;
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotOpenFile()
{
    QString fromFile = QFileDialog::getOpenFileName(this, tr("Выбрать архив"), "/", "ZIP Архив (*.zip)");
    model->removeRows();
    OpenArch(fromFile.toStdString().c_str());
}

void MainWindow::slotExitProgram()
{
    this->close();
}

