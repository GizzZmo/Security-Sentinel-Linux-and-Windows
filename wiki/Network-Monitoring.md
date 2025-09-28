# Network Monitoring

Comprehensive guide to Security Sentinel's network monitoring and traffic analysis capabilities.

## 🌐 Overview

Security Sentinel provides real-time network monitoring that tracks connections, analyzes traffic patterns, and detects potential security threats. The network monitoring system integrates with Windows networking APIs to provide deep visibility into network activity while maintaining minimal system impact.

## 🚀 Getting Started

### Enabling Network Monitoring

#### C++ Application Configuration
```ini
[network]
monitor_enabled=true               # Enable network monitoring
block_suspicious=true              # Auto-block suspicious IPs
connection_timeout=30              # Connection timeout (seconds)
monitor_dns_queries=true           # Monitor DNS requests
track_bandwidth_usage=true         # Track bandwidth consumption

[monitoring]
network_monitoring=true            # Enable network component
update_interval=5                  # Update frequency (seconds)
```

#### Web Interface Configuration
```env
VITE_NETWORK_MONITORING=true
VITE_NETWORK_UPDATE_INTERVAL=5000
VITE_SHOW_NETWORK_CHARTS=true
```

### Required Permissions

Network monitoring requires elevated privileges for full functionality:

```bash
# Run as Administrator for complete network access
# Right-click -> "Run as administrator"
SecuritySentinel.exe

# Or from elevated Command Prompt
runas /user:Administrator SecuritySentinel.exe
```

## 📊 Network Monitoring Features

### Real-time Connection Tracking

#### Active Connections Display
```
NETWORK CONNECTIONS (23 Active)
┌─────────────────┬─────────┬──────────┬─────────────┬──────────┐
│ Remote Address  │ Port    │ Protocol │ Process     │ Status   │
├─────────────────┼─────────┼──────────┼─────────────┼──────────┤
│ 142.250.191.78  │ 443     │ HTTPS    │ chrome.exe  │ ESTAB    │
│ 52.96.7.33      │ 993     │ IMAPS    │ outlook.exe │ ESTAB    │
│ 192.168.1.100   │ 3389    │ RDP      │ mstsc.exe   │ ESTAB    │
│ 8.8.8.8         │ 53      │ DNS      │ chrome.exe  │ ESTAB    │
└─────────────────┴─────────┴──────────┴─────────────┴──────────┘
```

#### Connection States
- **ESTABLISHED**: Active, established connection
- **LISTENING**: Process listening for incoming connections
- **TIME_WAIT**: Connection in closing state
- **SYN_SENT**: Connection attempt in progress
- **CLOSE_WAIT**: Connection being closed

#### Protocol Analysis
- **TCP**: Transmission Control Protocol connections
- **UDP**: User Datagram Protocol connections
- **ICMP**: Internet Control Message Protocol
- **HTTP/HTTPS**: Web traffic analysis
- **DNS**: Domain Name System queries
- **FTP/FTPS**: File transfer protocols
- **SMTP/POP3/IMAP**: Email protocols

### Traffic Pattern Analysis

#### Bandwidth Monitoring
```
BANDWIDTH USAGE (Last 5 Minutes)
├─ Inbound:  1.2 MB/s  ████████████░░░░
├─ Outbound: 0.8 MB/s  ████████░░░░░░░░  
├─ Total:    2.0 MB/s  ████████████████
└─ Peak:     3.4 MB/s  (2 minutes ago)

TOP BANDWIDTH CONSUMERS
┌─────────────────────┬─────────┬─────────┬──────────┐
│ Process             │ Inbound │ Outbound│ Total    │
├─────────────────────┼─────────┼─────────┼──────────┤
│ chrome.exe          │ 0.8 MB/s│ 0.3 MB/s│ 1.1 MB/s │
│ SecuritySentinel    │ 0.1 MB/s│ 0.1 MB/s│ 0.2 MB/s │
│ outlook.exe         │ 0.3 MB/s│ 0.4 MB/s│ 0.7 MB/s │
└─────────────────────┴─────────┴─────────┴──────────┘
```

