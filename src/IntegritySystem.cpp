#include "IntegritySystem.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

#ifdef _WIN32
#include <windows.h>
#include <wintrust.h>
#include <softpub.h>
#pragma comment(lib, "wintrust.lib")
#pragma comment(lib, "crypt32.lib")
#endif

namespace IntegritySystem {
    
    static std::vector<FileInfo> monitoredFiles;
    static bool initialized = false;
    
    bool Initialize() {
        if (initialized) {
            return true;
        }
        
        // Add critical application files to monitoring
        std::vector<std::string> criticalFiles = GetCriticalFiles();
        
        for (const auto& file : criticalFiles) {
            AddFileToCheck(file);
        }
        
        // Try to load existing baseline
        LoadBaseline();
        
        initialized = true;
        std::cout << "Integrity system initialized with " << monitoredFiles.size() 
                  << " files under monitoring." << std::endl;
        
        return true;
    }
    
    void AddFileToCheck(const std::string& filePath, const std::string& expectedHash) {
        // Check if file already exists in the list
        for (auto& file : monitoredFiles) {
            if (file.path == filePath) {
                if (!expectedHash.empty()) {
                    file.expectedHash = expectedHash;
                }
                return;
            }
        }
        
        // Add new file
        monitoredFiles.emplace_back(filePath, expectedHash);
    }
    
    IntegrityReport PerformIntegrityCheck() {
        IntegrityReport report;
        
        for (auto& fileInfo : monitoredFiles) {
            fileInfo.exists = Utils::FileExists(fileInfo.path);
            
            if (!fileInfo.exists) {
                fileInfo.isValid = false;
                report.errors.push_back("File missing: " + fileInfo.path);
                report.overallValid = false;
                continue;
            }
            
            // Calculate current hash
            fileInfo.actualHash = CalculateFileHash(fileInfo.path);
            
            if (fileInfo.actualHash.empty()) {
                fileInfo.isValid = false;
                report.errors.push_back("Failed to calculate hash for: " + fileInfo.path);
                report.overallValid = false;
                continue;
            }
            
            // If no expected hash, use the current one as baseline
            if (fileInfo.expectedHash.empty()) {
                fileInfo.expectedHash = fileInfo.actualHash;
                fileInfo.isValid = true;
                report.warnings.push_back("No baseline hash for: " + fileInfo.path + ", using current");
            } else {
                // Compare hashes
                fileInfo.isValid = (fileInfo.actualHash == fileInfo.expectedHash);
                
                if (!fileInfo.isValid) {
                    report.errors.push_back("Hash mismatch for: " + fileInfo.path);
                    report.overallValid = false;
                }
            }
        }
        
        report.files = monitoredFiles;
        
        return report;
    }
    
    bool QuickIntegrityCheck() {
        // Quick check focusing only on the main executable
        std::string execPath = Utils::GetExecutableDirectory() + "/SecuritySentinel";
        
        if (!Utils::FileExists(execPath)) {
            std::cerr << "INTEGRITY WARNING: Main executable not found!" << std::endl;
            return false;
        }
        
        // For quick check, we only verify the file exists and is readable
        std::ifstream file(execPath, std::ios::binary);
        if (!file.good()) {
            std::cerr << "INTEGRITY WARNING: Cannot read main executable!" << std::endl;
            return false;
        }
        
        file.close();
        return true;
    }
    
    std::string CalculateFileHash(const std::string& filePath) {
        return Utils::HashString(filePath); // Placeholder - Utils::HashString should calculate file hash
    }
    
