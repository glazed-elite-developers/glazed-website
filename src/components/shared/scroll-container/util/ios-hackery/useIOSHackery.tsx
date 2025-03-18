import { css } from '@emotion/react'
import { useCallback, useEffect, useRef } from 'react'

const Styles = {
  iOSScrollFix: css`
    flex: 1 0 calc(100% + 0.2rem);
  `,
}

/**
 * List of iOS devices that need the scroll fix.
 */
export const iDevices = [
  'iPad Simulator',
  'iPhone Simulator',
  'iPod Simulator',
  'iPad',
  'iPhone',
  'iPod',
]

/**
 * Detects iOS devices.
 *
 * @returns {Boolean} Whether its a iOS platform or not.
 */
export const isIOSDevice = () =>
  typeof window !== 'undefined' &&
  !!window.navigator.platform &&
  Boolean(iDevices.find((device) => navigator.platform === device))

/**
 * Scrolls a given DOM element up or down one pixel if the scroll position has reached the limits, so that the same element
 * will trigger the rubber band scrolling effects when the user scrolls it after its limits after that. This way, we prevent
 * the document's body to trigger that effects, so the user doesn't have to wait for the animation to finish to keep scrolling
 * in the scroll container.
 *
 * @see http://blog.christoffer.online/2015-06-10-six-things-i-learnt-about-ios-rubberband-overflow-scrolling/
 *
 * @param {DOMElement} element - DOM element.
 */
export const scrollElementIfOnLimit = (element: HTMLElement) => {
  const top = element.scrollTop

  if (top === 0) {
    element.scrollTop = 1
  } else if (top === element.scrollHeight - element.offsetHeight) {
    element.scrollTop = top - 1
  }
}

/**
 * Hook that prevents the rubber band scrolling effect from happening in the document's body, when we use
 * other DOM element as the root scroll container.
 *
 * @param {Object} props - Component props.
 *
 * @returns {Object} Component wrapped props.
 */
const useIOSHackery = ({
  onTouchStart = () => {},
  onTouchEnd = () => {},
  onScrollEnd = () => {},
  innerRef = () => {},
  ...props
}: any) => {
  const containerRef = useRef<HTMLElement | null>(null)
  const didTouchEndRef = useRef(true)

  const scrollIfOnLimit = useCallback(() => {
    if (containerRef.current) {
      scrollElementIfOnLimit(containerRef.current)
    }
  }, [])

  /**
   * Adds a scrolling behaviour that prevents the page body from scrolling.
   *
   * @param {Object} event - Event instance.
   *
   * @returns {Function} Handler.
   */
  const handleTouchStart = useCallback(
    (event: TouchEvent) => {
      scrollIfOnLimit()

      if (didTouchEndRef.current) {
        didTouchEndRef.current = false
      }

      return onTouchStart(event)
    },
    [scrollIfOnLimit, onTouchStart]
  )

  const handleTouchEnd = useCallback(
    (event: TouchEvent) => {
      didTouchEndRef.current = true

      return onTouchEnd(event)
    },
    [onTouchEnd]
  )

  const handleScrollEnd = useCallback(
    (...args) => {
      if (didTouchEndRef.current) {
        scrollIfOnLimit()
      }

      onScrollEnd(...args)
    },
    [scrollIfOnLimit, onScrollEnd]
  )

  const attachTouchEventListeners = useCallback(() => {
    if (containerRef.current) {
      containerRef.current.addEventListener('touchstart', handleTouchStart, {
        capture: true,
      })
      containerRef.current.addEventListener('touchend', handleTouchEnd, {
        capture: true,
      })
    }
  }, [handleTouchStart, handleTouchEnd])

  const detachTouchEventListeners = useCallback(() => {
    if (containerRef.current) {
      containerRef.current.removeEventListener('touchstart', handleTouchStart)
      containerRef.current.removeEventListener('touchend', handleTouchEnd)
    }
  }, [handleTouchStart, handleTouchEnd])

  const handleRef = useCallback(
    (ref) => {
      containerRef.current = ref
      innerRef(ref)
    },
    [innerRef]
  )

  useEffect(() => {
    setTimeout(scrollIfOnLimit)
    attachTouchEventListeners()
    return detachTouchEventListeners
  }, [])

  return {
    ...props,
    innerRef: handleRef,
    scrollingTimeout: 66,
    passiveScrollEvent: false,
    contentCSS: [Styles.iOSScrollFix, props.contentCSS],
    onScrollEnd: handleScrollEnd,
  }
}

export default useIOSHackery
