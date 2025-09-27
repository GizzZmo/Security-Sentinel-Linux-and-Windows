#include "JsonReporting.h"
#include "Utils.h"
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

namespace JsonReporting {
    
    std::string StatusToString(Status status) {
        switch (status) {
            case Status::PASS: return "pass";
            case Status::FAIL: return "fail";
            case Status::WARNING: return "warning";
            case Status::ERROR: return "error";
            default: return "unknown";
        }
    }
    
    std::string SeverityToString(Severity severity) {
        switch (severity) {
            case Severity::INFO: return "info";
            case Severity::LOW: return "low";
            case Severity::MEDIUM: return "medium";
            case Severity::HIGH: return "high";
            case Severity::CRITICAL: return "critical";
            default: return "unknown";
        }
    }
    
    Status StringToStatus(const std::string& str) {
        if (str == "pass") return Status::PASS;
        if (str == "fail") return Status::FAIL;
        if (str == "warning") return Status::WARNING;
        if (str == "error") return Status::ERROR;
        return Status::ERROR;
    }
    
    Severity StringToSeverity(const std::string& str) {
        if (str == "info") return Severity::INFO;
        if (str == "low") return Severity::LOW;
        if (str == "medium") return Severity::MEDIUM;
        if (str == "high") return Severity::HIGH;
        if (str == "critical") return Severity::CRITICAL;
        return Severity::INFO;
    }
    
    std::string CheckResultToJson(const CheckResult& result) {
        std::ostringstream json;
        json << "{\n";
        json << "  \"check_id\": \"" << Utils::EscapeJson(result.checkId) << "\",\n";
        json << "  \"status\": \"" << StatusToString(result.status) << "\",\n";
        json << "  \"severity\": \"" << SeverityToString(result.severity) << "\",\n";
        json << "  \"description\": \"" << Utils::EscapeJson(result.description) << "\",\n";
        
        // Add details
        if (!result.details.empty()) {
            json << "  \"details\": {\n";
            bool first = true;
            for (const auto& pair : result.details) {
                if (!first) json << ",\n";
                json << "    \"" << Utils::EscapeJson(pair.first) << "\": \"" 
                     << Utils::EscapeJson(pair.second) << "\"";
                first = false;
            }
            json << "\n  },\n";
        }
        
        if (!result.remediation.empty()) {
            json << "  \"remediation_steps\": \"" << Utils::EscapeJson(result.remediation) << "\",\n";
        }
        
        // Timestamp (ISO 8601 format)
        auto time_t = std::chrono::system_clock::to_time_t(result.timestamp);
        json << "  \"timestamp\": " << time_t << ",\n";
        json << "  \"execution_time_ms\": " << std::fixed << std::setprecision(2) 
             << result.executionTimeMs << "\n";
        json << "}";
        
        return json.str();
    }
    
    std::string SecurityReportToJson(const SecurityReport& report) {
        std::ostringstream json;
        json << "{\n";
        json << "  \"report_id\": \"" << Utils::EscapeJson(report.reportId) << "\",\n";
        json << "  \"version\": \"" << Utils::EscapeJson(report.version) << "\",\n";
        
        // Generated timestamp
        auto time_t = std::chrono::system_clock::to_time_t(report.generatedAt);
        json << "  \"generated_at\": " << time_t << ",\n";
        
        // System information
        if (!report.systemInfo.empty()) {
            json << "  \"system_info\": {\n";
            bool first = true;
            for (const auto& pair : report.systemInfo) {
                if (!first) json << ",\n";
                json << "    \"" << Utils::EscapeJson(pair.first) << "\": \"" 
                     << Utils::EscapeJson(pair.second) << "\"";
                first = false;
            }
            json << "\n  },\n";
        }
        
        // Results
        json << "  \"results\": [\n";
        for (size_t i = 0; i < report.results.size(); ++i) {
            if (i > 0) json << ",\n";
            
            // Indent the check result JSON
            std::string checkJson = CheckResultToJson(report.results[i]);
            std::istringstream iss(checkJson);
            std::string line;
            bool firstLine = true;
            while (std::getline(iss, line)) {
                if (!firstLine) json << "\n";
                json << "    " << line;
                firstLine = false;
            }
        }
        json << "\n  ]\n";
        json << "}";
        
        return json.str();
    }
    
    CheckResult CreateCheckResult(const std::string& checkId, Status status, 
                                 Severity severity, const std::string& description) {
        CheckResult result(checkId);
        result.status = status;
        result.severity = severity;
        result.description = description;
        return result;
    }
    
    bool SaveReportToFile(const SecurityReport& report, const std::string& filename) {
        try {
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return false;
            }
            
            file << SecurityReportToJson(report);
            file.close();
            
            std::cout << "Security report saved to: " << filename << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error saving report: " << e.what() << std::endl;
            return false;
        }
    }
    
    SecurityReport LoadReportFromFile(const std::string& filename) {
        SecurityReport report;
        
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file for reading: " << filename << std::endl;
                return report;
            }
            
            std::string content((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
            file.close();
            
            // Basic JSON parsing would go here
            // For now, return empty report as placeholder
            report.reportId = "loaded_from_file";
            
        } catch (const std::exception& e) {
            std::cerr << "Error loading report: " << e.what() << std::endl;
        }
        
        return report;
    }
    
    // Placeholder JSON parsing functions
    CheckResult JsonToCheckResult(const std::string& json) {
        CheckResult result("unknown");
        // TODO: Implement JSON parsing
        return result;
    }
    
    SecurityReport JsonToSecurityReport(const std::string& json) {
        SecurityReport report;
        // TODO: Implement JSON parsing
        return report;
    }
}