# GitHub Copilot Instructions - Security Sentinel

This repository contains **Security Sentinel**, a comprehensive security monitoring application for Windows 11 & Linux with AI-powered threat analysis. The project features a multi-architecture implementation with a native C++ application, Go-accelerated core operations, and a modern React web interface.

## Project Architecture

### Multi-Architecture Structure
- **C++ Native Application** (`src/`, `include/`) - Full Windows/Linux API integration with administrator-level monitoring
- **Go Core Module** (`core-go/`, `src/GoCore.cpp`) - Performance-critical operations and file integrity checking
- **React Web Interface** (`App.tsx`, `components/`, `services/`) - Modern TypeScript dashboard with cross-platform support
- **Shared Documentation** (`docs/`, `wiki/`) - Comprehensive guides and API documentation

### Core Technologies
- **C++ (17)**: Native Windows/Linux application using MSVC/GCC, CMake build system
- **Go (1.24+)**: High-performance core operations for file integrity and system analysis
- **React (19)**: Modern TypeScript frontend with Vite build tool  
- **Google Gemini AI**: Integrated AI assistant for intelligent threat analysis
- **Windows APIs**: Direct integration with Windows security and networking APIs
- **Linux APIs**: System monitoring via procfs, sysfs, and netlink sockets

## Coding Standards

### C++ Conventions
- **Standard**: C++17 with modern features (RAII, smart pointers, auto)
- **Naming**: `PascalCase` for classes, `camelCase_` for private members, `snake_case` for functions
- **Headers**: Use `#include` guards, separate interface (.h) and implementation (.cpp)
- **Memory**: Prefer `std::unique_ptr` and `std::shared_ptr` over raw pointers
- **Error Handling**: Use exceptions for initialization, return codes for runtime operations

### Go Conventions
- **Standard**: Go 1.24+ with modules, follow standard Go formatting
- **Naming**: Exported functions use `PascalCase`, internal use `camelCase`
- **Structure**: Organize by functionality, use clear package names
- **Error Handling**: Return explicit errors, use context for cancellation
- **Performance**: Optimize for security-critical operations, minimize allocations

### TypeScript/React Conventions  
- **Standard**: Strict TypeScript with explicit types
- **Components**: Functional components with hooks, `PascalCase` naming
- **Interfaces**: Export interfaces for props and data structures
- **State**: Use `useState` and `useEffect` hooks appropriately
- **Styling**: Tailwind CSS classes, avoid inline styles

### Commit Convention
Follow conventional commit format:
```
feat(scope): description
fix(scope): description  
docs(scope): description
style(scope): description
refactor(scope): description
test(scope): description
```

## Key Components

### C++ Core Classes
- **SecurityApp**: Main application controller and lifecycle management
- **GeminiClient**: AI API integration with HTTP streaming support
- **SecurityMonitor**: Real-time process and system resource monitoring
- **NetworkMonitor**: TCP/UDP connection tracking and threat detection
- **ThreatProtection**: Automated response and IP blocking system
- **ViewManager**: Console UI management and user interaction
- **GoCore**: Go integration bridge for performance-critical operations
- **IntegritySystem**: File integrity monitoring and tamper detection
- **JsonReporting**: Machine-readable report generation

### React Components
- **Dashboard**: Main overview with system metrics and charts
- **NetworkMonitor**: Network connection visualization and logs
- **ThreatProtection**: Security event timeline and threat management
- **AIAssistant**: Chat interface with Gemini AI integration
- **Sidebar**: Navigation between different views

### Services
- **geminiService.ts**: TypeScript client for Google Gemini API
- **Configuration**: INI-based config system for C++, env vars for React
- **Go Services**: Core performance modules for integrity checking and system analysis

## Development Guidelines

### When Working on C++ Code:
- Always check administrator privileges for Windows API calls
- Use Windows-specific APIs: `iphlpapi`, `psapi`, `wininet`, `ws2_32`
- For Linux: Use procfs, sysfs, and appropriate syscalls
- Handle errors gracefully with proper resource cleanup
- Thread safety considerations for monitoring components
- Test both Debug and Release builds
- Integrate with Go modules via GoCore bridge when performance is critical

