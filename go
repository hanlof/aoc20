#!/bin/bash

if [ -z "$1" ]; then
	echo provide day plz
	exit
fi
which_day="$1"

### Check if requested day exists yet. Otherwise exit!
# XXX this probably belongs in fetch_input ?!
seconds_per_day=$((60 * 60 * 24))
day1_time=$(date +%s --date="December 1 00:00:00 EST")
let day0_time=day1_time-seconds_per_day
let requested_day_time=day0_time+which_day*seconds_per_day
now_time=$(date +%s)
if [ ${requested_day_time} -gt ${now_time} ]; then
	let time_left=requested_day_time-now_time-3600
	echo "Day ${which_day} is in the future!"
	date +%T --date="@${time_left}"
	exit
fi

### Determine type of input data (by supplied argument)
input_type="1"
if [ ! -z "$2" ]; then
	case "$2" in
		single|s|one|oneline|1|o) input_type=1;;
		blank|block|blockwise|empty|b) input_type=b;;
		map|m) input_type=m;;
		*)
			echo "Unknown input type: $2";
			echo Select [s]ingle-line [b]lank-line-delimeted or [m]ap;
			exit;;
	esac
fi

### Figure out some filenames
# XXX maybe randomize prog name or add a unique number to the name
# because when you quickstart you could make mistakes and want to redo
# and then it's safer to just make a new file than delete/overwrite the
# existing one and it's easy to just rename anything later!

inf="input/input${which_day}"
binfile="bin/prog${which_day}"
c_file="prog${which_day}.c"
case "$input_type" in
	1) template_file=templates/single_line_input.c ;;
	b) template_file=templates/blank_line_delimeted_input.c ;;
	m) template_file=templates/map_input.c ;;
esac

test -e ${inf} || ./fetch_input "${which_day}" > "${inf}"

test -e "${c_file}" || {

cp -v "${template_file}" "${c_file}"
}

vim -c "TrunCommand ${binfile} < ${inf}" -O "${c_file}" "${inf}"
