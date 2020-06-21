#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>
#include "calcu_single.h"
#include "calcu_total.h"
#include "syndicated_loan.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SampleWidget; }
QT_END_NAMESPACE

class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    SampleWidget(QWidget *parent = nullptr);
    ~SampleWidget();

    /**
     * @brief
     * 静态函数，用于计算等额本息
     * @param 贷款总额
     * @param 利率
     * @param 还款月数
     * @param 月供
     * @param 利息
     * @param 还款总额
     */
    static void calculate_sameCapitalPlusInterest(long double loanMoney, double rate, int months,
                                                  long double &MIP,long long &interest, long long &refundMoney);

    /**
     * @brief
     * 静态函数，用于计算等额本金
     * @param 贷款总额
     * @param 利率
     * @param 还款月数
     * @param 每月递减
     * @param 利息
     * @param 还款总额
     */
    static void calculate_sameCapital(long double loanMoney, double rate, int months,
                                      long double &firstMonthPay, long double &decrease, long long &interest, long double &refundMoney);

    /**
     * @brief
     * 静态函数，用于计算等额本金
     */
    static void calculate_sameCapital();

private slots:
    /**
     * @brief
     * 当贷款类别改变时触发
     * @param index
     */
    void on_combobox_loanType_currentIndexChanged(int index);

    /**
     * @brief
     * 当按房屋面积、单价计算checkBox被点击时触发
     */
    void on_checkBox_calcu_single_clicked();

    /**
     * @brief
     * 当按贷款总额计算checkBox被点击时触发
     */
    void on_checkBox_calcu_total_clicked();

    /**
     * @brief
     * 当确认按钮被点击时触发
     */
    void on_pushButton_enter_clicked();

private:
    Ui::SampleWidget *ui;

    /**
     * 贷款类别， 0：商业贷款， 1：公积金贷款， 2：组合贷款
     */
    int loanType;

    /**
     * 计算方式， 0：按房屋面积、单价计算， 1：按贷款总额计算
     */
    int calcuType;

    /**
     * 商业贷款-按房屋面积、单价计算 窗口对象
     */
    Calcu_single* business_single = new Calcu_single(0);

    /**
     * 商业贷款-按贷款总额计算 窗口对象
     */
    Calcu_total* business_total = new Calcu_total(0);

    /**
     * 公积金贷款-按房屋面积、单价计算 窗口对象
     */
    Calcu_single* providentFund_single = new Calcu_single(1);

    /**
     * 公积金贷款-按贷款总额计算 窗口对象
     */
    Calcu_total* providentfund_total = new Calcu_total(1);

    /**
     * 组合贷款 窗口对象
     */
    Syndicated_loan* syndicated_loan = new Syndicated_loan();
};
#endif // SAMPLEWIDGET_H
