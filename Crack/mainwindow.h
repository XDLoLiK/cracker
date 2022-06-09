#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <time.h>
#include <unistd.h>

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QProgressBar>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QMediaPlayer;

class QMessageBox;

class QProgressBar;

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_patch_clicked();
    void on_exit_clicked();
    void updateProgressBar();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *crackMediaPlayer;
    QMessageBox *crackMessage;
};
#endif // MAINWINDOW_H