### When Working on Go Code:
- Focus on performance-critical operations (file integrity, system analysis)
- Use proper error handling with context
- Optimize for minimal memory allocations
- Ensure thread-safety for concurrent operations
- Export functions that need to be called from C++
- Follow Go best practices for security applications

### When Working on React Code:
- Maintain responsive design principles
- Use TypeScript interfaces for all props and state
- Implement proper error boundaries
- Follow React hooks best practices
- Ensure cross-platform browser compatibility

### AI Integration:
- Use streaming responses for better UX
- Implement proper rate limiting and error handling
- Maintain context awareness in conversations
- Provide security-focused prompts and responses
- Handle API key management securely

## Security Considerations

- **Privilege Escalation**: C++ app requires administrator rights for full monitoring
- **API Keys**: Store Gemini API keys in `config.ini` (C++) or `.env.local` (React)
- **Network Security**: Implement IP whitelisting and suspicious activity blocking
- **Data Privacy**: Avoid logging sensitive system information
- **Error Handling**: Don't expose internal paths or sensitive data in error messages

## Testing Strategy

### C++ Testing:
- Build both Debug and Release configurations
- Test with and without administrator privileges
- Verify Windows API integration works correctly
- Check resource usage and memory leaks
- Test configuration loading and error scenarios
- Run `test_enhancements.cpp` for core functionality validation

### Go Testing:
- Use Go's built-in testing framework (`go test`)
- Test performance-critical paths with benchmarks
- Validate file integrity operations with known test files
- Ensure proper error handling and resource cleanup
- Test concurrent operations for thread safety

### React Testing:
- Test components in isolation
- Verify TypeScript compilation
- Test responsive design across screen sizes
- Validate AI service integration
- Check bundle size and performance

### Integration Testing:
- End-to-end functionality verification
- Cross-platform compatibility (web interface)
- API integration reliability
- Documentation accuracy and completeness
- Test C++ <-> Go integration via GoCore bridge

### Manual Testing Checklist:
- [ ] Application starts with administrator privileges
- [ ] Configuration loading works with valid/invalid configs
- [ ] AI assistant responds correctly to security queries
- [ ] Network monitoring detects connections accurately
- [ ] Threat protection blocks suspicious IPs
- [ ] Dashboard updates show real-time data
- [ ] File integrity monitoring detects changes

## Build System

### C++ Build (CMake):
```bash
# Windows (Visual Studio)
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release

# Linux (GCC)
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Go Build (for core modules):
```bash
# Build Go shared library (if needed)
cd core-go
go build -buildmode=c-archive -o core.a
go build -buildmode=c-shared -o core.so
```

### React Build (Vite):
```bash
npm install
npm run dev    # Development server
npm run build  # Production build
```

### Full Project Build:
```bash
# Build all components
./build.sh  # Or build.bat on Windows
```

## Documentation Structure

- **README.md**: Main project overview and quick start
- **wiki/**: Comprehensive user guides and tutorials
- **docs/**: Technical documentation and API references
- **CONTRIBUTING.md**: Detailed contribution guidelines

## File Organization

```
├── src/              # C++ source files
├── include/          # C++ header files  
├── core-go/          # Go performance modules
├── components/       # React components
├── services/         # TypeScript services
├── docs/            # Technical documentation
├── wiki/            # User guides
├── .github/         # GitHub workflows and templates
├── test_enhancements # Test executable and source
└── build/           # C++ build artifacts (gitignored)
```

## Common Patterns

### Error Handling:
```cpp
// C++ - Use exceptions for critical errors
try {
    if (!InitializeComponent()) {
        throw std::runtime_error("Component initialization failed");
    }
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
}
```

```typescript
// TypeScript - Handle async operations properly
try {
    const response = await geminiService.sendMessage(message);
    setMessages(prev => [...prev, response]);
} catch (error) {
    console.error('AI service error:', error);
    setError('Failed to get AI response');
}
```

### Configuration Access:
```cpp
// C++ - Singleton pattern for configuration
auto& config = Utils::Config::Instance();
std::string apiKey = config.GetString("gemini", "api_key");
```

### JSON Reporting (New Feature):
```cpp
// C++ - JSON reporting for security checks
#include "JsonReporting.h"

