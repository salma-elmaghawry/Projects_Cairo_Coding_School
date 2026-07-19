#include <iostream>
using namespace std;

//parent class
class Person
{
    private:
    string  name ;
    int id;
    public:
    Person(string name, int id)
    {
        this->name = name;
        this->id = id;
    }
    virtual void display()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
    string getName()
    {
        return name;
    }
    int getId()
    {
        return id;
    }
    


};
