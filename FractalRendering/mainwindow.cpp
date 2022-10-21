#include "MainWindow.h"
#include <QMessageBox>

typedef QString string;
namespace {
    int getValFromBox(QDoubleSpinBox *box, QSlider *bar) {
        return (bar->maximum() - bar->minimum()) * (box->value() - box->minimum()) / (box->maximum() - box->minimum());
    }

    double getValFromBar(QDoubleSpinBox *box, QSlider *bar) {
        return box->minimum() + (box->maximum() - box->minimum()) * (bar->value() - bar->minimum()) / (bar->maximum() - bar->minimum());
    }

    QString timeFormat(qint64 time) {
        return QString::number(time / 1000) + " s " + QString::number(time % 1000) + " ms";
    }

}// namespace

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    prevSize = this->size();
    ui->rotationSlider->setValue(100 * FractalData::defaultSpeed);
    connectBoxBar();
    setValues();
    updateButtons();
    ui->fractalWidget->setFractalData(&data);
    readAndDraw();
    makeMenu();
    hideBorders();
}

MainWindow::~MainWindow() {
    delete ui;
    delete timer;
    delete elapsedTimer;
    delete temporaryDir;
}

void MainWindow::makeMenu() {
    auto fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Exit", [&]() { QApplication::quit(); });

    auto settingsMenu = menuBar()->addMenu("Settings");
    settingsMenu->addAction(
            "Fullscreen view", [&]() { hideAndShow(); }, QKeySequence(tr("F11")));
}

void MainWindow::updateButtons() {
    ui->fractalColorButton->setPalette(QPalette(data.fractalColor));
    ui->fractalColorButton->setText(data.fractalColor.name());
    ui->ambienceColorButton->setPalette(QPalette(data.ambienceColor));
    ui->ambienceColorButton->setText(data.ambienceColor.name());
}

void MainWindow::chooseColor(QColor const &color, ColorType type = FRACTAL) {
    QColor *colorMemory;
    if(type == AMBIENCE)
        colorMemory = &data.ambienceColor;
    else
        colorMemory = &data.fractalColor;
    if(color.isValid()) {
        *colorMemory = color;
        updateButtons();
        readAndDraw();
    }
}

void MainWindow::askColor(ColorType type) {
    QString title;
    if(type == AMBIENCE)
        title = "Select ambience color";
    else
        title = "Select fractal color";
    chooseColor(QColorDialog::getColor(Qt::green, this, title), type);
}

void MainWindow::connectBoxBar() {
    connect(ui->firstCoordBar, &QSlider::valueChanged, ui->firstCoordBox, [&]() { ui->firstCoordBox->setValue(getValFromBar(ui->firstCoordBox, ui->firstCoordBar)); });
    connect(ui->secondCoordBar, &QSlider::valueChanged, ui->secondCoordBox, [&]() { ui->secondCoordBox->setValue(getValFromBar(ui->secondCoordBox, ui->secondCoordBar)); });
    connect(ui->thirdCoordBar, &QSlider::valueChanged, ui->thirdCoordBox, [&]() { ui->thirdCoordBox->setValue(getValFromBar(ui->thirdCoordBox, ui->thirdCoordBar)); });
    connect(ui->powerBarSlider, &QSlider::valueChanged, ui->powerSpinBox, [&]() { ui->powerSpinBox->setValue(2 * ui->powerBarSlider->value()); });
    connect(ui->firstCoordBar, &QSlider::valueChanged, [&]() { readAndDraw(); });
    connect(ui->secondCoordBar, &QSlider::valueChanged, [&]() { readAndDraw(); });
    connect(ui->thirdCoordBar, &QSlider::valueChanged, [&]() { readAndDraw(); });
    connect(ui->powerBarSlider, &QSlider::valueChanged, [&]() { readAndDraw(); });
    connect(ui->fractalColorButton, &QPushButton::clicked, [&]() { askColor(FRACTAL); });
    connect(ui->ambienceColorButton, &QPushButton::clicked, [&]() { askColor(AMBIENCE); });
    connect(ui->randomizeButton, &QPushButton::clicked, [&]() { generateRandom(); });
    connect(ui->rotationBox, &QCheckBox::stateChanged, [&]() { readAndDraw(); });
    connect(ui->zoomButton, &QPushButton::clicked, [&]() {
        data.setZoomCoefficient();
        ui->fractalWidget->repaint();
    });
    connect(ui->rotationSlider, &QSlider::valueChanged, [&]() {
        ui->rotationBox->setCheckState(Qt::Checked);
        data.setAbsoluteSpeed(ui->rotationSlider->value() / 100.0);
    });
}

void MainWindow::readAndDraw() {
    if(!isSetting) {
        data = FractalData(ui->firstCoordBox->value(), ui->secondCoordBox->value(), ui->thirdCoordBox->value(), ui->powerSpinBox->value(),
                           static_cast<FractalType>(ui->typeBox->currentIndex()), data.fractalColor, data.ambienceColor, data.camera, data.zoomCoefficient, ui->rotationBox->isChecked());
        ui->fractalWidget->repaint();
    }
}


void MainWindow::setValues() {
    isSetting = true;
    ui->firstCoordBox->setValue(data.a);
    ui->secondCoordBox->setValue(data.b);
    ui->thirdCoordBox->setValue(data.c);
    ui->powerSpinBox->setValue(data.n);
    ui->typeBox->setCurrentIndex(data.type);
    updateButtons();
    isSetting = false;
}

void MainWindow::generateRandom() {
    data.genRandom();
    setValues();
    ui->fractalWidget->repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_F11) {
        hideAndShow();
    }
    if(event->key() == Qt::Key_Escape && isFullScreen) {
        hideAndShow();
    }
    QWidget::keyPressEvent(event);
}

void MainWindow::hideAndShow() {
    if(isFullScreen) {
        ui->menubar->show();
        ui->inputWidget->show();
        ui->statusbar->show();
        this->resize(prevSize);
        isFullScreen = false;
    } else {
        prevSize = this->size();
        ui->menubar->hide();
        ui->inputWidget->hide();
        ui->statusbar->hide();
        this->showMaximized();
        isFullScreen = true;
    }
}

void MainWindow::hideBorders() {
    ui->statusbar->hide();
    ui->centralwidget->setContentsMargins(0, 0, 0, 0);
}
