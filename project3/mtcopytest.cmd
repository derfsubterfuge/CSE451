md c:\mtcopysrc
md c:\mtcopydst
REM md z:\mtcopysrc
REM md z:\mtcopydst
del /q c:\mtcopysrc\*.*
REM del /q z:\mtcopydst\*.*
del /q c:\mtcopysrc\*.*
REM del /q z:\mtcopydst\*.*


rem copy large files

xcopy /q /y c:\windows\system32\*krnl*.exe c:\mtcopysrc
REM xcopy /q /y c:\windows\system32\*krnl*.exe z:\mtcopysrc
xcopy /q /y c:\windows\system32\MRT.exe    c:\mtcopysrc
REM xcopy /q /y c:\windows\system32\MRT.exe    z:\mtcopysrc
FOR %%s IN (c) DO FOR %%d IN (c) DO FOR %%t IN (1,2,10) DO FOR %%b IN (64, 512, 4096, 8192) DO mtcopy /T:%%t /B:%%b    /V %%s:\mtcopysrc\*.* %%d:\mtcopydst
FOR %%s IN (c) DO FOR %%d IN (c) DO FOR %%t IN (1,2,10) DO FOR %%b IN (64, 512, 4096, 8192) DO mtcopy /T:%%t /B:%%b /A /V %%s:\mtcopysrc\*.* %%d:\mtcopydst
del /q c:\mtcopysrc\*.*
REM del /q z:\mtcopysrc\*.*

rem copy smaller files

xcopy /q /y c:\windows\fonts\c*.ttf c:\mtcopysrc
REM xcopy /q /y c:\windows\fonts\c*.ttf z:\mtcopysrc
FOR %%s IN (c) DO FOR %%d IN (c) DO FOR %%t IN (1,2,10) DO FOR %%b IN (64, 512, 4096, 8192) DO mtcopy /T:%%t /B:%%b    /V %%s:\mtcopysrc\*.* %d:\mtcopydst
FOR %%s IN (c) DO FOR %%d IN (c) DO FOR %%t IN (1,2,10) DO FOR %%b IN (64, 512, 4096, 8192) DO mtcopy /T:%%t /B:%%b /A /V %%s:\mtcopysrc\*.* %d:\mtcopydst

rd /q /s c:\mtcopysrc
rd /q /s c:\mtcopydst
REM rd /q /s z:\mtcopysrc
REM rd /q /s z:\mtcopydst
