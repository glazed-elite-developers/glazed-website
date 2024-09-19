import React, { ReactNode } from 'react'

interface Props {
  body: string
  htmlAttributes?: Record<string, unknown>
  headComponents?: ReactNode[]
  bodyAttributes?: Record<string, unknown>
  preBodyComponents?: ReactNode[]
  postBodyComponents?: ReactNode[]
}

export default function HTML(props: Props) {
  return (
    <html {...props.htmlAttributes}>
      <head>
        <meta charSet="utf-8" />
        <meta httpEquiv="x-ua-compatible" content="ie=edge" />
        <meta
          name="viewport"
          content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no, viewport-fit=contain"
        />
        {props.headComponents}
      </head>
      <body {...props.bodyAttributes}>
        {props.preBodyComponents}
        <div
          key={`body`}
          id="___gatsby"
          dangerouslySetInnerHTML={{ __html: props.body }}
        />
        {props.postBodyComponents}
      </body>
    </html>
  )
}
