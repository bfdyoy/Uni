#include "mainwindow.h"
#include <QMessageBox>
#include <utility>

typedef QString string;

template <typename E>
constexpr typename std::underlying_type_t<E> to_underlying(E e) noexcept {
    return static_cast<typename std::underlying_type_t<E>>(e);
}

namespace {
    double getValFromBar(QDoubleSpinBox const *box, QSlider const *bar) 
    {
        auto delta = int(box->maximum() - box->minimum());
        auto var1 = int(bar->value() - bar->minimum());
        auto var2 = int(bar->maximum() - bar->minimum());
        return int(box->minimum()) + int(delta * int(var1 / var2));
    }
}// namespace

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    prevSize = this->size();
    ui->rotationSlider->setValue(int(100 * FractalData::defaultSpeed));
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
    // add File option
    auto fileMenu = menuBar()->addMenu("File");
    // add action to Exit the program
    fileMenu->addAction("Exit", []() { QApplication::quit(); });

    // add Settings option
    auto settingsMenu = menuBar()->addMenu("Settings");
    // add actions to make the app Fullscreen
    settingsMenu->addAction(
            "Fullscreen view", [this]() { hideAndShow(); }, QKeySequence(tr("F11")));
}

void MainWindow::updateButtons() 
// update the buttons
{
    ui->fractalColorButton->setPalette(QPalette(data.fractalColor));
    ui->fractalColorButton->setText(data.fractalColor.name());
    ui->ambienceColorButton->setPalette(QPalette(data.ambienceColor));
    ui->ambienceColorButton->setText(data.ambienceColor.name());
}

void MainWindow::chooseColor(QColor const &color, ColorType type = ColorType::FRACTAL) 
// handle the selection of a fractal
{
    QColor *colorMemory;
    if(type == ColorType::AMBIENCE)
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
    if(type == ColorType::AMBIENCE)
        title = "Select ambience color";
    else
        title = "Select fractal color";
    chooseColor(QColorDialog::getColor(Qt::green, this, title), type);
}

void MainWindow::connectBoxBar() 
// connect signals to slots
{
    connect(ui->firstCoordBar, &QSlider::valueChanged, ui->firstCoordBox, [this]() { ui->firstCoordBox->setValue(getValFromBar(ui->firstCoordBox, ui->firstCoordBar)); });
    connect(ui->secondCoordBar, &QSlider::valueChanged, ui->secondCoordBox, [this]() { ui->secondCoordBox->setValue(getValFromBar(ui->secondCoordBox, ui->secondCoordBar)); });
    connect(ui->thirdCoordBar, &QSlider::valueChanged, ui->thirdCoordBox, [this]() { ui->thirdCoordBox->setValue(getValFromBar(ui->thirdCoordBox, ui->thirdCoordBar)); });
    connect(ui->powerBarSlider, &QSlider::valueChanged, ui->powerSpinBox, [this]() { ui->powerSpinBox->setValue(2 * ui->powerBarSlider->value()); });
    connect(ui->firstCoordBar, &QSlider::valueChanged, [this]() { readAndDraw(); });
    connect(ui->secondCoordBar, &QSlider::valueChanged, [this]() { readAndDraw(); });
    connect(ui->thirdCoordBar, &QSlider::valueChanged, [this]() { readAndDraw(); });
    connect(ui->powerBarSlider, &QSlider::valueChanged, [this]() { readAndDraw(); });
    connect(ui->fractalColorButton, &QPushButton::clicked, [this]() { askColor(ColorType::FRACTAL); });
    connect(ui->ambienceColorButton, &QPushButton::clicked, [this]() { askColor(ColorType::AMBIENCE); });
    connect(ui->randomizeButton, &QPushButton::clicked, [this]() { generateRandom(); });
    connect(ui->rotationBox, &QCheckBox::stateChanged, [this]() { readAndDraw(); });
    connect(ui->zoomButton, &QPushButton::clicked, [this]() {
        data.setZoomCoefficient();
        ui->fractalWidget->repaint();
    });
    connect(ui->rotationSlider, &QSlider::valueChanged, [&]() {
        ui->rotationBox->setCheckState(Qt::Checked);
        data.setAbsoluteSpeed(ui->rotationSlider->value() / 100.0);
    });
}

void MainWindow::readAndDraw() 
// draw the fractal based on the information that it holds
{
    if(!isSetting) {
        data = FractalData(ui->firstCoordBox->value(), ui->secondCoordBox->value(), ui->thirdCoordBox->value(), quint8(ui->powerSpinBox->value()),
                           static_cast<FractalType>(ui->typeBox->currentIndex()), data.fractalColor, data.ambienceColor, data.camera, data.zoomCoefficient, ui->rotationBox->isChecked());
        ui->fractalWidget->repaint();
    }
}


void MainWindow::setValues() 
// set ui values
{
    isSetting = true;
    ui->firstCoordBox->setValue(data.a);
    ui->secondCoordBox->setValue(data.b);
    ui->thirdCoordBox->setValue(data.c);
    ui->powerSpinBox->setValue(data.n);
    ui->typeBox->setCurrentIndex(to_underlying(data.type));
    updateButtons();
    isSetting = false;
}

void MainWindow::generateRandom() 
// generate a new random value
{
    data.genRandom();
    setValues();
    ui->fractalWidget->repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event) 
// handle the signal from a key that was pressed
{
    if(event->key() == Qt::Key_F11) {
        hideAndShow();
    }
    if(event->key() == Qt::Key_Escape && isFullScreen) {
        hideAndShow();
    }
    QWidget::keyPressEvent(event);
}

void MainWindow::hideAndShow() 
// handle hide and show actions
{
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

void MainWindow::hideBorders() 
// hide the borders of the window
{
    ui->statusbar->hide();
    ui->centralwidget->setContentsMargins(0, 0, 0, 0);
}
