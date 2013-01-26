set cse451tools=o:\cse\courses\cse451\13wi\tools
set arch=x86
set path=%cse451tools%\x86;%cse451tools%\debugging tools for windows;%path%;

alias winbag    "windbg -k com:pipe,port=\\.\pipe\ws03com2"
alias mount     "vhdmount /p \"%USERPROFILE%\My Documents\My Virtual Machines\cse451Project1.vhd\""
alias dismount  "vhdmount /u /c all"


