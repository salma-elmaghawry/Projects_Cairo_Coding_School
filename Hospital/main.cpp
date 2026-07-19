
#include<iostream>
#include "appointment.cpp"
#include "hospital.cpp"

using namespace std;

int main() {
    Hospital manager;
    //patients
    manager.addPatient(Patient("John Doe", 1, "Flu"));
    manager.addPatient(Patient("Jane Smith", 2, "Cold"));
//doctors
    manager.addDoctor(Doctor("Dr. Brown", 1, "Cardiology"));
    manager.addDoctor(Doctor("Dr. Green", 2, "Neurology"));
//appointments
    manager.addAppointment(Appointment("John Doe", "Dr. Brown", "2023-10-15"));
    manager.addAppointment(Appointment("Jane Smith", "Dr. Green", "2023-10-16"));

    
      manager.displayDoctors();
      manager.displayPatients();
      manager.displayAppointments();
    return 0;
}