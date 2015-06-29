/*
 * img_provider.cpp
 * This source code is completely free.
 * 2015, Renat Ashirbakiev
 * r.robotman@yandex.ru - Russia->Moscow
 * https://github.com/ren-ashir/ImgAffineTransformation/
*/


#include <QCoreApplication>
#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "img_includs.h"
#include "imgtestgui.h"
using namespace std;
using namespace imgznd;

#include <QApplication>
class Application final : public QApplication {
public:
    Application(int& argc, char** argv) : QApplication{argc, argv} {}
    virtual bool notify(QObject *receiver, QEvent *e) override
    {
        try {
            return QApplication::notify(receiver, e);
            // Handle the desired exception type
        }
        catch(std::out_of_range &orn)
        {
            std::cerr << "out of range: " << orn.what() << "\n";
        }
        catch(std::bad_alloc &ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception: " << e.what() << '\n';
        }
        catch(...)
        {
            std::cerr << "Unknown exception [SANDBOX]\n";
            throw; // try to continue
        }
        return true;
    }
};

int main(int argc, char *argv[])
{

    Application a(argc, argv);
    ImgTestGui gui;
    gui.show();
    return a.exec();
}
/* backstage code
        //        int sz = 10000000000;
        //        float *px = new float[sz]; //{1,2,3,4,5,6};
        //        float *py = new float[sz]; //{1,2,3,4,4,6};
        //        std::for_each (px,px + sz,[](float &p) { static int i = 1; p = i; i++; });
        //        std::for_each (py,py + sz,[=](float &p) { static int i = sz; p = i; i--; });
        //        //std::copy(py,py + sz,ostream_iterator<float>(cout," "));
        //        // return 0;
        //        auto t0 = chrono::high_resolution_clock::now();
        //        imgznd::rotatePoint1thread(px,py,2.0,sz);
        //        auto t1 = chrono::high_resolution_clock::now();
        //        //cout << res << '\n';
        //        cout << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " msec\n";

        //        t0 = chrono::high_resolution_clock::now();
        //        imgznd::rotatePointMultithread(px,py,2.0,sz);
        //        t1 = chrono::high_resolution_clock::now();
        //        //cout << res << '\n';
        //        cout << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << " msec\n";

        // std::copy(px,px + sz,ostream_iterator<float>(cout," "));
        //        OpenCvImgRepr img(getJpgLink());//,imgOut;
        //        openCvResizeBorder(img,200,200);
        //        openCvRotate (img,img,30,1);


        // QGraphicsView view(&scene);
        //QGraphicsScene scene;
        //QGraphicsPixmapItem item(QPixmap(cvMatToQPixmap(img)));
        //scene.addItem(&item);
        //view.show();

        //                openCvResizeBorder(img,100,100);
        //                openCvRotate(img,imgOut,30,1);
        //                imgOut.saveToFile("rotated.png");

        //                openCvZoom (img,9.0);
        //                img.saveToFile("zoomed.png");

        //        ImgReader iread(getJpgLink());
        //        iread.testfSaveImage("new.jpg");

*/
