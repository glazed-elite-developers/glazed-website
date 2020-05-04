/**
 * Implement Gatsby's SSR (Server Side Rendering) APIs in this file.
 *
 * See: https://www.gatsbyjs.org/docs/ssr-apis/
 */
import * as React from 'react'
import { renderToString } from 'react-dom/server'
import { extractCritical } from 'emotion-server'
import { cache } from 'emotion'
import { CacheProvider } from '@emotion/core'
import RootElementWrapper from 're/RootElementWrapper'

export const replaceRenderer = ({ replaceBodyHTMLString, bodyComponent, setHeadComponents }) => {
  const { html, ids, css } = extractCritical(
    renderToString(<CacheProvider value={cache}>{bodyComponent}</CacheProvider>)
  )
  setHeadComponents([
    <style
      data-emotion-css={ids.join(' ')}
      dangerouslySetInnerHTML={{
        __html: css,
      }}
    />,
  ])
  replaceBodyHTMLString(html)
}

export const wrapRootElement = ({ element }) => {
  return <RootElementWrapper>{element}</RootElementWrapper>
}
