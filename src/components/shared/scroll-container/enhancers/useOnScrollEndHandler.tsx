import { UIEventHandler, useCallback, useRef } from 'react'
import {
  requestAnimationTimeout,
  cancelAnimationTimeout,
} from '../util/requestAnimationTimeout'

/**
 * Default timeout value for restoring pointer events after the scroll ends.
 */
export const DEFAULT_SCROLLING_TIMEOUT = 100

export type OnScrollEndHandlerProps = {
  scrollingTimeout?: number
  onScroll?: UIEventHandler<HTMLDivElement>
  onScrollEnd?: () => void
}

const useOnScrollEndHandler = ({
  scrollingTimeout = DEFAULT_SCROLLING_TIMEOUT,
  ...props
}: OnScrollEndHandlerProps) => {
  const scrollingTimeoutIdRef = useRef<{ id: number }>()

  /**
   * Restores the scroll container's pointer events.
   */
  const handleScrollEnd = useCallback(() => {
    scrollingTimeoutIdRef.current = undefined
    props.onScrollEnd?.()
  }, [scrollingTimeoutIdRef, props.onScrollEnd])

  /**
   * Clears an ongoing timeout, if one exists, triggered by a scroll event and registers a new one.
   */
  const refreshScrollingTimeoutId = useCallback(() => {
    if (scrollingTimeoutIdRef.current !== undefined) {
      cancelAnimationTimeout(scrollingTimeoutIdRef.current)
    }

    scrollingTimeoutIdRef.current = requestAnimationTimeout(
      handleScrollEnd,
      scrollingTimeout
    )
  }, [scrollingTimeoutIdRef, handleScrollEnd, scrollingTimeout])

  const handleScroll = useCallback(
    (...args: Parameters<UIEventHandler<HTMLDivElement>>) => {
      refreshScrollingTimeoutId()
      props.onScroll?.(...args)
    },
    [refreshScrollingTimeoutId, props.onScroll]
  )

  return { ...props, scrollingTimeout, onScroll: handleScroll }
}

export default useOnScrollEndHandler
