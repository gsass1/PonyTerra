@echo off

if "%1%"=="" goto error

set bash=C:\Program Files (x86)\Git\bin\bash.exe

"%bash%" --login -i -c "exec "unzip.sh" %1%"

goto done

:error

echo "Specify a file"

:done