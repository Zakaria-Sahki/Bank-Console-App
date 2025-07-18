#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsPeriod {

public :
	clsDate StartDate;
	clsDate EndDate;

	clsPeriod(clsDate StartDate, clsDate EndDate) {
		
		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}

	static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2) {

		if ((clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before) ||
			(clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enDateCompare::After))
			return false;
		else
			return true;
	}

	bool IsOverlapWith(clsPeriod Period2) {
		
		return IsOverlapPeriods(*this, Period2);
	}

	void Print() {
		
		cout << "Period Start: " << endl;
		StartDate.Print();
		cout << "Period End: " << endl;
		EndDate.Print();
	}

	static int PeriodLengthInDays(clsPeriod Period, bool IncludeEndDate = false) {

		return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
	}

	int PeriodLengthInDays(bool IncludeEndDate = false) {
		
		return PeriodLengthInDays(*this, IncludeEndDate);
	}

	static bool IsDateInPeriod(clsPeriod Period, clsDate Date) {

		return !((clsDate::CompareDates(Date, Period.StartDate) == clsDate::enDateCompare::Before) ||
			(clsDate::CompareDates(Date, Period.EndDate) == clsDate::enDateCompare::After));
	}

	bool IsDateInPeriod(clsDate Date) {
		
		return IsDateInPeriod(*this, Date);
	}

	static int CountOverlapDays(clsPeriod Period1, clsPeriod Period2) {

		int Period1Length = PeriodLengthInDays(Period1, true);
		int Period2Length = PeriodLengthInDays(Period2, true);
		int OverlapDays = 0;

		if (!IsOverlapPeriods(Period1, Period2))
			return 0;

		if (Period1Length < Period2Length) {

			while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate)) {

				if (IsDateInPeriod(Period2, Period1.StartDate))
					OverlapDays++;

				Period1.StartDate = clsDate::IncreaseDateByOneDay(Period1.StartDate);
			}
		}
		else {

			while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate)) {

				if (IsDateInPeriod(Period1, Period2.StartDate))
					OverlapDays++;

				Period2.StartDate = clsDate::IncreaseDateByOneDay(Period2.StartDate);
			}
		}

		return OverlapDays;
	}

	int CountOverlapDays(clsPeriod Period2) {
		
		return CountOverlapDays(*this, Period2);
	}

};

