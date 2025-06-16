#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate {

private:

    short _Day;
    short _Month;
    short _Year;

public:

    // Constructors of this class 

    clsDate() {

        time_t t = time(0);
        tm* now = localtime(&t);

        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string Date) {

        vector<string> vDate;
        vDate = clsString::Split(Date, "/");
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year) {

        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year) {

        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    // Methods of this class

    void SetDay(short Day) {
        _Day = Day;
    }

    short GetDay() {
        return _Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month) {
        _Month = Month;
    }

    short GetMonth() {
        return _Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year) {
        _Year = Year;
    }

    short GetYear() {
        return _Year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    void Print() {

        cout << DateToString() << endl;
    }

    clsDate StringToDate(string DateString) {

        clsDate Date;
        vector<string> vDate;

        vDate = clsString::Split(DateString, "/");
        Date._Day = stoi(vDate[0]);
        Date._Month = stoi(vDate[1]);
        Date._Year = stoi(vDate[2]);

        return Date;
    }

    static string DateToString(clsDate Date) {
        
        return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    string DateToString() {
        
        return DateToString(*this);
    }

    static bool IsLeapYear(short Year) {

        // if year is divisible by 4 AND not divisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        return (Year % 400 == 0) || (Year % 100 != 00 && Year % 4 == 0);
    }

    bool IsLeapYear() {

        return IsLeapYear(_Year);
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year) {

        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true) {

            MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

            if (RemainingDays > MonthDays) {

                RemainingDays -= MonthDays;
                Date._Month++;
            }
            else {

                Date._Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    static short DayOfWeekOrder(short Day, short Month, short Year) {

        short a, m, y;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        // Gregorian:
        //0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    static short DayOfWeekOrder(clsDate Date) {
        
        return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
    }

    static string MonthShortName(short MonthNumber) {

        string arrMonthNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        return arrMonthNames[MonthNumber - 1];
    }

    static string DayShortName(short DayOfWeekOrder) {

        string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrDayNames[DayOfWeekOrder];
    }

    static void PrintMonthCalendar(short Month, short Year) {

        // Index of the day from 0 to 6
        short current = DayOfWeekOrder(1, Month, Year);

        short NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        // Print the current month name
        printf("\n\n__________________%s__________________\n\n", MonthShortName(Month).c_str());

        // Print the columns
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        // Print appropriate spaces
        short i;
        for (i = 0; i < current; i++)
            printf("     ");

        short K = 0;

        for (short j = 1; j <= NumberOfDays; j++) {

            printf("%5d", j);

            if (++i == 7) {

                printf("\n");
                i = 0;
            }
        }
        printf("\n_______________________________________\n\n");
    }

    void PrintMonthCalendar() {
        
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(short Year) {

        printf("_______________________________________\n\n");
        printf("          Calendar - %d\n", Year);
        printf("_______________________________________\n");

        for (short i = 1; i <= 12; i++) {

            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar() {
        
        PrintYearCalendar(_Year);
    }

    static bool IsValidDate(clsDate Date) {

        if (Date._Day < 1 || Date._Day > 31)
            return false;

        if (Date._Month < 1 || Date._Month > 12)
            return false;

        if (Date._Month == 2) {

            if (IsLeapYear(Date._Year)) {
                if (Date._Day > 29)
                    return false;
            }
            else {

                if (Date._Day > 28)
                    return false;
            }
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > DaysInMonth)
            return false;

        return true;
    }

    bool IsValidDate() {
        
        return IsValidDate(*this);
    }

    static bool IsLastDayInMonth(clsDate Date) {

        return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
    }

    static short NumberOfDaysInAMonth(short Month, short Year) {

        if (Month < 1 || Month > 12)
            return 0;

        short NumberOfDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31 ,30, 31 };
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    short NumberOfDaysInAMonth() {
        
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    bool IsLastDayInMonth() {
        
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month) {

        return (Month == 12);
    }

    bool IsLastMonthInYear() {
        
        return IsLastMonthInYear(_Month);
    }

    static clsDate IncreaseDateByOneDay(clsDate &Date) {

        if (IsLastDayInMonth(Date)) {

            if (IsLastMonthInYear(Date._Month)) {

                Date._Month = 1;
                Date._Day = 1;
                Date._Year++;
            }
            else {

                Date._Day = 1;
                Date._Month++;
            }
        }
        else {
            Date._Day++;
        }

        return Date;
    }

    void AddOneDay() {
        
        IncreaseDateByOneDay(*this);
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

        return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? ((Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month ? (Date1._Day < Date2._Day) : false)) : false);
    }

    bool IsDateBeforeDate2(clsDate Date2) {
        
        return IsDate1BeforeDate2(*this, Date2);
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

        int Days = 0;
        while (IsDate1BeforeDate2(Date1, Date2)) {

            Days++;
            Date1 = IncreaseDateByOneDay(Date1);
        }

        return IncludeEndDay ? ++Days : Days;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
        
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static clsDate GetSystemDateForAge() {

        clsDate Date;

        time_t t = time(0);
        tm* now = localtime(&t);

        Date._Day = now->tm_mday;
        Date._Month = now->tm_mon + 1;
        Date._Year = now->tm_year + 1900;

        return Date;
    }

    static int CalculateYourAgeInDays(clsDate BirthDate) {
        
        clsDate Today = GetSystemDateForAge();
        return GetDifferenceInDays(BirthDate, Today, false);
    }

    static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2) {

        return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
    }

    bool IsDateEqualToDate2(clsDate Date2) {
        
        return IsDate1EqualToDate2(*this, Date2);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return  NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return  NumberOfDaysInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return  NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return  NumberOfHoursInAMonth(_Month, _Year) * 60;
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return  NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return  IsLeapYear(Year) ? 365 : 364;
    }

    short NumberOfDaysInAYear()
    {
        return  NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return  NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return  NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return  NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return  NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return  NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return  NumberOfSecondsInAYear(_Year);
    }

    static clsDate IncreaseDateByXDays(clsDate &Date, short Days) {

        for (short i = 1; i <= Days; i++) {

            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(short Days) {
        
        IncreaseDateByXDays(*this, Days);
    }

    static clsDate IncreaseDateByOneWeek(clsDate &Date) {

        for (short i = 1; i <= 7; i++) {

            Date = IncreaseDateByOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByOneWeek() {
        
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate &Date, short Weeks) {

        for (short i = 1; i <= Weeks; i++) {

            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks) {
        
        IncreaseDateByXWeeks(*this, Weeks);
    }

    static clsDate IncreaseDateByOneMonth(clsDate &Date) {

        if (Date._Month == 12) {

            Date._Month = 1;
            Date._Year++;
        }
        else {

            Date._Month++;
        }

        // last check day in date should not exceed max days in the current month.
        // example if date is 31/1/2022 increasing one month should not be 31 / 2 / 2022,
        //  it should be 28/2/2022

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > NumberOfDaysInCurrentMonth) {

            Date._Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void IncreaseDateByOneMonth() {
        
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(clsDate &Date, short Months) {

        for (short i = 1; i <= Months; i++) {

            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;

    }

    void IncreaseDateByXMonth(short Months) {
        
        IncreaseDateByXMonths(*this, Months);
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date) {

        Date._Year++;
        return Date;
    }

    void IncreaseDateByOneYear() {
        
        _Year++;
    }

    static clsDate IncreaseDateByXYears(clsDate &Date, short Years) {

        for (short i = 1; i <= Years; i++) {

            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }

    void IncreaseDateByXYears(short Years) {
        
        IncreaseDateByXYears(*this, Years);
    }

    static clsDate IncreaseDateByXYearsFaster(clsDate &Date, short Years) {

        Date._Year += Years;
        return Date;
    }

    void IncreaseDateByXYearsFaster(short Years) {
        
        _Year += Years;
    }

    static clsDate IncreaseDateByOneDecade(clsDate &Date) {

        // Decade is Period of 10 years.
        Date._Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade() {
        
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(clsDate &Date, short Decades) {

        for (short i = 1; i <= Decades * 10; i++) {

            Date = IncreaseDateByOneYear(Date);
        }
        return Date;
    }

    void IncreaseDateByXDecades(short Decades) {
        
        IncreaseDateByXDecades(*this, Decades);
    }

    static clsDate IncreaseDateByXDecadesFaster(clsDate &Date, short Decades) {

        Date._Year += Decades * 10;
        return Date;
    }

    void IncreaseDateByXDecadesFaster(short Decades) {
        
        IncreaseDateByXDecadesFaster(*this, Decades);
    }

    static clsDate IncreaseDateByOneCentury(clsDate &Date) {

        // Century is Period of 100 years.
        Date._Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury() {
        
        IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate &Date) {

        // Millennium is Period of 1000 years.
        Date._Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium() {
        
        IncreaseDateByOneMillennium(*this);
    }

    static bool IsFirstDayInMonth(short Day) {

        return (Day == 1);
    }

    bool IsFirstDayInMonth() {

        return IsFirstDayInMonth(_Day);
    }

    static bool IsFirstMonthInYear(short Month) {

        return (Month == 1);
    }

    bool IsFirstMonthInYear() {

        return IsFirstMonthInYear(_Month);
    }

    static clsDate DecreaseDateByOneDay(clsDate &Date) {

        if (IsFirstDayInMonth(Date.Day)) {

            if (IsFirstMonthInYear(Date.Month)) {

                Date.Month = 12;
                Date.Year--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);

            }
            else {

                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay() {
        
        DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDays(clsDate &Date, short Days) {

        for (short i = 1; i <= Days; i++) {

            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days) {
        
        DecreaseDateByXDays(*this, Days);
    }

    static clsDate DecreaseDateByOneWeek(clsDate &Date) {

        for (short i = 1; i <= 7; i++) {

            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByOneWeek() {
        
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(clsDate &Date, short Weeks) {

        for (short i = 1; i <= Weeks; i++) {

            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks) {
        
        DecreaseDateByXWeeks(*this, Weeks);
    }

    static clsDate DecreaseDateByOneMonth(clsDate &Date) {

        if (Date.Month == 1) {

            Date.Month = 12;
            Date.Year--;
        }
        else {

            Date.Month--;
        }

        // last check day in date should not exceed max days in the current month.
        // example if date is 31/3/2022 Decreasing one month should not be 31 / 2 / 2022,
        //  it should be 28/2/2022

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth) {

            Date.Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void DecreaseDateByOneMonth() {
        
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(clsDate &Date, short Months) {

        for (short i = 1; i <= Months; i++) {

            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;

    }

    void DecreaseDateByXMonths(short Months) {
        
        DecreaseDateByXMonths(*this, Months);
    }

    static clsDate DecreaseDateByOneYear(clsDate &Date) {

        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear() {
        
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(clsDate &Date, short Years) {

        for (short i = 1; i <= Years; i++) {

            Date = DecreaseDateByOneYear(Date);
        }
        return Date;
    }

    void DecreaseDateByXYears(short Years) {
        
        DecreaseDateByXYears(*this, Years);
    }

    static clsDate DecreaseDateByXYearsFaster(clsDate &Date, short Years) {

        Date.Year -= Years;
        return Date;
    }

    void DecreaseDateByXYearsFaster(short Years) {
        
        DecreaseDateByXYearsFaster(*this, Years);
    }

    static clsDate DecreaseDateByOneDecade(clsDate &Date) {

        // Decade is Period of 10 years.
        Date.Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade() {
        
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(clsDate &Date, short Decades) {

        for (short i = 1; i <= Decades * 10; i++) {

            Date = DecreaseDateByOneYear(Date);
        }
        return Date;
    }

    void DecreaseDateByXDecades(short Decades) {
        
        DecreaseDateByXDecades(*this, Decades);
    }

    static clsDate DecreaseDateByXDecadesFaster(clsDate &Date, short Decades) {

        Date.Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecadesFaster(short Decades) {
        
        DecreaseDateByXDecadesFaster(*this, Decades);
    }

    static clsDate DecreaseDateByOneCentury(clsDate &Date) {

        // Century is Period of 100 years.
        Date.Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury() {
        
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate &Date) {

        // Millennium is Period of 1000 years.
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium() {
    
        DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(clsDate Date) {

        return (DayOfWeekOrder(Date) == 6);
    }

    bool IsEndOfWeek() {
        
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date) {

        //Weekends are Fri and Sat.
        short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd() {
        
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date) {

        //Business Days are Sun,Mon,Tue,Wed and Thur.

        /*short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex >= 0 && DayIndex <= 4);*/

        //shorter method is to invert the IsWeekEnd: this will save updating code.
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay() {
        
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date) {

        return 6 - DayOfWeekOrder(Date);
    }

    short DaysUntilTheEndOfWeek() {
        
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date) {

        clsDate EndOfMonthDate;

        EndOfMonthDate._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
        EndOfMonthDate._Month = Date._Month;
        EndOfMonthDate._Year = Date._Year;

        return GetDifferenceInDays(Date, EndOfMonthDate, true);
    }

    short DaysUntilTheEndOfMonth() {
    
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date) {

        clsDate EndOfYearDate;

        EndOfYearDate._Day = 31;
        EndOfYearDate._Month = 12;
        EndOfYearDate._Year = Date._Year;

        return GetDifferenceInDays(Date, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear() {
        
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {

        short DaysCount = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo)) {

            if (IsBusinessDay(DateFrom)) {

                DaysCount++;
            }
            DateFrom = IncreaseDateByOneDay(DateFrom);
        }
        return DaysCount;
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays) {

        short WeekEndCounter = 0;

        // in case the date is weekend keep adding one day until you reach business day.
        // we get rid of all weekends before the first business day
        while (IsWeekEnd(DateFrom)) {

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }
        // here we increase the vacation dates to add all weekends to it.
        for (short i = 1; i <= VacationDays + WeekEndCounter; i++) {

            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }

        // in case the return date is week-end keep adding one day until you reach business day.
        while (IsWeekEnd(DateFrom)) {

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }

        return DateFrom;
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
    }

    bool IsDate1AfterDate2(clsDate Date2) {
        
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {

        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualToDate2(Date1, Date2))
            return enDateCompare::Equal;

        /*if (IsDate1AfterDate2(Date1, Date2))
            return enDateCompare::After;*/

            // this is faster
        return enDateCompare::After;
    }

    enDateCompare CompareDates(clsDate Date2) {
        
        return CompareDates(*this, Date2);
    }

    static string GetSystemDateTimeString() {
        
        // system datetime string.
        time_t t = time(0);
        tm* now = localtime(&t);

        short Year, Month, Day, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " +
            to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
    }
};

