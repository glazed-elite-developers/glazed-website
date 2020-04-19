open React;

type modalId = int;

type modalRenderer = (~id: modalId, ~onClose: unit => unit) => React.element
and modal = {
  id: modalId,
  renderer: modalRenderer,
};

type context = {
  openedModals: array(modal),
  openModal: modalRenderer => modal,
  closeModal: modal => unit,
};

let defaultContextValue: context = {
  openedModals: [||],
  openModal: _modal => {
    id: -1,
    renderer: (~id as _, ~onClose as _) => React.null
  },
  closeModal: _modal => (),
};

let context = createContext(defaultContextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = Context.provider(context);
};