#### Geographic Analysis
```
CONNECTION ORIGINS
├─ United States:     15 connections (65%)
├─ United Kingdom:     3 connections (13%)
├─ Germany:           2 connections (9%)
├─ Japan:             2 connections (9%)
└─ Other:             1 connection  (4%)

SUSPICIOUS LOCATIONS
⚠️  Russian Federation: 1 connection (Port scan detected)
⚠️  Unknown/TOR:        1 connection (Anonymized traffic)
```

### Port and Service Detection

#### Common Ports Monitoring
```
PORT ACTIVITY SUMMARY
┌─────────┬─────────────────────┬─────────┬──────────┐
│ Port    │ Service             │ Count   │ Status   │
├─────────┼─────────────────────┼─────────┼──────────┤
│ 80      │ HTTP                │ 5       │ Normal   │
│ 443     │ HTTPS               │ 12      │ Normal   │
│ 993     │ IMAPS               │ 2       │ Normal   │
│ 3389    │ RDP                 │ 1       │ Normal   │
│ 1337    │ Unknown             │ 1       │ ⚠️ Suspicious │
└─────────┴─────────────────────┴─────────┴──────────┘
```

#### Service Identification
- **Web Services**: HTTP (80), HTTPS (443)
- **Email Services**: SMTP (25/587), POP3 (110/995), IMAP (143/993)
- **Remote Access**: SSH (22), Telnet (23), RDP (3389)
- **File Transfer**: FTP (21), SFTP (22), FTPS (990)
- **DNS Services**: DNS (53)
- **Database Services**: MySQL (3306), PostgreSQL (5432)

## 🛡️ Threat Detection

### Automated Threat Detection

#### Port Scan Detection
```ini
[network]
scan_detection_threshold=5         # Trigger after 5 rapid connections
scan_detection_window=60           # Within 60 seconds
auto_block_scanners=true           # Automatically block detected scanners
```

**Detection Patterns**:
- **Horizontal Scan**: Same source connecting to multiple ports
- **Vertical Scan**: Multiple sources connecting to same port
- **Stealth Scan**: SYN scans, FIN scans, NULL scans
- **UDP Scan**: Rapid UDP probe attempts

#### DDoS Attack Detection
```ini
[network]
ddos_detection_threshold=100       # Trigger after 100 connections/minute
ddos_response_action=auto_block    # Automatically block source IPs
ddos_whitelist_local=true          # Don't block local network IPs
```

**Detection Criteria**:
- **Connection Rate**: Excessive connection attempts from single source
- **Bandwidth Spike**: Sudden massive increase in traffic
- **Resource Exhaustion**: High number of half-open connections
- **Protocol Floods**: SYN flood, UDP flood, ICMP flood

#### Suspicious Activity Patterns
```
THREAT DETECTION ALERTS
┌─────────────────────┬──────────────────┬─────────┬──────────┐
│ Timestamp           │ Threat Type      │ Source  │ Action   │
├─────────────────────┼──────────────────┼─────────┼──────────┤
│ 2024-01-15 14:32:15 │ Port Scan        │ 1.2.3.4 │ Blocked  │
│ 2024-01-15 14:30:45 │ Brute Force      │ 5.6.7.8 │ Monitored│
│ 2024-01-15 14:28:10 │ DNS Tunneling    │ Local   │ Alert    │
└─────────────────────┴──────────────────┴─────────┴──────────┘
```

### IP Reputation and Blacklisting

#### Automatic IP Blocking
```ini
[network]
auto_block_ips=true                # Enable automatic IP blocking
block_duration=3600                # Block for 1 hour (seconds)
permanent_block_threshold=5        # Permanent block after 5 violations
whitelist_ips=192.168.1.0/24      # Never block these IPs
```

#### Threat Intelligence Integration
- **Malware Communication**: Block known C&C servers
- **Botnet Detection**: Identify botnet communication patterns  
- **Tor Exit Nodes**: Monitor Tor network usage
- **VPN Detection**: Identify VPN and proxy connections

