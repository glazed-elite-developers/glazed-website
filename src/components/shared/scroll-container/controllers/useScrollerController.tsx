import { cx } from '@emotion/css'
import React, {
  CSSProperties,
  MutableRefObject,
  ReactNode,
  useCallback,
  useMemo,
  useRef,
  useState,
} from 'react'
import {
  defaultScrollPosition,
  defaultBoundingRect,
  serializeScrollPosition,
  serializeBoundingRect,
} from '../util/dimensions'
import Styles from './styles'

export type ScrollerControllerProps = {
  lock?: boolean
  contentStyle?: React.CSSProperties
  className?: string
  contentClassName?: string
  children?: ReactNode
  passiveScrollEvent?: boolean
  innerRef?:
    | MutableRefObject<HTMLDivElement>
    | ((node: HTMLDivElement | null) => void)
  noPointerEventsWhileScrolling?: boolean
  scrollContainers?: unknown
  scrollingTimeout?: number
  onScroll?: React.DOMAttributes<HTMLDivElement>['onScroll']
  onScrollEnd?: React.DOMAttributes<HTMLDivElement>['onScroll']
  hasRootContainer?: boolean
  useBodyScroller?: boolean
}

const useScrollerController = ({
  lock,
  className,
  contentStyle,
  contentClassName,
  children,
  passiveScrollEvent,
  innerRef,
  noPointerEventsWhileScrolling,
  scrollContainers,
  scrollingTimeout,
  onScroll,
  onScrollEnd,
  hasRootContainer,
  useBodyScroller,
  ...remainingProps
}: ScrollerControllerProps) => {
  const containerRef = useRef<HTMLElement | undefined>(undefined)
  const [state, setState] = useState<Pick<CSSProperties, 'pointerEvents'>>({
    pointerEvents: 'unset',
  })

  /**
   * Returns an object with the dimensions of the wrapped scroll container.
   *
   * @returns {Object} Scroll container dimensions.
   */
  const getBoundingRect = useCallback(
    () =>
      containerRef.current
        ? serializeBoundingRect(containerRef.current.getBoundingClientRect())
        : defaultBoundingRect,
    [containerRef]
  )

  /**
   * Returns the scroll position data of the wrapped scroll container.
   *
   * @returns {Object} Scroll position data.
   */
  const getScrollPosition = useCallback(
    () =>
      containerRef.current
        ? serializeScrollPosition(containerRef.current)
        : defaultScrollPosition,
    [containerRef]
  )

  /**
   * Disables the pointer events of the scroll container.
   *
   * @returns {undefined} Undefined.
   */
  const disablePointerEvents = useCallback(
    () => setState({ pointerEvents: 'none' }),
    [setState]
  )

  /**
   * Restores the pointer events of the scroll container.
   *
   * @returns {undefined} Undefined.
   */
  const enablePointerEvents = useCallback(
    () => setState({ pointerEvents: 'unset' }),
    [setState]
  )

  /**
   * Attaches a given scroll event handler to the scroll container.
   *
   * @param scrollHandler - Scroll event handler.
   */
  const attachScrollListener = useCallback(
    (scrollHandler: (this: HTMLElement, event: Event) => void) => {
      if (containerRef.current) {
        containerRef.current.addEventListener('scroll', scrollHandler, {
          passive: passiveScrollEvent,
        })
      }
    },
    [containerRef]
  )

  /**
   * Detaches a given scroll event handler from the scroll container.
   *
   * @param scrollHandler - Scroll event handler.
   */
  const detachScrollListener = useCallback(
    (scrollHandler: (this: HTMLElement, event: Event) => void) => {
      if (containerRef.current) {
        containerRef.current.removeEventListener('scroll', scrollHandler)
      }
    },
    [containerRef]
  )

  /**
   * Stores the ref of the scroll container element.
   *
   * @param ref - Element ref.
   */
  const handleRef = useCallback(
    (element: HTMLDivElement) => {
      containerRef.current = element

      if (innerRef) {
        // Handling both callback and mutable ref types.
        if (typeof innerRef === 'function') {
          innerRef(element)
        } else if (innerRef) {
          innerRef.current = element
        }
      }
    },
    [containerRef, innerRef]
  )

  const contentStyleValue = useMemo<CSSProperties>(
    () => ({
      ...contentStyle,
      pointerEvents: state.pointerEvents,
    }),
    [state.pointerEvents]
  )

  return {
    ...remainingProps,
    scrollTo: containerRef.current?.scroll,
    getBoundingRect,
    getScrollPosition,
    attachScrollListener,
    detachScrollListener,
    disablePointerEvents,
    enablePointerEvents,
    children: (
      <div
        ref={handleRef}
        className={cx([Styles.wrapper, className, lock && Styles.lockScroll])}
        {...remainingProps}
      >
        <div
          className={cx([Styles.content, contentClassName])}
          style={contentStyleValue}
        >
          {children}
        </div>
      </div>
    ),
  }
}

export default useScrollerController
