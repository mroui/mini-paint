#include "Headers/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow MiniPaint;
    MiniPaint.show();
    return application.exec();
}
