import * as React from 'react'
import { css, cx } from '@emotion/css'
import { Breakpoints, Colors, Fonts } from '../../styles/Theme'

const commonStyles = css`
  position: relative;
  font-weight: 700;
  font-family: ${Fonts.heading};
`

const Styles = {
  commonStyles,
  h1: css`
    ${commonStyles};
    font-size: ${1.5}rem;
    line-height: ${2.125}rem;
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: ${2.25}rem;
      line-height: ${2.75}rem;
    }
  `,

  h2: css`
    ${commonStyles};
    font-size: ${1.125}rem;
    color: ${Colors.grey};
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: ${2}rem;
    }
  `,

  h3: css`
    ${commonStyles};
    @media (min-width: ${Breakpoints.tabletLandscape}) {
      font-size: ${1.5}rem;
      line-height: ${2.75}rem;
    }
  `,

  h4: css`
    ${commonStyles};
  `,

  h5: css`
    ${commonStyles};
  `,

  h6: css`
    ${commonStyles};
  `,
}

export enum HeadingLevel {
  H1,
  H2,
  H3,
  H4,
  H5,
  H6,
}

interface HeadingProps {
  level: HeadingLevel
  className?: string
  children?: React.ReactNode
}

const Heading: React.FC<HeadingProps> = ({ level, className, children }) => {
  const Tag = `h${level + 1}` as JSX.ElementType
  const style = Styles[`h${level + 1}` as keyof typeof Styles]

  return <Tag className={cx([style, className])}>{children}</Tag>
}

export default Heading
