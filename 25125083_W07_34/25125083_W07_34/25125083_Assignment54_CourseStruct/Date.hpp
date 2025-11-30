//
//  Date.hpp
//  Learning
//
//  Created by Huy Nguyen on 25/11/25.
//

#ifndef Date_hpp
#define Date_hpp

#include "String.hpp"

#include <iostream>

struct Date
{
    int day;
    int month;
    int year;
};

String getFormattedDate(const Date& d, String format);
void outputDateWithFormat(std::ostream& os, const Date& d, const String& format);

std::istream& operator >>(std::istream& is, Date& d);
std::ostream& operator <<(std::ostream& os, const Date& d);

void inputDateFromConsole(Date& d);
void outputDateToConsole(const Date& d);

bool inputDateFromFile(Date& d, const String& filename);
bool outputDateToFile(const Date& d, const String& filename);
bool outputDateWithFormatToFile(const Date& d, const String& format, const String& filename);

int compareDate(const Date& d1, const Date& d2);

Date findTomorrow(Date d);
Date findYesterday(Date d);

void increaseDate(Date& d, int k);
void decreaseDate(Date& d, int k);

long long countTotalDaysSince1970(const Date& d);
int distanceToStartOfYear(const Date& d);
long long distanceTo1970(const Date& d);
long long distanceBetweenDates(const Date& d1, const Date& d2);

const String getDayOfWeek(const Date& d);

Date getTodayDate();
Date calculateAge(const Date& dob);

// Helper
bool isLeapYear(int year);
int daysInMonth(int month, int year);

#endif /* Date_hpp */
