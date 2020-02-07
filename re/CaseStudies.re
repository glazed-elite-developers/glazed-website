module Styles = {
  open Css;
  open Theme;
  
  let number = style([]);
  let projectName = style([]);
  let link = style([color(hex(Colors.glazedBlueLighter))]);
  
  let square = style([
    backgroundColor(hex(Colors.glazedBlue)),
    borderStyle(solid),
    borderWidth(px(1)),
    borderColor(hex(Colors.glazedBabyBlueDarker)),
    color(white),
    height(`percent(100.))
  ]);
  let fakeSquare = style([    
    height(`percent(100.))
  ]);

};

let str = React.string;

[@react.component]
let make = () => {
  <div>
    <Squares>
      [|
        <div className=Styles.square >
          <h1 className=Styles.projectName > {"// case studies" |> str} </h1>
        </div>
      |]
    </Squares>
    <Squares>
      [|
        <div className=Styles.square >
          <p className=Styles.number > {"// 01" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div className=Styles.square >
          <p className=Styles.number > {"// 02" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div className=Styles.square >
          <p className=Styles.number > {"// 03" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div className=Styles.square >
          <p className=Styles.number > {"// 04" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div className=Styles.fakeSquare />,
        <div className=Styles.square >
          <p className=Styles.number > {"// 05" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
      |]
    </Squares>
  </div>
};