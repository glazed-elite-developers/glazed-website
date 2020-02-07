module Styles = {
  open Css;
  open Theme;
  
  let number = style([]);
  let projectName = style([]);
  let link = style([color(hex(Colors.glazedBabyBlue))]);
};

let str = React.string;

[@react.component]
let make = () => {
  <div>
    <Squares>
      [|
        <div >
          <p className=Styles.number > {"// 01" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 02" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 03" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 04" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 05" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 05" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>,
        <div >
          <p className=Styles.number > {"// 06" |> str} </p>
          <h1 className=Styles.projectName > {"LVMH" |> str} </h1>
          <a className=Styles.link > {">explore case" |> str} </a>
        </div>
      |]
    </Squares>
  </div>
};