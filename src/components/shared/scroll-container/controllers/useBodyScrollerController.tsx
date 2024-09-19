import { initialBoundingRect, initialScrollPosition } from '../ScrollContext'

/**
 * Stores the original pointer events value when it is disabled while scrolling.
 */
export let originalBodyPointerEvents: CSSStyleDeclaration['pointerEvents'] =
  'initial'

/**
 * Returns an object with the window's current dimensions.
 *
 * @returns Window dimensions.
 */
export const getBoundingRect = () =>
  typeof window !== 'undefined'
    ? {
        top: 0,
        right: 0,
        bottom: 0,
        left: 0,
        width: typeof window.innerWidth === 'number' ? innerWidth : 0,
        height: typeof window.innerHeight === 'number' ? innerHeight : 0,
      }
    : initialBoundingRect

/**
 * Returns the document's scroll position data.
 *
 * @returns Scroll position data.
 */
export const getScrollPosition = () =>
  typeof window !== 'undefined'
    ? {
        scrollTop:
          'scrollY' in window
            ? window.scrollY
            : document.documentElement.scrollTop,
        scrollLeft:
          'scrollX' in window
            ? window.scrollX
            : document.documentElement.scrollLeft,
        scrollWidth: document.documentElement.scrollWidth,
        scrollHeight: document.documentElement.scrollHeight,
      }
    : initialScrollPosition

/**
 * Calls the window.scroll method.
 *
 * @returns Undefined.
 */
export const scrollTo = (...args: any) => window.scroll(...args)

/**
 * Attaches a given scroll event handler to the current window.
 *
 * @param passive - Whether the event listener should be passive or not.
 *
 * @returns Undefined.
 */
export const createAttachScrollListener =
  (passive = true) =>
  (scrollHandler: (this: Window, event: Event) => void) =>
    window.addEventListener('scroll', scrollHandler, { passive })

/**
 * Detaches a given scroll event handler from the current window.
 *
 * @param scrollHandler - Scroll event handler.
 *
 * @returns Undefined.
 */
export const detachScrollListener = (
  scrollHandler: (this: Window, event: Event) => void
) => window.removeEventListener('scroll', scrollHandler)

/**
 * Disables the pointer events for the body of the current document.
 */
export const disablePointerEvents = () => {
  originalBodyPointerEvents = document.body.style.pointerEvents
  document.body.style.pointerEvents = 'none'
}

/**
 * Restores the pointer events for the body of the current document.
 */
export const enablePointerEvents = () => {
  document.body.style.pointerEvents = originalBodyPointerEvents
}

export type BodyScrollerControllerProps = {
  passiveScrollEvent?: boolean
}

export const useBodyScrollerController = (
  props: BodyScrollerControllerProps
) => ({
  ...props,
  scrollTo,
  getBoundingRect,
  getScrollPosition,
  detachScrollListener,
  disablePointerEvents,
  enablePointerEvents,
  attachScrollListener: createAttachScrollListener(props.passiveScrollEvent),
})

export default useBodyScrollerController
