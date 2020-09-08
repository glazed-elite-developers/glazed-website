open Utils.React;

module Styles = {
  open Css;

  let wrapper = style([position(`relative), overflow(`hidden)]);
  let heightRegulator = style([position(`relative), overflow(`hidden)]);
  let stretchHorizontally = style([width(pct(100.))]);
  let stretchVertically = style([height(pct(100.))]);
  let ratioPlaceholder = style([display(`block)]);
  let container =
    style([
      position(`absolute),
      top(pct(50.)),
      left(pct(50.)),
      width(pct(100.)),
      transform(translate3d(pct(-50.), pct(-50.), `zero)),
    ]);
};

type stretchDirection =
  | Horizontal
  | Vertical;

/**
 * IE forces us to use an image with an inlined svg to be able to scale an svg mantaining its
 * aspect ratio.
 *
 * @param {Integer} width - Aspect ratio base width.
 * @param {Integer} height - Aspect ratio base height.
 * @returns {String} Img src atribute value.
 */
let getImgSrc = (width, height) =>
  "data:image/svg+xml,%3Csvg"
  ++ {j| viewBox='0 0 $(width) $(height)'|j}
  ++ {j| preserveAspectRatio='xMidYMid meet'|j}
  ++ " xmlns=\'http://www.w3.org/2000/svg\'/%3E";

module ImagePlaceholder = {
  [@react.component]
  let make = (~innerRef=?, ~stretchDirection, ~width, ~height, ~className=?) => {
    let src = getImgSrc(width, height);
    let width = stretchDirection === Horizontal ? Some("100%") : None;
    let height = stretchDirection === Vertical ? Some("100%") : None;

    <img
      src
      ?width
      ?height
      className=?{combineClassNames([Some(Styles.ratioPlaceholder), className])}
      ref=?innerRef
      alt="placeholder"
      role="presentation"
    />;
  };
};

[@react.component]
let make =
    (
      ~className=?,
      ~heightRegulatorClassName as baseHeightRegulatorClassName=?,
      ~imagePlaceholderClassName=?,
      ~contentClassName=?,
      ~stretchDirection: stretchDirection,
      ~placeholderRef=?,
      ~width: int,
      ~height: int,
      ~children,
    ) => {
  let heightRegulatorClassName =
    combineClassNames([
      baseHeightRegulatorClassName,
      Some(Styles.heightRegulator),
      stretchDirection === Horizontal
        ? Some(Styles.stretchHorizontally) : Some(Styles.stretchVertically),
    ]);

  <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
    <div className=?heightRegulatorClassName>
      <ImagePlaceholder
        innerRef=?placeholderRef
        className=?imagePlaceholderClassName
        stretchDirection
        width
        height
      />
      <div className=?{combineClassNames([Some(Styles.container), contentClassName])}>
        children
      </div>
    </div>
  </div>;
};

let default = make;
