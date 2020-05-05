open React;

type state = {
  openedModals: array(ModalsContext.modal),
  // Counter that is used to generate unique modal ids.
  counter: int,
};

type action =
  | OpenModal(ModalsContext.modal)
  | CloseModal(ModalsContext.modal);

let reducer = (state: state, action: action) => {
  switch (action) {
  | OpenModal(modal) => {
      openedModals: Belt.Array.concat(state.openedModals, [|modal|]),
      counter: state.counter + 1,
    }
  | CloseModal(modal) => {
      openedModals:
        Belt.Array.keep(state.openedModals, openedModal =>
          openedModal !== modal
        ),
      counter: state.counter + 1,
    }
  };
};

[@react.component]
let make =
    (
      ~children,
      ~className=?,
      ~onKeyDown=?,
      ~getInitialOpenedModals=() => [||],
    ) => {
  let initialState = {openedModals: getInitialOpenedModals(), counter: 0};
  let (state, dispatch) = useReducer(reducer, initialState);
  let openModal =
    useCallback1(
      (modalRenderer: ModalsContext.modalRenderer) => {
        let newModal: ModalsContext.modal = {
          id: state.counter,
          renderer: modalRenderer,
        };
        dispatch(OpenModal(newModal));
        newModal;
      },
      [|dispatch|],
    );
  let closeModal =
    useCallback1(modal => dispatch(CloseModal(modal)), [|dispatch|]);
  let contextAPI =
    useMemo3(
      (): ModalsContext.context =>
        {openedModals: state.openedModals, openModal, closeModal},
      (state.openedModals, openModal, closeModal),
    );
  let onKeyDown =
    useCallback2(
      event => {
        let eventKeyCode = ReactEvent.Keyboard.keyCode(event);
        let openedModalsCount = Belt.Array.length(state.openedModals);

        if (eventKeyCode === 27 && openedModalsCount > 0) {
          ReactEvent.Synthetic.preventDefault(event);
          switch (
            Belt.Array.get(state.openedModals, Belt.Array.length(state.openedModals) - 1)
          ) {
          | None => ()
          | Some(modal) => closeModal(modal)
          };
        } else {
          switch (onKeyDown) {
          | None => ()
          | Some(callback) => callback(event)
          };
        };
      },
      (state, closeModal),
    );

  <ModalsContext.Provider value=contextAPI>
    <StatelessModalController
      ?className
      onKeyDown
      onModalClose=closeModal
      openedModals={state.openedModals}>
      children
    </StatelessModalController>
  </ModalsContext.Provider>;
};

let default = make;

let useContextAPI = () => useContext(ModalsContext.context);