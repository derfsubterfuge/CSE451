set _drive=a:
if not "%1"=="" set _drive=%1

start /min testsize
start /min testext

:start

sleep 10
label %_drive% SORTBYNAME
dir /s %_drive%

sleep 10
label %_drive% SORTBYEXT
dir /s %_drive%

sleep 10
label %_drive% SORTBYTIME
dir /s %_drive%

sleep 10
label %_drive% SORTBYSIZE
dir /s %_drive%

sleep 10
label %_drive% SORTBYFAT
dir /s %_drive%

sleep 10
label %_drive% SORTYBYDATE
dir /s %_drive%

goto :start

