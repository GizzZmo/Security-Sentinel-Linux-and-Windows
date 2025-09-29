# Development Setup

Complete guide for setting up a Security Sentinel development environment.

## 🚀 Quick Start

### Prerequisites Overview

Security Sentinel is a dual-architecture project with both C++ and React components:

- **C++ Application**: Native Windows security monitoring with system-level access
- **React Web Interface**: Modern TypeScript dashboard with cross-platform support
- **Go Core Module**: Performance-critical operations for enhanced security checks

### Choose Your Development Focus

| Component | Language | Primary Use |
|-----------|----------|-------------|
| **Native App** | C++17 | Windows system monitoring, AI integration |
| **Web Interface** | TypeScript/React | Cross-platform dashboard, visualization |
| **Core Module** | Go 1.24+ | High-performance security operations |

## 🛠️ C++ Development Setup

### System Requirements

#### Windows Development Environment
- **OS**: Windows 11 (Windows 10 21H2+ supported)
- **IDE**: Visual Studio 2019/2022 Community or Professional
- **Compiler**: MSVC 14.2+ with C++17 support
- **Build System**: CMake 3.16 or newer
- **RAM**: 8GB minimum, 16GB recommended
- **Storage**: 10GB free space for development tools

#### Required Components
```bash
# Visual Studio Workloads (install via Visual Studio Installer)
- Desktop development with C++
- Windows 11 SDK (latest version)
- CMake tools for Visual Studio
- Git for Windows
- Windows Subsystem for Linux (optional but recommended)
```

### Installing Development Tools

