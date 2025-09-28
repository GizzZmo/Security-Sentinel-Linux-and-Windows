#pragma once

#include <string>
#include <vector>
#include <map>

/**
 * Self-protection and integrity verification system
 */
namespace IntegritySystem {
    
    struct FileInfo {
        std::string path;
        std::string expectedHash;
        std::string actualHash;
        bool isValid;
        bool exists;
        
        FileInfo(const std::string& p, const std::string& expected) 
            : path(p), expectedHash(expected), isValid(false), exists(false) {}
    };
    
    struct IntegrityReport {
        bool overallValid;
        std::vector<FileInfo> files;
        std::vector<std::string> warnings;
        std::vector<std::string> errors;
        
        IntegrityReport() : overallValid(true) {}
    };
    
    /**
     * Initialize integrity system with known good hashes
     */
    bool Initialize();
    
    /**
     * Add a file to the integrity check list
     * @param filePath Path to the file to monitor
     * @param expectedHash Expected SHA-256 hash (empty to calculate on first run)
     */
    void AddFileToCheck(const std::string& filePath, const std::string& expectedHash = "");
    
    /**
     * Perform comprehensive integrity check
     * @return IntegrityReport with detailed results
     */
    IntegrityReport PerformIntegrityCheck();
    
    /**
     * Quick integrity check for startup verification
     * @return true if all critical files are valid
     */
    bool QuickIntegrityCheck();
    
    /**
     * Calculate SHA-256 hash of a file
     * @param filePath Path to the file
     * @return Hex-encoded SHA-256 hash or empty string on error
     */
    std::string CalculateFileHash(const std::string& filePath);
    
    /**
     * Verify digital signature (Windows only)
     * @param filePath Path to the executable
     * @return true if signature is valid
     */
    bool VerifyDigitalSignature(const std::string& filePath);
    
    /**
     * Generate integrity baseline file
     * @param baselineFile Path where to save the baseline
     * @return true on success
     */
    bool GenerateBaseline(const std::string& baselineFile = "integrity.baseline");
    
    /**
     * Load integrity baseline from file
     * @param baselineFile Path to baseline file
     * @return true on success
     */
    bool LoadBaseline(const std::string& baselineFile = "integrity.baseline");
    
    /**
     * Check if the application executable has been tampered with
     * @return true if executable is valid
     */
    bool ValidateExecutable();
    
    /**
     * Get the list of critical files that should be monitored
     */
    std::vector<std::string> GetCriticalFiles();
}