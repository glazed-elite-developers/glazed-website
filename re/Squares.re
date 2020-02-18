module Styles = {
  open Css;
  let squaresContainer = style([display(`flex), flexWrap(wrap)]);
  let square =
    style([
      width(`percent(33.4)),
      paddingTop(`percent(33.4)),
      height(px(0)),
      position(relative),
      media(
        Theme.Breakpoints.tabletLandscape,
        [width(`percent(20.1)), paddingTop(`percent(20.1))],
      ),
    ]);
  let squareContent =
    style([
      position(absolute),
      top(px(0)),
      left(px(0)),
      width(`percent(100.)),
      height(`percent(100.)),
    ]);
};

let str = React.string;

[@react.component]
let make = (~children) => {
  <ol className=Styles.squaresContainer>
    {Array.mapi(
       (index, child) =>
         <li key={string_of_int(index)} className=Styles.square>
           <div className=Styles.squareContent> child </div>
         </li>,
       children,
     )
     |> ReasonReact.array}
  </ol>;
};
};
