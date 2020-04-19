open React;
open Utils.React;

module Styles = {
  open Css;

  let wrapper = style([position(`relative)]);
};

[@react.component]
let make =
    (
      ~children,
      ~onResize,
      ~className=?,
      ~innerRef=?,
      ~style=?,
      ~componentTag="div",
    ) => {
  ReactDOMRe.createElement(
    componentTag,
    ~props=
      ReactDOMRe.props(
        ~ref=?{
          Belt.Option.map(innerRef, Utils.React.Types.domRef);
        },
        ~style?,
        ~className=?combineClassNames([Some(Styles.wrapper), className]),
        (),
      ),
    [|<Fragment> children <ResizeMonitor onResize /> </Fragment>|],
  );
};