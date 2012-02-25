#!/bin/sh

if test $# -lt 1
then
  echo "usage: `basename $0` [-d|-f] [--] [files]" 1>&2
  exit 1
fi

if test "x$1" == "x-d" || test "x$1" == "x-f"
  then
    parametr="$1"
    shift
  else
    parametr="-f"
fi

if test "x$1" == "x--"
  then
    shift
fi

for i in "$@"
  do
    if test $parametr $i
      then
	echo $i
    fi
done

#while test "x$1" != "x"
#do
#  if test "$parametr" "$1"
#    then
#      echo "$1"
#  fi
#  shift
#done

exit 0
