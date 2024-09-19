import React, { ReactNode, FC } from 'react'
import { css, cx } from '@emotion/css'

// Styles
export const Styles = {
  wrapper: css`
    position: relative;
  `,
  mask: css`
    position: absolute;
    width: 100%;
    height: 100%;
    top: 0;
    left: 0;
    pointer-events: none;
    background-color: rgba(255, 255, 255, 0.35);
  `,
}

// Props interface for MaskContainer
interface MaskContainerProps {
  className?: string
  maskClassName?: string
  children: ReactNode
}

const MaskContainer: FC<MaskContainerProps> = ({
  className,
  maskClassName,
  children,
}) => {
  return (
    <div className={cx(Styles.wrapper, className)}>
      {children}
      <div className={cx(Styles.mask, maskClassName)} />
    </div>
  )
}

export default MaskContainer
