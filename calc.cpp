#include "calc.h"

#include <QtWidgets>

// ----------------------------------------------------------------------
Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    m_plblToolTip = new QLabel;
    m_plblToolTip->setWindowFlags(Qt::ToolTip);

    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);

    mnuBar = new QMenuBar;
    pmnu   = new QMenu("&Menu");
    pmnu->addAction("&Exit", this, SIGNAL(goodbye()));
    QAction* pCheckableAction = pmnu->addAction("&CheckableItem");
    pCheckableAction->setCheckable(true);
    pCheckableAction->setChecked(true);
    pmnuTD = new QMenu("TimeDat");


    QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'}
                           };

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createButton("CE"), 1, 3);

    ptopLayout->addWidget(createButton("EXIT"), 1, 2);
    r_time= new QLabel;
    r_time->setText("____");
    ptopLayout->addWidget(r_time, 1, 0, 1,2);

    one = new QTextEdit;
    ptopLayout->addWidget(one, 0, 5, 6, 1); //6, 0, 1, 6

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
           ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        }
    }
    setLayout(ptopLayout);

    ptimer = new QTimer(this);
    ptimer->start(1000);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotUpdateDateTime()));

}

// ----------------------------------------------------------------------
QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setToolTip(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}


// ----------------------------------------------------------------------
void Calculator::calculate()
{
    qreal   fOperand2    = m_stk.pop().toFloat();
    QString strOperation = m_stk.pop();
    qreal   fOperand1    = m_stk.pop().toFloat();
    qreal   fResult      = 0;

    if (strOperation == "+") {
        fResult = fOperand1 + fOperand2;
    }
    if (strOperation == "-") {
        fResult = fOperand1 - fOperand2;
    }
    if (strOperation == "/") {
        fResult = fOperand1 / fOperand2;
    }
    if (strOperation == "*") {
        fResult = fOperand1 * fOperand2;
    }
    m_plcd->display(fResult);

    one->append(QString::number(fResult)); //+"\n");

}

// ----------------------------------------------------------------------
void Calculator::slotButtonClicked()
{
    QString str = ((QPushButton*)sender())->text();

    if (str == "CE") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;            
    }
    if(str == "EXIT")
        {
        emit goodbye();
        return;}

    if (str.contains(QRegExp("[0-9]"))) {

        if(str_l == "+"||"-"||"*"||"/"){
        m_strDisplay="0";}

        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str == ".") {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }
    else {
        if (m_stk.count() >= 2) {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));
            if (str != "=") {
                m_stk.push(str);
            }
        }
        else {
//            if(m_stk.empty()==true){
            m_stk.push(QString().setNum(m_plcd->value()));//}
            m_stk.push(str);
            m_strDisplay = "";            
        }
        str_l = str;
    }
}


bool Calculator::event(QEvent* pe)
{
    if (pe->type() == QEvent::ToolTip) {
        QHelpEvent* peHelp = static_cast<QHelpEvent*>(pe);
        m_plblToolTip->move(peHelp->globalPos());
        //m_plblToolTip->setText(toolTip());
        //m_plblToolTip->show();
        QTimer::singleShot(3000, m_plblToolTip, SLOT(hide()));

        return true;
    }

    return QWidget::event(pe);
}

void Calculator::slotUpdateDateTime()
{
    QString str =
        QDateTime::currentDateTime().toString("dd.MM.yy h:mm:ss");
    r_time->setText(str);
    QString pDatTime ="13.07.20 15:14:30";
    if(str==pDatTime)
    {
        ShowWindow(str);
    }

}
void Calculator::ShowWindow (const QString& one)
{
    QLabel *pLabel = new QLabel(one);// =pLab.value();
    pLabel->show();
}
