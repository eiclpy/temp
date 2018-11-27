#ifndef UTILITIES_H
#define UTILITIES_H
#include "definition.h"
#include "structures.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

bool fnCheckBetween(int iData, int iLow, int iHigh)
{
	return iLow <= iData && iData <= iHigh;
}

void fnStrip(char *szStr)
{
	while (*szStr != '\n' && *szStr != '\0')
		++szStr;
	*szStr = '\0';
}

int fnFindLowerIndex(int *aSortedArray, int iLength, int iKey)
{
	int iLeft, iRight, iMid;
	iLeft = 0;
	iRight = iLength - 1;
	while (iLeft <= iRight)
	{
		iMid = (iLeft + iRight) / 2;
		if (aSortedArray[iMid] <= iKey)
		{
			iLeft = iMid + 1;
		}
		else
		{
			iRight = iMid - 1;
		}
	}
	return iRight;
}

int fnFindLower(int *aSortedArray, int iLength, int iKey)
{
	return aSortedArray[fnFindLowerIndex(aSortedArray, iLength + 1, iKey)];
}

Week fnDate2Week(sDateTime dtTmp)
{
	return (aSumOfDaysBeforeMonth[dtTmp.iMonth] + dtTmp.iDay) % DAYS_PER_WEEK;
}

Timestamp fnDateTime2Timestamp(sDateTime dtTmp)
{
	return ((aSumOfDaysBeforeMonth[dtTmp.iMonth] + dtTmp.iDay) * HOURS_PER_DAY + dtTmp.iHour) * MINUTES_PER_HOUR + dtTmp.iMinute;
}

sDateTime fnTimestamp2DateTime(Timestamp tsTmp)
{
	sDateTime dtTmp;

	dtTmp.iMinute = tsTmp % MINUTES_PER_HOUR;
	tsTmp /= MINUTES_PER_HOUR;

	dtTmp.iHour = tsTmp % HOURS_PER_DAY;
	tsTmp /= HOURS_PER_DAY;

	dtTmp.iMonth = fnFindLowerIndex(aSumOfDaysBeforeMonth, MONTHS_PER_YEAR, tsTmp);
	dtTmp.iDay = tsTmp - aSumOfDaysBeforeMonth[dtTmp.iMonth];

	return dtTmp;
}

Timestamp fnGetTimestamp()
{
	sDateTime dtTmp;

	do
	{
		printf("Input the month(1-12):");
		scanf("%d", &dtTmp.iMonth);
	} while (!fnCheckBetween(dtTmp.iMonth, MONTH_MIN, MONTH_MAX));

	do
	{
		printf("Input the date:");
		scanf("%d", &dtTmp.iDay);
	} while (!fnCheckBetween(dtTmp.iDay, DAY_MIN, aDaysOfMonth[dtTmp.iMonth]));

	do
	{
		printf("Input the hour(0-23):");
		scanf("%d", &dtTmp.iHour);
	} while (!fnCheckBetween(dtTmp.iHour, HOUR_MIN, HOUR_MAX));

	do
	{
		printf("Input the minute(0-59):");
		scanf("%d", &dtTmp.iMinute);
	} while (!fnCheckBetween(dtTmp.iMinute, MINUTE_MIN, MINUTE_MAX));

	return fnDateTime2Timestamp(dtTmp);
}

void fnPrintDatetime(Timestamp tsTmp)
{
	sDateTime dtTmp = fnTimestamp2DateTime(tsTmp);
	printf("%d/%d %d:%d", dtTmp.iMonth, dtTmp.iDay, dtTmp.iHour, dtTmp.iMinute);
}

void fnPrintAllClassroomInfo()
{
	printf("Classroom Info\ngiTotal:%d\n", giTotal);
	for (int i = 0; i < giTotal; ++i)
	{
		printf("%d %s %d\n", gBaseInfo[i].iRoomID, gBaseInfo[i].szRoomName, gBaseInfo[i].iRoomSize);
	}
}

void fnPrintAllClassroomDetails()
{
	printf("Classroom Details\ngiCount:%d\n", giCount);
	for (int i = 0; i < giCount; ++i)
	{
		printf("RoomID:%d StartTime:%d EndTime:%d Enable:%d\n", gDetails[i].iRoomID, gDetails[i].iStartTime, gDetails[i].iEndTime, gDetails[i].bEnable);
		printf("User:");
		puts(gDetails[i].szUser);
		printf("Usage:");
		puts(gDetails[i].szUsage);
	}
}

void fnInit()
{
	FILE *fin = fopen(szPathToBaseInfo, "r");
	assert(fin);
	while (~fscanf(fin, "%d %s %d", &gBaseInfo[giTotal].iRoomID, gBaseInfo[giTotal].szRoomName, &gBaseInfo[giTotal].iRoomSize))
	{
		++giTotal;
	}
	fclose(fin);
	fin = fopen(szPathToCalssroomInfo, "r");
	assert(fin);
	while (~fscanf(fin, "%d %d %d %d%*c", &gDetails[giCount].iRoomID, &gDetails[giCount].iStartTime, &gDetails[giCount].iEndTime, &gDetails[giCount].bEnable))
	{
		fgets(gDetails[giCount].szUser, sizeof(gDetails[giCount].szUser), fin);
		fnStrip(gDetails[giCount].szUser);
		fgets(gDetails[giCount].szUsage, LONG_STR_LEN, fin);
		fnStrip(gDetails[giCount].szUsage);

		if (gDetails[giCount].bEnable)
		{
			++giCount;
		}
	}
	fclose(fin);
}

void fnExit()
{
	FILE *fout = fopen(szPathToCalssroomInfo, "w");
	assert(fout);
	for (int i = 0; i < giCount; ++i)
	{
		if (gDetails[i].bEnable)
		{
			fprintf(fout, "%d %d %d %d\n%s\n%s\n", gDetails[i].iRoomID, gDetails[i].iStartTime, gDetails[i].iEndTime, gDetails[i].bEnable, gDetails[i].szUser, gDetails[i].szUsage);
		}
	}
	fclose(fout);
}

void fnPrintClassroomInfo(int iRoomID)
{
	printf("RoomID:%d\nRoomName:%s\nRoomSize:%d\n", gBaseInfo[iRoomID].iRoomID, gBaseInfo[iRoomID].szRoomName, gBaseInfo[iRoomID].iRoomSize);
}

bool fnCheckIsUsed(int RoomID, Timestamp tsStart, Timestamp tsEnd)
{
	for (int i = 0; i < giCount; ++i)
	{
		if (gDetails[i].bEnable && RoomID == gDetails[i].iRoomID && !(tsStart < gDetails[i].iStartTime && tsEnd <= gDetails[i].iStartTime || tsStart >= gDetails[i].iEndTime && tsEnd > gDetails[i].iEndTime))
			return true;
	}
	return false;
}

#endif