## 📊 Network Visualization

### C++ Console Interface

#### Connection Timeline
```
CONNECTION TIMELINE (Last 10 minutes)
14:30 |████████████████████████████████████████| 23 connections
14:31 |███████████████████████████████████████ | 22 connections  
14:32 |█████████████████████████████████████   | 20 connections
14:33 |██████████████████████████████████████  | 21 connections
14:34 |████████████████████████████████████████| 24 connections
14:35 |███████████████████████████████████████ | 22 connections
14:36 |██████████████████████████████████████  | 21 connections
14:37 |████████████████████████████████████████| 23 connections
14:38 |█████████████████████████████████████   | 20 connections
14:39 |████████████████████████████████████████| 25 connections
```

#### Protocol Distribution
```
PROTOCOL BREAKDOWN
HTTPS: ████████████████████████████ 70% (16 connections)
HTTP:  ██████████ 20% (5 connections)
DNS:   ████ 8% (2 connections)
Other: ██ 2% (1 connection)
```

### Web Interface Visualization

#### Interactive Network Map
- **Node-Link Diagram**: Visual representation of connections
- **Geographic Map**: World map showing connection locations  
- **Traffic Flow**: Animated data flow visualization
- **Connection Graph**: Real-time connection status graph

#### Charts and Analytics
- **Line Charts**: Traffic over time, connection counts
- **Pie Charts**: Protocol distribution, connection states
- **Bar Charts**: Top processes, bandwidth consumers
- **Heat Maps**: Activity patterns, threat locations

## 🔍 Deep Packet Analysis

### Protocol Analysis

#### HTTP/HTTPS Traffic
```
HTTP REQUEST ANALYSIS
┌─────────────────────┬─────────┬─────────┬──────────────┐
│ Domain              │ Method  │ Status  │ Process      │
├─────────────────────┼─────────┼─────────┼──────────────┤
│ google.com          │ GET     │ 200     │ chrome.exe   │
│ github.com          │ GET     │ 200     │ chrome.exe   │
│ malware-site.com    │ POST    │ 403     │ ⚠️ Blocked    │
└─────────────────────┴─────────┴─────────┴──────────────┘
```

#### DNS Query Monitoring
```
DNS QUERIES (Last 5 minutes)
┌─────────────────────┬─────────────────┬──────────────┐
│ Domain              │ Record Type     │ Response     │
├─────────────────────┼─────────────────┼──────────────┤
│ google.com          │ A               │ 142.250.191.78│
│ malware.evil        │ A               │ ⚠️ Blocked    │
│ suspicious.tor      │ A               │ ⚠️ Flagged    │
└─────────────────────┴─────────────────┴──────────────┘
```

### Content Filtering

#### URL Filtering
```ini
[network]
enable_url_filtering=true
block_malware_domains=true
block_adult_content=false
custom_blocklist=blocklist.txt
```

#### File Transfer Monitoring
- **Download Monitoring**: Track file downloads and sources
- **Upload Detection**: Monitor data exfiltration attempts  
- **File Type Analysis**: Analyze transferred file types
- **Malware Scanning**: Integration with antivirus for file scanning

## ⚙️ Configuration and Tuning

### Performance Optimization

#### Resource Management
```ini
[network]
max_connections_tracked=1000       # Maximum connections to track
connection_cache_size=256          # Connection cache size
update_interval=5                  # Update frequency (seconds)
enable_deep_inspection=false       # Disable for better performance
```

#### Memory Usage Control
```ini
[performance]
max_network_memory=128             # Maximum memory for network data (MB)
history_retention_minutes=60       # How long to keep connection history
cleanup_interval=300               # Cleanup unused data every 5 minutes
```

### Advanced Configuration

#### Custom Rules
```ini
[network_rules]
# Block all connections to port 1337
rule1=port:1337,action:block,alert:high

# Monitor all connections from specific IP
rule2=source:192.168.1.100,action:monitor,alert:medium  

# Alert on large data transfers
rule3=bandwidth:>50MB/min,action:alert,priority:high
```

