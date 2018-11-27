#include "definition.h"
#include "structures.h"
#include "utilities.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

bool fnFindApply();

bool fnCancelApply(int RoomID, Timestamp tsStart, Timestamp tsEnd){

}

int main()
{
	fnInit();
	printf("%d\n", fnCheckIsUsed(0, 30, 60));
	fnApplyClassRoom(0, 30, 120, "lpy's roommate", "play");
	printf("%d\n", fnCheckIsUsed(0, 30, 60));
	fnExit();
	return 0;
}

/*

fgets(gBaseInfo[giTotal].szUser, 16, fin);
		fgets(gBaseInfo[giTotal].szUsage, LONG_STR_LEN, fin);
		++giTotal;

		*/
