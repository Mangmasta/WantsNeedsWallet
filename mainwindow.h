#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "backend.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    balanceObject implementationBalance;

    expenseObject implementationWant;
    vector<expenseObject> wantVector;

    expenseObject implementationNeed;
    vector<expenseObject> needVector;

    goalObject implementationGoal;
    vector<goalObject> goalVector;

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    //void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void on_addGoal_clicked();

    void on_addFundsGoal_clicked();

    void on_deleteGoalButton_clicked();

    void on_addWant_clicked();

    void on_deleteWant_clicked();

    void on_deleteNeeds_clicked();

    void on_addNeeds_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_wantsList_currentRowChanged(int currentRow);

    void on_needsList_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
