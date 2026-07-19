

#include <iostream>
using namespace std;

class Appointment
{
    private:
    string patientName;
    string doctorName;
    string appointmentDate;
    public:
    Appointment(string patientName, string doctorName, string appointmentDate)
    {
        
        this->patientName = patientName;
        this->doctorName = doctorName;
        this->appointmentDate = appointmentDate;
    }
    void displayAppointment()
    {
        cout << "Patient Name: " << patientName << endl;
        cout << "Doctor Name: " << doctorName << endl;
        cout << "Appointment Date: " << appointmentDate << endl;
    }

};
