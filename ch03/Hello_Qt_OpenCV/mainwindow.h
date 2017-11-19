#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include <QTranslator>
#include "opencv2/opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private slots:
    void on_inputPushButton_pressed();

    void on_outputPushButton_pressed();

    void on_actionTurkish_triggered();

    void on_actionEnglish_triggered();

    void on_actionGerman_triggered();

private:
    Ui::MainWindow *ui;

    void loadSettings();
    void saveSettings();

    QTranslator *turkishTranslator;
    QTranslator *germanTranslator;

};

#endif // MAINWINDOW_H
