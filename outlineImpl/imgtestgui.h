/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/

#ifndef IMGTESTGUI_H
#define IMGTESTGUI_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <memory>
#include "img_includs.h"
#include "img_datamodel.h"



namespace Ui {
class ImgTestGui;
}


class ImgTestGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImgTestGui(QWidget *parent = 0);
    ~ImgTestGui();

private slots:
    void on_pushButton_clicked();

private:
    QPixmap qimg;
    imgznd::DataModel model;
    Ui::ImgTestGui *ui;
    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<QGraphicsPixmapItem> qgpitem;
};



#endif // IMGTESTGUI_H
