
#ifndef HOSPITAL_CPP
#define HOSPITAL_CPP
#include <iostream>
#include "patient.cpp"
#include "doctor.cpp"
#include "appointment.cpp"



using namespace std;

class Hospital
{
    private:
    vector<Patient>patients;
    vector<Doctor>doctors;
    vector<Appointment>appointments;
    public:
    void addPatient(Patient p)
    {
        patients.push_back(p);

    }
    void addDoctor(Doctor d)
    {
        doctors.push_back(d);
    }
    void addAppointment(Appointment a)
    {
        appointments.push_back(a);
    }
    void displayPatients()
    {
        cout<<"Patients List:"<<endl;
        for(int i=0;i<patients.size();i++)
        {
            patients[i].display();
            cout<<endl;
        }
    }
     void displayDoctors()
     {
        cout<<"Doctors List:"<<endl;
        for(int i=0;i<doctors.size();i++)
        {
            doctors[i].display();
            cout<<endl;
        }
     }
        void displayAppointments()
        {
            cout<<"Appointments List:"<<endl;
            for(int i=0;i<appointments.size();i++)
            {
                appointments[i].displayAppointment();
                cout<<endl;
            }
        }





};

#endif // HOSPITAL_CPP