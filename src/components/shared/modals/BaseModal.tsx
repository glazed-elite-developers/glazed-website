import React, { FC, ReactNode, Ref, SyntheticEvent, useCallback } from 'react'
import { cx } from '@emotion/css'
import InOutCSSTransition, {
  AnimationState,
  Props as InOutCSSTransitionProps,
} from '../InOutCSSTransition'
import Styles from './BaseModal.styles'

const getAnimationClassNames = (animationState: AnimationState) => {
  switch (animationState) {
    case AnimationState.BeforeAppearing:
      return [
        Styles.wrapperBeforeAppearingAnimation,
        Styles.contentBeforeAppearingAnimation,
      ]
    case AnimationState.Visible:
      return [Styles.wrapperVisible, Styles.contentVisible]
    case AnimationState.Leaving:
      return [Styles.wrapperLeaving, Styles.contentLeaving]
  }
}

export type Props = Omit<
  InOutCSSTransitionProps,
  'children' | 'in' | 'onEnter' | 'onExit' | 'onExited'
> & {
  className?: string
  scrollContainerClassName?: string
  contentClassName?: string
  modalId?: number
  testId?: string
  onClose: () => void
  in: NonNullable<InOutCSSTransitionProps['in']>
  onEnter: NonNullable<InOutCSSTransitionProps['onEnter']>
  onExit: NonNullable<InOutCSSTransitionProps['onExit']>
  onExited: NonNullable<InOutCSSTransitionProps['onExited']>
  children?: ReactNode
}

const BaseModal: FC<Props> = ({
  className,
  scrollContainerClassName,
  contentClassName,
  onClose,
  modalId,
  testId,
  children,
  ...props
}) => {
  const onContentClick = useCallback(
    (event: SyntheticEvent) => event.stopPropagation(),
    []
  )
  const onWrapperClick = useCallback(
    (event: SyntheticEvent) => {
      event.stopPropagation()
      onClose()
    },
    [onClose]
  )

  return (
    <InOutCSSTransition {...props}>
      {(nodeRef, animationState) => {
        const [animationWrapperClassName, animationContentClassName] =
          getAnimationClassNames(animationState)

        return (
          <div
            ref={nodeRef as Ref<HTMLDivElement>}
            className={cx([
              Styles.wrapper,
              animationWrapperClassName,
              className,
            ])}
            onClick={onWrapperClick}
            data-testid={testId}
          >
            <div
              className={cx([
                Styles.scrollContainer,
                animationContentClassName,
                scrollContainerClassName,
              ])}
            >
              <div
                className={cx([animationContentClassName, contentClassName])}
                onClick={onContentClick}
              >
                {children}
              </div>
            </div>
          </div>
        )
      }}
    </InOutCSSTransition>
  )
}

export default BaseModal
