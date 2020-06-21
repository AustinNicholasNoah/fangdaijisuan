#ifndef CALCU_SINGLE_H
#define CALCU_SINGLE_H

#include <QWidget>

namespace Ui {
class Calcu_single;
}

class Calcu_single : public QWidget
{
    Q_OBJECT

public:
    explicit Calcu_single(int loanType, QWidget *parent = nullptr);
    ~Calcu_single();

private slots:
    /**
     * @brief
     * 清空所有输入
     */
    void on_pushButton_clear_clicked();

    /**
     * @brief
     * 当输入发生改变时，检测是否所有lineEdit都有输入，有则激活按钮
     */
    void on_text_changed();

    void on_pushButton_start_clicked();

    /**
     * @brief
     * 还款方式：等额本息被选中时触发
     */
    void on_radioButton_sameCapitalPlusInterest_clicked();

    /**
     * @brief
     * 还款方式：等额本金被选中时触发
     */
    void on_radioButton_sameCapital_clicked();

private:
    Ui::Calcu_single *ui;

    /**
     * @brief
     * 还款方式， 0：等额本息， 1：等额本金
     */
    int refundType;
};

#endif // CALCU_SINGLE_H
