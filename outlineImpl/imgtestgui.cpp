/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#include "imgtestgui.h"
#include "ui_imgtestgui.h"


ImgTestGui::ImgTestGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImgTestGui)
{
    ui->setupUi(this);
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
    setNewPixmapToScene(model.getOpenCvRotatedQPixmap());
    setTimeAndUserStringToLogLine(" msec OpenCV took for rotate");
}

void ImgTestGui::on_pushButton_3_clicked()
{ // CUDA rotator

}

void ImgTestGui::on_pushButton_4_clicked()
{ // one CPU thread
    setNewPixmapToScene(model.getOneThreadCpuRotatedQPixmap());
    setTimeAndUserStringToLogLine(" msec for one thread CPU required");
}

//private
void ImgTestGui::setNewPixmapToScene(const QPixmap& pix)
{
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



