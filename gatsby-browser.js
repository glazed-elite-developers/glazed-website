import * as React from 'react'
import RootElementWrapper from 're/RootElementWrapper'

export const wrapRootElement = ({ element }) => {
  return <RootElementWrapper>{element}</RootElementWrapper>
}

export const shouldUpdateScroll = ({ routerProps, ...cenas }, ...args) => {
  console.log('should update?', cenas, args)
  const { state: { preventDefaultScrollBehavior = false } = {} } = routerProps.location.state || {}
  return !preventDefaultScrollBehavior
}
