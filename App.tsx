
import React, { useState } from 'react';
import { SecurityView } from './types';
import SecurityNavigationSidebar from './components/SecurityNavigationSidebar';
import SecurityHeader from './components/SecurityHeader';
import SecurityDashboard from './components/SecurityDashboard';
import NetworkTrafficMonitor from './components/NetworkTrafficMonitor';
import ThreatDetectionCenter from './components/ThreatDetectionCenter';
import SecurityAIAssistant from './components/SecurityAIAssistant';

const SecuritySentinelApp: React.FC = () => {
  const [currentView, setCurrentView] = useState<SecurityView>(SecurityView.SecurityDashboard);

  const renderSecurityView = () => {
    switch (currentView) {
      case SecurityView.SecurityDashboard:
        return <SecurityDashboard />;
      case SecurityView.NetworkTrafficMonitor:
        return <NetworkTrafficMonitor />;
      case SecurityView.ThreatDetectionCenter:
        return <ThreatDetectionCenter />;
      case SecurityView.SecurityAIAssistant:
        return <SecurityAIAssistant />;
      default:
        return <SecurityDashboard />;
    }
  };

  return (
    <div className="flex h-screen w-screen overflow-hidden">
      <SecurityNavigationSidebar currentView={currentView} onViewChange={setCurrentView} />
      <main className="flex-1 flex flex-col bg-slate-900">
        <SecurityHeader title={currentView} />
        <div className="flex-1 overflow-y-auto">
          {renderSecurityView()}
        </div>
      </main>
    </div>
  );
};

export default SecuritySentinelApp;
