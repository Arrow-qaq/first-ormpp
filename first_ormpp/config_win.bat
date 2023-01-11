cd /d  "%~dp0"
mkdir build
cd build
cmake -D WIN32=1   -G "Visual Studio 16 2019" -A x64  ..\
cd ..
pause
