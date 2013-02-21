set _drive=a:
if not %1%=="" set _drive=%1

md %_drive%\subdir

start /min create.cmd %_drive%\ 1 2 100
start /min delete.cmd %_drive%\ 1 3 100
start /min create.cmd %_drive%\ 1 5 100
start /min delete.cmd %_drive%\ 1 7 100

start /min create.cmd %_drive%\ 100 -2 0
start /min delete.cmd %_drive%\ 100 -3 0
start /min create.cmd %_drive%\ 100 -5 0
start /min delete.cmd %_drive%\ 100 -7 0

start /min wilddelete %_drive%\ 3
start /min wilddelete %_drive%\ 7

start /min create.cmd %_drive%\subdir\ 1 2 100
start /min delete.cmd %_drive%\subdir\ 1 3 100
start /min create.cmd %_drive%\subdir\ 1 5 100
start /min delete.cmd %_drive%\subdir\ 1 7 100

start /min create.cmd %_drive%\subdir\ 100 -2 0
start /min delete.cmd %_drive%\subdir\ 100 -3 0
start /min create.cmd %_drive%\subdir\ 100 -5 0
start /min delete.cmd %_drive%\subdir\ 100 -7 0

start /min wilddelete %_drive%\subdir\ 3
start /min wilddelete %_drive%\subdir\ 7

sleep 30
dir /s %_drive%\

echo "Now wait until everything settles down"
pause

chkdsk %_drive%
pause

dir /s %_drive%\

