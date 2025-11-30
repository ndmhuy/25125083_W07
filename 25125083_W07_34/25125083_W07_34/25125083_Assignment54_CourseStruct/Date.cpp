//
//  Date.cpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#include "Date.hpp"

#include <iostream>
#include <fstream>

String getFormattedDate(const Date& d, String format)
{
    const char* monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    char yyyy_str[5];
    char yy_str[3];
    char MM_str[3];
    char M_str[3];
    char dd_str[3];
    char d_str[3];
        
    snprintf(yyyy_str, 5, "%d", d.year);
    snprintf(yy_str, 3, "%02d", d.year % 100);
    snprintf(MM_str, 3, "%02d", d.month);
    snprintf(M_str, 3, "%d", d.month);
    snprintf(dd_str, 3, "%02d", d.day);
    snprintf(d_str, 3, "%d", d.day);
    
    String result = format;
    
    result.replace("yyyy", yyyy_str);
    result.replace("yy", yy_str);
    
    result.replace("MMM", monthNames[d.month - 1]);
    result.replace("MM", MM_str);
    result.replace("M", M_str);
    
    result.replace("dd", dd_str);
    result.replace("d", d_str);
    
    return result;
}

void outputDateWithFormat(std::ostream& os, const Date& d, const String& format)
{
    os << getFormattedDate(d, format);
}

std::istream& operator >>(std::istream& is, Date& d)
{
    char buffer;
    is >> d.day >> buffer >> d.month >> buffer >> d.year;
    is.ignore();
    return is;
}

std::ostream& operator <<(std::ostream& os, const Date& d)
{
    String formatted = getFormattedDate(d, "dd/MM/yyyy");
    os << formatted;
    return os;
}

bool inputDateFromFile(Date& d, const String& filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (!fin) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    // Suppose format: dd/MM/yyyy
    fin >> d;
    fin.close();
    return true;
}

bool outputDateToFile(const Date& d, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    // Format: yyyy-MM-dd
    outputDateWithFormat(fout, d, "yyyy-MM-dd");
    fout.close();
    return true;
}

bool outputDateWithFormatToFile(const Date& d, const String& format, const String& filename)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout) {
        std::cout << "File cannot be opened.\n";
        return false;
    }
    
    outputDateWithFormat(fout, d, format);
    fout.close();
    return true;
}

int compareDate(const Date& d1, const Date& d2)
{
    if (d1.year < d2.year) return -1;
    if (d1.year > d2.year) return 1;
    
    if (d1.month < d2.month) return -1;
    if (d1.month > d2.month) return 1;
    
    if (d1.day < d2.day) return -1;
    if (d1.day > d2.day) return 1;
    
    return 0;
}

Date findTomorrow(Date d)
{
    int maxDays = daysInMonth(d.month, d.year);
    if (d.day < maxDays) ++d.day;
    else {
        d.day = 1;
        if (d.month < 12) ++d.month;
        else {
            d.month = 1;
            ++d.year;
        }
    }
    return d;
}

Date findYesterday(Date d)
{
    if (d.day > 1) --d.day;
    else {
        if (d.month > 1) --d.month;
        else {
            d.month = 12;
            --d.year;
        }
        d.day = daysInMonth(d.month, d.year);
    }
    return d;
}

void increaseDate(Date& d, int k)
{
    for (int i = 0; i < k; ++i)
        d = findTomorrow(d);
}

void decreaseDate(Date& d, int k)
{
    for (int i = 0; i < k; ++i) {
        d = findYesterday(d);
    }
}

long long countTotalDaysSince1970(const Date& d)
{
    long long totalDays = 0LL;
    for (int y = 1970; y < d.year; ++y) {
        totalDays += (isLeapYear(y)) ? 366 : 365;
    }
    
    for (int m = 1; m < d.month; ++m) {
        totalDays += daysInMonth(m, d.year);
    }
    
    totalDays += d.day - 1;
    return totalDays;
}

int distanceToStartOfYear(const Date& d)
{
    int days = 0;
    for (int m = 1; m < d.month; ++m) {
        days += daysInMonth(m, d.year);
    }
    days += d.day - 1;
    return days;
}

long long distanceTo1970(const Date& d)
{
    return countTotalDaysSince1970(d);
}

long long distanceBetweenDates(const Date& d1, const Date& d2)
{
    return abs(countTotalDaysSince1970(d2) - countTotalDaysSince1970(d1));
}

// 1/1/1970 Thursday
const String getDayOfWeek(const Date& d)
{
    const String weekDay[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    long long days = countTotalDaysSince1970(d);
    int offset = (days + 3) % 7;
    return weekDay[offset];
}

Date getTodayDate()
{
    time_t now = time(0);
    tm ltm;
    
#ifdef _WIN32
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif
    
    Date today;
    today.year = 1900 + ltm.tm_year;
    today.month = 1 + ltm.tm_mon;
    today.day = ltm.tm_mday;
    return today;
}

Date calculateAge(const Date& dob)
{
    Date age;
    Date today = getTodayDate();
    
    age.day = today.day - dob.day;
    age.month = today.month - dob.month;
    age.year = today.year - dob.year;
    
    if (age.day < 0) {
        --age.month;
        int prevMonth, prevMonthYear;
        
        if (today.month == 1) {
            prevMonth = 12;
            prevMonthYear = today.year - 1;
        } else {
            prevMonth = today.month - 1;
            prevMonthYear = today.year;
        }
        
        age.day += daysInMonth(prevMonth, prevMonthYear);
    }
    if (age.month < 0) {
        --age.year;
        age.month += 12;
    }
    
    return age;
}

// Helper
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int month, int year)
{
    if (month == 2)
        return (isLeapYear(year)) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else return 31;

}

