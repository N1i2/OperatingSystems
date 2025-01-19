@echo off
echo ==========================
echo WMIC:
echo ==========================
echo  wmic memorychip get BankLabel, Capacity, MemoryType, Speed
wmic memorychip get BankLabel, Capacity, MemoryType, Speed
echo.

echo ==========================
echo PowerShell:
echo ==========================
echo powershell -Command "Get-WmiObject Win32_PhysicalMemory | Format-Table BankLabel, Capacity, Manufacturer, Speed"
powershell -Command "Get-WmiObject Win32_PhysicalMemory | Format-Table BankLabel, Capacity, Manufacturer, Speed"
echo.

echo ==========================
echo SystemInfo:
echo ==========================
echo systeminfo | findstr /C:"Total Physical Memory" /C:"Available Physical Memory"
systeminfo | findstr /C:"Total Physical Memory" /C:"Available Physical Memory"
echo.

echo ==========================
echo Performance Monitor:
echo ==========================
echo powershell -Command "Get-Counter '\Memory\Available MBytes' | Select-Object -ExpandProperty CounterSamples"
powershell -Command "Get-Counter '\Memory\Available MBytes' | Select-Object -ExpandProperty CounterSamples"
echo.

pause
