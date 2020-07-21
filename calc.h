//#ifndef CALC_H
#define CALC_H

#include <QMainWindow>
#pragma once

//#include <QWidget>
#include <QStack>
#include <QMenuBar>

class QLCDNumber;
class QPushButton;
class QTextEdit;
//class QMenuBar;
class QLabel;
class QDate;

// ======================================================================
class Calculator : public QWidget {
    Q_OBJECT
private:
    QLCDNumber*     m_plcd;
    QStack<QString> m_stk;
    QString         m_strDisplay;
    QTextEdit*      one ;
    QMenuBar*       mnuBar;
    QLabel*         m_plblToolTip;
    QLabel*         r_time;
    QDateTime*      dat;
    QTimer*         ptimer;
    QMenu*          pmnu;
    QMenu*          pmnuTD;

    QString         str_l;
protected:
    virtual bool event(QEvent* pe);


public:
    Calculator(QWidget* pwgt = 0);

    QPushButton* createButton(const QString& str);
    void         calculate   (                  );
    void ShowWindow (const QString& one);
public slots:
    void slotButtonClicked();
    void slotUpdateDateTime();
    //void createN();
signals:
    void goodbye       (   );
    //void pTimerN();
};

