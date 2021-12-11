#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setAcceptDrops(true);

    connect(ui->open, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(fileProcess()));
    connect(ui->Blur, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Crop, SIGNAL(triggered()), this, SLOT(switchPages()));
    connect(ui->Rotate, SIGNAL(triggered()), this, SLOT(switchPages()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileProcess()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action == ui->open && image.empty())
    {

        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image(*.png *.jpg *.jpeg)"));
        if(!filePath.isEmpty())
        {
            image = imread(filePath.toStdString().c_str());
            imshow("Image", image);
            emit ui->Crop->triggered();
        }
    }
    else if(action == ui->save && !image.empty())
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "",tr("Image(*.png *.jpg)"));
        if(!filePath.isEmpty())
        {
            imwrite(filePath.toStdString().c_str(), image);
            image.release();
            destroyWindow("Image");
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(true && image.empty())
    {
        event->acceptProposedAction();
        ui->label->setStyleSheet("border: 5px dashed #242424");
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl>urls = event->mimeData()->urls();
    if(urls.empty()) return;
    QString filePath = urls.first().toLocalFile();
    if(!filePath.isEmpty())
    {
        image = imread(filePath.toStdString().c_str());
        imshow("Image", image);
        emit ui->Crop->triggered();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!image.empty())
    {
        QMessageBox::StandardButton reply
                = QMessageBox::question(this, "Photoshop", "The image hasn't been saved, \n sure to exit?",QMessageBox::Yes | QMessageBox::No );
        if(reply == QMessageBox::Yes)
        {
            image.release();
            destroyWindow("Image");
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

void MainWindow::accept()
{
    pastImg = image.clone();
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        image = blur->blurFinish();
        emit ui->blurCheck->rejected();
        delete blur;
        newBlur();
    }
    else if(button == ui->sizeCheck)
    {
        image = size->sizeFinish();
        emit ui->sizeCheck->rejected();
        delete size;
        newResize();
    }
    else if(button == ui->rotateCheck)
    {
        image = rotate->rotateFinish();
        emit ui->rotateCheck->rejected();
        delete rotate;
        newRotate();
    }
    else if(button == ui->cropCheck)
    {
        image = crop->cropFinish();
        emit ui->cropCheck->rejected();
        delete crop;
        newCrop();
    }
    imshow("Image", image);
}

void MainWindow::reject()
{
    QDialogButtonBox *button = qobject_cast<QDialogButtonBox*>(sender());
    if(button == ui->blurCheck)
    {
        emit cleanBlur();
        ui->kernel->setValue(1);
    }
    else if(button == ui->sizeCheck)
    {
        emit cleanResize();
    }
    else if (button == ui->rotateCheck)
    {
        emit cleanRotate();
    }
    else if(button == ui->cropCheck)
    {
        emit cleanCrop();
    }
    destroyWindow("Preview");
}

void MainWindow::switchPages()
{
    if(!image.empty())
    {
        QAction *action = qobject_cast<QAction*>(sender());
        if(action == ui->Blur)
        {
            ui->stackedWidget->setCurrentIndex(1);
            ui->kernel->setMinimum(1);
            ui->kernel->setMaximum(17);
            ui->kernel->setSingleStep(2);
            newBlur();
        }
        else if(action == ui->Crop)
        {
            ui->stackedWidget->setCurrentIndex(7);
            ui->sizeSlider->setMaximum(12);
            ui->sizeSlider->setMinimum(-8);
            newCrop();
            newResize();
        }
        else if(action == ui->Rotate)
        {
            ui->stackedWidget->setCurrentIndex(8);
            newRotate();
        }
    }
    else return;
}

void MainWindow::newResize()
{
    size = new Resize(this, image);
    size->sizeSlider = ui->sizeSlider;
    connect(ui->sizeSlider, SIGNAL(valueChanged(int)), size, SLOT(valueChanged(int)));
    connect(ui->sizeCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->sizeCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanResize()), size, SLOT(rejected()));
}

void MainWindow::newRotate()
{
    rotate = new Rotate(this,image);

    rotate->vertical = ui->vertical;
    rotate->horizontal = ui->horizontal;
    rotate->counterclockwise = ui->cclockwise;
    rotate->clockwise = ui->clockwise;

    connect(ui->vertical, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->horizontal, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->cclockwise, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->clockwise, SIGNAL(clicked()), rotate, SLOT(buttonDown()));
    connect(ui->rotateCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->rotateCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanRotate()), rotate, SLOT(rejected()));
}

void MainWindow::newCrop()
{
    crop = new Crop(this,image);
    crop->self = ui->selfselect;
    crop->rectangle = ui->rectangle;

    connect(ui->selfselect, SIGNAL(clicked()), crop, SLOT(TypeChanged()));
    connect(ui->rectangle, SIGNAL(clicked()), crop, SLOT(TypeChanged()));
    connect(ui->cropCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->cropCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanCrop()), crop, SLOT(rejected()));
}


void MainWindow::newBlur()
{
    blur = new Blur(this,image);

    blur->Box = ui->box;
    blur->Gaussian = ui->gaussian;
    blur->Median = ui->median;
    blur->Bilateral = ui->bilateral;

    connect(ui->box, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->gaussian, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->median, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->bilateral, SIGNAL(clicked()), blur, SLOT(TypeChanged()));
    connect(ui->kernel, SIGNAL(valueChanged(int)), blur, SLOT(kernelChanged(int)));
    connect(ui->blurCheck, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->blurCheck, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(cleanBlur()), blur, SLOT(rejected()));
}
