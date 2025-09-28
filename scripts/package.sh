#!/bin/bash

# Package creation script for Security Sentinel
# This script creates various package formats for distribution

set -e

echo "📦 Security Sentinel Package Creator"
echo "==================================="
echo ""

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ] || [ ! -f "package.json" ]; then
    echo "❌ Error: Run this script from the project root directory"
    exit 1
fi

# Get version from package.json
VERSION=$(grep '"version"' package.json | sed 's/.*"version": *"\([^"]*\)".*/\1/')
echo "📋 Creating packages for version: $VERSION"
echo ""

# Create output directory
mkdir -p packages
rm -rf packages/*

# Build web interface
echo "🌐 Building web interface..."
npm ci --silent
npm run build

# Package web interface for NPM
echo "📦 Creating NPM package..."
npm pack --pack-destination=packages/

# Create web distribution archive
echo "📦 Creating web distribution archive..."
cd dist
tar -czf "../packages/security-sentinel-web-$VERSION.tar.gz" *
cd ..

# Build C++ application (Linux)
echo "🔨 Building C++ application for Linux..."
if [ -d "build" ]; then
    rm -rf build
fi
mkdir build
cd build
cmake ..
make -j$(nproc) --silent
cd ..

# Create Linux binary package
echo "📦 Creating Linux binary package..."
mkdir -p packages/linux-binary
cp build/bin/SecuritySentinel packages/linux-binary/
cp README.md packages/linux-binary/
cp LICENSE packages/linux-binary/
echo "[gemini]" > packages/linux-binary/config.ini
echo "api_key=YOUR_API_KEY_HERE" >> packages/linux-binary/config.ini
cd packages
tar -czf "security-sentinel-linux-$VERSION.tar.gz" linux-binary/
cd ..
rm -rf packages/linux-binary

# Create Debian package structure
echo "📦 Creating Debian package..."
mkdir -p packages/debian/security-sentinel/DEBIAN
mkdir -p packages/debian/security-sentinel/usr/bin
mkdir -p packages/debian/security-sentinel/usr/share/security-sentinel
mkdir -p packages/debian/security-sentinel/etc/security-sentinel

# Copy files
cp build/bin/SecuritySentinel packages/debian/security-sentinel/usr/bin/
cp README.md LICENSE packages/debian/security-sentinel/usr/share/security-sentinel/
echo "[gemini]" > packages/debian/security-sentinel/etc/security-sentinel/config.ini
echo "api_key=YOUR_API_KEY_HERE" >> packages/debian/security-sentinel/etc/security-sentinel/config.ini

# Create control file
cat > packages/debian/security-sentinel/DEBIAN/control << EOF
Package: security-sentinel
Version: $VERSION
Section: utils
Priority: optional
Architecture: amd64
Depends: libc6 (>= 2.31), libstdc++6 (>= 10)
Maintainer: GizzZmo <maintainer@example.com>
Description: Security Sentinel - Advanced Security Monitoring
 Security Sentinel is a comprehensive security monitoring application
 with AI-powered threat analysis, real-time system monitoring,
 and automated threat response capabilities.
 .
 Features include:
 - Real-time process and network monitoring
 - AI-powered threat analysis using Google Gemini
 - Automated IP blocking and threat response
 - Cross-platform support (Windows/Linux)
 - Web-based dashboard interface
Homepage: https://github.com/GizzZmo/Security-Sentinel
EOF

# Build Debian package
cd packages/debian
dpkg-deb --build security-sentinel
mv security-sentinel.deb "../security-sentinel_${VERSION}_amd64.deb"
cd ../..
rm -rf packages/debian

# Create checksums
echo "🔐 Creating checksums..."
cd packages
for file in *; do
    if [ -f "$file" ]; then
        sha256sum "$file" >> checksums.sha256
    fi
done
cd ..

echo ""
echo "✅ Package creation completed!"
echo "==============================="
echo ""
echo "📦 Created packages:"
ls -la packages/
echo ""
echo "📋 Package details:"
echo "- NPM package: $(ls packages/*.tgz 2>/dev/null || echo 'Not found')"
echo "- Web archive: packages/security-sentinel-web-$VERSION.tar.gz"
echo "- Linux binary: packages/security-sentinel-linux-$VERSION.tar.gz"
echo "- Debian package: packages/security-sentinel_${VERSION}_amd64.deb"
echo "- Checksums: packages/checksums.sha256"
echo ""
echo "🚀 Ready for distribution!"