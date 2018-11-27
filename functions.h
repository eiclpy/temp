#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "utilities.h"

void fnSuggestClassroom(Timestamp tsStart, Timestamp tsEnd, int iSize, int iLim)
{
	static bool bUsed[MAX_ROOM_CNT];
	memset(bUsed, 0, sizeof(bUsed));
	for (int i = 0; i < giCount; ++i)
	{
		if (gDetails[i].bEnable && !(tsStart < gDetails[i].iStartTime && tsEnd <= gDetails[i].iStartTime || tsStart >= gDetails[i].iEndTime && tsEnd > gDetails[i].iEndTime))
			bUsed[i] = true;
	}
	for (int i = 0; i < giTotal && iLim > 0; ++i)
	{
		if (!bUsed[i] && gBaseInfo[i].iRoomSize >= iSize)
		{
			--iLim;
			fnPrintClassroomInfo(i);
		}
	}
}

bool fnApplyClassRoom(int RoomID, Timestamp tsStart, Timestamp tsEnd, char *szUser, char *szUsage)
{
	if (fnCheckIsUsed(RoomID, tsStart, tsEnd))
		return false;
	else
	{
		gDetails[giCount].iRoomID = RoomID;
		gDetails[giCount].iStartTime = tsStart;
		gDetails[giCount].iEndTime = tsEnd;
		strcpy(gDetails[giCount].szUser, szUser);
		strcpy(gDetails[giCount].szUsage, szUsage);
		gDetails[giCount].bEnable = true;
		++giCount;
		return true;
	}
}

#endif
