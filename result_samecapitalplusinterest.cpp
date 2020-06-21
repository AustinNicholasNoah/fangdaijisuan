#include "result_samecapitalplusinterest.h"
#include "ui_result_samecapitalplusinterest.h"

Result_SameCapitalPlusInterest::Result_SameCapitalPlusInterest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result_SameCapitalPlusInterest)
{
    ui->setupUi(this);
}

Result_SameCapitalPlusInterest::~Result_SameCapitalPlusInterest()
{
    delete ui;
}

void Result_SameCapitalPlusInterest::setValue(bool hasFirstPay, long long MIP, long long loanTotalMoney,
                                              long long interset, long long refundMoney, int months, long long firstPay){
    //如果为按贷款总额计算，不需要首付，则禁用文本
    ui->label_firstPay->setEnabled(hasFirstPay);
    ui->label_firstPay_front->setEnabled(hasFirstPay);
    ui->label_firstPay_back->setEnabled(hasFirstPay);

    ui->label_firstPay->setText(QString::number(firstPay));
    ui->label_MIP->setText(QString::number(MIP));
    ui->label_loanToalMoney->setText(QString::number(loanTotalMoney));
    ui->label_interest->setText(QString::number(interset));
    ui->label_refundMoney->setText(QString::number(refundMoney));
    ui->label_months->setText(QString::number(months));
    ui->label_firstPay->setText(QString::number(firstPay));
}
