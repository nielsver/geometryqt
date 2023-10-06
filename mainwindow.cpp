#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QColorDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->Metric->setChecked(true);
    setcss();
    color = readColorFromSettingsFile();
    if (!color.isValid()) {
        ui->color->setText("Selected Color: White");
    } else {
        QString backgroundStyle;
        QString textStyle;

        if (color == Qt::black) {
            backgroundStyle = "background-color: white;";
            textStyle = "color: black;";
        } else {
            backgroundStyle = "background-color: black;";
            textStyle = "color: " + color.name() + ";";
        }

        QString combinedStyle = backgroundStyle + textStyle;
        ui->color->setStyleSheet(combinedStyle);
        ui->color->setText("Selected color: " + color.name());
    }


    windowtitle();

    connect(ui->Metric, &QCheckBox::stateChanged, this, &MainWindow::onMetricStateChanged);
    connect(ui->imperial, &QCheckBox::stateChanged, this, &MainWindow::onImperialStateChanged);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openColorPickerDialog);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::saveSettingsToFile);




}
void MainWindow::onMetricStateChanged(int state) {
    if (state == Qt::Checked) {
        ui->imperial->setChecked(false);
    }
}
void MainWindow::onImperialStateChanged(int state) {
    if (state == Qt::Checked) {
        ui->Metric->setChecked(false);
    }
}
void MainWindow::windowtitle() {

    setWindowTitle("Geometry");
    QPixmap pixmap(64, 64);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::darkBlue);
    pen.setWidth(2);

    painter.setPen(pen);

    QPointF p1(32, 10);
    QPointF p2(10, 62);
    QPointF p3(54, 62);

    QPolygonF triangle;
    triangle << p1 << p2 << p3;

    QLinearGradient gradient(p1, p2);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    QBrush brush(gradient);
    painter.setBrush(brush);

    painter.begin(&pixmap);

    painter.drawPolygon(triangle);

    painter.end();

    QIcon icon(pixmap);
    setWindowIcon(icon);


}
void MainWindow::setcss() {

    QString stylesheettab = "background-color: #F0F0F0;";
    QString title = "font-size: 24px; font-weight: bold; color: #007ACC; margin-bottom: 10px; text-align: center;";
    ui->tab_2->setStyleSheet(stylesheettab);
    ui->tab->setStyleSheet("background-color:black");
    ui->pushButton->setStyleSheet("QPushButton { background-color: #007ACC; color: white; border: none; padding: 8px 16px; margin: 5px; border-radius: 5px; } QPushButton:hover { background-color: #005CA3; color: white; }");
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: #007ACC; color: white; border: none; padding: 8px 16px; margin: 5px; border-radius: 5px; } QPushButton:hover { background-color: #005CA3; color: white; }");
    ui->label->setStyleSheet(title);
    ui->color->setStyleSheet("background-color: black;color: white;");
    ui->widget->setStyleSheet("color: white;");


}
void MainWindow::openColorPickerDialog() {
    color = QColorDialog::getColor();

        if (color.isValid()) {
            QString backgroundStyle;
            QString textStyle;

            if (color == Qt::black) {
                backgroundStyle = "background-color: white;";
                textStyle = "color: black;";
            } else {
                backgroundStyle = "background-color: black;";
                textStyle = "color: " + color.name() + ";";
            }

            QString combinedStyle = backgroundStyle + textStyle;
            ui->color->setStyleSheet(combinedStyle);
            ui->color->setText("Selected color: " + color.name());
        }
}
void MainWindow::saveSettingsToFile() {
    QString fileName = "settings.txt";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << color.name() << "\n";
        if (ui->Metric->isChecked()) {
            stream << "true" << "\n";
        } else {
            stream << "false" << "\n";
        }

        file.close();
    } else {
        qDebug() << "could not open file";
    }
    ui->tabWidget->setCurrentWidget(ui->tab);
}
QColor MainWindow::readColorFromSettingsFile()
{
    QString fileName = "settings.txt";
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return QColor(Qt::white);
        }

        QTextStream in(&file);
        QString line = in.readLine().trimmed();

        file.close();

        QColor color;
        color.setNamedColor(line);

        return color;
}

MainWindow::~MainWindow()
{
    delete ui;
}

