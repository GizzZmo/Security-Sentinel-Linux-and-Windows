#include "GoCore.h"
#ifdef __linux__
#include <dlfcn.h>
#endif
#include <iostream>
#include <cstdlib>

// Function pointers to Go functions
extern "C" {
    typedef int (*InitializeCore_t)();
    typedef char* (*GetSystemInfo_t)();
    typedef char* (*PerformFileIntegrityCheck_t)(const char*);
    typedef char* (*PerformRegistryCheck_t)(const char*);
    typedef char* (*PerformDirectoryAnalysis_t)(const char*);
    typedef void (*FreeString_t)(char*);
}

namespace GoCore {
    // Function pointers
    static InitializeCore_t InitializeCore = nullptr;
    static GetSystemInfo_t GetSystemInfo_Go = nullptr;
    static PerformFileIntegrityCheck_t PerformFileIntegrityCheck_Go = nullptr;
    static PerformRegistryCheck_t PerformRegistryCheck_Go = nullptr;
    static PerformDirectoryAnalysis_t PerformDirectoryAnalysis_Go = nullptr;
    static FreeString_t FreeString = nullptr;
    
    static void* goLibHandle = nullptr;
    static bool initialized = false;
    
    // Helper to load function from shared library
#ifdef __linux__
    template<typename T>
    bool LoadFunction(T& func, const char* name) {
        func = (T)dlsym(goLibHandle, name);
        if (!func) {
            std::cerr << "Failed to load function " << name << ": " << dlerror() << std::endl;
            return false;
        }
        return true;
    }
#endif
    
    int Initialize() {
        if (initialized) {
            return 0;
        }
        
#ifdef __linux__
        // Try to load the Go shared library
        const char* libPath = "./core-go/libsecurity_core.so";
        goLibHandle = dlopen(libPath, RTLD_LAZY);
        
        if (!goLibHandle) {
            std::cerr << "Cannot load Go core library: " << dlerror() << std::endl;
            return -1;
        }
        
        // Load all functions
        bool success = true;
        success &= LoadFunction(InitializeCore, "InitializeCore");
        success &= LoadFunction(GetSystemInfo_Go, "GetSystemInfo");
        success &= LoadFunction(PerformFileIntegrityCheck_Go, "PerformFileIntegrityCheck");
        success &= LoadFunction(PerformRegistryCheck_Go, "PerformRegistryCheck");
        success &= LoadFunction(PerformDirectoryAnalysis_Go, "PerformDirectoryAnalysis");
        success &= LoadFunction(FreeString, "FreeString");
        
        if (!success) {
            dlclose(goLibHandle);
            goLibHandle = nullptr;
            return -2;
        }
        
        // Initialize the Go core
        int result = InitializeCore();
        if (result == 0) {
            initialized = true;
            std::cout << "Go Core initialized successfully" << std::endl;
        } else {
            std::cerr << "Failed to initialize Go Core" << std::endl;
        }
        
        return result;
#else
        // Go core not available on non-Linux platforms
        std::cout << "Go core module not available on this platform" << std::endl;
        return -1;
#endif
    }
    
    std::string GetSystemInfo() {
        if (!initialized || !GetSystemInfo_Go) {
            return R"({"error": "Go core not initialized"})";
        }
        
        char* result = GetSystemInfo_Go();
        if (!result) {
            return R"({"error": "Failed to get system info"})";
        }
        
        std::string jsonResult(result);
        FreeString(result);
        
        return jsonResult;
    }
    
    std::string PerformFileIntegrityCheck(const std::string& filepath) {
        if (!initialized || !PerformFileIntegrityCheck_Go) {
            return R"({"error": "Go core not initialized"})";
        }
        
        char* result = PerformFileIntegrityCheck_Go(filepath.c_str());
        if (!result) {
            return R"({"error": "Failed to perform file integrity check"})";
        }
        
        std::string jsonResult(result);
        FreeString(result);
        
        return jsonResult;
    }
    
    std::string PerformRegistryCheck(const std::string& keyPath) {
        if (!initialized || !PerformRegistryCheck_Go) {
            return R"({"error": "Go core not initialized"})";
        }
        
        char* result = PerformRegistryCheck_Go(keyPath.c_str());
        if (!result) {
            return R"({"error": "Failed to perform registry check"})";
        }
        
        std::string jsonResult(result);
        FreeString(result);
        
        return jsonResult;
    }
    
    std::string PerformDirectoryAnalysis(const std::string& dirPath) {
        if (!initialized || !PerformDirectoryAnalysis_Go) {
            return R"({"error": "Go core not initialized"})";
        }
        
        char* result = PerformDirectoryAnalysis_Go(dirPath.c_str());
        if (!result) {
            return R"({"error": "Failed to perform directory analysis"})";
        }
        
        std::string jsonResult(result);
        FreeString(result);
        
        return jsonResult;
    }
    
    bool IsAvailable() {
        return initialized && goLibHandle != nullptr;
    }
}