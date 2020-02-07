[@bs.module] external developerPhoto: string = "static/images/bunny.jpg";

module Styles = {
  open Css;
  open Theme;
  
  let team = style([backgroundColor(hex(Colors.glazedBlueLighter))]);

  let number = style([]);
  let name = style([]);
  let link = style([color(hex(Colors.glazedBabyBlue))]);
  let developerSquare = style([
    backgroundImage(url(developerPhoto)), 
    backgroundSize(`contain),
    height(`percent(100.)),
    color(white)
  ]);

  let square = style([    
    height(`percent(100.)),
  ]);
};

let str = React.string;

[@react.component]
let make = () => {
  <div className=Styles.team>
    <Squares >
      [|
        <div className=Styles.square>
          <h1 className=Styles.name > {"// team" |> str} </h1>
        </div>
      |]
    </ Squares>
    <Squares >
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