#ifndef RESULT_SAMECAPITAL_H
#define RESULT_SAMECAPITAL_H

#include <QDialog>

namespace Ui {
class Result_sameCapital;
}

class Result_sameCapital : public QDialog
{
    Q_OBJECT

public:
    explicit Result_sameCapital(QWidget *parent = nullptr);
    ~Result_sameCapital();

    /**
     * @brief
     * 传值函数，将计算结果传入该对象
     * @param hasFirstPay
     * @param firstMonthPay
     * @param decrease
     * @param loanTotalMoney
     * @param interset
     * @param refundMoney
     * @param months
     * @param firstPay
     */
    void setValue(bool hasFirstPay, long long firstMonthPay, long long decrease, long long loanTotalMoney,
                  long long interset, long long refundMoney, int months, long long firstPay = 0);

private:
    Ui::Result_sameCapital *ui;
};

#endif // RESULT_SAMECAPITAL_H
