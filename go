#!/bin/bash

if [ -z $1 ]; then
	echo provide day plz
	exit
fi
which_day="$1"
inf="input/input${which_day}"
pf="prog${which_day}.c"

seconds_per_day=$((60 * 60 * 24))
day1_time=$(date +%s --date="December 1 00:00:00 EST")
let day0_time=day1_time-seconds_per_day
let requested_day_time=day0_time+which_day*seconds_per_day
now_time=$(date +%s)
if [ ${requested_day_time} -gt ${now_time} ]; then
	let time_left=requested_day_time-now_time-3600
	echo "That's in the future!"
	date +%T --date="@${time_left}"
	exit
fi

test -e ${inf} || ./fetch_input "$which_day" > "${inf}"

test -e "${pf}" || {
cat > "${pf}" <<EOF
#include <stdio.h>

int main(int argc, char * argv[])
{
	char * tmp;
	scanf("%s", &tmp);
}
EOF
}

vim -c "TrunCommand bin/prog${which_day} < ${inf}" -O "${pf}" "${inf}"
