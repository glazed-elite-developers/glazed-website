import * as React from 'react'
import { renderToString } from 'react-dom/server'
import { extractCritical } from '@emotion/server'
import { CacheProvider } from '@emotion/react'
import createCache from '@emotion/cache'
import {
  ReplaceRendererArgs,
  WrapRootElementBrowserArgs,
  WrapPageElementBrowserArgs,
} from 'gatsby'
import RootElementWrapper from '@components/shared/RootElementWrapper'
import PageElementWrapper from '@components/shared/PageElementWrapper'

const cache = createCache({ key: 'emotion-cache' })

export const replaceRenderer = ({
  replaceBodyHTMLString,
  bodyComponent,
  setHeadComponents,
}: ReplaceRendererArgs): void => {
  const { html, ids, css } = extractCritical(
    renderToString(<CacheProvider value={cache}>{bodyComponent}</CacheProvider>)
  )
  setHeadComponents([
    <style
      key="emotion-css"
      data-emotion-css={ids.join(' ')}
      dangerouslySetInnerHTML={{ __html: css }}
    />,
  ])
  replaceBodyHTMLString(html)
}

export const wrapRootElement = ({
  element,
}: WrapRootElementBrowserArgs): React.ReactElement => {
  return <RootElementWrapper>{element}</RootElementWrapper>
}

export const wrapPageElement = ({
  element,
  props,
}: WrapPageElementBrowserArgs): React.ReactElement => {
  return <PageElementWrapper {...props}>{element}</PageElementWrapper>
}
