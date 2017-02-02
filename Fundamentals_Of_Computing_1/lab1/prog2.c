/*Author: Nick Palutsis*/

#include <stdio.h>

int main(void)
{
	int td; /*enter touchdowns*/
	int xp; /*enter extra points*/
	int fg; /*enter field goals*/
	int st; /*enter safeties*/
	int tot; /*sums points*/

	printf("How many touchdowns did the Irish score?\n"); /*prompt*/
	scanf("%d", &td); /*read integers*/

	printf("How many extra points did the Irsih make?\n"); /*prompt*/
	scanf("%d", &xp); /*read integer*/

	printf("How many field goals did the Irish make?\n"); /*prompt*/
	scanf("%d", &fg); /*read integer*/

	printf("How many safeties did the Irsih get?\n"); /*prompt*/
	scanf("%d", &st); /*read integer*/

	tot = (td * 6) + (xp) + (fg * 3) + (st * 2); /*assign and calculate total*/

	printf("The Irish scored a total of %d points.\n", tot); /*print tot*/

	return 0; /*indicate successful program run*/
} /*end function main*/
