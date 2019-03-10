#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_9_clicked() //goals
{
    ui->stackedWidget->setCurrentIndex(1);
    updateListG(ui->listWidget, goalVector);
    //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayGoals().") );
}
void MainWindow::on_pushButton_10_clicked() //balance button
{
    ui->stackedWidget->setCurrentIndex(2);
    float test = implementationBalance.displayIncome();
    ui->balance->setText(string("$").append(to_string(test)).c_str());
    ui->pushButton_10->setText(string("$").append(to_string(test)).c_str());
}
void MainWindow::on_pushButton_11_clicked() //wants button
{

    //updateDetailsNeedWant("test",ui->wantName,ui->wantsPrice,ui->wantCategory);
    updateListE(ui->wantsList, wantVector);
    ui->stackedWidget->setCurrentIndex(3);
    //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayWants() and populate table.") );
}
void MainWindow::on_pushButton_12_clicked() //needs button
{
    ui->stackedWidget->setCurrentIndex(4);
    updateListE(ui->needsList, needVector);
    //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayNeeds() and populate table.") );
}


void MainWindow::on_pushButton_13_clicked() //back button on goals
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_14_clicked() //back button on balance
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_15_clicked() //back button on wants
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_16_clicked() //back button on needs
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_clicked()//add balance button
{
    bool ok;
    double bta = QInputDialog::getDouble(this, tr("QInputDialog::getText()"), tr("Input Balance to Add:"), 0.0, 0.0,2147483647, 2, &ok);

    if (ok)
    {
        implementationBalance.addIncome((float)bta);
        ui->balance->setText(string("$").append(to_string(implementationBalance.displayIncome())).c_str());
        //QMessageBox::information(this, tr("Unimplimented Function"), tr("run addIncome(") + text + tr(").") );
        //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayBalance() and update display.") );
    }

}

void MainWindow::on_addGoal_clicked()
{
    bool ok;
    QString gName = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Goal Name:"), QLineEdit::Normal, tr(""), &ok);
    if(ok && !gName.isEmpty())
    {
        bool ok2 = false;
        double total = QInputDialog::getDouble(this, tr("QInputDialog::getText()"), tr("Total Cost:"), 0.0, 0.0,2147483647, 2, &ok2);
        if(ok2)
        {
            bool ok3 = false;
            int priority = QInputDialog::getInt(this, tr("Input Priority"), tr("Input Priority as a number:"),1, 1, 200, 1, &ok3);
            if(ok3)
            {

                implementationGoal.addGoal(implementationGoal, goalVector, gName.toUtf8().constData(), total, priority);
                updateListG(ui->listWidget, goalVector);
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run addGoal(") + gName + tr(",") + QString::number(total) +  tr(",") + QString::number(priority) + tr(")"));
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayGoals().") );
            }

        }
    }
}

void MainWindow::on_addFundsGoal_clicked()
{
    bool ok;
    double funds = QInputDialog::getDouble(this, tr("Input Funds"), tr("Input Funds to add:"), 0.0, 0.0, 2147483647, 2, &ok);
    if(ok)
    {
       implementationGoal.addFunds(goalVector,(ui->listWidget->currentIndex().row())+1,funds, implementationBalance);
        //QMessageBox::information(this, tr("Unimplimented Function"), tr("run addFunds(") + QString::number(ui->listWidget->currentIndex().row()) + tr(",") + QString::number(funds) + tr(")") );
    }
}

void MainWindow::on_deleteGoalButton_clicked()
{
    QMessageBox::information(this, tr("Unimplimented Function"), tr("run deleteGoal(") + QString::number(ui->listWidget->currentIndex().row()) + tr(")") );
}

void MainWindow::on_addWant_clicked()
{
    bool ok;
    QString wName = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Want name:"), QLineEdit::Normal, tr(""), &ok);
    if(ok && !wName.isEmpty())
    {
        bool ok2 = false;
        double total = QInputDialog::getDouble(this, tr("QInputDialog::getText()"), tr("Total Cost:"), 0.0, 0.0,2147483647, 2, &ok2);
        if(ok2)
        {
            bool ok3 = false;
            QString Category = QInputDialog::getText(this, tr("Input Category"), tr("Input Category:"),QLineEdit::Normal, tr(""), &ok3);
            if(ok3)
            {
                implementationWant.addExpense(implementationWant,wantVector,implementationBalance, wName.toUtf8().constData(), total, Category.toUtf8().constData());
                updateListE(ui->wantsList, wantVector);
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run addWant(") + QString::number(total) + tr(",") + wName + tr(",") + Category + tr(")"));
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayWants().") );
            }

        }
    }
}

void MainWindow::on_deleteWant_clicked()
{
    QMessageBox::information(this, tr("Unimplimented Function"), tr("run deleteWant(") + QString::number(ui->wantsList->currentIndex().row()) + tr(")") );
}

void MainWindow::on_deleteNeeds_clicked()
{
    QMessageBox::information(this, tr("Unimplimented Function"), tr("run deleteNeed(") + QString::number(ui->needsList->currentIndex().row()) + tr(")") );
}

void MainWindow::on_addNeeds_clicked()
{
    bool ok;
    QString nName = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Need Name:"), QLineEdit::Normal, tr(""), &ok);
    if(ok && !nName.isEmpty())
    {
        bool ok2 = false;
        double total = QInputDialog::getDouble(this, tr("QInputDialog::getText()"), tr("Total Cost:"), 0.0, 0.0,2147483647, 2, &ok2);
        if(ok2)
        {
            bool ok3 = false;
            QString Category = QInputDialog::getText(this, tr("Input Category"), tr("Input Category:"),QLineEdit::Normal, tr(""), &ok3);
            if(ok3)
            {
                implementationNeed.addExpense(implementationNeed,needVector,implementationBalance, nName.toUtf8().constData(), total, Category.toUtf8().constData());
                updateListE(ui->needsList, needVector);
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run addNeed(") + QString::number(total) + tr(",") + nName + tr(",") + Category + tr(")"));
                //QMessageBox::information(this, tr("Unimplimented Function"), tr("run displayNeeds().") );
            }

        }
    }
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    updateDetailsGoals(*(goalVector.begin()+currentRow), ui->goalName, ui->goalPrice, ui->goalFunds);
}

void MainWindow::on_wantsList_currentRowChanged(int currentRow)
{
    updateDetailsNeedWant(*(wantVector.begin()+currentRow), ui->wantName, ui->wantsPrice, ui->wantCategory);
}

void MainWindow::on_needsList_currentRowChanged(int currentRow)
{
    updateDetailsNeedWant(*(needVector.begin()+currentRow), ui->needsName, ui->needsPrice, ui->needCategory);
}
