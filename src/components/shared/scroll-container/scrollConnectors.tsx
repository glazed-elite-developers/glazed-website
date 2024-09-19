import { useCallback, useContext, useEffect, useRef, useState } from 'react'
import { throttleWithRAF } from '@helpers/throttle'
import ScrollContext from './ScrollContext'
import { boundingRect, scrollPosition } from './util/dimensions'

export enum ScrollerType {
  Root,
  Closest,
}

export interface ScrollValues {
  position: scrollPosition
  boundingRect: boundingRect
}

/**
 * Creates a hook that connects the scroll context api for a given scroller type.
 *
 * @param scrollerType - Scroller type.
 *
 * @returns Hook.
 */
const createUseScrollerAPI = (scrollerType: ScrollerType) => () => {
  const contextPropertyName =
    scrollerType === ScrollerType.Closest ? 'closestScroller' : 'rootScroller'
  return useContext(ScrollContext)[contextPropertyName]
}

/**
 * Hook that connects the scroll context api of the app's root scroller.
 */
export const useRootScrollerAPI = createUseScrollerAPI(ScrollerType.Root)

/**
 * Hook that connects the scroll context api of the scroller closest up in the component tree.
 */
export const useClosestScrollerAPI = createUseScrollerAPI(ScrollerType.Closest)

/**
 * Builds the props to be injected according to the current scrolling state and the component props.
 *
 * @param _state - State object.
 * @param scrollValues - Scroll state.
 *
 * @returns Props to be injected.
 */
export const defaultScrollStateReducer = (
  _state: ScrollValues,
  scrollValues: ScrollValues
) => scrollValues

export function createUseScrollValues(scrollerType: ScrollerType) {
  const useScrollerAPI = createUseScrollerAPI(scrollerType)

  return function useScrollValues<State = ScrollValues>(
    scrollStateReducer: (
      state: State | undefined,
      scrollValues: ScrollValues
    ) => State = defaultScrollStateReducer as unknown as (
      state: State | undefined,
      scrollValues: ScrollValues
    ) => State,
    scrollEventThrottler = throttleWithRAF
  ) {
    const listenerRef = useRef()
    const scrollerAPI = useScrollerAPI()
    const getScrollValues = useCallback(
      () => ({
        position: scrollerAPI.getScrollPosition(),
        boundingRect: scrollerAPI.getBoundingRect(),
      }),
      [scrollerAPI]
    )
    const [state, setState] = useState(
      scrollStateReducer(undefined, getScrollValues())
    )
    const handleScroll = useCallback(
      scrollEventThrottler(() =>
        setState((state: State) => scrollStateReducer(state, getScrollValues()))
      ),
      [getScrollValues, setState, scrollStateReducer, scrollEventThrottler]
    )

    useEffect(() => {
      scrollerAPI.registerScrollListener(listenerRef, handleScroll)
      handleScroll()
      return () => scrollerAPI.unregisterScrollListener(listenerRef)
    })

    return state
  }
}

export const useRootScrollValues = createUseScrollValues(ScrollerType.Root)
export const useClosestScrollValues = createUseScrollValues(
  ScrollerType.Closest
)
