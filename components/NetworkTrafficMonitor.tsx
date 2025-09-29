
import React, { useState, useEffect, useRef } from 'react';
import type { NetworkSecurityLog } from '../types';
import Card from './Card';

const generateRandomIp = () => `${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}`;

const networkProtocols: NetworkSecurityLog['protocol'][] = ['TCP', 'UDP', 'ICMP', 'HTTP'];
const threatTypes: NetworkSecurityLog['threatType'][] = ['None', 'SYN Flood', 'Port Scan', 'Suspicious Payload'];

const generateNetworkSecurityLogEntry = (id: number): NetworkSecurityLog => {
  const threatType = threatTypes[Math.floor(Math.random() * threatTypes.length)];
  return {
    id,
    timestamp: new Date().toLocaleTimeString(),
    sourceIp: generateRandomIp(),
    destinationIp: `192.168.1.${Math.floor(Math.random() * 254) + 1}`,
    protocol: networkProtocols[Math.floor(Math.random() * networkProtocols.length)],
    threatType,
    securityStatus: threatType !== 'None' ? 'Blocked' : 'Allowed',
  };
};

const getSecurityStatusColor = (status: NetworkSecurityLog['securityStatus']) => {
  return status === 'Blocked' ? 'text-red-400' : 'text-green-400';
}

const getThreatTypeColor = (threatType: NetworkSecurityLog['threatType']) => {
  switch(threatType) {
    case 'SYN Flood': return 'bg-red-500/20 text-red-300';
    case 'Port Scan': return 'bg-yellow-500/20 text-yellow-300';
    case 'Suspicious Payload': return 'bg-orange-500/20 text-orange-300';
    default: return 'bg-slate-700/50 text-slate-300';
  }
}

const NetworkTrafficMonitor: React.FC = () => {
  const [securityLogs, setSecurityLogs] = useState<NetworkSecurityLog[]>([]);
  const logContainerRef = useRef<HTMLDivElement>(null);
  const idCounter = useRef(0);

  useEffect(() => {
    const initialLogs = Array.from({ length: 15 }, (_, i) => generateNetworkSecurityLogEntry(i));
    idCounter.current = 15;
    setSecurityLogs(initialLogs);

    const interval = setInterval(() => {
      setSecurityLogs(prevLogs => {
        const newSecurityLog = generateNetworkSecurityLogEntry(idCounter.current++);
        const updatedLogs = [newSecurityLog, ...prevLogs];
        if (updatedLogs.length > 50) {
          updatedLogs.pop();
        }
        return updatedLogs;
      });
    }, 2000);

    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    if (logContainerRef.current) {
      logContainerRef.current.scrollTop = 0;
    }
  }, [securityLogs]);

  return (
    <div className="p-6 h-full flex flex-col">
      <Card title="Real-time Network Security Traffic Monitor" className="flex-grow flex flex-col">
        <div className="grid grid-cols-6 gap-4 px-4 py-2 font-semibold text-slate-400 border-b border-slate-700">
          <div>Timestamp</div>
          <div>Source IP</div>
          <div>Destination IP</div>
          <div>Protocol</div>
          <div>Threat Type</div>
          <div className="text-right">Security Status</div>
        </div>
        <div ref={logContainerRef} className="overflow-y-auto flex-grow">
          {securityLogs.map(log => (
            <div key={log.id} className="grid grid-cols-6 gap-4 px-4 py-3 border-b border-slate-800 animate-fade-in text-sm items-center">
              <div className="text-slate-400">{log.timestamp}</div>
              <div>{log.sourceIp}</div>
              <div>{log.destinationIp}</div>
              <div><span className="px-2 py-1 text-xs rounded-full bg-slate-700">{log.protocol}</span></div>
              <div><span className={`px-2 py-1 text-xs rounded-full ${getThreatTypeColor(log.threatType)}`}>{log.threatType}</span></div>
              <div className={`text-right font-semibold ${getSecurityStatusColor(log.securityStatus)}`}>{log.securityStatus}</div>
            </div>
          ))}
        </div>
      </Card>
    </div>
  );
};

export default NetworkTrafficMonitor;
