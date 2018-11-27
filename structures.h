#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "definition.h"
#include <stdbool.h>

typedef struct
{
	int iRoomID;
	Str32 szRoomName;
	int iRoomSize;
} sClassroomBaseInfo;

typedef struct
{
	int iRoomID;
	Timestamp iStartTime;
	Timestamp iEndTime;
	Str32 szUser;
	String szUsage;
	bool bEnable;
} sClassroomDetails;

typedef struct
{
	int iMonth;
	int iDay;
	int iHour;
	int iMinute;
} sDateTime;


sClassroomBaseInfo gBaseInfo[MAX_ROOM_CNT];
int giTotal = 0;
sClassroomDetails gDetails[MAX_BORROW_CNT];
int giCount = 0;

#endif
