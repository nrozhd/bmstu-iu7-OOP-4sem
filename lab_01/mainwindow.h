#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include "QFileDialog"
#include "responsecodes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    response_code_t draw(void);

    void on_download_action_triggered();

    void on_upload_action_triggered();

    void on_moveButton_clicked();

    void on_scaleButton_clicked();

    void on_turnButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
