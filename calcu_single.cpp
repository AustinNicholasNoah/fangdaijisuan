#include "calcu_single.h"
#include "ui_calcu_single.h"
#include "samplewidget.h"
#include "result_samecapitalplusinterest.h"
#include "result_samecapital.h"
#include <QDebug>

Calcu_single::Calcu_single(int loanType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calcu_single)
{
    ui->setupUi(this);

    //默认为等额本息法还款
    refundType = 0;

    //若贷款类别为公积金贷款，改变贷款类别lable内容
    if(loanType == 1){
        ui->label_loanType->setText(tr("公积金贷款"));
    }

    //正则表达式限制输入
    ui->lineEdit_houseUnitCost->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,5}"), this));
    ui->lineEdit_houseArea->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,3}"), this));
    ui->lineEdit_loanRate->setValidator(new QRegExpValidator(QRegExp("[1-9]{0,1}[0-9]\\.[0-9]{0,2}"), this));
}

Calcu_single::~Calcu_single()
{
    delete ui;
}

void Calcu_single::on_pushButton_clear_clicked()
{
    //清空输入
    ui->lineEdit_houseUnitCost->clear();
    ui->lineEdit_houseArea->clear();
    ui->lineEdit_loanRate->clear();

    //按揭成数和按揭年数设为初始值
    ui->comboBox_ajcs->setCurrentIndex(3);
    ui->comboBox_ajns->setCurrentIndex(0);

    //设置为等额本息
    ui->radioButton_sameCapitalPlusInterest->setChecked(true);
    refundType = 0;
}

void Calcu_single::on_text_changed(){
    bool flag1 = !(ui->lineEdit_houseUnitCost->text().isEmpty());
    bool flag2 = !(ui->lineEdit_houseArea->text().isEmpty());
    bool flag3 = !(ui->lineEdit_loanRate->text().isEmpty());

    //如果三个lineEdit均有输入，激活按钮
    if(flag1 && flag2 && flag3){
        ui->pushButton_start->setEnabled(true);
    }
    //否则禁用按钮
    else{
        ui->pushButton_start->setEnabled(false);
    }
}

void Calcu_single::on_radioButton_sameCapitalPlusInterest_clicked()
{
    refundType = 0;
}

void Calcu_single::on_radioButton_sameCapital_clicked()
{
    refundType = 1;
}

//开始计算
void Calcu_single::on_pushButton_start_clicked()
{
    long long unitCost = ui->lineEdit_houseUnitCost->text().toInt();
    long long area = ui->lineEdit_houseArea->text().toInt();
    //转换成月利率
    double rate = ui->lineEdit_loanRate->text().toDouble() / 12 / 100;
    double ajcs = ui->comboBox_ajcs->currentText().toDouble() / 10;
    int months = ui->comboBox_ajns->currentText().toInt() * 12;

    //贷款总额
    long double loanMoney = unitCost * area * ajcs;
    //首付
    long long firstPay = unitCost * area * (1 - ajcs) + 0.5;//+0.5便于四舍五入

    //如果计算方式为等额本息
    if(refundType == 0){
        //每月还款额
        long double MIP;
        //利息
        long long interest;
        //还款总额
        long long refundMoney;

        //调用静态的计算函数，给变量赋值
        SampleWidget::calculate_sameCapitalPlusInterest(loanMoney, rate, months,
                                                        MIP, interest, refundMoney);

        Result_SameCapitalPlusInterest* res_dialog = new Result_SameCapitalPlusInterest();
        //将计算结果传入
        res_dialog->setValue(true, (long long)MIP, (long long)loanMoney, interest, refundMoney, months, firstPay);
        res_dialog->show();
    }
    //如果计算方式为等额本金
    else if(refundType == 1){
        //首月月供
        long double firstMonthPay;
        //每月递减
        long double decrease;
        //利息
        long long interest;
        //还款总额
        long double refundMoney;

        //调用静态的计算函数，给变量赋值
        SampleWidget::calculate_sameCapital(loanMoney, rate, months,
                                            firstMonthPay, decrease, interest, refundMoney);
        Result_sameCapital* res_dialog = new Result_sameCapital();
        //将计算结果传入
        res_dialog->setValue(true, (long long)firstMonthPay, (long long)decrease, (long long)loanMoney,
                             interest, (long long)refundMoney,months, firstPay);
        res_dialog->show();
    }
}

