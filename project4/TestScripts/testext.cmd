set _drive=a:
if not "%1"=="" set _drive=%1

label %_drive% SORTBYEXT

start /min createext.cmd %_drive%\ 1 2 999
start /min delete.cmd %_drive%\ 1 3 999
start /min createext.cmd %_drive%\ 1 5 999
start /min delete.cmd %_drive%\ 1 7 999

start /min createext.cmd %_drive%\ 999 -2 0
start /min delete.cmd %_drive%\ 999 -3 0
start /min createext.cmd %_drive%\ 999 -5 0
start /min delete.cmd %_drive%\ 999 -7 0

start /min wilddelete %_drive%\ 3
start /min wilddelete %_drive%\ 7

sleep 30
dir %_drive%\

echo "Now wait until everything settles down"
pause

chkdsk %_drive%
pause

dir %_drive%\

