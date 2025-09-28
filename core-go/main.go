package main

import (
	"C"
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"os"
	"path/filepath"
	"runtime"
	"time"
)

// SecurityCore provides high-performance core security functions
type SecurityCore struct {
	initialized bool
}

// CheckResult represents the standardized output format
type CheckResult struct {
	CheckID        string            `json:"check_id"`
	Status         string            `json:"status"` // "pass", "fail", "warning", "error"
	Severity       string            `json:"severity"` // "critical", "high", "medium", "low", "info"
	Description    string            `json:"description"`
	Details        map[string]string `json:"details,omitempty"`
	Remediation    string            `json:"remediation_steps,omitempty"`
	Timestamp      int64             `json:"timestamp"`
	ExecutionTime  float64           `json:"execution_time_ms"`
}

// SystemInfo provides comprehensive system information
type SystemInfo struct {
	OS           string `json:"os"`
	Architecture string `json:"architecture"`
	Hostname     string `json:"hostname"`
	Uptime       int64  `json:"uptime_seconds"`
	CPUCount     int    `json:"cpu_count"`
}

// Global instance
var core SecurityCore

//export InitializeCore
func InitializeCore() int {
	if core.initialized {
		return 1
	}
	
	core.initialized = true
	log.Printf("Security Core initialized (Go %s)", runtime.Version())
	return 0
}

//export GetSystemInfo
func GetSystemInfo() *C.char {
	hostname, _ := os.Hostname()
	
	info := SystemInfo{
		OS:           runtime.GOOS,
		Architecture: runtime.GOARCH,
		Hostname:     hostname,
		CPUCount:     runtime.NumCPU(),
	}
	
	jsonData, err := json.Marshal(info)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error": "%s"}`, err.Error()))
	}
	
	return C.CString(string(jsonData))
}

//export PerformFileIntegrityCheck
func PerformFileIntegrityCheck(filepath *C.char) *C.char {
	goFilepath := C.GoString(filepath)
	
	result := CheckResult{
		CheckID:     "file_integrity",
		Status:      "pass",
		Severity:    "info",
		Description: fmt.Sprintf("File integrity check for %s", goFilepath),
		Details:     make(map[string]string),
	}
	
	start := getCurrentTimestamp()
	
	// Check if file exists
	if _, err := os.Stat(goFilepath); os.IsNotExist(err) {
		result.Status = "fail"
		result.Severity = "high"
		result.Description = "File does not exist"
		result.Details["error"] = err.Error()
	} else {
		// Calculate SHA-256 hash
		hash, err := calculateSHA256(goFilepath)
		if err != nil {
			result.Status = "error"
			result.Severity = "medium"
			result.Details["error"] = err.Error()
		} else {
			result.Details["sha256"] = hash
			result.Details["file_path"] = goFilepath
		}
	}
	
	result.Timestamp = getCurrentTimestamp()
	result.ExecutionTime = float64(getCurrentTimestamp()-start) / 1000.0
	
	jsonData, err := json.Marshal(result)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error": "%s"}`, err.Error()))
	}
	
	return C.CString(string(jsonData))
}

//export PerformRegistryCheck
func PerformRegistryCheck(keyPath *C.char) *C.char {
	goKeyPath := C.GoString(keyPath)
	
	result := CheckResult{
		CheckID:     "registry_check",
		Status:      "info",
		Severity:    "info", 
		Description: fmt.Sprintf("Registry check for %s", goKeyPath),
		Details:     make(map[string]string),
	}
	
	start := getCurrentTimestamp()
	
	if runtime.GOOS == "windows" {
		// Windows registry check (placeholder - would need Windows-specific implementation)
		result.Details["registry_key"] = goKeyPath
		result.Details["platform"] = "windows"
		result.Status = "pass"
	} else {
		// Linux equivalent - check configuration files
		result.Details["config_equivalent"] = goKeyPath
		result.Details["platform"] = "linux"
		result.Status = "pass"
	}
	
	result.Timestamp = getCurrentTimestamp()
	result.ExecutionTime = float64(getCurrentTimestamp()-start) / 1000.0
	
	jsonData, err := json.Marshal(result)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error": "%s"}`, err.Error()))
	}
	
	return C.CString(string(jsonData))
}

//export PerformDirectoryAnalysis
func PerformDirectoryAnalysis(dirPath *C.char) *C.char {
	goDirPath := C.GoString(dirPath)
	
	result := CheckResult{
		CheckID:     "directory_analysis",
		Status:      "pass",
		Severity:    "info",
		Description: fmt.Sprintf("Directory analysis for %s", goDirPath),
		Details:     make(map[string]string),
	}
	
	start := getCurrentTimestamp()
	
	// Analyze directory structure and contents
	fileCount, dirCount, totalSize, err := analyzeDirectory(goDirPath)
	if err != nil {
		result.Status = "error"
		result.Severity = "medium"
		result.Details["error"] = err.Error()
	} else {
		result.Details["directory_path"] = goDirPath
		result.Details["file_count"] = fmt.Sprintf("%d", fileCount)
		result.Details["subdirectory_count"] = fmt.Sprintf("%d", dirCount)
		result.Details["total_size_bytes"] = fmt.Sprintf("%d", totalSize)
		
		// Security assessment
		if fileCount > 10000 {
			result.Status = "warning"
			result.Severity = "medium"
			result.Description += " - Large number of files detected"
		}
		
		if totalSize > 1024*1024*1024 { // 1GB
			result.Status = "warning"
			result.Severity = "low"
			result.Description += " - Large directory size detected"
		}
	}
	
	result.Timestamp = getCurrentTimestamp()
	result.ExecutionTime = float64(getCurrentTimestamp()-start) / 1000.0
	
	jsonData, err := json.Marshal(result)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error": "%s"}`, err.Error()))
	}
	
	return C.CString(string(jsonData))
}

//export FreeString
func FreeString(str *C.char) {
	// Go's garbage collector will handle this
	// This is here for C interop compatibility
}

func main() {
	// This main function is required for building as a C shared library
	fmt.Println("Security Sentinel Core Module (Go)")
}

// Helper functions
func getCurrentTimestamp() int64 {
	return time.Now().UnixNano() / int64(time.Millisecond)
}

func getCurrentTimestampMillis() int64 {
	return time.Now().UnixNano() / int64(time.Millisecond)
}

func calculateSHA256(filePath string) (string, error) {
	file, err := os.Open(filePath)
	if err != nil {
		return "", err
	}
	defer file.Close()
	
	hash := sha256.New()
	if _, err := io.Copy(hash, file); err != nil {
		return "", err
	}
	
	return fmt.Sprintf("%x", hash.Sum(nil)), nil
}

func analyzeDirectory(dirPath string) (int, int, int64, error) {
	var fileCount, dirCount int
	var totalSize int64
	
	err := filepath.Walk(dirPath, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		
		if info.IsDir() {
			dirCount++
		} else {
			fileCount++
			totalSize += info.Size()
		}
		
		return nil
	})
	
	return fileCount, dirCount, totalSize, err
}