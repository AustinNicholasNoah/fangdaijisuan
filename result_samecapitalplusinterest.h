#ifndef RESULT_SAMECAPITALPLUSINTEREST_H
#define RESULT_SAMECAPITALPLUSINTEREST_H

#include <QDialog>

namespace Ui {
class Result_SameCapitalPlusInterest;
}

class Result_SameCapitalPlusInterest : public QDialog
{
    Q_OBJECT

public:
    explicit Result_SameCapitalPlusInterest(QWidget *parent = nullptr);
    ~Result_SameCapitalPlusInterest();

    /**
     * @brief
     * 传值函数，将计算结果传入改对象
     * @param hasFirstPay
     * @param MIP
     * @param loanTotalMoney
     * @param interset
     * @param refundMoney
     * @param months
     * @param firstPay
     */
    void setValue(bool hasFirstPay, long long MIP, long long loanTotalMoney,
                  long long interset, long long refundMoney, int months, long long firstPay = 0);

private:
    Ui::Result_SameCapitalPlusInterest *ui;
};

#endif // RESULT_SAMECAPITALPLUSINTEREST_H
