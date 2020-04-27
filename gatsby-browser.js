import * as React from 'react'
import RootElementWrapper from 're/RootElementWrapper'

export const wrapRootElement = ({ element }) => {
  return <RootElementWrapper>{element}</RootElementWrapper>
}

export const shouldUpdateScroll = ({ routerProps }) => {
  const { state = {} } = routerProps.location.state || {}
  return !state.preventDefaultScrollBehavior
}
