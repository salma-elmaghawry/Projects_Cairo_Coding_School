#include<iostream>
#include "person.cpp"

using namespace std;

class Doctor : public Person
{
    private:
    string specialization;
    public:
    Doctor(string name, int id, string specialization) : Person(name, id)
    {
        this->specialization = specialization;
    }
    void display() override
    {
        Person::display();
        cout << "Specialization: " << specialization << endl;
    }
};