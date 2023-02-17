#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseButton_clicked()
{
    canDraw = false;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::currentPath(),
                                                    tr("Image Files (*.jpg *.jpeg *.png)"));
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this,
                             tr("No Image"),
                             tr("There is no selected file. Plese try again to select an image file."));
        return;
    }

    QPixmap* newPix = new QPixmap(fileName);

    if(newPix->isNull())
    {
        QMessageBox::warning(this,
                             tr("Invalid Image"),
                             tr("Invalid or corrupted file. Please try again with another image file."));
        return;
    }

    if(newPix->width() < 150 || newPix->height() < 150)
    {
        QMessageBox::warning(this,
                             tr("Invalid Size"),
                             tr("Image size too small. Please use an image larger than 150x150."));
        return;
    }

    pix = newPix;
    imageSize = pix->size();
    drawSize = pix->size();

    canDraw = true;
}
