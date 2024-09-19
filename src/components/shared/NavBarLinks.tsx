import React, { MouseEvent } from 'react'
import { css, cx } from '@emotion/css'
import { Link } from 'gatsby'
import { Breakpoints, Colors } from '@styles/Theme'

const Styles = {
  wrapper: css`
    display: flex;
    pointer-events: auto;
  `,
  lightTheme: css`
    color: ${Colors.almostWhite};
  `,
  darkTheme: css`
    color: ${Colors.darkGreyDarker};
  `,
  logoWrapper: css`
    flex: 0 0 auto;
  `,
  item: css`
    padding: 0.25rem;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 0.75rem;
    }
  `,
  dimmed: css`
    opacity: 0.6;
  `,
  explore: css`
    display: none;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      display: flex;
    }
  `,
}

const items: [string, string, boolean][] = [
  ['/#case-studies', 'case studies', true],
  ['/#about', 'about', true],
  ['/#team', 'team', true],
  ['/#manifesto', 'manifesto', true],
  ['https://blog.glazedsolutions.com', 'blog', false],
]

interface NavBarLinksProps {
  className?: string
  useDarkNavBarLinks?: boolean
  currentPageIndex: number
  onNavBarLinkClick?: (
    event: MouseEvent<HTMLAnchorElement>,
    link: string
  ) => void
}

function NavBarLinks({
  className,
  useDarkNavBarLinks = false,
  currentPageIndex,
  onNavBarLinkClick,
}: NavBarLinksProps) {
  const contextualStyles = useDarkNavBarLinks
    ? Styles.darkTheme
    : Styles.lightTheme

  return (
    <div className={cx([Styles.wrapper, className, contextualStyles])}>
      <div className={cx([Styles.dimmed, Styles.item, Styles.explore])}>
        explore:
      </div>
      {items.map(([link, label, isInternalLink], index) => {
        const isDimmed = index !== currentPageIndex - 1
        const onClick = onNavBarLinkClick
          ? (event: MouseEvent<HTMLAnchorElement>) =>
              onNavBarLinkClick(event, link)
          : undefined

        if (isInternalLink) {
          return (
            <Link
              to={link}
              className={cx([
                Styles.item,
                isDimmed && Styles.dimmed,
                contextualStyles,
              ])}
              onClick={onClick}
              replace
              key={index}
            >
              // {label}
            </Link>
          )
        } else {
          return (
            <a
              className={cx([
                Styles.item,
                isDimmed && Styles.dimmed,
                contextualStyles,
              ])}
              href={link}
              key={index}
            >
              // {label}
            </a>
          )
        }
      })}
    </div>
  )
}

export default NavBarLinks
