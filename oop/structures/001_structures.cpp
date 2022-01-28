#include <cassert>
#include <iostream>


struct Date
{
    int day;
    int month;
    int year;
};

int main()
{
    // declare instance of Date struct
    Date date;

    // initialize the instace memeber
    date.day = 29;
    date.month = 8;
    date.year = 1981;

    assert(date.day == 29);
    assert(date.month == 8);
    assert(date.year == 1981);

    std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
}