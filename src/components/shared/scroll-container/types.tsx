import { ReactNode } from 'react'

export type ScrollContainerBaseProps = {
  children?: ReactNode
  onScroll?: React.DOMAttributes<HTMLDivElement>['onScroll']
  onScrollEnd?: () => void
  hasRootContainer?: boolean
  useBodyScroller?: boolean
  noPointerEventsWhileScrolling?: boolean
}
