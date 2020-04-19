type levels =
  | H1
  | H2
  | H3
  | H4
  | H5
  | H6;

module Styles = {
  open Css;
  let commonStyles =
    style([
      position(`relative),
      fontWeight(`num(700)),
      fontFamily(Theme.Fonts.heading),
    ]);

  let h1 =
    merge([
      commonStyles,
      style([
        fontSize(rem(1.5)),
        lineHeight(rem(2.125)),
        media(
          Theme.Breakpoints.tabletPortrait,
          [fontSize(rem(2.25)), lineHeight(rem(2.75))],
        ),
      ]),
    ]);
  let h2 =
    merge([
      commonStyles,
      style([
        fontSize(rem(1.125)),
        color(hex(Theme.Colors.grey)),
        media(Theme.Breakpoints.tabletPortrait, [fontSize(rem(2.))]),
      ]),
    ]);
  let h3 =
    merge([
      commonStyles,
      style([
        media(
          Theme.Breakpoints.tabletPortrait,
          [fontSize(rem(1.5)), lineHeight(rem(2.75))],
        ),
      ]),
    ]);
  let h4 = merge([commonStyles, style([])]);
  let h5 = merge([commonStyles, style([])]);
  let h6 = merge([commonStyles, style([])]);
};

[@react.component]
let make = (~level: levels, ~className=?, ~children) => {
  let (component, styles) =
    switch (level) {
    | H1 => ("h1", Styles.h1)
    | H2 => ("h2", Styles.h2)
    | H3 => ("h3", Styles.h3)
    | H4 => ("h4", Styles.h4)
    | H5 => ("h5", Styles.h5)
    | H6 => ("h6", Styles.h6)
    };

  ReactDOMRe.createElement(
    component,
    ~props=
      ReactDOMRe.props(
        ~className=?Utils.React.combineClassNames([Some(styles), className]),
        (),
      ),
    [|children|],
  );
};

let default = make;