#include "samplewidget.h"
#include "ui_samplewidget.h"

SampleWidget::SampleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SampleWidget)
{
    ui->setupUi(this);

    //贷款类别默认为商业贷款
    loanType = 0;
}

SampleWidget::~SampleWidget()
{
    delete ui;
}


void SampleWidget::on_combobox_loanType_currentIndexChanged(int index)
{
    loanType = index;

    //注意：当贷款类别为组合贷款时，计算方式只能为按贷款总额计算
    if(loanType == 2){
        calcuType = 1;

        ui->checkBox_calcu_total->setChecked(true);
        ui->checkBox_calcu_single->setChecked(false);

        ui->pushButton_enter->setEnabled(true);

        //使用户无法修改
        ui->checkBox_calcu_total->setEnabled(false);
        ui->checkBox_calcu_single->setEnabled(false);
    }
    else{
        ui->checkBox_calcu_total->setEnabled(true);
        ui->checkBox_calcu_single->setEnabled(true);
    }
}

void SampleWidget::on_checkBox_calcu_single_clicked()
{
    //如果按房屋面积、单价计算被勾选，激活按钮，并将另一个checkBox取消勾选
    if(ui->checkBox_calcu_single->isChecked()){
        calcuType = 0;
        ui->checkBox_calcu_total->setChecked(false);
        ui->pushButton_enter->setEnabled(true);
    }
    //如果被取消勾选，则禁用按钮
    else{
        ui->pushButton_enter->setEnabled(false);
    }
}

void SampleWidget::on_checkBox_calcu_total_clicked()
{
    //如果被勾选，激活按钮，并将另一个checkBox取消勾选
    if(ui->checkBox_calcu_total->isChecked()){
        calcuType = 1;
        ui->checkBox_calcu_single->setChecked(false);
        ui->pushButton_enter->setEnabled(true);
    }
    else{
        ui->pushButton_enter->setEnabled(false);
    }
}

void SampleWidget::on_pushButton_enter_clicked()
{
    //商业贷款
    if(loanType == 0){
        //按房屋面积、单价计算
        if(calcuType == 0){
            business_single->show();
        }
        //按贷款总额计算
        else if(calcuType == 1){
            business_total->show();
        }
    }
    //公积金贷款
    else if(loanType == 1){
        //按房屋面积、单价计算
        if(calcuType == 0){
            providentFund_single->show();
        }
        //按贷款总额计算
        else if(calcuType == 1){
            providentfund_total->show();
        }
    }
    //组合贷款
    else if(loanType == 2){
        syndicated_loan->show();
    }
}

void SampleWidget::calculate_sameCapitalPlusInterest(long double loanMoney, double rate, int months,
                                                     long double &MIP,long long &interest, long long &refundMoney){
    //每月月供额=〔贷款本金×月利率×(1+月利率)^还款月数〕÷〔(1+月利率)^还款月数-1〕
    MIP = (loanMoney * rate * powl((1 + rate), months) / (powl((1 + rate), months) - 1));

    //还款总额=每月月供额x还款月数
    refundMoney = MIP * months;

    //总利息=还款总额-贷款本金
    interest = MIP * months + 0.5 - loanMoney;

    //+0.5便于向下取整四舍五入
    MIP += 0.5;
    refundMoney += 0.5;
    interest += 0.5;
}

void SampleWidget::calculate_sameCapital(long double loanMoney, double rate, int months,
                                         long double &firstMonthPay, long double &decrease, long long &interest, long double &refundMoney){
    //首月月供额=(贷款本金÷还款月数)+贷款本金×月利率
    firstMonthPay = (loanMoney / months) + loanMoney * rate;
    //每月月供递减额=每月应还本金×月利率=贷款本金÷还款月数×月利率
    decrease = loanMoney / months * rate;

    //当前月份月供
    long double curMonthPay = firstMonthPay;
    refundMoney = 0;
    for(int i = 1; i<= months; ++i){
        //让还款总额逐一加上每月月供
        refundMoney += curMonthPay;
        curMonthPay -= decrease;
    }
    //利息为还款总额减去贷款本金
    interest = refundMoney - loanMoney;

    //+0.5便于四舍五入
    firstMonthPay += 0.5;
    decrease += 0.5;
    refundMoney += 0.5;
    interest += 0.5;
}
