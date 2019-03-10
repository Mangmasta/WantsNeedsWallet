#include "backend.h"
using namespace std;


balanceObject::balanceObject()
{
    income = 0.0;
}

void balanceObject::addIncome(float amt)
{
    income += amt;
}

void balanceObject::removeIncome(float amt)
{

    income = income - amt;

}

float balanceObject::displayIncome()
{
    return  income;
}

expenseObject::expenseObject(float priceI, string catagoryI, string dateI)
    {
        price = priceI;
        catagory = catagoryI;
        date = dateI;
    }

    expenseObject::expenseObject()
    {
    }

    bool expenseObject::isNewer(expenseObject &compare, expenseObject &newN) //is new more recent
    {
        int dateArrayC[3];
        dateArrayC[0] = stoi(compare.date.substr(0, 2));
        dateArrayC[1] = stoi(compare.date.substr(3, 2));
        dateArrayC[2] = stoi(compare.date.substr(6, 4));

        int dateArrayN[3];
        dateArrayN[0] = stoi(newN.date.substr(0, 2)); //month
        dateArrayN[1] = stoi(newN.date.substr(3, 2)); //day
        dateArrayN[2] = stoi(newN.date.substr(6, 4)); //year

        //cout << dateArrayC[0] << " " << dateArrayC[1] << " " << dateArrayC[2] << endl;
        //cout << dateArrayN[0] << " " << dateArrayN[1] << " " << dateArrayN[2] << endl;

        if (dateArrayN[2] > dateArrayC[2]) //if new node year is newer than Compare node year
        {
            //cout << "True" << endl;
            return true;
        }
        else if (dateArrayN[0] > dateArrayC[0]) //if new node month is newer than Compare node month
        {
            //cout << "True" << endl;
            return true;
        }
        else if (dateArrayN[1] > dateArrayC[1]) //if new node day is newer than Compare node day
        {
            //cout << "True" << endl;
            return true;
        }
        else
        {
            //cout << "False" << endl;
            return false;
        }
    }


    void expenseObject::sortVector(vector<expenseObject> &theVector)
    {
        for(int i = 0; i < theVector.size()-1; i++)
        {
            for (int j = i+1; j < theVector.size(); j++)
            {
                if (isNewer(theVector[i], theVector[j])) //if j is more recent than i
                {
                    if (isNewer(theVector[i], theVector[j]))
                    {
                        cout << theVector[j].date << " is more recent than " << theVector[i].date << endl;
                    }
                    expenseObject temp = theVector[i];
                    cout << endl << endl << endl << "Here is date vector i: " << temp.date << endl;
                    cout << "Here is date vector j: " << theVector[j].date << endl;
                    theVector[i] = theVector[j];
                    theVector[j] = temp;
                }
            }
        }
    }

    //subtract from balance
    void expenseObject::addExpense(expenseObject &obj, vector<expenseObject> &theVector, balanceObject& balanceObj, string name, float price, string category)
    {
        /*
        cout << "Enter price: ";
        cin >> price;
        cin.ignore(20, '\n');
        cout << "Enter catagory: ";
        getline(cin, catagory);
        cout << "Enter date: ";
        getline(cin, date);
        */
        obj.name = name;
        obj.price = price;
        obj.catagory = catagory;
        obj.date = "01/01/01";

        //cout << price << " ";
        //cout << catagory << " ";
        //cout << date << " " << endl;

        if (theVector.empty())
        {
            //cout << "it is empty" << endl;
            theVector.push_back(obj);
        }
        else
        {
            theVector.push_back(obj);
            sortVector(theVector);
        }
        balanceObj.removeIncome(price);
    }

    //add back to balance
    void expenseObject::deleteExpense(vector<expenseObject> &theVector, int location, balanceObject& balanceObj)
    {
        vector<expenseObject>::iterator t = theVector.begin() + location;
        balanceObj.addIncome(theVector[location-1].price);
        theVector.erase(t);
    }

    void expenseObject::displayExpense(expenseObject &obj, vector<expenseObject> &theVector)
    {
        for (int i = 0; i < theVector.size(); i++)
        {
            cout << theVector[i].price << endl;
            cout << theVector[i].catagory << endl;
            cout << theVector[i].date << endl;
        }
    }

    goalObject::goalObject()
        {
            allocatedSofar = 0;
        }

        void goalObject::fixPriority(vector<goalObject> &theVector)
        {
            for (int j = 0; j < theVector.size(); j++) //change priority of all vectors to that which its index is plus one, don't want to start at 0 priority
            {
                theVector[j].priority = j+1;
            }
        }

        void goalObject::addGoal(goalObject &obj, vector<goalObject> &theVector, string name, float cost, int priority)
        {


            obj.name = name;
            obj.cost = cost;
            //obj.dateHappen = dateHappen;
            obj.priority = priority;


            if (theVector.empty())
            {
                //cout << "it is empty" << endl;
                obj.priority = 1;
                theVector.push_back(obj);
            }
            else
            {
                //cout << "it is not empty" << endl;
                //cout << theVector.size() << endl;
                bool alreadyAdded = false;

                int origSize = theVector.size();
                for (int i = 0; i < origSize; i++)
                {
                    if (theVector[i].priority == obj.priority) // if new object has same priority
                    {
                        theVector.insert(theVector.begin() + i, obj); //add it to where its priority is
                        alreadyAdded = true;
                        i++;
                    }
                }
                fixPriority(theVector); //change the priorities

                if (alreadyAdded == false)
                {
                    theVector.push_back(obj);
                    obj.priority = theVector.size();
                }

            }
        }

        void goalObject::displayGoal(goalObject &obj, vector<goalObject> &theVector)
        {
            for (int i = 0; i < theVector.size(); i++)
            {
                cout << theVector[i].name << endl;
                cout << theVector[i].dateHappen << endl;
                cout << theVector[i].cost << endl;
                cout << theVector[i].allocatedSofar << endl;
            }
        }

        //add back to balance
        void goalObject::deleteGoal(vector<goalObject> &theVector, int location, balanceObject& balanceObj)
        {
            vector<goalObject>::iterator t = theVector.begin() + location;
            balanceObj.addIncome(theVector[location-1].allocatedSofar);
            theVector.erase(t);
            fixPriority(theVector);
        }

        //remove from balance
        void goalObject::addFunds(vector<goalObject> &theVector, int location, float moneyAdd, balanceObject& balanceObj)
        {
            balanceObj.removeIncome(moneyAdd);
            theVector[location - 1].allocatedSofar = theVector[location - 1].allocatedSofar + moneyAdd;
        }