#### Visual Studio Setup
1. **Download Visual Studio**:
   - [Visual Studio Community 2022](https://visualstudio.microsoft.com/downloads/) (Free)
   - [Visual Studio Professional 2022](https://visualstudio.microsoft.com/vs/professional/) (Paid)

2. **Select Workloads**:
   ```
   ☑️ Desktop development with C++
     ☑️ Windows 11 SDK (10.0.22000.0 or later)
     ☑️ CMake tools for Visual Studio
     ☑️ Git for Windows
     ☑️ IntelliCode
   ```

3. **Individual Components**:
   ```
   ☑️ C++ Core Features
   ☑️ C++ 2022 Redistributable Update
   ☑️ C++ CMake tools for Windows
   ☑️ Windows 11 SDK (latest)
   ```

#### Alternative: CMake + Visual Studio Code
```bash
# Install CMake
winget install Kitware.CMake

# Install Build Tools for Visual Studio 2022
winget install Microsoft.VisualStudio.2022.BuildTools

# Install Visual Studio Code
winget install Microsoft.VisualStudioCode

# Install VS Code extensions
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools
code --install-extension GitHub.copilot
```

### Building the C++ Application

#### Clone and Setup
```bash
# Clone the repository
git clone https://github.com/GizzZmo/Security-Sentinel-Linux-and-Windows.git
cd Security-Sentinel-Linux-and-Windows

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Build the project
cmake --build . --config Debug
# Or for release
cmake --build . --config Release
```

#### CMake Configuration Options
```bash
# Enable debugging features
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG_FEATURES=ON

# Enable testing
cmake .. -DBUILD_TESTS=ON -DENABLE_TESTING=ON

# Custom installation prefix
cmake .. -DCMAKE_INSTALL_PREFIX="C:\SecuritySentinel"

# Enable Go core integration
cmake .. -DENABLE_GO_CORE=ON
```

#### Build Targets
```bash
# Build main application
cmake --build . --target SecuritySentinel

# Build tests (if enabled)
cmake --build . --target Tests

# Build documentation (if Doxygen available)
cmake --build . --target docs

# Install to configured prefix
cmake --build . --target install
```

### Development Configuration

#### config.ini for Development
```ini
[gemini]
api_key=YOUR_DEVELOPMENT_API_KEY_HERE
model=gemini-2.5-flash
max_tokens=1000
temperature=0.7

[logging]
debug_mode=true
log_level=DEBUG
log_file=dev_security_sentinel.log
console_output=true

[development]
enable_test_features=true
mock_system_calls=false
test_data_path=test_data/
enable_profiling=true
```

#### Debugging in Visual Studio
```cpp
// Enable debug heap
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// In main():
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
```

## ⚛️ React Web Interface Setup

### Node.js Environment

#### Installing Node.js
```bash
# Install Node.js (LTS version recommended)
# Download from https://nodejs.org/
# Or use winget
winget install OpenJS.NodeJS

# Verify installation
node --version    # Should be 20.19+ or later
npm --version     # Should be 8.x or later
```

#### Alternative Node Managers
```bash
# Using Volta (recommended for team development)
winget install Volta.Volta
volta install node@20
volta install npm@latest

# Using nvm-windows
winget install CoreyButler.NVMforWindows
nvm install 20.19.0
nvm use 20.19.0
```

### Web Development Setup

#### Project Setup
```bash
# Navigate to project root
cd Security-Sentinel-Linux-and-Windows

# Install dependencies
npm install

# Install development dependencies
npm install --save-dev

# Verify installation
npm list
```

#### Development Dependencies
```json
{
  "devDependencies": {
    "@types/react": "^18.2.0",
    "@types/react-dom": "^18.2.0",
    "@typescript-eslint/eslint-plugin": "^5.57.0",
    "@typescript-eslint/parser": "^5.57.0",
    "@vitejs/plugin-react": "^4.0.0",
    "eslint": "^8.37.0",
    "eslint-plugin-react-hooks": "^4.6.0",
    "eslint-plugin-react-refresh": "^0.3.4",
    "typescript": "^5.0.2",
    "vite": "^4.3.2",
    "vitest": "^0.30.1"
  }
}
```

#### Development Scripts
```bash
# Start development server
npm run dev

# Build for production
npm run build

# Preview production build
npm run preview

# Run linting
npm run lint

# Run tests
npm test

# Type checking
npm run type-check
```

#### Environment Configuration
```env
# .env.local (for development)
VITE_GEMINI_API_KEY=your_development_api_key_here
VITE_APP_TITLE=Security Sentinel [DEV]
VITE_DEBUG_MODE=true
VITE_UPDATE_INTERVAL=1000
VITE_ENABLE_MOCK_DATA=true
```

### IDE Configuration

#### VS Code Setup
```json
// .vscode/settings.json
{
  "typescript.preferences.importModuleSpecifier": "relative",
  "editor.defaultFormatter": "esbenp.prettier-vscode",
  "editor.formatOnSave": true,
  "editor.codeActionsOnSave": {
    "source.fixAll.eslint": true
  },
  "emmet.includeLanguages": {
    "typescript": "html"
  }
}
```

#### Recommended Extensions
```json
// .vscode/extensions.json
{
  "recommendations": [
    "ms-vscode.vscode-typescript-next",
    "bradlc.vscode-tailwindcss",
    "esbenp.prettier-vscode",
    "dbaeumer.vscode-eslint",
    "GitHub.copilot",
    "ms-vscode.vscode-json"
  ]
}
```

## 🐹 Go Core Module Setup

### Go Development Environment

#### Installing Go
```bash
# Install Go 1.24+
winget install GoLang.Go

# Verify installation
go version    # Should be 1.24 or later

# Set up Go environment
go env GOPATH
go env GOROOT
```

#### Go Module Setup
```bash
# Navigate to core-go directory
cd core-go

# Initialize module (if not already done)
go mod init security-core

# Download dependencies
go mod tidy

# Build shared library
go build -buildmode=c-shared -o libsecurity_core.so main.go
```

#### Development Commands
```bash
# Format code
go fmt ./...

# Run tests
go test ./...

# Build for different targets
GOOS=windows go build -buildmode=c-shared -o libsecurity_core.dll main.go
GOOS=linux go build -buildmode=c-shared -o libsecurity_core.so main.go

# Benchmark performance
go test -bench=.
```

## 🧪 Testing Setup

### C++ Testing

#### Google Test Setup
```bash
# CMake will automatically fetch Google Test
cmake .. -DBUILD_TESTS=ON

# Build tests
cmake --build . --target Tests

# Run tests
cd build
ctest --output-on-failure

# Or run directly
.\Debug\Tests.exe
```

#### Test Structure
```cpp
// Example test file: tests/test_security_monitor.cpp
#include <gtest/gtest.h>
#include "SecurityMonitor.h"

class SecurityMonitorTest : public ::testing::Test {
protected:
    void SetUp() override {
        monitor = std::make_unique<SecurityMonitor>();
    }
    
    std::unique_ptr<SecurityMonitor> monitor;
};

TEST_F(SecurityMonitorTest, InitializationTest) {
    EXPECT_TRUE(monitor->Initialize());
}
```

### React Testing

#### Testing Framework
```bash
# Install testing dependencies
npm install --save-dev @testing-library/react @testing-library/jest-dom vitest jsdom

# Run tests
npm test

# Run tests with coverage
npm run test:coverage

# Run tests in watch mode
npm run test:watch
```

#### Example Component Test
```typescript
// tests/Dashboard.test.tsx
import { render, screen } from '@testing-library/react';
import { describe, it, expect } from 'vitest';
import Dashboard from '../src/components/Dashboard';

describe('Dashboard', () => {
  it('renders dashboard title', () => {
    render(<Dashboard />);
    expect(screen.getByText('Security Dashboard')).toBeInTheDocument();
  });
});
```

### Integration Testing

#### End-to-End Testing Setup
```bash
# Install Playwright for E2E testing
npm install --save-dev @playwright/test

# Run E2E tests
npm run test:e2e

# Run specific browser
npm run test:e2e -- --project=chromium
```

## 🔧 Development Workflow

### Git Configuration

#### Initial Setup
```bash
# Configure Git
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Set up SSH key for GitHub
ssh-keygen -t ed25519 -C "your.email@example.com"
# Add to GitHub account: https://github.com/settings/keys
```

#### Branch Strategy
```bash
# Create feature branch
git checkout -b feature/your-feature-name

# Create bug fix branch
git checkout -b fix/issue-description

# Work on branch, commit changes
git add .
git commit -m "feat: add new security monitoring feature"

# Push to origin
git push -u origin feature/your-feature-name
```

### Code Quality

#### Pre-commit Hooks
```bash
# Install pre-commit (optional but recommended)
pip install pre-commit

# Set up hooks
pre-commit install

# Run hooks manually
pre-commit run --all-files
```

#### Linting and Formatting
```bash
# C++ (using clang-format)
clang-format -i src/**/*.cpp include/**/*.h

# TypeScript/React
npm run lint
npm run lint:fix

# Go
go fmt ./...
go vet ./...
```

### Debugging Tools

#### C++ Debugging
- **Visual Studio Debugger**: Full-featured debugging with breakpoints
- **Application Verifier**: Memory and handle leak detection
- **Process Monitor**: File and registry access monitoring
- **Dependency Walker**: DLL dependency analysis

#### React Debugging
- **React Developer Tools**: Browser extension for React debugging
- **Redux DevTools**: State management debugging
- **Vite HMR**: Hot module replacement for rapid development
- **Browser DevTools**: Network, performance, and console debugging

## 📚 Development Resources

### Documentation

#### Code Documentation
```bash
# Generate C++ documentation with Doxygen
doxygen Doxyfile

# Generate TypeScript documentation
npm run docs:generate
```

#### API References
- **Gemini AI API**: [Official Documentation](https://ai.google.dev/docs)
- **Windows APIs**: [Microsoft Documentation](https://docs.microsoft.com/en-us/windows/win32/api/)
- **React**: [Official React Docs](https://reactjs.org/docs/)
- **TypeScript**: [TypeScript Handbook](https://www.typescriptlang.org/docs/)

### Learning Resources

#### Security Development
- **OWASP Secure Coding Practices**
- **Microsoft Security Development Lifecycle**
- **Windows Security APIs Documentation**
- **Network Security Monitoring Best Practices**

#### Performance Optimization
- **C++ Optimization Techniques**
- **React Performance Optimization**
- **Memory Management Best Practices**
- **Profiling and Performance Analysis**

## 🚀 Advanced Development

### Performance Profiling

#### C++ Profiling
```bash
# Using Visual Studio Diagnostic Tools
# Profile -> Performance Profiler -> CPU Usage

# Using Intel VTune (if available)
# Advanced CPU and memory profiling

# Custom performance counters
#include <chrono>
auto start = std::chrono::high_resolution_clock::now();
// Code to profile
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
```

#### React Profiling
```bash
# React DevTools Profiler
# Available in browser extension

# Bundle analysis
npm run build -- --analyze

# Runtime performance monitoring
import { Profiler } from 'react';

function onRenderCallback(id, phase, actualDuration) {
  console.log('Component render time:', actualDuration);
}
```

### Continuous Integration

#### GitHub Actions Setup
The project includes automated CI/CD workflows:
- **C++ Build**: Automated compilation and testing
- **Web Interface**: React build and test automation
- **Security Scanning**: Automated security vulnerability detection
- **Code Quality**: Linting and code quality checks

#### Local CI Testing
```bash
# Test workflows locally using act
# Install act: https://github.com/nektos/act
act -j build-cpp
act -j build-web
```

### Enterprise Development

#### Multi-Environment Setup
```bash
# Development environment
npm run dev

# Staging environment
npm run build:staging

# Production environment
npm run build:production
```

#### Configuration Management
```bash
# Environment-specific configurations
config/
├── development.ini
├── staging.ini
└── production.ini
```

This development setup guide provides everything needed to contribute effectively to Security Sentinel. Choose the components you want to work on and follow the corresponding setup instructions.