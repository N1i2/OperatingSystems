@echo off

set targetDir=TXT
echo %1

if not exist %targetDir% (
    mkdir %targetDir%
)

move %1 %targetDir%

echo All files with extension %1 moved to catalog %targetDir%
pause