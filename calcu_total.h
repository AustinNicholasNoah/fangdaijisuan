#ifndef CALCU_TOTAL_H
#define CALCU_TOTAL_H

#include <QWidget>

namespace Ui {
class Calcu_total;
}

class Calcu_total : public QWidget
{
    Q_OBJECT

public:
    explicit Calcu_total(int loanType, QWidget *parent = nullptr);
    ~Calcu_total();

private slots:
    /**
     * @brief
     * 当输入发生改变时，检测是否所有lineEdit都有输入，有则激活按钮
     */
    void on_text_changed();

    /**
     * @brief
     * 清空重填
     */
    void on_pushButton_clear_clicked();

    /**
     * @brief
     * 还款方式：等额本息被选中时触发
     */
    void on_radioButton_sameCapitalPlusInterest_clicked();

    /**
     * @brief
     * 还款方式：等额本金被选中时触发
     */
    void on_radioButton_radioButton_sameCapital_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::Calcu_total *ui;

    /**
     * @brief
     * 还款方式， 0：等额本息， 1：等额本金
     */
    int refundType;
};

#endif // CALCU_TOTAL_H
