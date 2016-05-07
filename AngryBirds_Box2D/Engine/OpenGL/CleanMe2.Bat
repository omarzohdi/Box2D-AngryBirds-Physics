REM
REM Keenan's Hack to remove intermediate files
REM If you find a way to enhance, please return updates to
REM ekeenan2@cdm.depaul.edu
REM  mm mm

REM cleanup root director

    rmdir /S /Q GLFW\Debug
    rmdir /S /Q GLFW\Release
    rmdir /S /Q GLFW\lib
    rmdir /S /Q GLFW\ipch
    del /F /S /A:H GLFW\*.suo
    del /F /S GLFW\*.sdf

    rmdir /S /Q GLTools\Debug
    rmdir /S /Q GLTools\Release
    rmdir /S /Q GLTools\lib
    rmdir /S /Q GLTools\ipch
    del /F /S /A:H GLTools\*.suo
    del /F /S GLTools\*.sdf


