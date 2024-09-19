import { UIEventHandler, useCallback } from 'react'

export type NoPointerEventsWhileScrollingProps = {
  onScroll: UIEventHandler<HTMLDivElement>
  onScrollEnd: () => void
  enablePointerEvents?: () => void
  disablePointerEvents?: () => void
}

/**
 * Hook that enhances ScrollContainer's behavior disabling the pointer events in it while scrolling.
 */
const useNoPointerEventsWhileScrolling = (
  props: NoPointerEventsWhileScrollingProps
) => {
  const onScroll: UIEventHandler<HTMLDivElement> = useCallback(
    (...args: Parameters<UIEventHandler<HTMLDivElement>>) => {
      props.disablePointerEvents?.()
      props.onScroll?.(...args)
    },
    [props.disablePointerEvents, props.onScroll]
  )
  const onScrollEnd = useCallback(() => {
    props.enablePointerEvents?.()
    props.onScrollEnd?.()
  }, [props.enablePointerEvents, props.onScrollEnd])

  return {
    ...props,
    onScroll,
    onScrollEnd,
  }
}

export default useNoPointerEventsWhileScrolling
