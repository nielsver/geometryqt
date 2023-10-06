#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void windowtitle();
    void setcss();
    QColor readColorFromSettingsFile();

private slots:
    void onMetricStateChanged(int state);
    void onImperialStateChanged(int state);
    void openColorPickerDialog();
    void saveSettingsToFile();




private:
    Ui::MainWindow *ui;
    QColor selectedColor;
    QColor color = QColor(Qt::white);

};
#endif // MAINWINDOW_H
