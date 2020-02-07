[@bs.module] external developerPhoto: string = "static/images/bunny.jpg";

module Styles = {
  open Css;
  open Theme;
  
  let number = style([]);
  let name = style([]);
  let link = style([color(hex(Colors.glazedBabyBlue))]);
  let developerSquare = style([
      backgroundImage(url(developerPhoto)), 
      backgroundSize(`contain),
      height(`percent(100.))
    ]);
};

let str = React.string;

[@react.component]
let make = () => {
  <div>
    <Squares>
      [|
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Ismael Abreu" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>,
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Ricardo Moutinho" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>,
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Diogo Nunes" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>,
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Ismael Abreu" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>,
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Ricardo Moutinho" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>,
        <div className=Styles.developerSquare>
          <h1 className=Styles.name > {"Diogo Nunes" |> str} </h1>
          <a className=Styles.link > {"//Reason  //Gatsby" |> str} </a>
        </div>
      |]
    </Squares>
  </div>
};