//#########################################
void updateListG(QListWidget* ltu, vector<goalObject> &ts)
{
    ltu->clear();
    for ( auto i = ts.begin(); i != ts.end(); i++ ) {
        ltu->addItem((*i).name.c_str());
    }
    return;
}

void updateListE(QListWidget* ltu, vector<expenseObject> &ts)
{
    ltu->clear();
    for ( auto i = ts.begin(); i != ts.end(); i++ ) {
        ltu->addItem((*i).name.c_str());
    }
    return;
}

void updateDetailsNeedWant(expenseObject &ts, QLabel *name, QLabel *price, QLabel *category)
{
 name->setText(ts.name.c_str());
 price->setText(string("$").append(to_string(ts.price)).c_str());
 //category->setText(ts.catagory.c_str());
}

void updateDetailsGoals(goalObject &gs, QLabel *name, QLabel *price, QLabel *funds)
{
    float ctp = gs.cost;
        float atp = gs.allocatedSofar;
name->setText(gs.name.c_str());
price->setText(string("$").append(to_string(ctp)).c_str());
funds->setText(to_string(atp).c_str());
}
/*

int main()
{
    balanceObject implementationBalance;

    expenseObject implementationWant;
    vector<expenseObject> wantVector;

    expenseObject implementationAdd;
    vector<expenseObject> addVector;

    goalObject implementationGoal;
    vector<goalObject> goalVector;

    float whatever;

    cout << "Enter income: ";
    cin >> whatever;
    implementationBalance.addIncome(whatever);
    implementationWant.addExpense(implementationWant, wantVector, implementationBalance);
    implementationWant.displayExpense(implementationWant, wantVector);
    //implementationGoal.addGoal(implementationGoal, goalVector);
    //implementationGoal.displayGoal(implementationGoal, goalVector);
    implementationBalance.displayIncome();

    implementationGoal.addGoal(implementationGoal, goalVector);
    implementationGoal.addGoal(implementationGoal, goalVector);
    implementationGoal.addGoal(implementationGoal, goalVector);
    //implementationGoal.displayGoal(implementationGoal, goalVector);
    //implementationGoal.displayGoal(implementationGoal, goalVector);
    implementationGoal.addFunds(goalVector, 1, 50.0, implementationBalance);
    implementationBalance.displayIncome();
    //implementationGoal.displayGoal(implementationGoal, goalVector);
    implementationGoal.deleteGoal(goalVector, 1, implementationBalance);
    implementationBalance.displayIncome();




    system("pause");
    return 0;
}*/
