#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QPixmap pixmap("/home/stanislav/ded-sem-2/Crack/Cracker/Images/Anime.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
    ui->setupUi(this);

    ui->exit->setStyleSheet("background-color:  rgba(255, 255, 255, 0)");
    ui->patch->setStyleSheet("background-color: rgba(255, 255, 255, 0)");

    crackMediaPlayer = new QMediaPlayer;
    crackMediaPlayer->setMedia(QUrl::fromLocalFile("/home/stanislav/ded-sem-2/Crack/Cracker/Music/SkrillexCrack.mp3"));
    crackMediaPlayer->setVolume(100);

    ui->crackProgress->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_patch_clicked()
{
    ui->patch->setEnabled(false);

    FILE *to_patch = fopen("/home/stanislav/ded-sem-2/Crack/pasha_crack_2.0.out", "rb");

    fseek(to_patch, 0, SEEK_END);
    int size = ftell(to_patch);
    fseek(to_patch, 0, SEEK_SET);

    if (size != 17096) {
        crackMessage = new QMessageBox;
        crackMessage->setWindowTitle("Crack Status");
        crackMessage->setText("Wrong file");
        crackMessage->exec();
        return;
    }

    char *buffer = (char *) calloc(size, 1);
    fread(buffer, 1, size, to_patch);
    fclose(to_patch);

    if (buffer[0x113a + 8]  == 0x0a && buffer[0x113a + 9]  == 0x41 && buffer[0x113a + 10] == 0x40) {
        crackMessage = new QMessageBox;
        crackMessage->setWindowTitle("Crack Status");
        crackMessage->setText("File has already been patched");
        crackMessage->exec();
        return;
    } else {
        buffer[0x113a + 8]  = 0x0a;
        buffer[0x113a + 9]  = 0x41;
        buffer[0x113a + 10] = 0x40;
    }

    to_patch = fopen("/home/stanislav/ded-sem-2/Crack/pasha_crack_2.0.out", "wb");
    fwrite(buffer, 1, size, to_patch);
    fclose(to_patch);

    ui->crackProgress->show();
    crackMediaPlayer->play();

    QTimer *progressTimer = new QTimer;
    connect(progressTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    progressTimer->start(261);
}

void MainWindow::on_exit_clicked()
{
    MainWindow::close();
}

void MainWindow::updateProgressBar()
{
    ui->crackProgress->setValue(ui->crackProgress->value() + 1);

    if (ui->crackProgress->value() == 99) {
        sleep(1);
        ui->crackProgress->setValue(ui->crackProgress->value() + 1);
        crackMessage = new QMessageBox;
        crackMessage->setWindowTitle("Crack Status");
        crackMessage->setText("Cracked successfully, you newbie");
        crackMessage->exec(); 
    }
}
