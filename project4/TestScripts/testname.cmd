set _drive=a:
if not "%1"=="" set _drive=%1

label %_drive% SORTBYNAME

start /min create.cmd %_drive%\ 1 2 1000
start /min delete.cmd %_drive%\ 1 3 1000
start /min create.cmd %_drive%\ 1 5 1000
start /min delete.cmd %_drive%\ 1 7 1000

start /min create.cmd %_drive%\ 1000 -2 0
start /min delete.cmd %_drive%\ 1000 -3 0
start /min create.cmd %_drive%\ 1000 -5 0
start /min delete.cmd %_drive%\ 1000 -7 0

start /min wilddelete %_drive%\ 3
start /min wilddelete %_drive%\ 7

sleep 30
dir %_drive%\

echo "Now wait until everything settles down"
pause

chkdsk %_drive%
pause

dir %_drive%\