using namespace JsonReporting;
CheckResult result = CreateCheckResult("integrity_check", Status::PASS, 
                                      Severity::INFO, "File integrity verified");
result.details["file_count"] = "42";
result.executionTimeMs = 15.3;

std::string jsonOutput = CheckResultToJson(result);
// Output machine-readable security reports
```

```cpp
// C++ - Go integration via GoCore
#include "GoCore.h"

// Initialize Go runtime
if (GoCore::Initialize() != 0) {
    throw std::runtime_error("Go core initialization failed");
}

// Call Go function for file integrity check
std::string result = GoCore::PerformFileIntegrityCheck("config.ini");
if (result.empty()) {
    std::cerr << "File integrity check failed" << std::endl;
}
```

```typescript
// TypeScript - Environment variables (Note: Use process.env in Node.js context)
const apiKey = process.env.GEMINI_API_KEY;
// For Vite development, use import.meta.env.VITE_* prefix
const viteApiKey = import.meta.env.VITE_GEMINI_API_KEY;
```

## Dependencies

### C++ Libraries:
- Standard C++17 library
- Windows SDK APIs (Windows)
- Linux system libraries (procfs, sysfs, netlink)
- Threading support (std::thread)
- Go shared library integration

### Go Modules:
- Standard Go library (1.24+)
- Crypto/hash libraries for integrity checking
- OS interface libraries
- JSON processing libraries

### Node.js Packages:
- `react` ^19.1.0 - UI framework
- `@google/genai` ^1.10.0 - Gemini AI SDK
- `recharts` ^3.2.0 - Charting library
- `typescript` ~5.9.2 - Type safety

## Release Process

1. Update version in `CMakeLists.txt` and `package.json`
2. Create git tag: `git tag v1.x.x`
3. Push tag: `git push origin v1.x.x`
4. GitHub Actions automatically builds and creates release
5. Release includes both Windows executable and web deployment package

## Support and Community

- **Issues**: GitHub Issues for bug reports and feature requests
- **Discussions**: GitHub Discussions for community Q&A
- **Wiki**: Comprehensive documentation at `/wiki/Home.md`
- **Contributing**: See `CONTRIBUTING.md` for detailed guidelines

## Troubleshooting & Development Tips

### Common Build Issues

**CMake Configuration Fails:**
```bash
# Ensure CMake 3.16+ and proper compiler
cmake --version
# Windows: Install Visual Studio 2019/2022 with C++ tools
# Linux: Install build-essential and cmake
sudo apt-get install build-essential cmake
```

**Go Integration Issues:**
```bash
# Verify Go installation and version
go version  # Should be 1.24+
# Rebuild Go modules if needed
cd core-go && go mod tidy
```

**React Build Failures:**
```bash
# Clear cache and reinstall
rm -rf node_modules package-lock.json
npm cache clean --force
npm install
```

### Runtime Issues

**Administrator Privileges:**
- C++ app requires admin rights on Windows for full monitoring
- Run as administrator or use elevated PowerShell
- Linux may require root or specific capabilities

**API Key Configuration:**
```ini
# C++ - config.ini format
[gemini]
api_key=your_key_here
```

```bash
# React - .env.local format  
GEMINI_API_KEY=your_key_here
```

**Performance Optimization:**
- Enable Release build for production use
- Monitor memory usage in Debug builds
- Use Go core for performance-critical operations
- Profile network monitoring intervals

### Debugging Tips

**C++ Debugging:**
- Use Visual Studio debugger or GDB
- Enable debug symbols in CMake build
- Check Windows Event Viewer for API errors
- Validate administrator privileges programmatically

**Go Debugging:**
- Use `go run -race` to detect race conditions
- Profile with `go tool pprof`
- Add logging to Go functions called from C++

**React Debugging:**
- Use browser developer tools
- Check console for TypeScript errors
- Validate environment variables are loaded
- Test API endpoints independently

---

**Remember**: This is a security-focused application. Always consider the security implications of any changes, especially when working with Windows APIs, network operations, or AI integration. Maintain the principle of least privilege and ensure all sensitive operations are properly validated and secured.