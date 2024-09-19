import React from 'react'
import { cx, css } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '../../styles/Theme'
import NavBarLinks from './NavBarLinks'
import ScrollContainer from './scroll-container/ScrollContainer'
import MobileFooterLayout from './MobileFooterLayout'

export const StyleVariables = {
  height: '3.75rem',
}

export const Styles = {
  wrapper: css`
    position: fixed;
    bottom: 0;
    left: 0;
    right: 0;
    display: flex;
    align-items: center;
    white-space: nowrap;
    transform: translateZ(0);

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      display: none;
    }
  `,
  navBarLinksWrapper: css`
    position: relative;
    overflow: hidden;
    flex: 1 1 auto;

    &::after {
      content: '';
      position: absolute;
      top: 0;
      right: 0;
      bottom: 0;
      left: 0;
      box-shadow: 0 0 10px 10px ${Colors.glazedBlueMidnight};
      pointer-events: none;
    }
  `,
  navBarLinksScrollerContent: css`
    flex-direction: row;
    font-family: ${Fonts.heading};
    font-size: 0.625rem;
  `,
  navBarLinks: css`
    display: flex;
    align-items: center;
    padding: 0 0.625rem;
    height: ${StyleVariables.height};
    opacity: 0.8;
  `,
}

interface MobileFooterProps {
  className?: string
  navBarLinksClassName?: string
  currentPageIndex?: number
  componentAtTheRight?: React.ReactNode
}

const MobileFooter: React.FC<MobileFooterProps> = ({
  className,
  navBarLinksClassName,
  currentPageIndex = 0,
  componentAtTheRight,
}) => {
  const combinedWrapperClassName = cx([Styles.wrapper, className])
  const combinedNavBarLinksClassName = cx([
    Styles.navBarLinks,
    navBarLinksClassName,
  ])

  return (
    <MobileFooterLayout className={combinedWrapperClassName}>
      <div className={Styles.navBarLinksWrapper}>
        <ScrollContainer contentClassName={Styles.navBarLinksScrollerContent}>
          <NavBarLinks
            currentPageIndex={currentPageIndex}
            className={combinedNavBarLinksClassName}
          />
        </ScrollContainer>
      </div>
      {componentAtTheRight}
    </MobileFooterLayout>
  )
}

export default MobileFooter
