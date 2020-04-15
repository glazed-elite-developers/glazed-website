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
  React.forwardRef(
    (
      ~children,
      ~className: option(string)=?,
      ~backgroundImageUrl: option(string)=?,
      ref_,
    ) => {
    let inlineStyle =
      switch (backgroundImageUrl) {
      | None => ReactDOMRe.Style.make()
      | Some(url) =>
        ReactDOMRe.Style.make(~backgroundImage={j|url('$(url)')|j}, ())
      };

    // TODO: we could be using <Gatsby.BackgroundImage> here instead of inline styles.
    <section
      ref=?{
        Js.Nullable.toOption(ref_)->Belt.Option.map(ReactDOMRe.Ref.domRef)
      }
      className={Utils.React.combineOptionalStyles(
        ~baseStyles=Styles.wrapper,
        ~className?,
      )}
      style=inlineStyle>
      children
    </section>;
  });

let default = make;