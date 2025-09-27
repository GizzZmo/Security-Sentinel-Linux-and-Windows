# GitHub Copilot Instructions - Security Sentinel

This repository contains **Security Sentinel**, a comprehensive security monitoring application for Windows 11 with AI-powered threat analysis. The project features a dual-architecture implementation with both a native C++ application and a modern React web interface.

## Project Architecture

### Dual Implementation Structure
- **C++ Native Application** (`src/`, `include/`) - Full Windows API integration with administrator-level monitoring
- **React Web Interface** (`App.tsx`, `components/`, `services/`) - Modern TypeScript dashboard with cross-platform support
- **Shared Documentation** (`docs/`, `wiki/`) - Comprehensive guides and API documentation

### Core Technologies
- **C++ (17)**: Native Windows application using MSVC, CMake build system
- **React (19)**: Modern TypeScript frontend with Vite build tool  
- **Google Gemini AI**: Integrated AI assistant for intelligent threat analysis
- **Windows APIs**: Direct integration with Windows security and networking APIs

## Coding Standards

### C++ Conventions
- **Standard**: C++17 with modern features (RAII, smart pointers, auto)
- **Naming**: `PascalCase` for classes, `camelCase_` for private members, `snake_case` for functions
- **Headers**: Use `#include` guards, separate interface (.h) and implementation (.cpp)
- **Memory**: Prefer `std::unique_ptr` and `std::shared_ptr` over raw pointers
- **Error Handling**: Use exceptions for initialization, return codes for runtime operations

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

### React Components
- **Dashboard**: Main overview with system metrics and charts
- **NetworkMonitor**: Network connection visualization and logs
- **ThreatProtection**: Security event timeline and threat management
- **AIAssistant**: Chat interface with Gemini AI integration
- **Sidebar**: Navigation between different views

### Services
- **geminiService.ts**: TypeScript client for Google Gemini API
- **Configuration**: INI-based config system for C++, env vars for React

## Development Guidelines

### When Working on C++ Code:
- Always check administrator privileges for Windows API calls
- Use Windows-specific APIs: `iphlpapi`, `psapi`, `wininet`, `ws2_32`
- Handle errors gracefully with proper resource cleanup
- Thread safety considerations for monitoring components
- Test both Debug and Release builds

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

## Build System

### C++ Build (CMake):
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### React Build (Vite):
```bash
npm install
npm run dev    # Development server
npm run build  # Production build
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
├── components/       # React components
├── services/         # TypeScript services
├── docs/            # Technical documentation
├── wiki/            # User guides
├── .github/         # GitHub workflows and templates
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

```typescript
// TypeScript - Environment variables
const apiKey = import.meta.env.VITE_GEMINI_API_KEY;
```

## Dependencies

### C++ Libraries:
- Standard C++17 library
- Windows SDK APIs
- Threading support (std::thread)

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

---

**Remember**: This is a security-focused application. Always consider the security implications of any changes, especially when working with Windows APIs, network operations, or AI integration. Maintain the principle of least privilege and ensure all sensitive operations are properly validated and secured.