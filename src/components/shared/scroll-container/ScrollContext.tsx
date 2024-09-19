import React, {
  createContext,
  ReactNode,
  useCallback,
  useContext,
  useMemo,
  useRef,
} from 'react'
import { boundingRect, scrollPosition } from './util/dimensions'

export const initialScrollPosition: scrollPosition = {
  scrollTop: 0,
  scrollLeft: 0,
  scrollWidth: 0,
  scrollHeight: 0,
}

export const initialBoundingRect: boundingRect = {
  top: 0,
  right: 0,
  bottom: 0,
  left: 0,
  width: 0,
  height: 0,
}

export type scrollerAPI = {
  registerScrollListener: (component: unknown, handler: () => void) => void
  unregisterScrollListener: (component: unknown) => void
  getScrollPosition: () => scrollPosition
  getBoundingRect: () => boundingRect
  scrollTo: (scrollToOptions: ScrollToOptions) => void
}

const defaultScrollerAPI: scrollerAPI = {
  registerScrollListener: () => {},
  unregisterScrollListener: () => {},
  getScrollPosition: () => initialScrollPosition,
  getBoundingRect: () => initialBoundingRect,
  scrollTo: () => {},
}

type ScrollContext = {
  hasRootContainer: boolean
  closestScroller: scrollerAPI
  rootScroller: scrollerAPI
}

const defaultContextValue = {
  // Scroll container instances highest in the component tree set this flag to true,
  // which we then use to prevent the rubber band scroll animations in iOS.
  hasRootContainer: false,
  closestScroller: defaultScrollerAPI,
  rootScroller: defaultScrollerAPI,
}

let API = {}

/**
 * Scroll context object, that contains both ScrollContext.Provider and ScrollContext.Consumer.
 */
const ScrollContext = createContext<ScrollContext>(defaultContextValue)

type HookArguments = {
  getScrollPosition: () => scrollPosition
  getBoundingRect: () => boundingRect
  scrollTo: (options: ScrollToOptions) => void
}

type HookResult = [scrollerAPI, () => void]

export const useScrollerAPI: (args: HookArguments) => HookResult = ({
  getScrollPosition,
  getBoundingRect,
  scrollTo,
}) => {
  const registeredScrollListenersRef = useRef<
    Array<{ component: unknown; handler: () => void }>
  >([])

  /**
   * Register a given component that wants to be notified when scroll events occur.
   *
   * @param {Component} component - Component instance.
   * @param {Function} handler - Component handler.
   *
   * @returns {undefined} Undefined.
   */
  const registerScrollListener = useCallback(
    (component: unknown, handler: () => void) =>
      registeredScrollListenersRef.current.push({ component, handler }),
    [registeredScrollListenersRef]
  )

  /**
   * Unregisters a given component that no longer wants to be notified when scroll events occur.
   *
   * @param {Component} component - Component instance.
   *
   * @returns {undefined} Undefined.
   */
  const unregisterScrollListener = useCallback(
    (component: unknown) => {
      registeredScrollListenersRef.current =
        registeredScrollListenersRef.current.filter(
          (subscription) => subscription.component !== component
        )
    },
    [registeredScrollListenersRef]
  )

  /**
   * Calls the handlers of all registered scroll event listeners.
   */
  const notifySubscribedListeners = useCallback(() => {
    for (const subscription of registeredScrollListenersRef.current) {
      subscription.handler()
    }
  }, [registeredScrollListenersRef])

  /**
   * Builds the context API for interacting with this scroll container.
   */
  const scrollerAPI = useMemo(
    () => ({
      registerScrollListener,
      unregisterScrollListener,
      getScrollPosition,
      getBoundingRect,
      scrollTo,
    }),
    [
      registerScrollListener,
      unregisterScrollListener,
      getScrollPosition,
      getBoundingRect,
      scrollTo,
    ]
  )

  return [scrollerAPI, notifySubscribedListeners]
}

type Props = {
  scrollerAPI: scrollerAPI
  children?: ReactNode
}

export const ScrollContextProvider = ({ scrollerAPI, children }: Props) => {
  const scrollContext = useContext(ScrollContext)
  const scrollContextToPassDown = useMemo(
    () =>
      scrollContext.hasRootContainer
        ? { ...scrollContext, closestScroller: scrollerAPI }
        : {
            hasRootContainer: true,
            closestScroller: scrollerAPI,
            rootScroller: scrollerAPI,
          },
    [scrollerAPI, scrollContext.hasRootContainer]
  )

  return (
    <ScrollContext.Provider value={scrollContextToPassDown}>
      {children}
    </ScrollContext.Provider>
  )
}

export default ScrollContext
