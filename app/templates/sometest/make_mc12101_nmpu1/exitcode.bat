set exitcode=%errorlevel%
echo %exitcode% >.exitcode
echo %exitcode% 
if %exitcode% gtr 1 (
	exit /B 0
) else (
	exit /B 1
)
