
cd %4

echo Project Name: %1
echo Solution Configuration: %2
echo Compiler Path: %3

echo Mode: %mode%
echo Start building

: --os windows --type remote C:\Repositories\seac\TestProject\main.gcew

%3 --os windows --type %2 main.gcew

echo End building

