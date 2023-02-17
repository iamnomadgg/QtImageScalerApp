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

void MainWindow::paintEvent(QPaintEvent* event)
{
    if(canDraw)
    {
        paintImage("",
                   ui->productImage->pos().x(),
                   ui->productImage->pos().y());
    }
}

void MainWindow::paintImage(QString fileName, int x, int y)
{
    QPainter painter;
    QImage saveImage(150, 150, QImage::Format_RGB16);

    if(fileName.isEmpty())
    {
        painter.begin(this);
    }
    else
    {
        painter.begin(&saveImage);
    }

    if(pix != nullptr)
    {
        painter.setClipRect(x, y, 150, 150);
        painter.fillRect(QRect(x, y, 150, 150), Qt::SolidPattern);
        painter.drawPixmap(x - drawPos.x(),
                           y - drawPos.y(),
                           drawSize.width(),
                           drawSize.height(),
                           *pix);
    }

    painter.end();

    if(fileName != "")
    {
        saveImage.save(fileName);
        QMessageBox::information(this,
                                 "Success",
                                 "Image has been successfully saved!");
    }
}

void MainWindow::on_saveButton_clicked()
{
    if(canDraw)
    {
        if(pix == nullptr)
        {
            return;
        }
        //Save new pic from painter
        paintImage(QCoreApplication::applicationDirPath() + "/image.jpg", 0, 0);
    }
}


void MainWindow::on_scaleSlider_valueChanged(int value)
{
    drawSize = imageSize * value / 100;
    update();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    drawPos.setX(value * drawSize.width() / 100 * 0.5);
    update();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    drawPos.setY(value * drawSize.height() / 100 * 0.5);
    update();
}

