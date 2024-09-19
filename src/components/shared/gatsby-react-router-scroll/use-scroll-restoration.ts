import { useLocation, WindowLocation } from '@reach/router'
import { ScrollContext } from './scroll-handler'
import {
  useRef,
  useContext,
  useLayoutEffect,
  MutableRefObject,
  useCallback,
  useMemo,
} from 'react'

interface IScrollRestorationProps<T extends HTMLElement> {
  ref: MutableRefObject<T | null>
  onScroll(): void
}

export type ScrollRestorationBehavior =
  | 'scroll-to-top'
  | 'restore-state-value'
  | 'none'
export type GetScrollRestorationBehaviorFunction<State> = (
  location: WindowLocation<State>
) => ScrollRestorationBehavior

export function useScrollRestoration<
  T extends HTMLElement,
  State extends unknown
>(
  identifier: string,
  getScrollRestorationBehaviour: GetScrollRestorationBehaviorFunction<State> = () =>
    'restore-state-value'
): IScrollRestorationProps<T> {
  const location = useLocation() as WindowLocation<State>
  const state = useContext(ScrollContext)
  const ref = useRef<T>(null)
  const stateKey = useMemo(
    () => `${identifier}#${location.key}`,
    [location.key, identifier]
  )
  const onScroll = useCallback(() => {
    if (ref.current) {
      state.save(location, identifier, ref.current.scrollTop)
    }
  }, [stateKey])

  useLayoutEffect((): void => {
    if (ref.current) {
      const restorationBehavior = getScrollRestorationBehaviour(location)

      if (restorationBehavior === 'scroll-to-top') {
        ref.current.scrollTo(0, 0)
      } else if (restorationBehavior === 'restore-state-value') {
        const position = state.read(location, identifier)
        ref.current.scrollTo(0, position || 0)
      }
    }
  }, [stateKey])

  return { ref, onScroll }
}
