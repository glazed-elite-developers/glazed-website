open React;

module Styles = {
  open Css;

  let wrapper =
    style([
      position(`relative),
      display(`flex),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      flexDirection(`column),
    ]);
  let overlayContainer = style([width(pct(100.))]);
};

type state = {
  openedModals: array(ModalsContext.modal),
  // Counter that is used to generate unique modal ids.
  counter: int,
};

let getInitialOpenedModals = () => [||];

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
      ~getInitialOpenedModals=getInitialOpenedModals,
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
            Belt.Array.get(
              state.openedModals,
              Belt.Array.length(state.openedModals) - 1,
            )
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
      (state.openedModals, closeModal),
    );

  <ModalsContext.Provider value=contextAPI>
    <div
      className=?{
        Utils.React.combineClassNames([Some(Styles.wrapper), className])
      }
      role="presentation"
      onKeyDown>
      children
      <div className=Styles.overlayContainer tabIndex=0>
        <ReactTransitionGroup.TransitionGroup>
          {React.array(
             Belt.Array.map(state.openedModals, modal =>
               modal.renderer(~id=modal.id, ~onClose=() => closeModal(modal))
             ),
           )}
        </ReactTransitionGroup.TransitionGroup>
      </div>
    </div>
  </ModalsContext.Provider>;
};

let default = make;

let useContextAPI = () => useContext(ModalsContext.context);