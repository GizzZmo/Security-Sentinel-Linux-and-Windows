#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <chrono>

// Forward declarations
class SecurityViewManager;
class SecurityGeminiClient;
class SystemSecurityMonitor;

/**
 * Main security application class for Windows 11 & Linux Security Sentinel
 * Coordinates all security components and manages application lifecycle
 */
class SecuritySentinelApp {
public:
    SecuritySentinelApp();
    ~SecuritySentinelApp();

    // Security application lifecycle
    bool InitializeSecurity();
    int RunSecurityMonitoring();
    void ShutdownSecurity();

    // Security view management
    void ShowSecurityView(const std::string& viewName);
    void SetSecurityStatusMessage(const std::string& message);

    // Getters for security components
    SecurityGeminiClient* GetSecurityGeminiClient() const { return securityGeminiClient_.get(); }
    SystemSecurityMonitor* GetSystemSecurityMonitor() const { return systemSecurityMonitor_.get(); }

private:
    std::unique_ptr<SecurityViewManager> securityViewManager_;
    std::unique_ptr<SecurityGeminiClient> securityGeminiClient_;
    std::unique_ptr<SystemSecurityMonitor> systemSecurityMonitor_;
    
    bool isSecurityRunning_;
    std::string securityStatusMessage_;

    void InitializeSecurityComponents();
    void SetupSecurityEventHandlers();
};