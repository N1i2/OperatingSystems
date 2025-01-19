@echo off

set targetDir=TXT

if not exist %targetDir% (
	mkdir %targetDir%
)

move *.txt %targetDir%

echo All file moved in catalog %targetDir%
pause