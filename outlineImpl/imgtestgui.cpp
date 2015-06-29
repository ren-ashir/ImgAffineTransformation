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
    setTimeAndUserStringToLogLine(" msec OpenCV took for the rotate");
}

void ImgTestGui::on_pushButton_3_clicked()
{ // CUDA rotator
}

void ImgTestGui::on_pushButton_4_clicked()
{ // one CPU thread
    setNewPixmapToScene(model.getOneThreadCpuRotatedQPixmap());
    setTimeAndUserStringToLogLine(" msec for a one thread CPU required");
}
void ImgTestGui::on_pushButton_5_clicked()
{ // multi CPU thread
    setNewPixmapToScene (model.getMultithreadRoratedQpixmap());
    setTimeAndUserStringToLogLine(" msec a multithrad CPU took for the rotate");
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

void ImgTestGui::on_pushButton_6_clicked()
{
   // model.saveButtonPushed();
//   QGraphicsPixmapItem TMP;
//   TMP.pixmap().toImage().save("output.jpg")
    qgpitem->pixmap().toImage().save("output.jpg");
}
