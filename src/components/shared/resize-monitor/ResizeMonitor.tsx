import { css, cx } from '@emotion/css'
import throttle from '@helpers/throttle'
import React, { useCallback, useEffect, useRef, useState } from 'react'

const wrapper = css`
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: -1;
  overflow: hidden;
  display: block;
  visibility: hidden;
  pointer-events: none;
`

interface ResizeMonitorProps {
  className?: string
  onResize?: (rect?: DOMRect) => void
}

const ResizeMonitor: React.FC<ResizeMonitorProps> = ({
  className,
  onResize,
}) => {
  const placeholderObjectRef = useRef<HTMLObjectElement | null>(null)
  const objectDefaultViewRef = useRef<Window | null>(null)
  const [hasData, setHasData] = useState(false)

  const dispatchResizeEvent = useCallback(
    throttle(() => {
      if (onResize) {
        const element = placeholderObjectRef.current
        onResize(element?.getBoundingClientRect())
      }
    }, 100),
    [onResize]
  )

  const handleContentResize = useCallback(() => {
    dispatchResizeEvent()
  }, [dispatchResizeEvent])

  const handleLoad = useCallback(() => {
    const element = placeholderObjectRef.current
    if (element) {
      const objectDefaultView = element.contentDocument?.defaultView
      if (objectDefaultView) {
        objectDefaultViewRef.current = objectDefaultView
        objectDefaultView.addEventListener('resize', handleContentResize)
        dispatchResizeEvent()
      }
    }
  }, [handleContentResize, dispatchResizeEvent])

  const data = hasData ? 'about:blank' : undefined

  useEffect(() => {
    setHasData(true)
    return () => {
      const objectDefaultView = objectDefaultViewRef.current
      if (objectDefaultView) {
        objectDefaultView.removeEventListener('resize', handleContentResize)
      }
    }
  }, [handleContentResize])

  return (
    <object
      ref={placeholderObjectRef}
      aria-label="resize monitor placeholder"
      role="presentation"
      type="text/html"
      data={data}
      onLoad={handleLoad}
      className={cx(wrapper, className)}
    />
  )
}

export { ResizeMonitor }
export default ResizeMonitor
