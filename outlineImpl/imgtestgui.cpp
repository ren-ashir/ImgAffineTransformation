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
{
    qgpitem = make_unique<QGraphicsPixmapItem>(model.getQPixmap());
    scene = make_unique<QGraphicsScene>();
    scene->addItem(qgpitem.get());
    ui->graphicsView->setScene(scene.get());
    ui->graphicsView->show();
}
