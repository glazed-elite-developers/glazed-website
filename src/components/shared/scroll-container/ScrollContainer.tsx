import React, {
  ReactNode,
  UIEventHandler,
  useCallback,
  useContext,
  useEffect,
  useMemo,
} from 'react'
import useIOSHackery, { isIOSDevice } from './util/ios-hackery/useIOSHackery'
import ScrollContext, {
  ScrollContextProvider,
  useScrollerAPI,
} from './ScrollContext'
import useScrollerController, {
  ScrollerControllerProps,
} from './controllers/useScrollerController'
import useBodyScrollerController, {
  BodyScrollerControllerProps,
} from './controllers/useBodyScrollerController'
import useNoPointerEventsWhileScrolling from './enhancers/useNoPointerEventsWhileScrolling'
import useOnScrollEndHandler from './enhancers/useOnScrollEndHandler'
import { compose, identity } from '@helpers'
import { ScrollContainerBaseProps } from './types'

type ScrollContainerProps = ScrollContainerBaseProps &
  (
    | ({ useBodyScroller: true } & BodyScrollerControllerProps)
    | ({ useBodyScroller?: false } & ScrollerControllerProps)
  )

const ScrollContainer = ({
  useBodyScroller,
  noPointerEventsWhileScrolling = false,
  onScroll,
  ...baseProps
}: ScrollContainerProps) => {
  const scrollContext = useContext(ScrollContext)
  const needsIOSHackery = useMemo(
    () => isIOSDevice() && !scrollContext.hasRootContainer,
    [scrollContext.hasRootContainer]
  )
  const useEnhancers = useMemo(
    () =>
      compose(
        needsIOSHackery ? useIOSHackery : identity,
        useBodyScroller ? useBodyScrollerController : useScrollerController,
        noPointerEventsWhileScrolling
          ? useNoPointerEventsWhileScrolling
          : identity,
        (props: { onScrollEnd: () => void }) =>
          props.onScrollEnd !== undefined ? useOnScrollEndHandler(props) : props
      ),
    []
  )
  const props = useEnhancers(baseProps)
  const [scrollerAPI, notifySubscribedListeners] = useScrollerAPI(props)

  /**
   * Notifies all scroll event listeners for a scroll event and disables the pointer events for the scroll container
   * for better performance.
   */
  const handleScroll = useCallback(
    (...args: Parameters<UIEventHandler<HTMLDivElement>>) => {
      notifySubscribedListeners()
      onScroll?.(...args)
    },
    [notifySubscribedListeners, onScroll]
  )

  useEffect(() => {
    props.attachScrollListener(handleScroll)
    return () => props.detachScrollListener(handleScroll)
  }, [handleScroll])

  return (
    <ScrollContextProvider scrollerAPI={scrollerAPI}>
      {props.children}
    </ScrollContextProvider>
  )
}

export default ScrollContainer
