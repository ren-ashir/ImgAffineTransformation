/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include "imgtestgui.h"
#include "ui_imgtestgui.h"
#include <QFileInfo>
#include <QDir>
ImgTestGui::ImgTestGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImgTestGui)
{
    ui->setupUi(this);
    ui->lineEdit_path_3->setText(model.getPath().c_str());
    ui->lineEdit_dest_path->setText(QDir::currentPath() + "/out" + ui->lineEdit_path_3->text().split("/").back());
}

ImgTestGui::~ImgTestGui()
{
    delete ui;
}

void ImgTestGui::on_pushButton_clicked()
{ // For the image view
    setNewPixmapToScene(model.getStrightforwardQPixmap());
    setTimeAndUserStringToLogLine(" msec for read the image");
}

void ImgTestGui::on_pushButton_2_clicked()
{ // An OpenCV button
    double angle = ui->lineEdit_deg_5->text().toDouble();
    setNewPixmapToScene(model.getOpenCvRotatedQPixmap(angle));
    setTimeAndUserStringToLogLine(" msec OpenCV took for the rotate");
}

void ImgTestGui::on_pushButton_3_clicked()
{ // CUDA rotator
    double angle = ui->lineEdit_deg_5->text().toDouble();
    setNewPixmapToScene(model.getCUDARotatedPixmap(angle));
    setTimeAndUserStringToLogLine(" msec for CUDA required");
}

void ImgTestGui::on_pushButton_4_clicked()
{ // one CPU thread
    double angle = ui->lineEdit_deg_5->text().toDouble();
    setNewPixmapToScene(model.getOneThreadCpuRotatedQPixmap(angle));
    setTimeAndUserStringToLogLine(" msec for a one thread CPU required");
}
void ImgTestGui::on_pushButton_5_clicked()
{ // multi CPU thread
    double angle = ui->lineEdit_deg_5->text().toDouble();
    setNewPixmapToScene (model.getMultithreadRoratedQpixmap(angle));
    setTimeAndUserStringToLogLine(" msec a multithrad CPU took for the rotate");
}

//private
void ImgTestGui::setNewPixmapToScene(const QPixmap& pix)
{
    qDebug () << model.getPath().c_str();
    ui->lineEdit_path_3->setText(model.getPath().c_str());
    qgpitem = make_unique<QGraphicsPixmapItem>(pix);
    scene = make_unique<QGraphicsScene>();
    scene->addItem(qgpitem.get());
    ui->graphicsView->setScene(scene.get());
    ui->graphicsView->show();
}

void ImgTestGui::setTimeAndUserStringToLogLine(const QString &s)
{
    ui->lineEdit_4->setText(QString::number(model.lastOperationTime()) + s);
}

void ImgTestGui::on_pushButton_6_clicked()
{
    // model.saveButtonPushed();
    //   QGraphicsPixmapItem TMP;
    //   TMP.pixmap().toImage().save("output.jpg")
//    QFileInfo file(ui->lineEdit_dest_path->text());
//    if (file.exists() && file.isDir())
     qgpitem->pixmap().toImage().save(ui->lineEdit_dest_path->text());
}

void ImgTestGui::on_lineEdit_path_3_textChanged(const QString &arg1)
{
    qDebug () << arg1;
    model.setPath(ui->lineEdit_path_3->text().toStdString());
     ui->lineEdit_dest_path->setText(QDir::currentPath() + "/out" + ui->lineEdit_path_3->text().split("/").back());
}
