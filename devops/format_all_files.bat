@echo off

FOR /R "../Source/Decibel/" %%f IN (*.cpp, *.h, *.cs) DO (
    clang-format -i "%%f"
    echo %%f
)
