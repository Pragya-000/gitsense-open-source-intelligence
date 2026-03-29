import { useState } from 'react'
import './index.css'
import { RepoOverview } from './components/RepoOverview'
import { AiAssistant } from './components/AiAssistant'

function App() {
  const [activeRepo, setActiveRepo] = useState<string>('');

  return (
    <div className="app-container">
      <div className="background-shapes">
        <div className="shape shape-1"></div>
        <div className="shape shape-2"></div>
        <div className="shape shape-3"></div>
      </div>

      <header className="app-header glass">
        <div className="logo-section">
          <div className="logo-icon">GS</div>
          <h1>GitSense <span className="highlight">Intelligence</span></h1>
        </div>
        <p className="subtitle">X-Ray Vision for Open Source Ecosystems</p>
      </header>

      <main className="main-content">
        <section className="analysis-section fade-in">
          <RepoOverview onDataLoaded={(repo) => setActiveRepo(repo)} />
        </section>

        <section className={`assistant-section fade-in ${activeRepo ? 'active' : 'idle'}`}>
          <AiAssistant repoUrl={activeRepo} />
        </section>
      </main>

      <footer className="app-footer">
        <p>GitSense Open Source Intelligence - Strictly Offline FOSS AI</p>
      </footer>
    </div>
  )
}

export default App
