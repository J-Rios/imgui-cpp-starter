@echo off
setlocal

REM -----------------------------------------------------------------------------------------------
REM Windows 11 Installation Requirements Script
REM
REM This script checks and installs the following tools:
REM - Git
REM - Python
REM - Jinja2
REM - MSYS2
REM - UCRT64 GCC
REM - Ninja
REM - CMake
REM - GDB
REM
REM Here are the steps to install them manually:
REM 1. Open a CMD terminal.
REM 2. Install Msys2 via winget:
REM     winget install MSYS2.MSYS2
REM 3. Open Msys2 environment:
REM     C:\msys64\msys2.exe
REM 4. Update Msys2 (once updated, reopen it again):
REM     pacman -Syu
REM 5. Install the toolchain tools:
REM     pacman -S \
REM         mingw-w64-ucrt-x86_64-gcc \
REM         mingw-w64-ucrt-x86_64-gdb \
REM         mingw-w64-ucrt-x86_64-cmake \
REM         mingw-w64-ucrt-x86_64-ninja
REM 6. Add the UCRT64 binaries folder to windows PATH (add to "user" PATH to avoid admin needs):
REM     "C:\msys64\ucrt64\bin"
REM 7. Close-Open the CMD terminal and verify that all tools are now installed and available:
REM     gcc --version
REM     g++ --version
REM     gdb --version
REM     cmake --version
REM     ninja --version
REM -----------------------------------------------------------------------------------------------

echo.
echo =====================================================
echo Installing Git
echo =====================================================
echo.
where git >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Git already installed.
) else (
    echo [INFO] Installing Git...
    winget install --id Git.Git --accept-package-agreements --accept-source-agreements
    if errorlevel 1 (
        echo [ERROR] Git installation failed.
        exit /b 1
    )
    echo [OK] Git installed successfully.
)

echo.
echo =====================================================
echo Installing Python
echo =====================================================
echo.
where python >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] Python already installed.
) else (
    echo [INFO] Installing Python...
    winget install Python.Python.3.12 --accept-package-agreements --accept-source-agreements
    if errorlevel 1 (
        echo [ERROR] Python installation failed.
        exit /b 1
    )
    echo [OK] Python installed successfully.
)

echo.
echo =====================================================
echo Installing MSYS2
echo =====================================================
echo.
if exist "C:\msys64\msys2.exe" (
    echo [OK] MSYS2 is already installed.
) else (
    echo [INFO] Installing MSYS2...
    winget install --id MSYS2.MSYS2 --accept-package-agreements --accept-source-agreements
    if errorlevel 1 (
        echo [ERROR] MSYS2 installation failed.
        exit /b 1
    )
)
REM --- Wait until installed ---
if not exist "C:\msys64\msys2.exe" (
    echo [ERROR] C:\msys64\msys2.exe not found.
    exit /b 1
)
REM --- Updating MSYS2 ---
echo Updating MSYS2...
C:\msys64\usr\bin\bash.exe -lc "pacman -Syu --noconfirm"

echo.
echo =====================================================
echo Installing toolchain
echo =====================================================
echo.
C:\msys64\usr\bin\bash.exe -lc ^
"pacman -S --needed --noconfirm ^
mingw-w64-ucrt-x86_64-gcc ^
mingw-w64-ucrt-x86_64-gdb ^
mingw-w64-ucrt-x86_64-cmake ^
mingw-w64-ucrt-x86_64-ninja ^
mingw-w64-ucrt-x86_64-python ^
mingw-w64-ucrt-x86_64-python-pip"
if errorlevel 1 (
    echo [ERROR] Toolchain installation failed.
    exit /b 1
)

echo.
echo =====================================================
echo Installing Python Modules
echo =====================================================
echo.
python.exe -m pip install --break-system-packages jinja2
if errorlevel 1 (
    echo [ERROR] Python modules installation failed.
    exit /b 1
)
C:\msys64\ucrt64\bin\python.exe -m pip install --break-system-packages jinja2
if errorlevel 1 (
    echo [ERROR] Python modules installation failed.
    exit /b 1
)

echo.
echo =====================================================
echo Adding UCRT64 to User PATH
echo =====================================================
echo.
for /f "tokens=2*" %%A in (
    'reg query HKCU\Environment /v Path 2^>nul ^| find "Path"'
) do set USERPATH=%%B
echo %USERPATH% | find /I "C:\msys64\ucrt64\bin" >nul
if errorlevel 1 (
    setx PATH "%USERPATH%;C:\msys64\ucrt64\bin" >nul
    echo [OK] PATH updated.
) else (
    echo [OK] PATH already contains C:\msys64\ucrt64\bin
)

echo.
echo =====================================================
echo Installation completed
echo =====================================================
echo.
echo Open a NEW CMD window and verify:
echo.
echo     git --version
echo     gcc --version
echo     g++ --version
echo     gdb --version
echo     cmake --version
echo     ninja --version
echo     python --version
echo.

pause
