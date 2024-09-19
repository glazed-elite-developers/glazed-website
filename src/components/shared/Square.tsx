import React from 'react'
import { cx, css } from '@emotion/css'

const Styles = {
  wrapper: css`
    position: relative;
    &::before {
      content: '';
      display: block;
      padding-top: 100%;
    }
  `,

  content: css`
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
  `,
}

interface SquareProps {
  children?: React.ReactNode
  className?: string
  contentClassName?: string
  onMouseEnter?: React.MouseEventHandler<HTMLDivElement>
}

const Square: React.FC<SquareProps> = ({
  children,
  className,
  contentClassName,
  onMouseEnter,
}) => {
  return (
    <div
      className={cx([Styles.wrapper, className])}
      onMouseEnter={onMouseEnter}
    >
      <div className={cx([Styles.content, contentClassName])}>{children}</div>
    </div>
  )
}

export default Square
