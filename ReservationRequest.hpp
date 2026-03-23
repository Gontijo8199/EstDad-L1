#ifndef ReservationRequest_hpp
#define ReservationRequest_hpp

#include<iostream>

using namespace std;

class ReservationRequest {

private:
    string course_name;
    string weekday;
    int start_hour;
    int end_hour;
    int student_count;

public:

    ReservationRequest(string course_name, string weekday, int start_hour, int end_hour, int student_count);
    ~ReservationRequest();

    int getStartHour();
    int getEndHour();
    string getCourseName();
    string getWeekday();
    int getStudentCount();
};

#endif