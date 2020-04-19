module Styles = {
  open Css;

  let wrapper =
    style([
      minHeight(pct(100.)),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundSize(`cover),
    ]);
};

[@react.component]
let make =
    (
      ~children,
      ~id=?,
      ~className: option(string)=?,
      ~backgroundImageUrl: option(string)=?,
      ~innerRef=?,
      ~onResize,
    ) => {
  let inlineStyle =
    switch (backgroundImageUrl) {
    | None => ReactDOMRe.Style.make()
    | Some(url) =>
      ReactDOMRe.Style.make(~backgroundImage={j|url('$(url)')|j}, ())
    };

  // TODO: we could be using <Gatsby.BackgroundImage> here instead of inline styles.
  <ResizeMonitorContainer
    componentTag="section"
    ?id
    ?innerRef
    className=?{
      Utils.React.combineClassNames([Some(Styles.wrapper), className])
    }
    style=inlineStyle
    onResize>
    children
  </ResizeMonitorContainer>;
};

let default = make;