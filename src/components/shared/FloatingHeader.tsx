import React, { SyntheticEvent, useMemo, useRef } from 'react'
import { css, cx } from '@emotion/css'
import Header from './Header'
import { Colors } from '../../styles/Theme'
import { useClosestScrollValues } from './scroll-container/scrollConnectors'

const Styles = {
  header: css`
    position: fixed;
    background-color: ${Colors.whiteTurquoise};
    transition: all 200ms ease-out;
  `,
  headerWithShadow: css`
    box-shadow: 0px 7px 15px rgba(0, 0, 0, 0.04);
  `,
}

type ScrollDirection = 'Up' | 'Down'

const scrollDirectionOffset = 15

const useHeaderPosition = (): [ScrollDirection, boolean] => {
  const scrollValues = useClosestScrollValues()
  const scrollTop = scrollValues.position.scrollTop
  const lastScrollDataRef = useRef<[number, ScrollDirection]>([scrollTop, 'Up'])
  const [lastScrollTop, lastScrollDirection] = lastScrollDataRef.current

  const scrollDirection: ScrollDirection =
    scrollTop > lastScrollTop + scrollDirectionOffset
      ? 'Down'
      : lastScrollTop <= scrollTop
      ? lastScrollDirection
      : 'Up'

  const shouldHaveBackground = scrollTop > scrollDirectionOffset
  lastScrollDataRef.current = [scrollTop, scrollDirection]

  return [scrollDirection, shouldHaveBackground]
}

interface FloatingHeaderProps {
  innerRef?: React.RefObject<HTMLElement>
  className?: string
  componentAtTheRight?: React.ReactNode
  onNavBarLinkClick?: (event: SyntheticEvent, path: string) => void
  useDarkNavBarLinks?: boolean
  currentPageIndex?: number
}

const FloatingHeader: React.FC<FloatingHeaderProps> = ({
  innerRef,
  className,
  componentAtTheRight,
  onNavBarLinkClick,
  useDarkNavBarLinks = false,
  currentPageIndex,
}) => {
  const [scrollDirection, shouldHaveBackground] = useHeaderPosition()

  // Conditionally set the header style based on scroll direction
  const headerStyle = useMemo(() => {
    return scrollDirection === 'Down'
      ? { transform: 'translateY(-100%)' }
      : undefined
  }, [scrollDirection])

  const headerClassName = shouldHaveBackground
    ? cx([Styles.header, Styles.headerWithShadow])
    : Styles.header

  return (
    <Header
      style={headerStyle}
      innerRef={innerRef}
      className={cx([headerClassName, className])}
      componentAtTheRight={componentAtTheRight}
      onNavBarLinkClick={onNavBarLinkClick}
      useDarkNavBarLinks={useDarkNavBarLinks}
      currentPageIndex={currentPageIndex}
    />
  )
}

export default FloatingHeader
export { scrollDirectionOffset, useHeaderPosition }
