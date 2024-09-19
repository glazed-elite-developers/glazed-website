import React, { ReactNode, memo } from 'react'
import { cx, css } from '@emotion/css'
import { Breakpoints } from '../../styles/Theme'

export const Styles = {
  wrapper: css`
    display: flex;
    flex-direction: column;
    flex: 1 1 0.00000001rem;
    height: 100%;
    padding: 4.1875rem 1.25rem 0;

    @media (min-width: ${Breakpoints.tabletLandscape}) {
      padding: 6.25rem 4.75rem 0;
    }
  `,
}

interface MainProps {
  className?: string
  children?: ReactNode
}

const Main: React.FC<MainProps> = ({ className, children }) => {
  return <main className={cx([Styles.wrapper, className])}>{children}</main>
}

export default memo(Main)
