import { css, cx } from '@emotion/css'
import React, {
  ReactNode,
  RefObject,
  CSSProperties,
  FC,
  createElement,
} from 'react'
import { ResizeMonitor } from './ResizeMonitor'

// Styles
const wrapper = css`
  position: relative;
`

// Component Props
interface ResizeMonitorContainerProps {
  children?: ReactNode
  onResize?: (rect?: DOMRect) => void
  className?: string
  id?: string
  innerRef?: RefObject<HTMLElement>
  style?: CSSProperties
  componentTag?: string
}

const ResizeMonitorContainer: FC<ResizeMonitorContainerProps> = ({
  children,
  onResize,
  className,
  id,
  innerRef,
  style,
  componentTag = 'div',
}) => {
  const classNames = cx(wrapper, className)

  return createElement(
    componentTag,
    {
      ref: innerRef,
      className: classNames,
      id,
      style,
    },
    <>
      {children}
      <ResizeMonitor onResize={onResize} />
    </>
  )
}

export default ResizeMonitorContainer
