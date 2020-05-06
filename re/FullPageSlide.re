module Styles = {
  open Css;

  let wrapper =
    style([
      minHeight(pct(100.)),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Theme.Colors.white)),
    ]);
};

[@react.component]
let make = (~children, ~id=?, ~className: option(string)=?, ~innerRef=?, ~onResize) => {
  <ResizeMonitorContainer
    componentTag="section"
    ?id
    ?innerRef
    className=?{Utils.React.combineClassNames([Some(Styles.wrapper), className])}
    onResize>
    children
  </ResizeMonitorContainer>;
};

let default = make;