#### Integration Settings
```ini
[integrations]
siem_integration=true              # Send data to SIEM
syslog_server=192.168.1.200        # Syslog server for events
webhook_url=https://alerts.company.com/network
email_alerts=admin@company.com
```

## 🔒 Security Best Practices

### Network Security Recommendations

#### Firewall Integration
1. **Windows Firewall**: Automatically create firewall rules for blocked IPs
2. **Third-party Firewalls**: Integration with enterprise firewalls
3. **Network Segmentation**: Monitor traffic between network segments
4. **VPN Monitoring**: Track VPN connections and usage

#### Monitoring Best Practices
1. **Baseline Establishment**: Learn normal network patterns
2. **Regular Review**: Analyze network reports regularly
3. **Incident Response**: Develop procedures for network security events
4. **Documentation**: Maintain records of network security incidents

### Compliance and Auditing

#### Logging and Retention
```ini
[logging]
network_log_file=network_activity.log
log_level=INFO                     # INFO, WARN, ERROR
max_log_size=100                   # MB
log_rotation=daily
retention_days=90
```

#### Audit Trail
- **Connection Logs**: Complete record of network connections
- **Security Events**: Log all security-related network events  
- **Configuration Changes**: Track changes to network monitoring settings
- **Access Logs**: Monitor who accesses network monitoring data

## 🚨 Troubleshooting

### Common Issues

#### "No Network Data" Problem
**Solutions**:
1. Run as Administrator
2. Check Windows Firewall settings
3. Verify network adapter is enabled
4. Check WMI service status: `sc query winmgmt`

#### Performance Impact
**Solutions**:
1. Increase update intervals: `update_interval=10`
2. Reduce tracked connections: `max_connections_tracked=500`
3. Disable deep inspection: `enable_deep_inspection=false`
4. Limit history retention: `history_retention_minutes=30`

#### Missing Connections
**Solutions**:
1. Verify administrative privileges
2. Check network monitoring permissions
3. Ensure required Windows services are running
4. Update network adapter drivers

### Diagnostic Commands

#### Network Diagnostics
```bash
# Check network configuration
ipconfig /all

# Display active connections
netstat -an

# Show routing table  
route print

# Test DNS resolution
nslookup google.com

# Check firewall status
netsh advfirewall show allprofiles
```

#### System Diagnostics
```bash
# Check WMI functionality
wmic path win32_networkadapter get name,index

# Verify process network access
netstat -b

# Check Windows services
sc query winmgmt
sc query eventlog
sc query dnscache
```

## 📈 Advanced Features

### Machine Learning Integration

#### Anomaly Detection
- **Traffic Pattern Analysis**: Detect unusual traffic patterns
- **Behavioral Analysis**: Learn normal application network behavior
- **Threat Prediction**: Predict potential security threats based on patterns
- **Adaptive Thresholds**: Automatically adjust detection thresholds

#### AI-Powered Analysis
```
AI NETWORK ANALYSIS
├─ Normal Behavior:     85% confidence
├─ Suspicious Activity: 12% confidence  
├─ Threat Detected:     3% confidence
└─ Recommendation: Monitor 192.168.1.15 for unusual activity
```

### Enterprise Features

#### Multi-System Monitoring
- **Centralized Dashboard**: Monitor multiple systems from single interface
- **Distributed Monitoring**: Deploy monitoring across network infrastructure
- **Correlation Engine**: Correlate events across multiple systems
- **Reporting**: Generate comprehensive network security reports

#### Integration Capabilities
- **SIEM Integration**: Send data to Security Information and Event Management systems
- **API Access**: Programmatic access to network monitoring data
- **Webhook Support**: Real-time notifications via webhooks
- **Database Integration**: Store network data in enterprise databases

This comprehensive network monitoring guide provides the foundation for effective network security monitoring with Security Sentinel. Regular monitoring and analysis of network activity is crucial for maintaining system security and detecting threats early.