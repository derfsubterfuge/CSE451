echo %1 %2 %3 %4 %5
sleep 1
for /L %%i in (%3, %4, %5) do move %1%%i %2%%i
exit

