rem this file is for building DSPLIB in small memory module

call dosrun.bat

set OPTIONS= -g -vcpu:3.3
set SRC=55x_src
set DSPLIB=55xdsp_r3
set FILES= *.asm
set EXT=asm

rem built library in SRC dir  and then copy to root
del %DSPLIB%.src
del %DSPLIB%.lib
cd %SRC%
del *.obj

cl55 %OPTIONS% %FILES%

ar55 -r %DSPLIB%.src *.%EXT% ..\include\*.h
ar55 -r %DSPLIB%.lib *.obj
copy %DSPLIB%.src ..
copy %DSPLIB%.lib ..

del *.src
del *.lib
dir *.obj >> ..\junk.txt
del *.obj
cd ..
