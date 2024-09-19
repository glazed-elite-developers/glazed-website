import { css, cx } from '@emotion/css'
import { TransitionGroup } from 'react-transition-group'
import React, {
  FC,
  ReactElement,
  ReactNode,
  SyntheticEvent,
  useCallback,
} from 'react'
import { Props as BaseModalProps } from './BaseModal'

const Styles = {
  wrapper: css`
    position: relative;
    display: flex;
    flex: 1 1 0.00000001rem;
    flex-direction: column;
  `,
  overlayContainer: css`
    width: 100%;
  `,
}

export type ModalRenderer = (
  propsForModal: { modalId: number; onClose: () => void } & BaseModalProps
) => ReactElement | null

export type Modal = {
  id: number
  renderer: ModalRenderer
  preventCloseOnEscape?: boolean
}

/**
 * Basically only here to memoize the onClose function and to trick the type system into accepting rendering
 * this component with the BaseModal props optional, but mandatory on the actual Modal component inself.
 */
const ModalRenderWrapper: FC<
  Partial<BaseModalProps> & {
    modal: Modal
    onModalClose: (modal: Modal) => void
  }
> = ({ modal, onModalClose, ...transitionGroupProps }) => {
  const onClose = useCallback(() => onModalClose(modal), [modal, onModalClose])
  return modal.renderer({
    modalId: modal.id,
    ...(transitionGroupProps as BaseModalProps),
    onClose,
  })
}

type Props = {
  className?: string
  overlayContainerClassName?: string
  onKeyDown: (event: SyntheticEvent) => void
  onModalClose: (modal: Modal) => void
  openedModals: Array<Modal>
  children?: ReactNode
}
const StatelessModalController: FC<Props> = ({
  className,
  overlayContainerClassName,
  onKeyDown,
  onModalClose,
  openedModals,
  children,
}) => {
  return (
    <div
      className={cx([Styles.wrapper, className])}
      role="presentation"
      onKeyDown={onKeyDown}
    >
      {children}
      {/* eslint-disable-next-line jsx-a11y/no-noninteractive-tabindex */}
      <div
        className={cx([Styles.overlayContainer, overlayContainerClassName])}
        tabIndex={0}
      >
        <TransitionGroup>
          {openedModals.map((modal, index) => (
            <ModalRenderWrapper
              key={index}
              modal={modal}
              onModalClose={onModalClose}
            />
          ))}
        </TransitionGroup>
      </div>
    </div>
  )
}

export default StatelessModalController
