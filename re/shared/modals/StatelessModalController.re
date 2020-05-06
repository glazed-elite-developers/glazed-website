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

[@react.component]
let make =
    (
      ~children,
      ~className=?,
      ~onKeyDown=?,
      ~onModalClose: ModalsContext.modal => unit,
      ~openedModals: array(ModalsContext.modal),
    ) => {
  <div
    className=?{Utils.React.combineClassNames([Some(Styles.wrapper), className])}
    role="presentation"
    ?onKeyDown>
    children
    <div className=Styles.overlayContainer tabIndex=0>
      <ReactTransitionGroup.TransitionGroup>
        {React.array(
           Belt.Array.map(openedModals, modal =>
             modal.renderer(~id=modal.id, ~onClose=() => onModalClose(modal))
           ),
         )}
      </ReactTransitionGroup.TransitionGroup>
    </div>
  </div>;
};
