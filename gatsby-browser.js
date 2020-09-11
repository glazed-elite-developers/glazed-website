import * as React from 'react'
import RootElementWrapper from 're/RootElementWrapper'
import PageElementWrapper from 're/PageElementWrapper'

export const wrapRootElement = ({ element }) => {
  return <RootElementWrapper>{element}</RootElementWrapper>
}

export const wrapPageElement = ({ element, props }) => {
  return <PageElementWrapper>{element}</PageElementWrapper>
}

export const shouldUpdateScroll = ({ routerProps }) => {
  const { state: { preventDefaultScrollBehavior = false } = {} } = routerProps.location.state || {}
  return routerProps.location.action === 'PUSH' ? !preventDefaultScrollBehavior : false
}
