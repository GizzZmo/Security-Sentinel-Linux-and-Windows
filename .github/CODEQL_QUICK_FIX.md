# 🚨 CodeQL Configuration Conflict - Quick Fix Guide

## The Problem
You're seeing this error in your GitHub Actions workflow:

```
CodeQL analyses from advanced configurations cannot be processed when the default setup is enabled
```

## The Solution (5-Minute Fix)

This is **NOT a code issue** - it's a repository settings conflict. Here's how to fix it:

### 🎯 Quick Fix Steps

1. **Go to your repository settings**:
   ```
   https://github.com/GizzZmo/Security-Sentinel/settings/security_analysis
   ```

2. **Find the "Code scanning" section**

3. **Look for "Default setup" with CodeQL enabled**

4. **Click the "..." menu or "Configure" button**

5. **Select "Remove" or "Disable"**

6. **Confirm the change**

That's it! Your next workflow run should succeed.

### 🔍 Why This Happens

- **Advanced Configuration**: Your repository has a custom CodeQL workflow with matrix strategy (JavaScript + C++)
- **Default Setup**: GitHub also has a default CodeQL setup enabled
- **Conflict**: These two configurations cannot run simultaneously

### ✅ What You Keep

Your advanced configuration provides:
- ✅ Multi-language analysis (JavaScript + C++)
- ✅ Custom C++ build process
- ✅ Integration with other security tools
- ✅ More comprehensive scanning

### 📚 Detailed Instructions

For step-by-step instructions with screenshots, see: [`.github/CODEQL_SETUP.md`](.github/CODEQL_SETUP.md)

### 🆘 Still Having Issues?

1. **Check permissions**: You need Admin/Write access to the repository
2. **Wait a few minutes**: Settings changes can take time to propagate
3. **Clear cache**: Try refreshing your browser
4. **Check organization settings**: If this is an org repo, check org-level restrictions

### 🔗 Useful Links

- [GitHub Code Scanning Documentation](https://docs.github.com/en/code-security/code-scanning)
- [Repository Security Settings](https://github.com/GizzZmo/Security-Sentinel/settings/security_analysis)
- [Workflow File](/.github/workflows/security.yml)

---

**Need help?** Open an issue in this repository with the error message and we'll help you troubleshoot.