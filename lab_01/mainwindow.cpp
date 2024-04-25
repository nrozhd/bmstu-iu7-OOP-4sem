#include "mainwindow.h"

#include <cstring>
#include <climits>

#include "ui_mainwindow.h"
#include "manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    request_t request = {.action = INIT};
    action_manager(request);
}

MainWindow::~MainWindow()
{
    request_t request = {.action = QUIT};
    action_manager(request);
    delete ui;
}

response_code_t MainWindow::draw(void)
{
    request_t request = {.action = DRAW};
    request.scene.data = ui->graphicsView->scene();
    request.scene.height = ui->graphicsView->height();
    request.scene.width = ui->graphicsView->width();

    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);

    return rc;
}

void MainWindow::on_download_action_triggered()
{
    QString path = QFileDialog::getOpenFileName();

    request_t request = {.action = LOAD};

    strncpy(request.filename, path.toUtf8().data(), path.size());

    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);
    else
    {
        rc = draw();
        if (rc)
            failure_message(rc);
    }
}


void MainWindow::on_upload_action_triggered()
{
    QString path = QFileDialog::getSaveFileName();

    request_t request = {.action = SAVE};

    strncpy(request.filename, path.toUtf8().data(), path.size());

    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);
    else
    {
        rc = draw();
        if (rc)
            failure_message(rc);
    }
}

double get_field_num(QLineEdit *field)
{
    bool is_correct_num;
    double num = field->text().toFloat(&is_correct_num);

    if (!is_correct_num)
        return INT_MIN;

    return num;
}

void MainWindow::on_moveButton_clicked()
{
    double dx = get_field_num(ui->dxField);
    double dy = get_field_num(ui->dyField);
    double dz = get_field_num(ui->dzField);

    if ((dx == INT_MIN) || (dy == INT_MIN) || (dz == INT_MIN))
    {
        failure_message(WRONG_MOVE_COEFFICIENTS);
        return;
    }

    request_t request = {.action = MOVE, .move = {dx, dy, dz}};
    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);
    else
    {
        rc = draw();
        if (rc)
            failure_message(rc);
    }
}


void MainWindow::on_scaleButton_clicked()
{

    double kx = get_field_num(ui->kxField);
    double ky = get_field_num(ui->kyField);
    double kz = get_field_num(ui->kzField);

    if ((kx == INT_MIN) || (ky == INT_MIN) || (kz == INT_MIN))
    {
        failure_message(WRONG_SCALE_COEFFICIENTS);
        return;
    }

    request_t request = {.action = SCALE, .scale = {kx, ky, kz}};
    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);
    else
    {
        rc = draw();
        if (rc)
            failure_message(rc);
    }
}

void MainWindow::on_turnButton_clicked()
{
    double ax = get_field_num(ui->axField);
    double ay = get_field_num(ui->ayField);
    double az = get_field_num(ui->azField);

    if ((ax == INT_MIN) || (ay == INT_MIN) || (az == INT_MIN))
    {
        failure_message(WRONG_TURN_COEFFICIENTS);
        return;
    }

    request_t request = {.action = TURN, .turn = {ax, ay, az}};
    response_code_t rc = action_manager(request);

    if (rc)
        failure_message(rc);
    else
    {
        rc = draw();
        if (rc)
            failure_message(rc);
    }
}

