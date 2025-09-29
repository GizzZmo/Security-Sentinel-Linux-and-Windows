# CodeQL Configuration Guide

## 🚨 Current Issue: Configuration Conflict

**Error**: "CodeQL analyses from advanced configurations cannot be processed when the default setup is enabled"

**Cause**: This repository uses an advanced CodeQL matrix configuration that conflicts with GitHub's default CodeQL setup.

> **🚀 Need a quick fix?** See [CODEQL_QUICK_FIX.md](CODEQL_QUICK_FIX.md) for a 5-minute solution guide.

## 🛠️ Resolution Options

### Option 1: Keep Custom Advanced Configuration (Recommended)

The current setup provides more comprehensive analysis with:
- ✅ Multi-language support (JavaScript, C++)
- ✅ Custom build steps for C++
- ✅ Integration with security scanning workflow
- ✅ Better control over analysis parameters

**Steps to resolve**:

#### 🔧 Step-by-Step GitHub UI Instructions

1. **Navigate to Repository Settings**
   - Go to your repository: `https://github.com/GizzZmo/Security-Sentinel`
   - Click the **"Settings"** tab (far right in the repository menu)

2. **Access Security Settings**
   - In the left sidebar, click **"Security"** (under "Security" section)
   - Then click **"Code scanning"**

3. **Disable Default Setup**
   - Look for a section titled **"Default setup"** or **"CodeQL analysis"**
   - You should see an entry showing "CodeQL" with a status of "Active" or "Enabled"
   - Click the **"..."** (three dots) or **"Configure"** button next to it
   - Select **"Remove"**, **"Disable"**, or **"Turn off"**

4. **Confirm Changes**
   - Confirm the removal when prompted
   - The default setup should now show as "Disabled" or be removed entirely

5. **Verify Advanced Configuration**
   - Your custom workflow in `.github/workflows/security.yml` will continue to work
   - The next push or PR will trigger the advanced configuration without conflicts
#### 🔍 Alternative Access Methods

**If you can't find "Code scanning" in Security settings:**

1. **Direct URL Method**:
   - Go directly to: `https://github.com/GizzZmo/Security-Sentinel/settings/security_analysis`
   - Look for the "Code scanning" section on this page

2. **Repository Actions Tab Method**:
   - Go to the **"Actions"** tab in your repository
   - Look for workflows with names like "CodeQL" or "github-code-scanning/codeql"
   - These indicate the default setup is active

3. **Security Tab Method**:
   - Go to the **"Security"** tab in your repository
   - Click **"Code scanning alerts"**
   - Look for a **"Set up code scanning"** or **"Configure"** button

#### ⚠️ Important Notes

- **Backup Recommendation**: Before making changes, note down your current settings
- **Timing**: Changes may take a few minutes to take effect
- **Verification**: After disabling, check that new workflow runs complete successfully
- **Rollback**: You can re-enable default setup later if needed

### Option 2: Use Default Setup (Simplified)

If you prefer GitHub's default setup:
1. Remove or comment out the `codeql-analysis` job from `.github/workflows/security.yml` (lines 55-109)
2. Keep the default CodeQL setup enabled in repository settings

**Trade-offs of Default Setup:**
- ✅ Simpler configuration
- ✅ Automatically maintained by GitHub
- ❌ Less control over build process
- ❌ May miss C++ custom build requirements
- ❌ Cannot customize analysis parameters

## 📝 Current Configuration Details

### Custom Matrix Configuration (security.yml)
```yaml
strategy:
  fail-fast: false
  matrix:
    language: ['javascript', 'cpp']
```

This provides:
- **JavaScript Analysis**: Web interface components, React/TypeScript code
- **C++ Analysis**: Native application security scanning with custom build
- **Manual C++ Build**: Ensures proper compilation context for analysis

### Additional Security Tools Integration
The current workflow also includes:
- **Semgrep**: Static analysis with SARIF upload (ci-cpp.yml)
- **Dependency Scanning**: npm audit with vulnerability reporting
- **Secret Scanning**: GitLeaks + TruffleHog for credential detection
- **License Compliance**: Automated license checking and reporting

## 🔍 Verification Steps

After disabling default setup:

1. **Re-run the Security Workflow**:
   - Go to **Actions** tab
   - Find the "🔐 Security Scanning" workflow
   - Click **"Run workflow"** to test manually

2. **Check Security Tab**:
   - Go to **Security** → **Code scanning**
   - Verify both JavaScript and C++ analyses complete successfully
   - Look for results from both language scans

3. **Monitor Workflow Logs**:
   - Check that the error message no longer appears
   - Verify both matrix jobs (JavaScript and C++) complete
   - Confirm SARIF files upload successfully

## 🔧 Troubleshooting

### Still Getting the Error?

1. **Clear Browser Cache**: Clear your browser cache and try again
2. **Wait for Propagation**: GitHub settings changes can take 5-10 minutes to propagate
3. **Check Multiple Locations**: Ensure all default setups are disabled:
   - Repository Settings → Security → Code scanning
   - Repository Settings → Security → Security analysis
   - Organization settings (if applicable)

### Permission Issues

If you can't access the settings:
- Ensure you have **Admin** or **Write** permissions on the repository
- Contact the repository owner to make the changes
- Check if the repository is part of an organization with restricted settings

### Workflow Still Failing?

1. **Check Workflow Permissions**:
   - Go to Settings → Actions → General
   - Ensure "Read and write permissions" are enabled
   - Verify "Allow GitHub Actions to create and approve pull requests" if needed

2. **Review Security Settings**:
   - Settings → Security → Security analysis
   - Ensure required permissions are granted for code scanning

## 📞 Support

If you continue to experience issues:
1. **Check Workflow Logs**: Look for specific error messages in the failed job logs
2. **Verify Repository Permissions**: Ensure security-events write access is available
3. **Language Detection**: Confirm CodeQL correctly detects JavaScript and C++ files
4. **GitHub Status**: Check [GitHub Status](https://www.githubstatus.com/) for service issues

### Getting Help

- **GitHub Documentation**: [Code scanning setup](https://docs.github.com/en/code-security/code-scanning)
- **Community Support**: [GitHub Community Discussions](https://github.com/community/community)
- **Enterprise Support**: Contact GitHub Support if using GitHub Enterprise

---

**✅ Success Indicator**: When properly configured, you'll see CodeQL results for both JavaScript and C++ in your Security tab, with no configuration conflict errors in workflow logs.

**Note**: This configuration provides enterprise-grade security scanning. The advanced setup is recommended for comprehensive security coverage of this multi-language project.