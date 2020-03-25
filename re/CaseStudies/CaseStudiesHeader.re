module Styles = {
  open Css;

  let image=style([
    position(`relative),
    selector(".gatsby-image-wrapper", [
      maxHeight(rem(51.25)),
      maxWidth(rem(86.)),
      marginLeft(`auto)
    ]),
    media(
      Theme.Breakpoints.tabletLandscape,
      [
        marginTop(rem(6.875)),
        marginLeft(rem(4.6875))
      ]
    )
  ]);

  let mask = style([
    position(`absolute),
    width(pct(100.)),
    height(pct(100.)),
    backgroundColor(rgba(0, 0, 0, 0.3)),
    top(`zero),
    left(`zero)
  ]);
};

[@react.component]
let make = (
  ~image: unit,
  _title: string,
  _area: string,
  _text: string,
  _techs: array(string),
  _year: string,
  _brief: string
) => {
  <header>
    <div className=Styles.image>
      <Gatsby.Image fluid=image />
      <div className=Styles.mask />
    </div>
  </header>;
};

let default = make;