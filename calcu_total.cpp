#include "calcu_total.h"
#include "ui_calcu_total.h"
#include "samplewidget.h"
#include "result_samecapitalplusinterest.h"
#include "result_samecapital.h"

Calcu_total::Calcu_total(int loanType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calcu_total)
{
    ui->setupUi(this);

    //如果为公积金贷款，则修改贷款类别label
    if(loanType == 1){
        ui->label_loanType->setText(tr("公积金贷款"));
    }

    //还款方式：默认为等额本息
    refundType = 0;

    //正则表达式限制输入
    ui->lineEdit_loanTotalMoney->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,5}\\.[0-9]{0,2}"), this));
    ui->lineEdit_loanRate->setValidator(new QRegExpValidator(QRegExp("[1-9]{0,1}[0-9]\\.[0-9]{0,2}"), this));
}

Calcu_total::~Calcu_total()
{
    delete ui;
}

void Calcu_total::on_text_changed(){
    bool flag1 = !(ui->lineEdit_loanTotalMoney->text().isEmpty());
    bool flag2 = !(ui->lineEdit_loanRate->text().isEmpty());

    //如果两个lineEdit均有输入，激活按钮
    if(flag1 && flag2){
        ui->pushButton_start->setEnabled(true);
    }
    //否则禁用按钮
    else{
        ui->pushButton_start->setEnabled(false);
    }
}

void Calcu_total::on_pushButton_clear_clicked()
{
    //清空输入
    ui->lineEdit_loanTotalMoney->clear();
    ui->lineEdit_loanRate->clear();

    //按揭年数设为初始值
    ui->comboBox_ajns->setCurrentIndex(0);

    //设置为等额本息
    ui->radioButton_sameCapitalPlusInterest->setChecked(true);
    refundType = 0;
}

void Calcu_total::on_radioButton_sameCapitalPlusInterest_clicked()
{
    refundType = 0;
}

void Calcu_total::on_radioButton_radioButton_sameCapital_clicked()
{
    refundType = 1;
}

void Calcu_total::on_pushButton_start_clicked()
{
    long double loanMoney = ui->lineEdit_loanTotalMoney->text().toDouble() * 10000;
    //转换成月利率
    double rate = ui->lineEdit_loanRate->text().toDouble() / 12 / 100;
    int months = ui->comboBox_ajns->currentText().toInt() * 12;

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
        res_dialog->setValue(false, (long long)MIP, (long long)loanMoney, interest, refundMoney, months);
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
        res_dialog->setValue(false, (long long)firstMonthPay, (long long)decrease, (long long)loanMoney,
                             interest, (long long)refundMoney, months);
        res_dialog->show();
    }
}
