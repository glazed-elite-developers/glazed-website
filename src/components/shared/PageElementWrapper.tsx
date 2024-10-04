import React, { FC, MutableRefObject, ReactNode } from 'react'
import { css } from '@emotion/css'
import ScrollContainer from './scroll-container'
import ModalsController from './modals/ModalsController'
import { useScrollRestoration } from './gatsby-react-router-scroll'
import { GetScrollRestorationBehaviorFunction } from './gatsby-react-router-scroll/use-scroll-restoration'

const Styles = {
  wrapper: css`
    height: 100%;
    display: flex;
    flex-direction: column;
    flex: 1 1 0.0000001rem;
  `,
  content: css`
    height: 100%;
    display: flex;
    flex-direction: column;
    flex: 1 0 auto;
  `,
}

interface PageElementWrapperProps {
  children: ReactNode
}

export const getScrollRestorationBehaviour: GetScrollRestorationBehaviorFunction<{
  state: { preventDefaultScrollBehavior?: boolean }
}> = (location) => {
  const preventDefaultScrollBehavior =
    location.state?.state?.preventDefaultScrollBehavior || false
  const action = (location as { action?: string }).action
  return action === 'PUSH'
    ? !preventDefaultScrollBehavior
      ? 'scroll-to-top'
      : 'none'
    : 'restore-state-value'
}

const PageElementWrapper: FC<PageElementWrapperProps> = ({ children }) => {
  const scrollRestoration = useScrollRestoration(
    'scrollContainer',
    getScrollRestorationBehaviour
  )
  return (
    <ModalsController>
      <ScrollContainer
        innerRef={scrollRestoration.ref as MutableRefObject<HTMLDivElement>}
        className={Styles.wrapper}
        contentClassName={Styles.content}
        onScroll={scrollRestoration.onScroll}
      >
        {children}
      </ScrollContainer>
    </ModalsController>
  )
}

export default PageElementWrapper
