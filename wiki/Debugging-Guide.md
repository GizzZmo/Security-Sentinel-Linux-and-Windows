# Debugging Guide

Comprehensive guide for troubleshooting and debugging Security Sentinel issues.

## 🔍 Overview

This guide provides systematic approaches to diagnosing and resolving issues with Security Sentinel. Whether you're experiencing installation problems, performance issues, or unexpected behavior, this guide will help you identify and fix the problem.

## 🚨 Quick Troubleshooting

### Common Quick Fixes

#### 1. Restart as Administrator
Many issues can be resolved by ensuring Security Sentinel runs with proper privileges:
```bash
# Windows Command Prompt (Run as Administrator)
cd "C:\Path\To\SecuritySentinel"
SecuritySentinel.exe

# PowerShell (Run as Administrator)
Set-Location "C:\Path\To\SecuritySentinel"
.\SecuritySentinel.exe
```

#### 2. Check API Connectivity
Verify Gemini AI API connection:
```bash
# Test API key validity
curl -H "Authorization: Bearer YOUR_API_KEY" ^
  "https://generativelanguage.googleapis.com/v1beta/models"

# Or use the built-in test
SecuritySentinel.exe --test-api
```

#### 3. Validate Configuration
Check configuration file syntax:
```bash
# Test configuration
SecuritySentinel.exe --validate-config

# Or manually check config.ini
notepad config.ini
```

#### 4. Reset to Defaults
Reset configuration to default values:
```bash
# Backup current config
copy config.ini config.ini.backup

# Generate default config
SecuritySentinel.exe --generate-config

# Or delete config.ini to use built-in defaults
del config.ini
```

## 🔧 Systematic Debugging Process

### Step 1: Identify the Problem Category

#### Installation Issues
- Application won't start
- Missing dependencies
- Permission errors
- Installation corruption

#### Runtime Issues
- Application crashes
- Performance problems
- Feature not working
- Unexpected behavior

#### Configuration Issues
- API connection failures
- Settings not taking effect
- File permission problems
- Network connectivity issues

#### Network/Monitoring Issues
- No network data displayed
- Missing processes
- Incomplete system information
- Monitoring not working

### Step 2: Gather System Information

#### System Details
```bash
# System information
systeminfo

# Windows version
winver

# Installed programs
wmic product get name,version

# Running services
sc query state= all
```

#### Application Information
```bash
# Check if running
tasklist | findstr SecuritySentinel

# Check file integrity
dir SecuritySentinel.exe
certutil -hashfile SecuritySentinel.exe SHA256

# Check permissions
icacls SecuritySentinel.exe
```

#### Network Status
```bash
# Network connectivity
ping google.com
ping generativelanguage.googleapis.com

# Firewall status
netsh advfirewall show allprofiles

# Network adapters
ipconfig /all
```

## 🔍 Diagnostic Tools

### Built-in Diagnostics

#### Configuration Validation
```bash
# Validate configuration file
SecuritySentinel.exe --validate-config

# Test API connectivity
SecuritySentinel.exe --test-api

# Check system requirements
SecuritySentinel.exe --system-check

# Verify file integrity
SecuritySentinel.exe --integrity-check
```

#### Debug Mode
Enable detailed logging for troubleshooting:
```ini
[logging]
debug_mode=true
log_level=DEBUG
log_file=debug.log
console_output=true
```

#### Verbose Output
```bash
# Run with verbose logging
SecuritySentinel.exe --verbose

# Or with specific debug categories
SecuritySentinel.exe --debug=network,ai,security
```

### Log Analysis

#### Log File Locations
```bash
# Default log location
.\security_sentinel.log

# Debug log (when enabled)
.\debug.log

# System event logs
eventvwr.msc
```

#### Understanding Log Levels
- **DEBUG**: Detailed debug information
- **INFO**: General information messages
- **WARN**: Warning messages (non-critical issues)
- **ERROR**: Error messages (critical issues)
- **FATAL**: Fatal errors (application termination)

#### Common Log Patterns
```
# Successful startup
INFO: Security Sentinel initialized successfully
INFO: AI client connected to Gemini API
INFO: Network monitoring started

# API connection issues
ERROR: Failed to connect to Gemini API
ERROR: Invalid API key or quota exceeded
WARN: API response timeout, retrying...

# Permission issues
ERROR: Access denied reading process list
ERROR: Insufficient privileges for network monitoring
WARN: Running without administrator privileges

# Network issues
ERROR: Network interface not found
WARN: Firewall blocking network requests
INFO: Network monitoring limited due to restrictions
```

