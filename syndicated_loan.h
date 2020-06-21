#ifndef SYNDICATED_LOAN_H
#define SYNDICATED_LOAN_H

#include <QWidget>

namespace Ui {
class Syndicated_loan;
}

class Syndicated_loan : public QWidget
{
    Q_OBJECT

public:
    explicit Syndicated_loan(QWidget *parent = nullptr);
    ~Syndicated_loan();

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
    void on_radioButton_sameCapital_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::Syndicated_loan *ui;

    /**
     * @brief
     * 还款方式， 0：等额本息， 1：等额本金
     */
    int refundType;
};

#endif // SYNDICATED_LOAN_H
