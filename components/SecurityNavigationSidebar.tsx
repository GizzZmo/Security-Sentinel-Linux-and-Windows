
import React from 'react';
import { SecurityView } from '../types';
import Icon from './icon';

interface SecurityNavigationSidebarProps {
  currentView: SecurityView;
  onViewChange: (view: SecurityView) => void;
}

const SecurityNavigationItem: React.FC<{
  view: SecurityView;
  iconName: string;
  currentView: SecurityView;
  onViewChange: (view: SecurityView) => void;
}> = ({ view, iconName, currentView, onViewChange }) => {
  const isActive = currentView === view;
  return (
    <button
      onClick={() => onViewChange(view)}
      className={`flex items-center w-full px-4 py-3 text-left rounded-lg transition-colors duration-200 ${
        isActive
          ? 'bg-blue-600/30 text-white'
          : 'text-slate-300 hover:bg-slate-700/50 hover:text-white'
      }`}
    >
      <Icon name={iconName} className="w-5 h-5 mr-4" />
      <span className="font-medium">{view}</span>
    </button>
  );
};

const SecurityNavigationSidebar: React.FC<SecurityNavigationSidebarProps> = ({ currentView, onViewChange }) => {
  return (
    <div className="flex flex-col w-64 h-full bg-slate-800/30 backdrop-blur-md border-r border-slate-700/50 p-4">
      <div className="flex items-center mb-8">
        <Icon name="shield" className="w-8 h-8 text-blue-400" />
        <h1 className="ml-3 text-xl font-bold text-white">Security Sentinel</h1>
      </div>
      <nav className="flex flex-col space-y-2">
        <SecurityNavigationItem view={SecurityView.SecurityDashboard} iconName="dashboard" currentView={currentView} onViewChange={onViewChange} />
        <SecurityNavigationItem view={SecurityView.NetworkTrafficMonitor} iconName="network" currentView={currentView} onViewChange={onViewChange} />
        <SecurityNavigationItem view={SecurityView.ThreatDetectionCenter} iconName="shield" currentView={currentView} onViewChange={onViewChange} />
        <SecurityNavigationItem view={SecurityView.SecurityAIAssistant} iconName="assistant" currentView={currentView} onViewChange={onViewChange} />
      </nav>
      <div className="mt-auto text-center text-xs text-slate-500">
        <p>&copy; 2024 Windows 11 Sentinel</p>
        <p>Version 1.0.0</p>
      </div>
    </div>
  );
};

export default SecurityNavigationSidebar;
