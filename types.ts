
export enum SecurityView {
  SecurityDashboard = 'Security Dashboard',
  NetworkTrafficMonitor = 'Network Traffic Monitor',
  ThreatDetectionCenter = 'Threat Detection Center',
  SecurityAIAssistant = 'Security AI Assistant',
}

export interface SecurityChatMessage {
  role: 'user' | 'model';
  content: string;
}

export interface NetworkSecurityLog {
  id: number;
  timestamp: string;
  sourceIp: string;
  destinationIp: string;
  protocol: 'TCP' | 'UDP' | 'ICMP' | 'HTTP';
  threatType: 'None' | 'SYN Flood' | 'Port Scan' | 'Suspicious Payload';
  securityStatus: 'Allowed' | 'Blocked';
}