## 🐛 Common Issues and Solutions

### Installation and Startup Issues

#### "Application Failed to Start"
**Symptoms**: SecuritySentinel.exe won't launch
**Solutions**:
1. Check system requirements: Windows 11, x64 architecture
2. Install Visual C++ Redistributables
3. Run as Administrator
4. Check antivirus exclusions
5. Verify file integrity

#### "DLL Missing" Errors
**Symptoms**: Error messages about missing DLL files
**Solutions**:
```bash
# Install Visual C++ Redistributables
# Download from Microsoft official site

# Check for Windows Updates
sfc /scannow
dism /online /cleanup-image /restorehealth

# Repair .NET Framework if needed
```

#### Permission Denied Errors
**Symptoms**: Access denied messages, limited functionality
**Solutions**:
1. Run as Administrator
2. Check Windows User Account Control (UAC) settings
3. Verify file permissions: `icacls SecuritySentinel.exe`
4. Add antivirus exclusions
5. Check group policy restrictions

### API and Network Issues

#### "AI Assistant Not Responding"
**Symptoms**: AI features don't work, no responses
**Solutions**:
1. Verify API key in config.ini
2. Check internet connectivity
3. Test API directly: `curl` command
4. Check firewall settings
5. Verify API quota and billing

#### "Network Monitoring Limited"
**Symptoms**: Missing network data, incomplete connections
**Solutions**:
1. Run as Administrator
2. Check Windows Firewall settings
3. Verify network adapter status
4. Check group policy network restrictions
5. Ensure WMI service is running

#### "Failed to Load Configuration"
**Symptoms**: Settings not loading, using defaults
**Solutions**:
```bash
# Check file existence and permissions
dir config.ini
icacls config.ini

# Validate syntax
SecuritySentinel.exe --validate-config

# Generate new default config
SecuritySentinel.exe --generate-config
```

### Performance Issues

#### High CPU Usage
**Symptoms**: SecuritySentinel consuming excessive CPU
**Solutions**:
1. Adjust monitoring intervals in config.ini
2. Disable unnecessary monitoring features
3. Check for background scans
4. Update to latest version
5. Adjust thread pool size

#### High Memory Usage  
**Symptoms**: Excessive memory consumption
**Solutions**:
```ini
[performance]
max_memory_usage=256          # Limit memory usage
max_events=5000               # Reduce event history
enable_caching=false          # Disable caching if needed
```

#### Slow Response Times
**Symptoms**: UI sluggish, delayed updates
**Solutions**:
1. Increase update intervals
2. Reduce displayed data points
3. Check disk space availability
4. Disable debug logging
5. Close other resource-intensive applications

### Feature-Specific Issues

#### Process Monitoring Not Working
**Debugging Steps**:
```bash
# Check privileges
whoami /priv

# Test process access
tasklist /v

# Check Windows services
sc query winmgmt
sc query eventlog
```

#### Network Monitoring Incomplete
**Debugging Steps**:
```bash
# Check network interfaces
ipconfig
netstat -an

# Verify WMI functionality
wmic process list brief
wmic path win32_networkadapter get name,index
```

#### Threat Protection Disabled
**Debugging Steps**:
1. Check Windows Defender integration
2. Verify firewall access
3. Check group policy settings
4. Validate threat database updates

## 📊 Performance Profiling

### Monitoring System Impact

#### Resource Usage Monitoring
```bash
# Monitor Security Sentinel resource usage
typeperf "\Process(SecuritySentinel)\% Processor Time" -si 5

# Memory usage
typeperf "\Process(SecuritySentinel)\Working Set" -si 5

# Disk I/O
typeperf "\Process(SecuritySentinel)\IO Read Bytes/sec" -si 5
```

#### Performance Tuning
```ini
[performance]
max_memory_usage=128           # MB, adjust based on system RAM
cpu_usage_threshold=50         # %, alert threshold
update_interval=10             # seconds, reduce for better performance
thread_pool_size=2             # threads, adjust based on CPU cores
enable_caching=true            # improve response times
```

### Optimization Strategies

#### For Low-End Systems
```ini
[optimization]
performance_mode=low_resource
update_interval=30
max_events=1000
enable_caching=false
background_priority=low
```

#### For High-End Systems
```ini
[optimization]  
performance_mode=high_performance
update_interval=1
max_events=50000
enable_caching=true
background_priority=normal
```

## 🔬 Advanced Debugging

### Debug Builds

#### Compiling Debug Version
```bash
# CMake debug build
mkdir build-debug && cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug

# Run debug version
Debug\SecuritySentinel.exe --debug
```

