// figureswidget.cpp
#include "figureswidget.h"
#include <QtWidgets>
#include <QPainter>
#include <QMouseEvent>

figureswidget::figureswidget(QWidget *parent)
    : QWidget{parent}
{
    Shape rectangle;
    rectangle.type = Shape::Rectangle;
    rectangle.rect = QRect(100, 300, 100, 100);

    Shape circle;
    circle.type = Shape::Circle;
    circle.circle = QRect(300, 50, 100, 100);

    Shape triangle;
    triangle.type = Shape::Triangle;
    triangle.poly << QPoint(600, 300) << QPoint(650, 400) << QPoint(550, 400);

    shapes.append(rectangle);
    shapes.append(circle);
    shapes.append(triangle);

}

void figureswidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(Qt::black);

    QColor shapeColor = readColorFromSettingsFile();
    if (!shapeColor.isValid()) {
        shapeColor = Qt::white;
    }

    painter.setBrush(shapeColor);

    for (const Shape &shape : shapes) {
        if (shape.type == Shape::Rectangle) {
            painter.fillRect(shape.rect, shapeColor);
        } else if (shape.type == Shape::Circle) {
            painter.drawEllipse(shape.circle);
        } else if (shape.type == Shape::Triangle) {
            painter.drawPolygon(shape.poly);
        }
    }
}


void figureswidget::mousePressEvent(QMouseEvent *event)
{
    bool metric = readMetricFromSettingsFile();
    messagebox.setWindowTitle("Surface Area");
    for (int i = 0; i < shapes.size(); ++i) {
        const Shape &shape = shapes[i];

        if (shape.type == Shape::Rectangle && shape.rect.contains(event->pos())) {
            qDebug() << "Clicked on rectangle " << i;
            bool ok;
            double width, height;
            if (metric) {
                width = QInputDialog::getDouble(this, "Rectangle Width", "Enter width (in meters):", 0, 0, 1000, 2, &ok);
                height = QInputDialog::getDouble(this, "Rectangle Height", "Enter height (in meters):", 0, 0, 1000, 2, &ok);
            } else {
                width = QInputDialog::getDouble(this, "Rectangle Width", "Enter width (in feet):", 0, 0, 1000, 2, &ok);
                height = QInputDialog::getDouble(this, "Rectangle Height", "Enter height (in feet):", 0, 0, 1000, 2, &ok);
                width *= 0.3048;
                height *= 0.3048;
            }

            if (!ok) {
                return;
            }

            double surfaceArea = width * height;

            if (metric) {
                messagebox.setText("Surface area of rectangle: " + QString::number(surfaceArea) + " square meters");
                messagebox.exec();
            } else {
                messagebox.setText("Surface area of rectangle: " + QString::number(surfaceArea) + " square feet");
                messagebox.exec();
            }

            break;
        } else if (shape.type == Shape::Circle && shape.circle.contains(event->pos())) {
            qDebug() << "Clicked on circle " << i;
            bool ok;
            double radius;
            if (metric) {
                radius = QInputDialog::getDouble(this, "Circle Radius", "Enter radius (in meters):", 0, 0, 1000, 2, &ok);
            } else {
                radius = QInputDialog::getDouble(this, "Circle Radius", "Enter radius (in feet):", 0, 0, 1000, 2, &ok);
                radius *= 0.3048;
            }

            if (!ok) {
                return;
            }

            double surfaceArea = 3.14159 * radius * radius;

            if (metric) {
                messagebox.setText("Surface area of circle: " + QString::number(surfaceArea) + " square meters");
                messagebox.exec();
                qDebug() << "Surface area of circle: " << surfaceArea << " square meters";
            } else {
                messagebox.setText("Surface area of circle: " + QString::number(surfaceArea) + " square feet");
                messagebox.exec();
            }

            break;
        } else if (shape.type == Shape::Triangle && shape.poly.containsPoint(event->pos(), Qt::OddEvenFill)) {
            qDebug() << "Clicked on triangle " << i;
            bool ok;
            double base, triHeight;
            if (metric) {
                base = QInputDialog::getDouble(this, "Triangle Base", "Enter base (in meters):", 0, 0, 1000, 2, &ok);
                triHeight = QInputDialog::getDouble(this, "Triangle Height", "Enter height (in meters):", 0, 0, 1000, 2, &ok);
            } else {
                base = QInputDialog::getDouble(this, "Triangle Base", "Enter base (in feet):", 0, 0, 1000, 2, &ok);
                triHeight = QInputDialog::getDouble(this, "Triangle Height", "Enter height (in feet):", 0, 0, 1000, 2, &ok);
                base *= 0.3048;
                triHeight *= 0.3048;
            }

            if (!ok) {
                return;
            }

            double surfaceArea = 0.5 * base * triHeight;

            if (metric) {
                messagebox.setText("Surface area of triangle: " + QString::number(surfaceArea) + " square meters");
                messagebox.exec();
            } else {
                messagebox.setText("Surface area of trianlge: " + QString::number(surfaceArea) + " square feet");
                messagebox.exec();
            }

            break;
        }

    }

}

QColor figureswidget::readColorFromSettingsFile()
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


bool figureswidget::readMetricFromSettingsFile()
{
    QString fileName = "settings.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return true;
    }

    QTextStream in(&file);

    in.readLine();

    QString secondLine;
    if (in.atEnd()) {
        file.close();
        return true;
    }
    secondLine = in.readLine().trimmed();
    qDebug() << secondLine;
    file.close();
    bool result = (secondLine.compare("true", Qt::CaseInsensitive) == 0);

    return result;
}
