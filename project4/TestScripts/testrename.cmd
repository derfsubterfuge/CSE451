set _drive=a:
if not "%1"=="" set _drive=%1

start /min rename.cmd %_drive%\fil xyz 1 2 100
start /min rename.cmd %_drive%\fil xyz 1 3 100
start /min rename.cmd %_drive%\fil xyz 1 5 100
start /min rename.cmd %_drive%\fie xyz 1 7 100

start /min rename.cmd %_drive%\fil xyz 100 -2 0
start /min rename.cmd %_drive%\fil xyz 100 -3 0
start /min rename.cmd %_drive%\fil xyz 100 -5 0
start /min rename.cmd %_drive%\fil xyz 100 -7 0

sleep 30
dir %_drive%\

echo "Now wait until everything settles down"
pause

chkdsk %_drive%
pause

dir %_drive%\

