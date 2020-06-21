#include "result_samecapital.h"
#include "ui_result_samecapital.h"

Result_sameCapital::Result_sameCapital(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result_sameCapital)
{
    ui->setupUi(this);
}

Result_sameCapital::~Result_sameCapital()
{
    delete ui;
}

void Result_sameCapital::setValue(bool hasFirstPay, long long firstMonthPay, long long decrease, long long loanTotalMoney,
                                  long long interset, long long refundMoney, int months, long long firstPay){
    //如果为按贷款总额计算，不需要首付，则禁用文本
    ui->label_firstPay->setEnabled(hasFirstPay);
    ui->label_firstPay_front->setEnabled(hasFirstPay);
    ui->label_firstPay_back->setEnabled(hasFirstPay);

    ui->label_firstPay->setText(QString::number(firstPay));
    ui->label_firstMonthPay->setText(QString::number(firstMonthPay));
    ui->label_loanMoney->setText(QString::number(loanTotalMoney));
    ui->label_decreaseMoney->setText(QString::number(decrease));
    ui->label_interest->setText(QString::number(interset));
    ui->label_refundMoney->setText(QString::number(refundMoney));
    ui->label_months->setText(QString::number(months));
    ui->label_firstPay->setText(QString::number(firstPay));
}
