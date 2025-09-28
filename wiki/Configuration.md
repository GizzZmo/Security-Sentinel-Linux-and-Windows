# Configuration

Complete guide to configuring Security Sentinel for optimal performance and security monitoring.

## 📋 Overview

Security Sentinel uses configuration files to customize its behavior, security monitoring parameters, AI integration, and user interface settings. This guide covers all configuration options for both C++ and web interfaces.

## 🔧 Configuration Files

### C++ Application Configuration

#### `config.ini` Format

```ini
# Security Sentinel Configuration File

[gemini]
api_key=YOUR_API_KEY_HERE
model=gemini-2.5-flash
max_tokens=1000
temperature=0.7
timeout=30

[monitoring]
enabled=true
update_interval=5
log_level=INFO
max_events=10000
process_monitoring=true
network_monitoring=true
resource_monitoring=true

[network]
monitor_enabled=true
block_suspicious=true
whitelist_ips=192.168.1.0/24,10.0.0.0/8,127.0.0.1
scan_detection_threshold=5
ddos_detection_threshold=100
connection_timeout=30

[ui]
color_scheme=dark
refresh_rate=1000
show_advanced=false
console_width=120
console_height=30

[security]
enable_integrity_check=true
enable_signature_verification=true
baseline_file=integrity.baseline
quarantine_threats=true
auto_block_ips=true

[performance]
max_memory_usage=512
cpu_usage_threshold=80
disk_usage_threshold=90
performance_logging=true

[logging]
log_file=security_sentinel.log
max_log_size=100
rotate_logs=true
log_retention_days=30
debug_mode=false
```

### Web Interface Configuration

#### `.env.local` Format

```env
# Gemini AI Configuration
VITE_GEMINI_API_KEY=your_api_key_here
VITE_GEMINI_MODEL=gemini-2.5-flash
VITE_GEMINI_MAX_TOKENS=1000
VITE_GEMINI_TEMPERATURE=0.7

# Application Settings
VITE_APP_TITLE=Security Sentinel
VITE_UPDATE_INTERVAL=5000
VITE_MAX_EVENTS=1000
VITE_DEBUG_MODE=false

# UI Configuration
VITE_THEME=dark
VITE_CHART_UPDATE_INTERVAL=1000
VITE_SHOW_ADVANCED_FEATURES=false
VITE_NOTIFICATION_TIMEOUT=5000
```

## ⚙️ Configuration Sections

### Gemini AI Settings

#### API Configuration
```ini
[gemini]
api_key=YOUR_API_KEY_HERE          # Your Google Gemini API key (required)
model=gemini-2.5-flash             # AI model to use
max_tokens=1000                    # Maximum response length
temperature=0.7                    # Response creativity (0.0-1.0)
timeout=30                         # API request timeout (seconds)
retry_attempts=3                   # Number of retry attempts
retry_delay=1                      # Delay between retries (seconds)
```

**Model Options:**
- `gemini-2.5-flash`: Fast, efficient (recommended)
- `gemini-pro`: More sophisticated reasoning
- `gemini-pro-vision`: Image analysis capabilities

**Temperature Guidelines:**
- `0.1-0.3`: Focused, deterministic responses
- `0.4-0.7`: Balanced (recommended)
- `0.8-1.0`: Creative but less consistent

### Monitoring Configuration

#### System Monitoring
```ini
[monitoring]
enabled=true                       # Enable system monitoring
update_interval=5                  # Update frequency (seconds)
log_level=INFO                     # Logging level (DEBUG, INFO, WARN, ERROR)
max_events=10000                   # Maximum events to store
process_monitoring=true            # Monitor running processes
network_monitoring=true            # Monitor network connections
resource_monitoring=true           # Monitor system resources
startup_scan=true                  # Perform startup system scan
```

**Log Levels:**
- `DEBUG`: Detailed debug information
- `INFO`: General information messages
- `WARN`: Warning messages
- `ERROR`: Error messages only

#### Process Monitoring
```ini
[processes]
whitelist_processes=explorer.exe,winlogon.exe,csrss.exe
blacklist_processes=malware.exe,trojan.exe
monitor_new_processes=true
check_digital_signatures=true
scan_process_memory=false
alert_on_suspicious=true
```

