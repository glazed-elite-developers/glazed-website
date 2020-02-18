module Styles = {
  open Css;
  open Theme;

  let number =
    style([
      color(hex(Colors.almostWhite)),
      fontFamily(Fonts.heading),
      fontSize(px(10)),
      fontWeight(`bolder),
      lineHeight(px(23)),
      opacity(0.67),
      // width() 25px;
      textAlign(`left),
      marginTop(px(20)),
      marginLeft(px(30)),
    ]);
  let projectName = hovered =>
    style([
      color(hex(Colors.almostWhite)),
      fontFamily(Fonts.heading),
      fontSize(px(32)),
      fontWeight(`bolder),
      lineHeight(px(48)),
      opacity(0.9),
      width(px(183)),
      textAlign(`left),
      marginLeft(px(30)),
      ...hovered ? [] : [position(`absolute), bottom(px(20))],
    ]);
  let projectArea = hovered =>
    style([
      color(white),
      fontFamily("Multi"),
      fontSize(px(14)),
      fontWeight(`normal),
      letterSpacing(pxFloat(0.31)),
      lineHeight(px(34)),
      marginLeft(px(30)),
      ...hovered ? [] : [display(`none)],
    ]);
  let link = hovered =>
    style([
      marginLeft(px(30)),
      color(hex(Colors.glazedBlueLighter)),
      ...hovered ? [] : [display(`none)],
    ]);

  let square = hovered =>
    style([
      backgroundColor(hex(Colors.glazedBlueDarker)),
      opacity(0.5),
      borderStyle(solid),
      borderWidth(px(1)),
      borderColor(hex(Colors.glazedBabyBlueDarker)),
      color(white),
      height(`percent(100.)),
      ...hovered
           ? [opacity(1.0), backgroundColor(hex(Colors.glazedBlueDarker))]
           : [],
    ]);
  let fakeSquare = style([height(`percent(100.))]);
};

let str = React.string;

type caseStudie = {
  name: string,
  area: string,
};
let caseStudies = [|
  {name: "LVMH", area: "Fashion - Ecommerce"},
  {name: "Farfetch", area: "Fashion - Ecommerce"},
  {name: "Switch", area: "Fashion - Ecommerce"},
  {name: "ASOS", area: "Fashion - Ecommerce"},
  {name: "Meo Music", area: "Fashion - Ecommerce"},
|];

[@react.component]
let make = () => {
  let (hovered, setHovered) = React.useState(() => 0);

  let handleOver = (i, _) => {
    setHovered(_ => i);
  };

  <div>
    <Squares>
      [|
        <div className={Styles.square(false)}>
          <h1 className={Styles.projectName(false)}>
            {"// case studies" |> str}
          </h1>
        </div>,
      |]
    </Squares>
    <Squares>
      {caseStudies
       |> Array.mapi((i, cs) => {
            let isHovered = hovered == i;
            <div
              onMouseEnter={handleOver(i)}
              className={Styles.square(isHovered)}>
              <p className=Styles.number>
                {"// 0" ++ string_of_int(i + 1) |> str}
              </p>
              <h2 className={Styles.projectName(isHovered)}>
                {cs.name |> str}
              </h2>
              <p className={Styles.projectArea(isHovered)}>
                {cs.area |> str}
              </p>
              <a className={Styles.link(isHovered)}>
                {">explore case" |> str}
              </a>
            </div>;
          })}
    </Squares>
  </div>;
};