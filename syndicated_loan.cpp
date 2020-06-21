#include "syndicated_loan.h"
#include "ui_syndicated_loan.h"
#include "samplewidget.h"
#include "result_samecapital.h"
#include "result_samecapitalplusinterest.h"

Syndicated_loan::Syndicated_loan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Syndicated_loan)
{
    ui->setupUi(this);

    //还款方式：默认为等额本息
    refundType = 0;

    //正则表达式限制输入
    ui->lineEdit_busynessLoanMoney->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,5}\\.[0-9]{0,2}"), this));
    ui->lineEdit_businessRate->setValidator(new QRegExpValidator(QRegExp("[1-9]{0,1}[0-9]\\.[0-9]{0,2}"), this));

    ui->lineEdit_providentFundLoanMoney->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{0,5}\\.[0-9]{0,2}"), this));
    ui->lineEdit_providentFundRate->setValidator(new QRegExpValidator(QRegExp("[1-9]{0,1}[0-9]\\.[0-9]{0,2}"), this));
}

Syndicated_loan::~Syndicated_loan()
{
    delete ui;
}

void Syndicated_loan::on_text_changed(){
    bool flag1 = !(ui->lineEdit_busynessLoanMoney->text().isEmpty());
    bool flag2 = !(ui->lineEdit_businessRate->text().isEmpty());
    bool flag3 =!(ui->lineEdit_providentFundLoanMoney->text().isEmpty());
    bool flag4 = !(ui->lineEdit_providentFundRate->text().isEmpty());

    //如果两个lineEdit均有输入，激活按钮
    if(flag1 && flag2 && flag3 && flag4){
        ui->pushButton_start->setEnabled(true);
    }
    //否则禁用按钮
    else{
        ui->pushButton_start->setEnabled(false);
    }
}

void Syndicated_loan::on_pushButton_clear_clicked()
{
    //清空输入
    ui->lineEdit_busynessLoanMoney->clear();
    ui->lineEdit_businessRate->clear();
    ui->lineEdit_providentFundLoanMoney->clear();
    ui->lineEdit_providentFundRate->clear();

    //按揭年数设为初始值
    ui->comboBox_ajns->setCurrentIndex(0);

    //设置为等额本息
    ui->radioButton_sameCapitalPlusInterest->setChecked(true);
    refundType = 0;
}

void Syndicated_loan::on_radioButton_sameCapitalPlusInterest_clicked()
{
    refundType = 0;
}

void Syndicated_loan::on_radioButton_sameCapital_clicked()
{
    refundType = 1;
}

void Syndicated_loan::on_pushButton_start_clicked()
{
    long double businessLoanMoney = ui->lineEdit_busynessLoanMoney->text().toDouble() * 10000;
    //转换成月利率
    double businessRate = ui->lineEdit_businessRate->text().toDouble() / 12 / 100;

    long double PFLMoney = ui->lineEdit_providentFundLoanMoney->text().toDouble() * 10000;
    //转换成月利率
    double PFRate = ui->lineEdit_providentFundRate->text().toDouble() / 12 / 100;

    int months = ui->comboBox_ajns->currentText().toInt() * 12;

    long long loanMoney = businessLoanMoney + PFLMoney + 0.5;//+0.5便于四舍五入

    //如果计算方式为等额本息
    if(refundType == 0){
        //每月还款额
        long double MIP1, MIP2, MIP;
        //利息
        long long interest1, interest2, interest;
        //还款总额
        long long refundMoney1, refundMoney2, refundMoney;

        //分别计算商业贷款和公积金贷款两部分
        SampleWidget::calculate_sameCapitalPlusInterest(businessLoanMoney, businessRate, months,
                                                        MIP1, interest1, refundMoney1);
        SampleWidget::calculate_sameCapitalPlusInterest(PFLMoney, PFRate, months,
                                                        MIP2, interest2, refundMoney2);

        //将两部分结果相加
        MIP = MIP1 + MIP2 + 0.5;//+0.5便于四舍五入
        interest = interest1 + interest2;
        refundMoney = refundMoney1 + refundMoney2;

        Result_SameCapitalPlusInterest* res_dialog = new Result_SameCapitalPlusInterest();
        //将计算结果传入
        res_dialog->setValue(false, (long long)MIP, loanMoney, interest, refundMoney, months);
        res_dialog->show();
    }
    //如果计算方式为等额本金
    else if(refundType == 1){
        //首月月供
        long double firstMonthPay1, firstMonthPay2, firstMonthPay;
        //每月递减
        long double decrease1, decrease2, decrease;
        //利息
        long long interest1, interest2, interest;
        //还款总额
        long double refundMoney1, refundMoney2, refundMoney;

        //分别计算商业贷款和公积金贷款两部分
        SampleWidget::calculate_sameCapital(businessLoanMoney, businessRate, months,
                                            firstMonthPay1, decrease1, interest1, refundMoney1);
        SampleWidget::calculate_sameCapital(PFLMoney, PFRate, months,
                                            firstMonthPay2, decrease2, interest2, refundMoney2);
        //将两部分结果相加
        firstMonthPay = firstMonthPay1 + firstMonthPay2 + 0.5;//+0.5便于四舍五入
        decrease = decrease1 + decrease2 + 0.5;//+0.5便于四舍五入
        interest = interest1 + interest2;
        refundMoney = refundMoney1 + refundMoney2 + 0.5;//+0.5便于四舍五入

        Result_sameCapital* res_dialog = new Result_sameCapital();
        //将计算结果传入
        res_dialog->setValue(false, (long long)firstMonthPay, (long long)decrease, loanMoney,
                             interest, (long long)refundMoney, months);
        res_dialog->show();
    }
}
