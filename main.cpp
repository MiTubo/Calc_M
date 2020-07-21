//This programm have problem with:
//    1)accuracity
//    Working( 2)recurring click on action ( +, -, /, *) without click "=" between them)

#include "calc.h"
#include <QApplication>
//#include<class_menubar.h>
#include <QtWidgets>

//#include <QApplication>
//#include "Calculator.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMenuBar wgt;
    QMenu *pmnu   = new QMenu("&Menu");
    pmnu->addAction("&Exit", &app, SLOT(quit()));

    Calculator   *calculator = new Calculator;
    QObject::connect(calculator, SIGNAL(goodbye()),  &app, SLOT(quit()));

    //QObject::connect(calculator, SIGNAL(pTimerN()),  calculator, SLOT(createN()));

    QBoxLayout* pbxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    pbxLayout->addWidget(calculator);
    wgt.setLayout(pbxLayout);
    wgt.resize(300,300);
    wgt.addMenu(pmnu);
    wgt.show();


    //calculator.setWindowTitle("Calculator");
    //calculator.resize(230, 200);
    //calculator.setToolTip("My Tool Tip");

    //QObject::connect(&calculator, SIGNAL(goodbye()),  &app, SLOT(quit()));

    //calculator.show();
    return app.exec();
}

