#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;

    static const int daysInMonth[];

public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        Normalize();
    }

    Date(int daysFromEpoch) {
        year = 1;
        month = 1;
        day = daysFromEpoch;
        Normalize();
    }

    void Normalize() {
        while (month < 1) {
            year--;
            month += 12;
        }

        while (month > 12) {
            year++;
            month -= 12;
        }

        int maxDaysInMonth = daysInMonth[month - 1];
        if (month == 2 && IsLeapYear())
            maxDaysInMonth++;

        while (day < 1) {
            month--;
            if (month < 1) {
                year--;
                month = 12;
            }
            maxDaysInMonth = daysInMonth[month - 1];
            if (month == 2 && IsLeapYear())
                maxDaysInMonth++;

            day += maxDaysInMonth;
        }

        while (day > maxDaysInMonth) {
            day -= maxDaysInMonth;
            month++;
            if (month > 12) {
                year++;
                month = 1;
            }
            maxDaysInMonth = daysInMonth[month - 1];
            if (month == 2 && IsLeapYear())
                maxDaysInMonth++;
        }
    }

    bool IsLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    Date& operator+=(int days) {
        day += days;
        Normalize();
        return *this;
    }

    Date operator+(int days) const {
        Date result = *this;
        result += days;
        return result;
    }

    Date operator-(int days) const {
        return *this + (-days);
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.year << '-' << date.month << '-' << date.day;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date) {
        is >> date.year >> date.month >> date.day;
        date.Normalize();
        return is;
    }
};

const int Date::daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    Date date1(2023, 11, 20);
    Date date2(738395);
    std::cout << "Date from epoch: " << date2 << std::endl;

    int daysToAdd = 5;
    Date date1AfterAdd = date1 + daysToAdd;
    std::cout << "Date 1 after + " << daysToAdd << " days: " << date1AfterAdd << std::endl;

    int daysToSubtract = 3;
    Date date1AfterSubtract = date1 - daysToSubtract;
    std::cout << "Date 1 after - " << daysToSubtract << " days: " << date1AfterSubtract << std::endl;

    return 0;
}
