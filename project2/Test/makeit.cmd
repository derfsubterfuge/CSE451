cl -nologo -I. -I..\public\sdk\inc\crt -I..\public\sdk\inc -D_X86_=1 -Di386=1 -DSTD_CALL -DCONDITION_HANDLING=1 -DNT_INST=0 -DWIN32=100 -D_NT1X_=100 -DWINNT=1 -D_WIN32_WINNT=0x0501 -DWINVER=0x0501 -DWIN32_IE=0x0600 -DWIN32_LEAN_AND_MEAN=1 -DDEVL=1 -D__BUILD_MACHINE__=WinDDK -DFPO=1 -DNODEBUG -D_DLL=1 /c /Zel /Zp8 /Gy /cbstring /W3 /WX /Gz /QIfdiv- /G6 /Gi- /Gm- /GX- /GR- /Z7 /Oxs /Oy test.c
link -out:test.exe -machine:ix86 @test.link
