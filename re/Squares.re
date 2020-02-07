module Styles = {
  open Css;
  open Theme;
  let squaresContainer = 
    style([
      display(`flex),
      flexWrap(wrap)
    ]);
  let square =
    style([
      width(`percent(33.3)),
      paddingTop(`percent(33.3)),
      height(px(0)),
      position(relative),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          width(`percent(18.)),
          paddingTop(`percent(18.))
        ],
      ),
      backgroundColor(hex(Colors.glazedBlue)),
      borderStyle(solid),
      borderWidth(px(1)),
      borderColor(hex(Colors.glazedBabyBlueDarker)),
      color(white)
    ]);
  let squareContent = 
    style([
      position(absolute),
      top(px(0)),
      left(px(0)),
      width(`percent(100.)),
      height(`percent(100.))
    ]);
};

let str = React.string;

[@react.component]
let make = (~children) => {
  <ol className=Styles.squaresContainer >
    { Array.mapi(
      (i, (child)) => {
        <li className=Styles.square >
          <div className=Styles.squareContent >
            child
          </div>
        </li>
      }, children)
      |> ReasonReact.array
    }
    
  </ol>
};

