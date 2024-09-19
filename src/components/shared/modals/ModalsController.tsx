import React, {
  createContext,
  FC,
  ReactNode,
  SyntheticEvent,
  useCallback,
  useContext,
  useMemo,
  useReducer,
} from 'react'
import StatelessModalController, {
  Modal,
  ModalRenderer,
} from './StatelessModalController'

type ModalsContext = {
  openedModals: Array<Modal>
  openModal: (
    renderer: ModalRenderer,
    options?: { preventCloseOnEscape?: boolean }
  ) => Modal
  closeModal: (modal: Modal) => void
}

const defaultContextValue: ModalsContext = {
  openedModals: [],
  openModal: () => ({ id: -1, renderer: () => null }),
  closeModal: () => undefined,
}

const ModalsContext = createContext<ModalsContext>(defaultContextValue)

type State = {
  openedModals: Array<Modal>
  counter: number
}

type Action = {
  type: 'OpenModal' | 'CloseModal'
  modal: Modal
}

const reducer = (state: State, action: Action) => {
  switch (action.type) {
    case 'OpenModal': {
      const openedModals = [...state.openedModals, action.modal]
      const openedModalsUniqueById = Array.from(
        openedModals
          .reduce(
            (map, modal) => map.set(modal.id, modal),
            new Map<number, Modal>()
          )
          .values()
      )
      return {
        ...state,
        openedModals: openedModalsUniqueById,
        counter: state.counter + 1,
      }
    }
    case 'CloseModal':
      return {
        ...state,
        openedModals: state.openedModals.filter(
          (modal: Modal) => modal !== action.modal
        ),
      }
  }
}

type Props = {
  className?: string
  overlayContainerClassName?: string
  onKeyDown?: (event: SyntheticEvent) => void
  getInitialOpenedModals?: () => Array<Modal>
  children?: ReactNode
}

const ModalsController: FC<Props> = ({
  className,
  overlayContainerClassName,
  onKeyDown: baseOnKeyDown,
  getInitialOpenedModals = () => [],
  children,
}: Props) => {
  const [state, dispatch] = useReducer(reducer, {
    openedModals: getInitialOpenedModals(),
    counter: 0,
  })
  const openModal = useCallback(
    (
      modalRenderer: ModalRenderer,
      options: Pick<Modal, 'preventCloseOnEscape'> = {}
    ) => {
      const newModal: Modal = {
        id: state.counter,
        renderer: modalRenderer,
        preventCloseOnEscape: options.preventCloseOnEscape,
      }
      dispatch({ type: 'OpenModal', modal: newModal })

      return newModal
    },
    [state.counter]
  )
  const closeModal = useCallback(
    (modal: Modal) => {
      dispatch({ type: 'CloseModal', modal })
    },
    [state.openedModals.length]
  )
  const contextAPI = useMemo(
    (): ModalsContext => ({
      openedModals: state.openedModals,
      openModal,
      closeModal,
    }),
    [state.openedModals, openModal, closeModal]
  )
  const onKeyDown = useCallback(
    (event) => {
      const eventKeyCode = event.keyCode
      const openedModalsCount = state.openedModals.length

      if (eventKeyCode === 27 && openedModalsCount > 0) {
        event.preventDefault()
        const lastOpenedModal =
          state.openedModals[state.openedModals.length - 1]

        if (!lastOpenedModal.preventCloseOnEscape) {
          return closeModal(lastOpenedModal)
        }
      }

      if (baseOnKeyDown !== undefined) {
        return baseOnKeyDown(event)
      }
    },
    [state, closeModal, baseOnKeyDown]
  )

  return (
    <ModalsContext.Provider value={contextAPI}>
      <StatelessModalController
        className={className}
        overlayContainerClassName={overlayContainerClassName}
        onKeyDown={onKeyDown}
        onModalClose={closeModal}
        openedModals={state.openedModals}
      >
        {children}
      </StatelessModalController>
    </ModalsContext.Provider>
  )
}

export const useModalsAPI = (): ModalsContext => useContext(ModalsContext)

export default ModalsController
