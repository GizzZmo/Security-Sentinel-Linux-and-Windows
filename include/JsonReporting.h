#pragma once

#include <string>
#include <map>
#include <vector>
#include <chrono>

/**
 * JSON Report System for standardized security check output
 */
namespace JsonReporting {
    
    enum class Severity {
        INFO,
        LOW,
        MEDIUM,
        HIGH,
        CRITICAL
    };
    
    enum class Status {
        PASS,
        FAIL,
        WARNING,
        ERROR
    };
    
    struct CheckResult {
        std::string checkId;
        Status status;
        Severity severity;
        std::string description;
        std::map<std::string, std::string> details;
        std::string remediation;
        std::chrono::system_clock::time_point timestamp;
        double executionTimeMs;
        
        CheckResult(const std::string& id) 
            : checkId(id), status(Status::PASS), severity(Severity::INFO), 
              timestamp(std::chrono::system_clock::now()), executionTimeMs(0.0) {}
    };
    
    struct SecurityReport {
        std::string reportId;
        std::string version;
        std::chrono::system_clock::time_point generatedAt;
        std::vector<CheckResult> results;
        std::map<std::string, std::string> systemInfo;
        
        SecurityReport() : version("1.0"), generatedAt(std::chrono::system_clock::now()) {}
    };
    
    /**
     * Convert CheckResult to JSON string
     */
    std::string CheckResultToJson(const CheckResult& result);
    
    /**
     * Convert SecurityReport to JSON string
     */
    std::string SecurityReportToJson(const SecurityReport& report);
    
    /**
     * Parse JSON string to CheckResult
     */
    CheckResult JsonToCheckResult(const std::string& json);
    
    /**
     * Parse JSON string to SecurityReport
     */
    SecurityReport JsonToSecurityReport(const std::string& json);
    
    /**
     * Helper functions for enum conversions
     */
    std::string StatusToString(Status status);
    std::string SeverityToString(Severity severity);
    Status StringToStatus(const std::string& str);
    Severity StringToSeverity(const std::string& str);
    
    /**
     * Create a standardized check result
     */
    CheckResult CreateCheckResult(const std::string& checkId, Status status, 
                                 Severity severity, const std::string& description);
    
    /**
     * Save report to file
     */
    bool SaveReportToFile(const SecurityReport& report, const std::string& filename);
    
    /**
     * Load report from file
     */
    SecurityReport LoadReportFromFile(const std::string& filename);
}