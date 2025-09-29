
import React from 'react';
import Card from './Card';

const securityThreatProtections = [
  {
    attackTool: 'Metasploit Framework',
    threatCategory: 'Vulnerability Exploitation',
    mitigationStrategy: 'Utilizes signature-based detection for known exploits and payloads. Continuously updated vulnerability database to patch against emerging threats before they are leveraged.',
  },
  {
    attackTool: 'Nmap Network Scanner',
    threatCategory: 'Reconnaissance & Footprinting',
    mitigationStrategy: 'Detects various scan types (SYN, XMAS, FIN) through anomaly detection. Alerts on rapid, sequential port scans from single sources and identifies unusual network discovery patterns.',
  },
  {
    attackTool: 'Wireshark Analyzer',
    threatCategory: 'Suspicious Traffic Analysis',
    mitigationStrategy: 'While Wireshark is a defensive tool, our engine automates its principles. It performs deep packet inspection to identify malformed packets, protocol abuse, and signs of data exfiltration or C2 communication.',
  },
  {
    attackTool: 'KratosKnife (DDoS)',
    threatCategory: 'Denial of Service Attacks',
    mitigationStrategy: 'Employs multiple layers of defense: Rate limiting, SYN cookie protection against SYN floods, and anomaly detection to identify unusual traffic volumes characteristic of UDP, ICMP, and HTTP floods.',
  },
];

const ThreatDetectionCenter: React.FC = () => {
  return (
    <div className="p-6 space-y-6">
      <Card title="Advanced Threat Detection & Protection Center">
        <p className="text-slate-400">
          Security Sentinel employs a multi-layered defense strategy combining signature-based detection for known threats and anomaly detection for novel attacks. Below is a breakdown of how we protect against specific tools and vectors.
        </p>
      </Card>
      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        {securityThreatProtections.map((p, index) => (
          <Card key={index} title={p.attackTool}>
            <div className="space-y-3">
              <div>
                <h4 className="font-semibold text-blue-400">Threat Category</h4>
                <p className="text-slate-300">{p.threatCategory}</p>
              </div>
              <div>
                <h4 className="font-semibold text-green-400">Mitigation Strategy</h4>
                <p className="text-slate-400 text-sm">{p.mitigationStrategy}</p>
              </div>
            </div>
          </Card>
        ))}
      </div>
    </div>
  );
};

export default ThreatDetectionCenter;
