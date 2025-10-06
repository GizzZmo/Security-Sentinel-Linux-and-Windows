# ⚠️ CodeQL Error: "Advanced configurations cannot be processed when default setup is enabled"

## 🚨 You're seeing this because:
Your repository has **BOTH** enabled:
1. ✅ Custom CodeQL workflow (the good one!)
2. ❌ Default GitHub Code Scanning (conflicts!)

## ⚡ Quick Fix (2 minutes):

### Step 1: Click this link
👉 **https://github.com/GizzZmo/Security-Sentinel/settings/security_analysis**

### Step 2: Find "Default setup"
Look for a section called "Code scanning" → "Default setup" showing as "Active" or "Enabled"

### Step 3: Disable it
Click the **"..."** menu → Select **"Remove"** or **"Disable"**

### Step 4: Re-run the workflow
Go back to the [Actions tab](https://github.com/GizzZmo/Security-Sentinel/actions) and click "Re-run all jobs"

## ✅ That's it!
Your workflow should now complete successfully.

---

## 📚 More Help

- **Detailed Guide:** [CODEQL_QUICK_FIX.md](CODEQL_QUICK_FIX.md)
- **Full Documentation:** [CODEQL_SETUP.md](CODEQL_SETUP.md)
- **Can't find it?** See [troubleshooting section](CODEQL_QUICK_FIX.md#-still-having-issues)

## 💡 Why This Error?

GitHub doesn't allow **both** default setup AND custom workflow to run at the same time.

**Your custom workflow is better** because it:
- ✅ Analyzes both JavaScript AND C++ code
- ✅ Uses custom CMake build for accurate C++ analysis
- ✅ Provides more comprehensive security scanning

**Keep the custom workflow, disable the default setup.**

---

**Need permission?** Contact the repository owner: @GizzZmo

**Still stuck?** [Open an issue](https://github.com/GizzZmo/Security-Sentinel/issues/new) with your error message.
