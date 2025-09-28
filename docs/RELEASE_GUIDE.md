# Release Triggering Guide

This document shows how to trigger a release using the enhanced package publishing infrastructure.

## Method 1: Git Tag Release (Recommended)

To create a new release with all package formats:

```bash
# 1. Ensure you're on the main branch
git checkout main
git pull origin main

# 2. Create and push a git tag
git tag v1.1.0
git push origin v1.1.0
```

This will automatically trigger the GitHub Actions release workflow and create:

### Windows Package
- `security-sentinel-windows-v1.1.0.zip`
- Contains SecuritySentinel.exe, config.ini template, README, LICENSE

### Linux Packages
- `security-sentinel-linux-v1.1.0.tar.gz` - Binary package
- `security-sentinel_1.1.0_amd64.deb` - Debian package for apt installation

### Web Interface Packages
- `security-sentinel-web-v1.1.0.tar.gz` - Standalone web interface
- `security-sentinel-web-interface-1.1.0.tgz` - NPM package

### Verification Files
- `checksums.sha256` - SHA-256 checksums for all packages

## Method 2: Manual Workflow Dispatch

You can also manually trigger the release workflow:

1. Go to [GitHub Actions](https://github.com/GizzZmo/Security-Sentinel/actions)
2. Select "Release" workflow
3. Click "Run workflow"
4. Enter version: `v1.1.0`
5. Click "Run workflow" button

## Expected Release Assets

After the workflow completes, the GitHub release will contain:

```
Release: Security Sentinel v1.1.0
├── security-sentinel-windows-v1.1.0.zip      (Windows executable)
├── security-sentinel-linux-v1.1.0.tar.gz     (Linux binary)
├── security-sentinel_1.1.0_amd64.deb         (Debian package)
├── security-sentinel-web-v1.1.0.tar.gz       (Web interface)
├── security-sentinel-web-interface-1.1.0.tgz (NPM package)
└── checksums.sha256                           (Integrity verification)
```

## Installation Examples

### Windows Users
```powershell
# Download and extract
Expand-Archive security-sentinel-windows-v1.1.0.zip
cd security-sentinel-windows-v1.1.0
# Edit config.ini with Gemini API key
.\SecuritySentinel.exe
```

### Linux Users (Debian/Ubuntu)
```bash
# Install via DEB package
sudo dpkg -i security-sentinel_1.1.0_amd64.deb
sudo apt-get install -f  # Fix dependencies if needed

# Configure API key
sudo nano /etc/security-sentinel/config.ini

# Run
sudo SecuritySentinel
```

### Linux Users (Binary)
```bash
# Extract and run
tar -xzf security-sentinel-linux-v1.1.0.tar.gz
cd linux-binary
# Edit config.ini with API key
sudo ./SecuritySentinel
```

### Web Interface Hosting
```bash
# Extract web files
tar -xzf security-sentinel-web-v1.1.0.tar.gz
# Serve with any web server (nginx, apache, etc.)
```

### Developers (NPM)
```bash
npm install @security-sentinel/web-interface@1.1.0
```

## Package Manager Integration

### Windows Package Manager (Winget)
After release, users can install via:
```powershell
winget install GizzZmo.SecuritySentinel
```

### NPM Registry
After publishing to NPM:
```bash
npm install -g @security-sentinel/web-interface
```

## Verification

Users can verify package integrity:
```bash
# Download checksums.sha256
curl -OL https://github.com/GizzZmo/Security-Sentinel/releases/download/v1.1.0/checksums.sha256

# Verify files
sha256sum -c checksums.sha256
```

## Current Status

✅ **Ready to Release**: All packaging infrastructure is in place
- Enhanced GitHub Actions workflow with multi-platform builds
- Package scripts tested and working
- Winget manifests prepared
- NPM package configuration complete
- Documentation updated

The repository is now ready for a professional v1.1.0 release with comprehensive package distribution.