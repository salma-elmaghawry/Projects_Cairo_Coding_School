
#include<iostream>
using namespace std;
#include "person.cpp"

//child class
class Patient : public Person

{
    private:
    string disease;
    public:
    Patient(string name, int id, string disease) : Person(name, id)
    {
        this->disease = disease;
    }
    void display() override
    {
        Person::display();

        cout << "Disease: " << disease << endl;
    }

};
