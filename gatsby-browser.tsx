import React from 'react'
import { GatsbyBrowser } from 'gatsby'
import RootElementWrapper from '@components/shared/RootElementWrapper'
import PageElementWrapper from '@components/shared/PageElementWrapper'

export const wrapRootElement: GatsbyBrowser['wrapRootElement'] = (props) => {
  return <RootElementWrapper>{props.element}</RootElementWrapper>
}

export const wrapPageElement: GatsbyBrowser['wrapPageElement'] = (props) => {
  return <PageElementWrapper>{props.element}</PageElementWrapper>
}

export const shouldUpdateScroll: GatsbyBrowser['shouldUpdateScroll'] = (
  props
) => {
  const preventDefaultScrollBehavior =
    props.routerProps.location.state?.state?.preventDefaultScrollBehavior ||
    false
  const action = (props.routerProps.location as { action?: string }).action
  return action === 'PUSH' ? !preventDefaultScrollBehavior : false
}
