# CodeQL Configuration Guide

## 🚨 Current Issue: Configuration Conflict

**Error**: "CodeQL analyses from advanced configurations cannot be processed when the default setup is enabled"

**Cause**: This repository uses an advanced CodeQL matrix configuration that conflicts with GitHub's default CodeQL setup.

## 🛠️ Resolution Options

### Option 1: Keep Custom Advanced Configuration (Recommended)

The current setup provides more comprehensive analysis with:
- ✅ Multi-language support (JavaScript, C++)
- ✅ Custom build steps for C++
- ✅ Integration with security scanning workflow
- ✅ Better control over analysis parameters

**Steps to resolve**:
1. Go to your repository's **Settings** → **Security** → **Code scanning**
2. Find the **Default setup** section
3. Click **Remove** or **Disable** the default CodeQL setup
4. Keep the existing custom workflow in `.github/workflows/security.yml`

### Option 2: Use Default Setup (Simplified)

If you prefer GitHub's default setup:
1. Remove or comment out the `codeql-analysis` job from `.github/workflows/security.yml` (lines 55-104)
2. Keep the default CodeQL setup enabled in repository settings

## 📝 Current Configuration Details

### Custom Matrix Configuration (security.yml)
```yaml
strategy:
  fail-fast: false
  matrix:
    language: ['javascript', 'cpp']
```

This provides:
- **JavaScript Analysis**: Web interface components
- **C++ Analysis**: Native application security scanning
- **Manual C++ Build**: Ensures proper compilation context

### Additional Security Tools
- **Semgrep**: Static analysis with SARIF upload (ci-cpp.yml)
- **Dependency Scanning**: npm audit
- **Secret Scanning**: GitLeaks + TruffleHog
- **License Compliance**: License checker

## 🔍 Verification Steps

After disabling default setup:
1. Re-run the security workflow
2. Check **Security** → **Code scanning** for results
3. Verify both JavaScript and C++ analyses complete successfully

## 📞 Support

If you continue to experience issues:
1. Check workflow logs for specific error messages
2. Ensure repository permissions allow security-events write access
3. Verify CodeQL languages are correctly detected

---

**Note**: This configuration provides enterprise-grade security scanning. The advanced setup is recommended for comprehensive security coverage.