    bool VerifyDigitalSignature(const std::string& filePath) {
#ifdef _WIN32
        WINTRUST_FILE_INFO fileData;
        memset(&fileData, 0, sizeof(fileData));
        fileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
        
        // Convert to wide string
        std::wstring wideFilePath;
        wideFilePath.assign(filePath.begin(), filePath.end());
        fileData.pcwszFilePath = wideFilePath.c_str();
        
        GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
        WINTRUST_DATA wintrustData;
        
        memset(&wintrustData, 0, sizeof(wintrustData));
        wintrustData.cbStruct = sizeof(wintrustData);
        wintrustData.pPolicyCallbackData = nullptr;
        wintrustData.pSIPClientData = nullptr;
        wintrustData.dwUIChoice = WTD_UI_NONE;
        wintrustData.fdwRevocationChecks = WTD_REVOKE_NONE;
        wintrustData.dwUnionChoice = WTD_CHOICE_FILE;
        wintrustData.dwStateAction = WTD_STATEACTION_VERIFY;
        wintrustData.hWVTStateData = nullptr;
        wintrustData.pwszURLReference = nullptr;
        wintrustData.dwUIContext = 0;
        wintrustData.pFile = &fileData;
        
        LONG lStatus = WinVerifyTrust(nullptr, &WVTPolicyGUID, &wintrustData);
        
        // Clean up
        wintrustData.dwStateAction = WTD_STATEACTION_CLOSE;
        WinVerifyTrust(nullptr, &WVTPolicyGUID, &wintrustData);
        
        return lStatus == ERROR_SUCCESS;
#else
        // On Linux, we don't have built-in signature verification
        // Could implement GPG signature verification here
        return true; // Placeholder
#endif
    }
    
    bool GenerateBaseline(const std::string& baselineFile) {
        try {
            std::ofstream file(baselineFile);
            if (!file.is_open()) {
                std::cerr << "Failed to create baseline file: " << baselineFile << std::endl;
                return false;
            }
            
            file << "# Security Sentinel Integrity Baseline\n";
            file << "# Generated at: " << Utils::FormatTime(std::chrono::system_clock::now()) << "\n\n";
            
            for (const auto& fileInfo : monitoredFiles) {
                if (Utils::FileExists(fileInfo.path)) {
                    std::string hash = CalculateFileHash(fileInfo.path);
                    if (!hash.empty()) {
                        file << fileInfo.path << ":" << hash << "\n";
                    }
                }
            }
            
            file.close();
            std::cout << "Integrity baseline generated: " << baselineFile << std::endl;
            return true;
            
        } catch (const std::exception& e) {
            std::cerr << "Error generating baseline: " << e.what() << std::endl;
            return false;
        }
    }
    
    bool LoadBaseline(const std::string& baselineFile) {
        if (!Utils::FileExists(baselineFile)) {
            std::cout << "No existing baseline found, will generate on next check." << std::endl;
            return false;
        }
        
        try {
            std::ifstream file(baselineFile);
            if (!file.is_open()) {
                return false;
            }
            
            std::string line;
            int loadedCount = 0;
            
            while (std::getline(file, line)) {
                // Skip comments and empty lines
                if (line.empty() || line[0] == '#') {
                    continue;
                }
                
                size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    std::string path = line.substr(0, colonPos);
                    std::string hash = line.substr(colonPos + 1);
                    
                    // Update existing entry or add new one
                    bool found = false;
                    for (auto& fileInfo : monitoredFiles) {
                        if (fileInfo.path == path) {
                            fileInfo.expectedHash = hash;
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        AddFileToCheck(path, hash);
                    }
                    
                    loadedCount++;
                }
            }
            
            file.close();
            std::cout << "Loaded " << loadedCount << " file hashes from baseline." << std::endl;
            return true;
            
        } catch (const std::exception& e) {
            std::cerr << "Error loading baseline: " << e.what() << std::endl;
            return false;
        }
    }
    
    bool ValidateExecutable() {
        std::string execPath = Utils::GetExecutableDirectory() + "/SecuritySentinel";
        
        // Check if file exists
        if (!Utils::FileExists(execPath)) {
            std::cerr << "SECURITY WARNING: Main executable not found!" << std::endl;
            return false;
        }
        
        // Verify digital signature on Windows
#ifdef _WIN32
        if (!VerifyDigitalSignature(execPath)) {
            std::cerr << "SECURITY WARNING: Digital signature verification failed!" << std::endl;
            return false;
        }
#endif
        
        return true;
    }
    
    std::vector<std::string> GetCriticalFiles() {
        std::vector<std::string> files;
        std::string baseDir = Utils::GetExecutableDirectory();
        
        // Main executable
        files.push_back(baseDir + "/SecuritySentinel");
        files.push_back(baseDir + "/SecuritySentinel.exe");
        
        // Configuration files
        files.push_back(baseDir + "/config.ini");
        files.push_back("./config.ini");
        
        // Go core library
        files.push_back(baseDir + "/core-go/libsecurity_core.so");
        files.push_back("./core-go/libsecurity_core.so");
        
        // Critical headers (development)
        files.push_back("./include/SecurityApp.h");
        files.push_back("./include/Utils.h");
        
        return files;
    }
}