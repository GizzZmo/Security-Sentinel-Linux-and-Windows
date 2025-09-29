import React, { useState, useRef, useEffect } from 'react';
import type { SecurityChatMessage } from '../types';
import { sendMessageStream } from '../services/geminiService';
import Icon from './icon';
import Spinner from './Spinner';

const SecurityAIAssistant: React.FC = () => {
  const [securityMessages, setSecurityMessages] = useState<SecurityChatMessage[]>([]);
  const [securityQuery, setSecurityQuery] = useState('');
  const [isAnalyzing, setIsAnalyzing] = useState(false);
  const messagesEndRef = useRef<HTMLDivElement>(null);

  const scrollToBottom = () => {
    messagesEndRef.current?.scrollIntoView({ behavior: 'smooth' });
  };

  useEffect(() => {
    scrollToBottom();
  }, [securityMessages, isAnalyzing]);

  const handleSecurityQuery = async () => {
    if (!securityQuery.trim() || isAnalyzing) return;

    const userSecurityMessage: SecurityChatMessage = { role: 'user', content: securityQuery };
    setSecurityMessages(prev => [...prev, userSecurityMessage]);
    setSecurityQuery('');
    setIsAnalyzing(true);

    const aiSecurityResponse: SecurityChatMessage = { role: 'model', content: '' };
    setSecurityMessages(prev => [...prev, aiSecurityResponse]);

    try {
      const stream = await sendMessageStream(securityMessages, securityQuery);
      for await (const chunk of stream) {
        setSecurityMessages(prev =>
          prev.map((msg, index) =>
            index === prev.length - 1 && msg.role === 'model'
              ? { ...msg, content: msg.content + chunk.text }
              : msg
          )
        );
      }
    } catch (error) {
      console.error('Security AI Assistant error:', error);
      const errorMessage: SecurityChatMessage = {
        role: 'model',
        content: 'Sorry, I encountered an error analyzing your security query. Please try again.',
      };
      setSecurityMessages(prev => [...prev.slice(0, -1), errorMessage]);
    } finally {
      setIsAnalyzing(false);
    }
  };

  const handleSecurityKeyPress = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault();
      handleSecurityQuery();
    }
  };

  return (
    <div className="p-6 h-full flex flex-col bg-slate-900/20">
      <div className="flex-grow overflow-y-auto pr-4 space-y-6">
        {securityMessages.map((msg, index) => (
          <div key={index} className={`flex items-start gap-4 ${msg.role === 'user' ? 'justify-end' : ''}`}>
            {msg.role === 'model' && (
              <div className="w-8 h-8 flex-shrink-0 bg-blue-500/20 rounded-full flex items-center justify-center">
                <Icon name="bot" className="w-5 h-5 text-blue-300" />
              </div>
            )}
            <div
              className={`max-w-xl p-4 rounded-xl whitespace-pre-wrap ${
                msg.role === 'user'
                  ? 'bg-blue-600 text-white rounded-br-none'
                  : 'bg-slate-700/80 text-slate-200 rounded-bl-none'
              }`}
            >
              {msg.content}
              {isAnalyzing && msg.role === 'model' && index === securityMessages.length - 1 && (
                <div className="flex items-center mt-2">
                  <Spinner />
                  <span className="ml-2 text-slate-400">Analyzing security data...</span>
                </div>
              )}
            </div>
            {msg.role === 'user' && (
              <div className="w-8 h-8 flex-shrink-0 bg-slate-600/50 rounded-full flex items-center justify-center">
                <Icon name="user" className="w-5 h-5 text-slate-300" />
              </div>
            )}
          </div>
        ))}
        <div ref={messagesEndRef} />
      </div>
      <div className="flex gap-4 mt-4">
        <input
          type="text"
          value={securityQuery}
          onChange={(e) => setSecurityQuery(e.target.value)}
          onKeyPress={handleSecurityKeyPress}
          placeholder="Ask about security threats, network analysis, or system protection..."
          className="flex-1 px-4 py-2 bg-slate-700/50 border border-slate-600/50 rounded-md text-white placeholder-slate-400 focus:outline-none focus:border-blue-500"
        />
        <button
          onClick={handleSecurityQuery}
          disabled={isAnalyzing || !securityQuery.trim()}
          className="p-2 rounded-md bg-blue-600 text-white hover:bg-blue-500 disabled:bg-slate-600 disabled:cursor-not-allowed transition-colors"
        >
          {isAnalyzing ? <Spinner /> : <Icon name="send" className="w-5 h-5" />}
        </button>
      </div>
    </div>
  );
};

export default SecurityAIAssistant;