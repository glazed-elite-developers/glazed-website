[@bs.module] external image: string = "assets/examples/bunny.jpg";

let str = React.string;

module Styles = {
  open Css;

  let wrapper = style([
      display(`flex),
      width(`percent(100.0)),
      flexWrap(`wrap),
      justifyContent(`flexStart),
      alignContent(`spaceBetween),
      ]);

  let colorSquare = style([
      display(`flex),
      float(`left),
      width(em(10.5)),
      height(em(10.5)),
      flexDirection(`column),
      justifyContent(`center),
      alignItems(`center),
    ]);
};

let colors = [|
    ("black", Theme.Colors.black, Theme.Colors.white),
    ("white", Theme.Colors.white, Theme.Colors.black),
    ("orange", Theme.Colors.orange, Theme.Colors.black),
    ("grey", Theme.Colors.grey, Theme.Colors.black),
    ("darkGrey", Theme.Colors.darkGrey, Theme.Colors.black),
    ("darkGreyDarker", Theme.Colors.darkGreyDarker, Theme.Colors.black),
    ("blueDarker", Theme.Colors.blueDarker, Theme.Colors.black),
    ("glazedBlue", Theme.Colors.glazedBlue, Theme.Colors.black),
    ("glazedBlueLight", Theme.Colors.glazedBabyBlueLight, Theme.Colors.black),
    ("glazedBlueLighter", Theme.Colors.glazedBlueLighter, Theme.Colors.black),
    ("glazedBlueDarker", Theme.Colors.glazedBabyBlueDarker, Theme.Colors.black),
    ("glazedBabyBlue", Theme.Colors.glazedBabyBlue, Theme.Colors.black),
    ("glazedBabyBlueLight", Theme.Colors.glazedBabyBlueLight, Theme.Colors.black),
    ("glazedBabyBlueDarker", Theme.Colors.glazedBabyBlueDarker, Theme.Colors.black),
|];


[@react.component]
let make = () => {
    <div className=Styles.wrapper>
    { Array.mapi(
        (i, (name, bgColor, color)) => {
            <div
                className=Styles.colorSquare 
                key=string_of_int(i)
                style=(ReactDOMRe.Style.make(~backgroundColor=bgColor, ~color=color, ()))>
                <p>{ str(name) }</p>
                <p>{ str(color) }</p>
            </div>
        }, colors)
        |> ReasonReact.array
    }
    </div>
  
};

let default = make;