#pragma once

#include <string>

/**
 * Go Core Library Interface
 * Provides high-performance security operations implemented in Go
 */
namespace GoCore {
    /**
     * Initialize the Go security core module
     * @return 0 on success, non-zero on failure
     */
    int Initialize();
    
    /**
     * Get comprehensive system information in JSON format
     * @return JSON string with system information
     */
    std::string GetSystemInfo();
    
    /**
     * Perform file integrity check with SHA-256 hashing
     * @param filepath Path to the file to check
     * @return JSON string with check results
     */
    std::string PerformFileIntegrityCheck(const std::string& filepath);
    
    /**
     * Perform registry/configuration check
     * @param keyPath Registry key path (Windows) or config path (Linux)
     * @return JSON string with check results
     */
    std::string PerformRegistryCheck(const std::string& keyPath);
    
    /**
     * Perform comprehensive directory analysis
     * @param dirPath Directory path to analyze
     * @return JSON string with analysis results
     */
    std::string PerformDirectoryAnalysis(const std::string& dirPath);
    
    /**
     * Check if Go core is available and loaded
     * @return true if Go core is available
     */
    bool IsAvailable();
}