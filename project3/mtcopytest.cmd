md c:\mtcopysrc
md c:\mtcopydst
md z:\mtcopysrc
md z:\mtcopydst
del /q c:\mtcopysrc\*.*
del /q z:\mtcopydst\*.*
del /q c:\mtcopysrc\*.*
del /q z:\mtcopydst\*.*


rem copy large files

xcopy /q /y c:\windows\system32\*krnl*.exe c:\mtcopysrc
xcopy /q /y c:\windows\system32\*krnl*.exe z:\mtcopysrc
xcopy /q /y c:\windows\system32\MRT.exe    c:\mtcopysrc
xcopy /q /y c:\windows\system32\MRT.exe    z:\mtcopysrc
FOR %%s IN (c, z) DO FOR %%d IN (c, z) DO FOR %%t IN (1,2,5,10,20) DO FOR %%b IN (64, 512, 4096, 8192, 1048576, 7999) DO mtcopy /T:%%t /B:%%b    /V %%s:\mtcopysrc\*.* %%d:\mtcopydst
FOR %%s IN (c, z) DO FOR %%d IN (c, z) DO FOR %%t IN (1,2,5,10,20) DO FOR %%b IN (64, 512, 4096, 8192, 1048576, 7999) DO mtcopy /T:%%t /B:%%b /A /V %%s:\mtcopysrc\*.* %%d:\mtcopydst
del /q c:\mtcopysrc\*.*
del /q z:\mtcopysrc\*.*

rem copy smaller files

xcopy /q /y c:\windows\fonts\c*.ttf c:\mtcopysrc
xcopy /q /y c:\windows\fonts\c*.ttf z:\mtcopysrc
FOR %%s IN (c, z) DO FOR %%d IN (c, z) DO FOR %%t IN (1,2,5,10,20) DO FOR %%b IN (64, 512, 4096, 8192, 1048576, 7999) DO mtcopy /T:%%t /B:%%b    /V %%s:\mtcopysrc\*.* %d:\mtcopydst
FOR %%s IN (c, z) DO FOR %%d IN (c, z) DO FOR %%t IN (1,2,5,10,20) DO FOR %%b IN (64, 512, 4096, 8192, 1048576, 7999) DO mtcopy /T:%%t /B:%%b /A /V %%s:\mtcopysrc\*.* %d:\mtcopydst

rd /q /s c:\mtcopysrc
rd /q /s c:\mtcopydst
rd /q /s z:\mtcopysrc
rd /q /s z:\mtcopydst