### Network Security Settings

#### Network Monitoring
```ini
[network]
monitor_enabled=true               # Enable network monitoring
block_suspicious=true              # Auto-block suspicious IPs
whitelist_ips=192.168.1.0/24      # Trusted IP ranges
scan_detection_threshold=5         # Port scan detection threshold
ddos_detection_threshold=100       # DDoS detection threshold
connection_timeout=30              # Connection timeout (seconds)
monitor_dns_queries=true           # Monitor DNS requests
track_bandwidth_usage=true         # Track bandwidth consumption
```

**IP Range Formats:**
- Single IP: `192.168.1.100`
- CIDR Range: `192.168.1.0/24`
- Multiple ranges: `192.168.1.0/24,10.0.0.0/8,127.0.0.1`

#### Firewall Integration
```ini
[firewall]
integrate_windows_firewall=true
auto_create_rules=true
rule_prefix=SecuritySentinel_
allow_user_override=true
log_blocked_connections=true
```

### User Interface Configuration

#### Console Interface (C++)
```ini
[ui]
color_scheme=dark                  # UI color scheme (dark/light)
refresh_rate=1000                  # UI refresh rate (milliseconds)
show_advanced=false                # Show advanced features
console_width=120                  # Console width (characters)
console_height=30                  # Console height (lines)
enable_sound_alerts=true           # Sound notifications
```

#### Web Interface
```env
VITE_THEME=dark                    # UI theme (dark/light)
VITE_CHART_UPDATE_INTERVAL=1000    # Chart refresh rate (ms)
VITE_SHOW_ADVANCED_FEATURES=false # Advanced features visibility
VITE_NOTIFICATION_TIMEOUT=5000     # Notification display time (ms)
VITE_AUTO_REFRESH=true             # Auto-refresh dashboard
```

### Security Configuration

#### Integrity Protection
```ini
[security]
enable_integrity_check=true        # Enable file integrity monitoring
enable_signature_verification=true # Verify digital signatures
baseline_file=integrity.baseline   # Integrity baseline file
quarantine_threats=true            # Quarantine detected threats
auto_block_ips=true                # Automatically block threat IPs
self_protection=true               # Enable self-protection features
```

#### Threat Response
```ini
[threats]
auto_response_enabled=true         # Enable automatic threat response
response_sensitivity=medium        # Response sensitivity (low/medium/high)
quarantine_directory=quarantine/   # Quarantine directory
threat_log_file=threats.log        # Threat activity log
alert_threshold=medium             # Alert threshold
notification_methods=popup,log     # Notification methods
```

### Performance Settings

#### Resource Management
```ini
[performance]
max_memory_usage=512               # Maximum memory usage (MB)
cpu_usage_threshold=80             # CPU usage alert threshold (%)
disk_usage_threshold=90            # Disk usage alert threshold (%)
performance_logging=true           # Enable performance logging
background_priority=normal         # Process priority
thread_pool_size=4                 # Worker thread pool size
```

#### Optimization
```ini
[optimization]
enable_caching=true               # Enable data caching
cache_size_mb=64                  # Cache size (MB)
optimize_for=performance          # Optimization target (performance/memory)
lazy_loading=true                 # Enable lazy loading
compress_logs=true                # Compress log files
cleanup_interval=24               # Cleanup interval (hours)
```

## 🔄 Configuration Management

### Loading Configuration

#### C++ Application
```cpp
// Configuration is automatically loaded from:
// 1. config.ini (current directory)
// 2. ~/.security-sentinel/config.ini (user directory)
// 3. Environment variables (SECURITY_SENTINEL_*)

// Custom configuration file
set SECURITY_SENTINEL_CONFIG=C:\custom\path\config.ini
```

#### Web Interface
```javascript
// Configuration loaded from environment variables
// Create .env.local file in project root
// Variables prefixed with VITE_ are available in browser
```

### Environment Variables

#### Override Configuration
```bash
# Windows (Command Prompt)
set GEMINI_API_KEY=your_api_key_here
set SECURITY_SENTINEL_DEBUG=1
set SECURITY_SENTINEL_LOG_LEVEL=DEBUG

# Windows (PowerShell)
$env:GEMINI_API_KEY="your_api_key_here"
$env:SECURITY_SENTINEL_DEBUG="1"

# Linux/WSL
export GEMINI_API_KEY=your_api_key_here
export SECURITY_SENTINEL_DEBUG=1
```

