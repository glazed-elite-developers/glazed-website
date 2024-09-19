import React, { FC, ReactNode, RefObject } from 'react'
import { cx, css } from '@emotion/css'
import { Colors } from '../../styles/Theme'
import ResizeMonitorContainer from './resize-monitor/ResizeMonitorContainer'

const Styles = {
  wrapper: css`
    min-height: 100%;
    flex: 1 0 auto;
    background-color: ${Colors.white};
  `,
}

interface FullPageSlideProps {
  children?: ReactNode
  id?: string
  className?: string
  innerRef?: RefObject<HTMLElement>
  onResize?: (rect?: DOMRect) => void
}

const FullPageSlide: FC<FullPageSlideProps> = ({
  children,
  id,
  className,
  innerRef,
  onResize,
}) => {
  return (
    <ResizeMonitorContainer
      id={id}
      innerRef={innerRef}
      className={cx([Styles.wrapper, className])}
      componentTag="section"
      onResize={onResize}
    >
      {children}
    </ResizeMonitorContainer>
  )
}

export default FullPageSlide
