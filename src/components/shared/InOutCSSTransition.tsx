import React, {
  FC,
  ReactNode,
  Ref,
  useCallback,
  useEffect,
  useRef,
  useState,
} from 'react'
import { Transition } from 'react-transition-group'
import { TransitionProps } from 'react-transition-group/Transition'

// The animation only works when we force the setState to be asynchronous.
// Modal fade animation states.
export enum AnimationState {
  BeforeAppearing = 'beforeAppearing',
  Visible = 'visible',
  Leaving = 'leaving',
}

// The animation only works when we force the setState to be asynchronous.
export const TICK = 17

export type Props = Pick<
  TransitionProps,
  | 'in'
  | 'mountOnEnter'
  | 'unmountOnExit'
  | 'onEnter'
  | 'onEntering'
  | 'onEntered'
  | 'onExit'
  | 'onExiting'
  | 'onExited'
  | 'nodeRef'
  | 'timeout'
  | 'addEndListener'
> & {
  initialState?: AnimationState
  children: (
    nodeRef: Ref<HTMLElement | undefined>,
    animationState: AnimationState
  ) => ReactNode
}

const InOutCSSTransition: FC<Props> = ({
  children,
  timeout = 300,
  onEnter,
  onExit,
  initialState = AnimationState.BeforeAppearing,
  ...props
}) => {
  const nodeRef = useRef<HTMLElement>()
  const [animationState, setAnimationState] =
    useState<AnimationState>(initialState)
  const handleEnter = useCallback(
    (node: HTMLElement, isAppearing: boolean) => {
      setTimeout(() => setAnimationState(() => AnimationState.Visible), TICK)
      if (onEnter !== undefined) {
        onEnter(node, isAppearing)
      }
    },
    [onEnter, setAnimationState]
  )
  const handleExit = useCallback(
    (node: HTMLElement) => {
      setAnimationState(() => AnimationState.Leaving)
      if (onExit !== undefined) {
        onExit(node)
      }
    },
    [setAnimationState, onExit]
  )

  useEffect(() => {
    if (props.in && initialState === AnimationState.BeforeAppearing) {
      handleEnter(undefined as any, true)
    }
  }, [])

  return (
    <Transition
      {...props}
      nodeRef={nodeRef}
      timeout={timeout}
      onEnter={handleEnter}
      onExit={handleExit}
    >
      {children(nodeRef, animationState)}
    </Transition>
  )
}

export default InOutCSSTransition