### Configuration Validation

#### Automatic Validation
Security Sentinel validates configuration on startup:
- **Required Settings**: API keys, essential parameters
- **Value Ranges**: Numeric values within acceptable ranges  
- **File Paths**: Accessibility of specified files and directories
- **Network Settings**: Validity of IP ranges and network parameters

#### Error Handling
- **Missing Config**: Uses default values with warnings
- **Invalid Values**: Falls back to safe defaults
- **Syntax Errors**: Reports specific line numbers and issues
- **Permission Issues**: Guidance for resolving access problems

## 🏆 Best Practices

### Security Configuration

#### API Key Management
1. **Secure Storage**: Store API keys in secure configuration files
2. **Environment Variables**: Use environment variables for sensitive data
3. **Access Control**: Restrict access to configuration files
4. **Regular Rotation**: Regularly rotate API keys and credentials

#### Network Security
1. **Whitelist Approach**: Use IP whitelists rather than blacklists when possible
2. **Least Privilege**: Configure minimal necessary permissions
3. **Regular Updates**: Keep security configurations updated
4. **Monitoring**: Enable comprehensive monitoring and logging

### Performance Optimization

#### Resource Management
1. **Memory Limits**: Set appropriate memory usage limits
2. **CPU Thresholds**: Configure CPU usage thresholds for alerts
3. **Disk Management**: Monitor and manage disk usage
4. **Background Processing**: Optimize background task priorities

#### Update Intervals
1. **Balance**: Balance monitoring frequency with performance impact
2. **Critical Systems**: Use shorter intervals for critical monitoring
3. **Resource Usage**: Adjust based on system capabilities
4. **User Experience**: Consider impact on user interface responsiveness

## 🔍 Troubleshooting Configuration

### Common Issues

#### Configuration File Problems
```bash
# Check if configuration file exists
dir config.ini

# Verify file permissions
icacls config.ini

# Test configuration syntax
SecuritySentinel.exe --test-config
```

#### API Key Issues
```bash
# Test API connectivity
curl -H "Authorization: Bearer YOUR_API_KEY" https://generativelanguage.googleapis.com/v1beta/models
```

#### Network Configuration
```bash
# Test network connectivity
ping google.com
netstat -an | findstr :443
```

### Diagnostic Tools

#### Configuration Validation
```bash
# C++ Application
SecuritySentinel.exe --validate-config

# Web Interface  
npm run config:validate
```

#### Debug Mode
```ini
[logging]
debug_mode=true
log_level=DEBUG
```

### Getting Help

#### Documentation Resources
- **Configuration Examples**: Complete examples in `docs/` directory
- **Default Values**: Reference documentation for all default settings
- **Migration Guides**: Guidance for upgrading configurations

#### Support Channels
- **GitHub Issues**: Report configuration problems
- **Community Forum**: Ask configuration questions
- **Documentation**: Comprehensive configuration reference

## 📈 Advanced Configuration

### Custom Monitoring Rules

#### Process Rules
```ini
[process_rules]
rule1=name:suspicious.exe,action:block,alert:high
rule2=path:*\temp\*,action:monitor,alert:medium
rule3=signature:invalid,action:quarantine,alert:high
```

#### Network Rules
```ini
[network_rules]
rule1=port:1337,action:block,alert:high
rule2=protocol:http,destination:malware.com,action:block
rule3=bandwidth:>100MB/min,action:alert,priority:high
```

### Integration Configuration

#### External Tools
```ini
[integrations]
siem_enabled=true
siem_endpoint=https://your-siem.com/api
siem_api_key=your_siem_key
webhook_urls=https://alerts.company.com/webhook
email_alerts=admin@company.com
```

### Enterprise Features
```ini
[enterprise]
central_logging=true
policy_enforcement=strict
compliance_mode=pci_dss
audit_logging=comprehensive
```

This configuration guide provides comprehensive coverage of all Security Sentinel configuration options. For specific use cases or advanced configurations, refer to the relevant sections or contact support for assistance.