#### Debug Symbols and Stack Traces
Enable debugging symbols for detailed crash analysis:
```bash
# Generate minidumps on crash
set SECURITY_SENTINEL_CRASH_DUMPS=1

# Enable stack traces
set SECURITY_SENTINEL_STACK_TRACE=1
```

### Memory Debugging

#### Detecting Memory Leaks
```bash
# Use Visual Studio Diagnostic Tools
# Or Application Verifier for detailed analysis
appverif.exe

# Check for handle leaks
handle.exe -p SecuritySentinel
```

#### Performance Profiling
```bash
# Use Windows Performance Profiler (WPP)
# Or Visual Studio Performance Profiler
# Monitor CPU, memory, and I/O usage patterns
```

### Network Debugging

#### Packet Capture Analysis
```bash
# Use Wireshark to capture API traffic
# Filter by: host generativelanguage.googleapis.com

# Or use built-in Windows tools
netsh trace start capture=yes
# Reproduce issue
netsh trace stop
```

#### API Debugging
```bash
# Enable HTTP request logging
set SECURITY_SENTINEL_HTTP_DEBUG=1

# Monitor API requests and responses
# Check for proper headers, authentication, and payload
```

## 📝 Creating Bug Reports

### Information to Include

#### System Information
- Windows version and build number
- Security Sentinel version
- Hardware specifications
- Antivirus software
- Network configuration

#### Problem Description
- Clear description of the issue
- Steps to reproduce the problem
- Expected vs. actual behavior
- Screenshots or error messages
- Frequency and patterns

#### Log Files
```bash
# Collect relevant logs
copy security_sentinel.log bug_report\
copy config.ini bug_report\
copy debug.log bug_report\

# System event logs (if relevant)
wevtutil qe System /f:text > bug_report\system_events.txt
```

#### Configuration Files
Include sanitized configuration (remove API keys):
```ini
[gemini]
api_key=***REDACTED***
model=gemini-2.5-flash

[monitoring]
enabled=true
update_interval=5
```

### Bug Report Template

```markdown
## Bug Report

### Environment
- **OS**: Windows 11 Build 22H2
- **Security Sentinel Version**: 1.1.0  
- **Hardware**: Intel i7, 16GB RAM
- **Antivirus**: Windows Defender

### Problem Description
Clear description of what went wrong...

### Steps to Reproduce
1. Step one
2. Step two
3. Step three

### Expected Behavior
What should have happened...

### Actual Behavior
What actually happened...

### Logs
```
[Include relevant log entries]
```

### Additional Context
Any other relevant information...
```

## 🆘 Getting Help

### Support Channels

#### Community Support
- **GitHub Discussions**: General questions and community help
- **GitHub Issues**: Bug reports and feature requests
- **Wiki Documentation**: Comprehensive guides and tutorials

#### Self-Help Resources
- **Built-in Help**: Press F1 or use `--help` parameter
- **Configuration Validation**: Use `--validate-config`
- **System Check**: Use `--system-check`
- **Log Analysis**: Review log files for error patterns

#### Professional Support
- **Enterprise Support**: Contact for enterprise-level assistance
- **Consulting Services**: Professional configuration and deployment help
- **Training**: Security monitoring best practices training

### Before Asking for Help

1. **Search Existing Issues**: Check if your problem has been reported
2. **Try Quick Fixes**: Attempt the common solutions first
3. **Gather Information**: Collect logs, configuration, and system details
4. **Reproduce the Issue**: Ensure you can consistently reproduce the problem
5. **Prepare Details**: Have clear description and steps ready

## 🔄 Continuous Improvement

### Debug Information Collection

#### Automated Diagnostics
```bash
# Generate diagnostic report
SecuritySentinel.exe --diagnostic-report

# Includes:
# - System information
# - Configuration analysis
# - Log file analysis
# - Performance metrics
# - Network connectivity tests
```

#### Telemetry and Analytics
Consider enabling anonymous telemetry to help improve the product:
```ini
[telemetry]
enabled=true
anonymous_usage_stats=true
crash_reporting=true
performance_data=true
```

### Feedback and Improvement
- **Feature Requests**: Suggest improvements based on debugging experience
- **Documentation Updates**: Help improve debugging documentation
- **Tool Contributions**: Contribute debugging utilities and scripts
- **Best Practices**: Share effective debugging techniques

This comprehensive debugging guide should help you resolve most issues with Security Sentinel. Remember to always backup your configuration before making changes, and don't hesitate to seek community support when needed.