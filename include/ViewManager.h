#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

class SecurityApp;

/**
 * Manages different security monitoring views/screens in the application
 * Handles navigation between security modules and view state management
 */
class SecurityViewManager {
public:
    enum class SecurityView {
        SecurityDashboard,
        NetworkTrafficMonitor,
        ThreatDetectionCenter,
        SecurityAIAssistant
    };

    explicit SecurityViewManager(SecurityApp* app);
    ~SecurityViewManager();

    // Security view management
    void ShowSecurityView(SecurityView view);
    void ShowSecurityView(const std::string& viewName);
    SecurityView GetCurrentSecurityView() const { return currentSecurityView_; }
    std::string GetCurrentSecurityViewName() const;

    // Security console-based UI management
    void InitializeSecurityConsole();
    void ShowSecurityMainMenu();
    void HandleSecurityUserInput();
    void ClearSecurityScreen();
    void SetSecurityTitle(const std::string& title);

    // Security status and messaging
    void ShowSecurityStatusBar(const std::string& message = "");
    void ShowSecurityError(const std::string& error);
    void ShowSecuritySuccess(const std::string& message);

private:
    SecurityApp* securityApp_;
    SecurityView currentSecurityView_;
    bool isSecurityRunning_;

    // Security view implementations
    void ShowSecurityDashboard();
    void ShowNetworkTrafficMonitor();
    void ShowThreatDetectionCenter();
    void ShowSecurityAIAssistant();

    // UI helpers for security interface
    void PrintSecurityHeader(const std::string& title);
    void PrintSecuritySeparator();
    std::string GetSecurityUserInput(const std::string& prompt);
    int GetSecurityMenuChoice(int maxChoice);
    
    // Console color support for security interface
    void SetSecurityConsoleColor(int color);
    void ResetSecurityConsoleColor();
};