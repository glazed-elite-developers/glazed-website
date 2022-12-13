import React from 'react'
import Prism from 'prism-react-renderer/prism'
import Highlight, { defaultProps } from 'prism-react-renderer'

if (typeof global !== 'undefined') {
  global.Prism = Prism
} else {
  window.Prism = Prism
}

require('prismjs/components/prism-swift')

export default ({ children, className }) => {
  const language = className ? className.replace(/language-/, '') : 'javascript'
  return (
    <Highlight className={className} {...defaultProps} code={children} language={language} theme={undefined}>
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
  )
}
