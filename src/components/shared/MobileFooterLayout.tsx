import React from 'react'
import { css, cx } from '@emotion/css'
import { Colors } from '../../styles/Theme'

const height = '3.75rem'

const styles = {
  wrapper: css`
    background-color: ${Colors.glazedBlueMidnight};
    height: ${height};
  `,
}

interface MobileFooterLayoutProps {
  className?: string
  children?: React.ReactNode
}

const MobileFooterLayout: React.FC<MobileFooterLayoutProps> = ({
  className,
  children,
}) => {
  return <footer className={cx([styles.wrapper, className])}>{children}</footer>
}

export default MobileFooterLayout
