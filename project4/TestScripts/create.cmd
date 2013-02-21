echo %1 %2 %3 %4 %5
sleep 1
for /L %%i in (%2, %3, %4) do echo %1fil%%i%5 > %1fil%%i
exit


