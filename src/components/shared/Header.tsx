import React, {
  FC,
  memo,
  ReactNode,
  RefObject,
  SyntheticEvent,
  CSSProperties,
  useMemo,
} from 'react'
import { Link } from 'gatsby'
import SVG from './SVG'
import NavBarLinks from './NavBarLinks'
import LogoGlazedSvg from '@static/images/logo-glazed.svg'
import LogoGlazedOutlineSvg from '@static/images/logo-glazed-outline.svg'
import { cx, css } from '@emotion/css'
import ResizeMonitorContainer from './resize-monitor/ResizeMonitorContainer'
import { Breakpoints, Fonts } from '@styles/Theme'

export const StyleVariables = {
  height: '117px',
}

const Styles = {
  nav: css`
    display: flex;
    align-items: center;
    pointer-events: none;
    padding: 1.25rem;
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 2.1875rem 4.6875rem;
      height: ${StyleVariables.height};
    }
  `,

  logoWrapper: css`
    display: flex;
    flex: 0 0 auto;
    width: 122px;
    pointer-events: auto;
  `,

  logo: css`
    height: 2.1875rem;
  `,

  navBarLinks: css`
    display: none;
    flex: 1 1 0.000000001rem;
    font-family: ${Fonts.heading};
    font-size: 0.75rem;
    font-weight: 700;
    line-height: 0.875rem;
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      display: flex;
    }
  `,
}

interface NavBarProps {
  innerRef?: RefObject<HTMLDivElement>
  className?: string
  style?: CSSProperties
  componentAtTheRight?: ReactNode
  onNavBarLinkClick?: (event: SyntheticEvent, href: string) => void
  useDarkNavBarLinks?: boolean
  currentPageIndex?: number
  onResize?: (rect?: DOMRect) => void
}

const Header: FC<NavBarProps> = memo(
  ({
    innerRef,
    className,
    style,
    componentAtTheRight,
    onNavBarLinkClick,
    useDarkNavBarLinks = false,
    currentPageIndex = 0,
    onResize,
  }) => {
    const logoToUse = useDarkNavBarLinks ? LogoGlazedSvg : LogoGlazedOutlineSvg
    const navClassName = cx([Styles.nav, className])
    const logoElement = <SVG className={Styles.logo} asset={logoToUse} />
    const navBarLinksProps = {
      className: Styles.navBarLinks,
      useDarkNavBarLinks,
      currentPageIndex,
      onNavBarLinkClick,
    }
    const onLogoClick = useMemo(() => {
      if (onNavBarLinkClick) {
        return (event: SyntheticEvent) => onNavBarLinkClick(event, '/#hey')
      }
    }, [onNavBarLinkClick])

    return (
      <ResizeMonitorContainer
        innerRef={innerRef}
        className={navClassName}
        style={style}
        onResize={onResize}
      >
        <Link to="/#hey" className={Styles.logoWrapper} onClick={onLogoClick}>
          {logoElement}
        </Link>
        <NavBarLinks {...navBarLinksProps} />
        {componentAtTheRight}
      </ResizeMonitorContainer>
    )
  }
)

export default Header
