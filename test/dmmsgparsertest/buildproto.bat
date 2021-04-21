@echo off

for /f %%i in ('dir %~dp0*.proto /b') do (
            echo checking "%~dp0%%i"
            %~dp0dmconfig.exe --PROTONAME=%%i
            del /s /q *.cf.h
            del /s /q *.cf.cc
            %~dp0protoc.exe --cpp_out=. %%i
            if errorlevel 1 (
                echo error: "%~dp0%%i"
                goto FAILED
                )
            )

goto END

:FAILED
pause

:END
