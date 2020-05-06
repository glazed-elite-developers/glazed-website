open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let squareContent = style([display(`flex), flexDirection(`column)]);
  let leftBlueSquareStyles = [
    before([
      contentRule(""),
      display(`block),
      position(`absolute),
      bottom(`px(1)),
      left(`px(1)),
      width(px(5)),
      height(px(5)),
      backgroundColor(hex(Colors.glazedBlueDarkerish)),
      opacity(0.8),
    ]),
  ];
  let content = withCornerDot =>
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.000001)),
      padding3(~top=`rem(0.625), ~h=`rem(0.9375), ~bottom=`rem(0.9375)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~top=`rem(1.25), ~h=`rem(1.875), ~bottom=`rem(1.875))],
      ),
      ...withCornerDot ? leftBlueSquareStyles : [],
    ]);
  let hidden =
    style([
      visibility(`hidden),
      opacity(0.),
      transitions([
        Transition.shorthand(~duration=0, ~delay=400, "visibility"),
        Transition.shorthand(~duration=400, "opacity"),
      ]),
    ]);
  let visible =
    style([visibility(`visible), opacity(1.), transition(~duration=150, "opacity")]);
  let contentWhenSelected =
    style([
      position(`absolute),
      top(`zero),
      right(`zero),
      bottom(`zero),
      left(`zero),
      backgroundColor(rgba(41, 98, 246, 0.8)),
      border(px(1), `solid, hex(Colors.glazedBabyBlueDarker)),
    ]);
};

[@react.component]
let make =
    (
      ~children=?,
      ~className=?,
      ~contentWrapperClassName as baseContentWrapperClassName=?,
      ~contentClassName as baseContentClassName=?,
      ~contentWhenSelected=?,
      ~isSelected=false,
      ~onMouseEnter=?,
    ) => {
  let hasContentWhenSelected = contentWhenSelected !== None;
  let contentWrapperClassName =
    combineClassNames([Some(Styles.squareContent), baseContentWrapperClassName]);
  let contentClassName =
    combineClassNames([
      Some(
        isSelected
          ? Css.merge([Styles.content(hasContentWhenSelected), Styles.hidden])
          : Css.merge([Styles.content(hasContentWhenSelected), Styles.visible]),
      ),
      baseContentClassName,
    ]);
  let contentWhenSelectedClassName =
    combineClassNames([
      Some(Styles.content(false)),
      Some(
        isSelected
          ? Css.merge([Styles.contentWhenSelected, Styles.visible])
          : Css.merge([Styles.contentWhenSelected, Styles.hidden]),
      ),
    ]);
  let wrappedChildren =
    switch (children) {
    | None => None
    | Some(children') => Some(<div className=?contentClassName> children' </div>)
    };
  let wrappedContentWhenSelected =
    switch (contentWhenSelected) {
    | None => None
    | Some(content) => Some(<div className=?contentWhenSelectedClassName> content </div>)
    };

  let childrenForSquare =
    switch (wrappedContentWhenSelected) {
    | None => wrappedChildren
    | Some(content) =>
      switch (wrappedChildren) {
      | None => Some(content)
      | Some(children') => Some(<> children' content </>)
      }
    };

  <Square
    ?className
    contentClassName=?contentWrapperClassName
    ?onMouseEnter
    children=?childrenForSquare
  />;
};

let default = make;
