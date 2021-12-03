import React from 'react'
import Highlight, { defaultProps } from 'prism-react-renderer'

export default ({ children, className }) => {
  const language = className ? className.replace(/language-/, '') : 'javascript'

  return (
    <Highlight className={className} {...defaultProps} code={children} language={language} theme={undefined}>
      {({ className, style, tokens, getLineProps, getTokenProps }) => (
        <code className={className} style={style}>
          {tokens.slice(0, tokens.length - 1).map((line, i) => (
            <div key={i} {...getLineProps({ line, key: i })}>
              {line.map((token, key) => (
                <span key={key} {...getTokenProps({ token, key })} />
              ))}
            </div>
          ))}
        </code>
      )}
    </Highlight>
  )
}
