#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <string>
#include <vector>
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>

using namespace std;

class balanceObject
{
public:
    float income;

    balanceObject();

    void addIncome(float amt);

    void removeIncome(float amt);

    float displayIncome();
};

class expenseObject
{
public:
    float price;
    string catagory;
    string date;
    string name;

    expenseObject(float priceI, string catagoryI, string dateI);

    expenseObject();

    bool isNewer(expenseObject &compare, expenseObject &newN); //is new more recent

    void sortVector(vector<expenseObject> &theVector);

    //subtract from balance
    void addExpense(expenseObject &obj, vector<expenseObject> &theVector, balanceObject& balanceObj, string name, float price, string category);

    //add back to balance
    void deleteExpense(vector<expenseObject> &theVector, int location, balanceObject& balanceObj);

    void displayExpense(expenseObject &obj, vector<expenseObject> &theVector);

};

class goalObject
{
public:
    int priority;
    float cost, allocatedSofar;
    string name, dateHappen;

    goalObject();

    void fixPriority(vector<goalObject> &theVector);

    void addGoal(goalObject &obj, vector<goalObject> &theVector, string name, float cost, int priority);
    void displayGoal(goalObject &obj, vector<goalObject> &theVector);

    //add back to balance
    void deleteGoal(vector<goalObject> &theVector, int location, balanceObject& balanceObj);

    //remove from balance
    void addFunds(vector<goalObject> &theVector, int location, float moneyAdd, balanceObject& balanceObj);

};


void updateListG(QListWidget* ltu, vector<goalObject> &ts);

void updateListE(QListWidget* ltu, vector<expenseObject> &ts);

void updateDetailsNeedWant(expenseObject &ts, QLabel *name, QLabel *price, QLabel *category);

void updateDetailsGoals(goalObject &gs, QLabel *name, QLabel *price, QLabel *funds);

#endif // BACKEND_H
