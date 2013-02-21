echo %1 %2 %3 %4
sleep 1
for /L %%i in (%2, %3, %4) do del %1fil%%i
exit


