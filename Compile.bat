@REM mkdir build32Win
@REM cd build32Win
@REM cmake .. -A Win32 -DMySuffix2=32
@REM cmake --build . --config Release
@REM cd ..

mkdir build64Win
cd build64Win
cmake .. -A x64 -DMySuffix2=64
cmake --build . --config Release
cd ..
