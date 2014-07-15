@echo off

if "%1%"=="" goto error

set bash=C:\Program Files (x86)\Git\bin\bash.exe

"%bash%" --login -i -c "exec "set-build-number.sh" %1%"

goto done

:error

echo "Specify a build number"

:done