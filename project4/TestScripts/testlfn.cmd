set _drive=a:
if not "%1"=="" set _drive=%1

md %_drive%\longfilename

start /min create.cmd %_drive%\ 100000 2000 1000000
start /min delete.cmd %_drive%\ 100000 3000 1000000
start /min create.cmd %_drive%\ 100000 5000 1000000
start /min delete.cmd %_drive%\ 100000 7000 1000000

start /min create.cmd %_drive%\ 100000 -2000 0
start /min delete.cmd %_drive%\ 100000 -3000 0
start /min create.cmd %_drive%\ 100000 -5000 0
start /min delete.cmd %_drive%\ 100000 -7000 0

start /min wilddelete %_drive%\ 3
start /min wilddelete %_drive%\ 7

start /min create.cmd %_drive%\longfilename\ 100000 2000 1000000
start /min delete.cmd %_drive%\longfilename\ 100000 3000 1000000
start /min create.cmd %_drive%\longfilename\ 100000 5000 1000000
start /min delete.cmd %_drive%\longfilename\ 100000 7000 1000000

start /min create.cmd %_drive%\longfilename\ 100000 -2000 0
start /min delete.cmd %_drive%\longfilename\ 100000 -3000 0
start /min create.cmd %_drive%\longfilename\ 100000 -5000 0
start /min delete.cmd %_drive%\longfilename\ 100000 -7000 0

start /min wilddelete %_drive%\longfilename\ 3
start /min wilddelete %_drive%\longfilename\ 7

sleep 30
dir /s %_drive%\

echo "Now wait until everything settles down"
pause

chkdsk %_drive%
pause

dir /s %_drive%\

