#include "samplewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SampleWidget w;
    w.show();
    return a.exec();
}
