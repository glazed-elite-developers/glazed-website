import React, { FC } from 'react'
import { Language, Highlight, Prism } from 'prism-react-renderer'
import PrismCSS from '../../styles/PrismCSS'

// @TODO: Check this.
// // Check for global or window object and assign Prism
// if (typeof window !== 'undefined') {
//   ;(window as any).global.Prism = Prism
// } else {
//   ;(window as any).Prism = Prism
// }

// import 'prismjs/components/prism-swift'

interface CodeBlockProps {
  children: string
  className?: string
}

const CodeBlock: FC<CodeBlockProps> = ({ children, className }) => {
  const language: Language = className
    ? (className.replace(/language-/, '') as Language)
    : 'javascript'

  return (
    <>
      <PrismCSS />
      {/* Assuming PrismCSS is a valid component you use for styling */}
      <Highlight code={children} language={language} theme={undefined}>
        {({ className, style, tokens, getLineProps, getTokenProps }) => (
          <code className={className} style={style}>
            {tokens.map((line, i) => (
              <div key={i} {...getLineProps({ line, key: i })}>
                {line.map((token, key) => (
                  <span key={key} {...getTokenProps({ token, key })} />
                ))}
              </div>
            ))}
          </code>
        )}
      </Highlight>
    </>
  )
}

export default CodeBlock
