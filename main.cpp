//This programm have problem with:
//         1)accuracity
//    Done 2)recurring click on action ( +, -, /, *) without click "=" between them)

#include "calc.h"
#include <QApplication>

#include <QtWidgets>


// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMenuBar wgt;
    QMenu *pmnu   = new QMenu("&Menu");
    pmnu->addAction("&Exit", &app, SLOT(quit()));

    Calculator   *calculator = new Calculator;
    QObject::connect(calculator, SIGNAL(goodbye()),  &app, SLOT(quit()));

    QBoxLayout* pbxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    pbxLayout->addWidget(calculator);
    wgt.setLayout(pbxLayout);
    wgt.resize(300,300);
    wgt.addMenu(pmnu);
    wgt.show();

    return app.exec();
}

