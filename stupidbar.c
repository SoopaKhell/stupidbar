#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <unistd.h>

static char *get_time() {
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime( &rawtime );

	char *timestr = malloc(20);
	strftime(timestr,20,"🕒 %I:%M %p", info);

    return timestr;
}


static char *get_battery() {
	int capacity;
	FILE *capacity_file;
	capacity_file = fopen("/sys/class/power_supply/BAT0/capacity", "r");

	fscanf(capacity_file, "%d", &capacity); //store capacityfile in capacity
	fclose(capacity_file); //close it

	char *battery = malloc(3);
	snprintf(battery, 3, "%d", capacity);

	return battery;
}

long get_seconds_left() {
	time_t ts = time(NULL);
	struct tm *tm;
	struct tm *now = localtime(&ts);

	if (now->tm_wday == 3) {
		int schedule[10][3] = {
			{8,10,00},
			{9,12,00},
			{10,04,00},
			{10,56,00},
			{11,31,00},
			{11,59,00},
			{13,00,00},
			{13,47,00},
			{14,39,00},
			{15,32,12}
		};

		long int seconds_left = 0;
		for (int i = 0; i < sizeof(schedule); i++) {

			if ((tm = localtime(&ts))) {
				tm->tm_hour = schedule[i][0];
				tm->tm_min  = schedule[i][1];
				tm->tm_sec  = schedule[i][2];

				seconds_left = mktime(tm) - ts;

				if (seconds_left > 0) {
					break;
				}
			}
		}

		return seconds_left;
	} else {
		int schedule[9][3] = {
			{8,10,00},
			{9,17,00},
			{10,14,00},
			{11,11,00},
			{11,41,00},
			{12,41,00},
			{13,38,00},
			{14,35,00},
			{15,32,20}
		};

		long int seconds_left = 0;
		for (int i = 0; i < sizeof(schedule); i++) {

			if ((tm = localtime(&ts))) {
				tm->tm_hour = schedule[i][0];
				tm->tm_min  = schedule[i][1];
				tm->tm_sec  = schedule[i][2];

				seconds_left = mktime(tm) - ts;

				if (seconds_left > 0) {
					break;
				}
			}
		}

		return seconds_left;
	}
}

int main(void) {
	long secondsleft = get_seconds_left();

	if (secondsleft == 1730) {
		system("rofi -e '\n	class ends in 15s\n' > /dev/null");
	}

	int hour = secondsleft / 3600;
	int minute = secondsleft / 60;
	int seconds = secondsleft % 60;

	printf(" %d:%d:%d  🔋 %s%%  %s \n", hour, minute, seconds, get_battery(), get_time());
}
