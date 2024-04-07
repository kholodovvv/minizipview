#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QLabel>

class Tablemodel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void OpenArch(const QString &);
    QString ChoosingUnitMeasure(const int &);
    ~MainWindow();

private:
    QTableView *tableView;
    Tablemodel *model;
    QLabel *statusLabel;

private slots:
    void slotOpenFile();
    void slotExitProgram();
};
#endif // MAINWINDOW_H
