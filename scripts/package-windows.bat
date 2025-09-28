@echo off
REM Windows Package Creation Script for Security Sentinel
REM Creates MSI installer and other Windows package formats

echo 📦 Security Sentinel Windows Package Creator
echo =============================================
echo.

REM Check if we're in the right directory
if not exist "CMakeLists.txt" (
    echo ❌ Error: Run this script from the project root directory
    exit /b 1
)

if not exist "package.json" (
    echo ❌ Error: Run this script from the project root directory
    exit /b 1
)

REM Get version from package.json
for /f "tokens=2 delims=:" %%a in ('findstr "version" package.json') do (
    for /f "tokens=2 delims=," %%b in ("%%a") do (
        set VERSION=%%~b
        set VERSION=%VERSION:"=%
        set VERSION=%VERSION: =%
    )
)

echo 📋 Creating Windows packages for version: %VERSION%
echo.

REM Create output directory
if not exist "packages" mkdir packages
if exist "packages\*" del /q packages\*

REM Build web interface
echo 🌐 Building web interface...
call npm ci --silent
call npm run build

REM Create web distribution archive
echo 📦 Creating web distribution archive...
cd dist
tar -czf "..\packages\security-sentinel-web-%VERSION%.tar.gz" *
cd ..

REM Build Windows C++ application
echo 🔨 Building Windows C++ application...
if exist "build" rmdir /s /q build
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
cd ..

REM Create Windows binary package
echo 📦 Creating Windows binary package...
mkdir packages\windows-binary
copy build\bin\Release\SecuritySentinel.exe packages\windows-binary\
copy README.md packages\windows-binary\
copy LICENSE packages\windows-binary\
echo [gemini]> packages\windows-binary\config.ini
echo api_key=YOUR_API_KEY_HERE>> packages\windows-binary\config.ini

REM Create ZIP archive
cd packages
powershell Compress-Archive -Path "windows-binary\*" -DestinationPath "security-sentinel-windows-%VERSION%.zip"
cd ..
rmdir /s /q packages\windows-binary

REM Create checksums
echo 🔐 Creating checksums...
cd packages
for %%f in (*) do (
    certutil -hashfile "%%f" SHA256 >> checksums.sha256
)
cd ..

echo.
echo ✅ Windows package creation completed!
echo =====================================
echo.
echo 📦 Created packages:
dir packages\
echo.
echo 📋 Package details:
echo - Windows binary: packages\security-sentinel-windows-%VERSION%.zip
echo - Web archive: packages\security-sentinel-web-%VERSION%.tar.gz
echo - Checksums: packages\checksums.sha256
echo.
echo 🚀 Ready for distribution!