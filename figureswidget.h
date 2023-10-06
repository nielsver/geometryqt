#ifndef FIGURESWIDGET_H
#define FIGURESWIDGET_H

#include <QWidget>
#include <QWidget>
#include <QVector>
#include <QRect>
#include <QPolygon>
#include <QMessageBox>

class figureswidget : public QWidget
{
    Q_OBJECT
public:
    explicit figureswidget(QWidget *parent = nullptr);

signals:


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QColor readColorFromSettingsFile();
    bool readMetricFromSettingsFile();

private:
    struct Shape {
           enum Type { Rectangle, Circle, Triangle };
           Type type;
           QRect rect;
           QRect circle;
           QPolygon poly;
       };

       QVector<Shape> shapes;
       QMessageBox messagebox;


};

#endif // FIGURESWIDGET_H
