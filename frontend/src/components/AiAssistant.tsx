import React, { useState, useRef, useEffect } from 'react';
import './components.css';

interface AiAssistantProps {
    repoUrl: string;
}

export const AiAssistant: React.FC<AiAssistantProps> = ({ repoUrl }) => {
    const [messages, setMessages] = useState<{ role: 'user' | 'ai', text: string }[]>([]);
    const [input, setInput] = useState('');
    const [loading, setLoading] = useState(false);
    const endRef = useRef<HTMLDivElement>(null);

    useEffect(() => {
        endRef.current?.scrollIntoView({ behavior: 'smooth' });
    }, [messages]);

    const handleAsk = async () => {
        if (!input.trim() || !repoUrl) return;
        const userMsg = input.trim();
        setInput('');
        setMessages(prev => [...prev, { role: 'user', text: userMsg }]);
        setLoading(true);

        try {
            const response = await fetch('http://localhost:8080/ask', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ repo: repoUrl, question: userMsg })
            });
            if (!response.ok) throw new Error('Failed to fetch AI reply');
            const data = await response.json();
            setMessages(prev => [...prev, { role: 'ai', text: data.answer }]);
        } catch (e: any) {
            setMessages(prev => [...prev, { role: 'ai', text: `System Error: ${e.message}` }]);
        } finally {
            setLoading(false);
        }
    };

    return (
        <div className="card glass ai-assistant">
            <h2 className="title ai-title">✨ Repo AI Assistant</h2>
            <div className="chat-window">
                {messages.length === 0 ? (
                    <div className="chat-placeholder">Ask me anything about the repository's architecture, security, or code quality!</div>
                ) : (
                    messages.map((m, idx) => (
                        <div key={idx} className={`chat-bubble ${m.role}`}>
                            <div className="bubble-text">{m.text}</div>
                        </div>
                    ))
                )}
                {loading && <div className="chat-bubble ai"><div className="typing-indicator"><span></span><span></span><span></span></div></div>}
                <div ref={endRef} />
            </div>
            <div className="chat-input-area">
                <input
                    type="text"
                    placeholder="E.g., Are there any major security vulnerabilities?"
                    value={input}
                    onChange={(e) => setInput(e.target.value)}
                    onKeyDown={(e) => e.key === 'Enter' && handleAsk()}
                    className="input-field chat-input"
                    disabled={!repoUrl}
                />
                <button onClick={handleAsk} disabled={loading || !input.trim() || !repoUrl} className="primary-btn chat-send">
                    Send
                </button>
            </div>
        </div>
    );
};
