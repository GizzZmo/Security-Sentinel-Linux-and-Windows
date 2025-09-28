# Package Distribution Guide

This guide explains the different package formats available for Security Sentinel and how to use them for distribution.

## Available Package Formats

### 1. NPM Package (Web Interface)
- **File**: `@security-sentinel/web-interface-x.x.x.tgz`
- **Purpose**: For developers wanting to integrate the web interface
- **Installation**: `npm install @security-sentinel/web-interface`

### 2. Web Distribution Archive
- **File**: `security-sentinel-web-x.x.x.tar.gz`
- **Purpose**: Standalone web interface for hosting
- **Installation**: Extract and serve with any web server

### 3. Linux Binary Package
- **File**: `security-sentinel-linux-x.x.x.tar.gz`
- **Purpose**: Linux binary with all dependencies
- **Installation**: Extract and run the executable

### 4. Debian Package
- **File**: `security-sentinel_x.x.x_amd64.deb`
- **Purpose**: Native package for Ubuntu/Debian systems
- **Installation**: `sudo dpkg -i security-sentinel_x.x.x_amd64.deb`

### 5. Windows ZIP Package
- **File**: `security-sentinel-windows-x.x.x.zip`
- **Purpose**: Windows executable with dependencies
- **Installation**: Extract and run SecuritySentinel.exe

### 6. Winget Manifest
- **Location**: `manifests/winget/`
- **Purpose**: Windows Package Manager integration
- **Installation**: `winget install GizzZmo.SecuritySentinel`

## Distribution Channels

### GitHub Releases
- All package formats available as release assets
- Automated builds via GitHub Actions
- Checksums provided for integrity verification

### NPM Registry
- Web interface package published to npm
- Semantic versioning following project releases
- TypeScript definitions included

### Windows Package Manager
- Official winget package submission
- Automated updates through Microsoft's review process
- Easy installation for Windows users

### Linux Package Repositories
- Debian package ready for apt repository
- PPA submission possible for Ubuntu users
- Manual installation available

## Creating Packages

### Automated (Recommended)
```bash
# Use the packaging script
./scripts/package.sh  # Linux
# or
scripts\package-windows.bat  # Windows
```

### Manual Build Process
```bash
# 1. Build web interface
npm ci
npm run build

# 2. Create NPM package
npm pack

# 3. Build C++ application
mkdir build && cd build
cmake ..
make -j$(nproc)  # Linux
# or
cmake --build . --config Release  # Windows

# 4. Package manually
# See scripts/package.sh for detailed commands
```

## Verification

All packages include SHA-256 checksums for integrity verification:

```bash
# Verify package integrity
sha256sum -c checksums.sha256
```

## Distribution Best Practices

1. **Version Consistency**: All packages share the same version number
2. **Checksums**: Always provide checksums for verification
3. **Documentation**: Include installation instructions for each format
4. **Testing**: Test packages on target platforms before release
5. **Automation**: Use CI/CD for consistent package creation

## Package Manager Integration

### NPM
```json
{
  "dependencies": {
    "@security-sentinel/web-interface": "^1.1.0"
  }
}
```

### Winget
```powershell
winget install GizzZmo.SecuritySentinel
```

### APT (Future)
```bash
# After PPA setup
sudo apt update
sudo apt install security-sentinel
```

## Troubleshooting

### Package Installation Issues
- Verify checksums match downloaded files
- Check system requirements are met
- Ensure proper permissions for installation

### Build Issues
- Install all required dependencies
- Check compiler versions match requirements
- Verify Node.js and npm versions

For detailed troubleshooting, see the main [Troubleshooting Guide](wiki/Troubleshooting.md).