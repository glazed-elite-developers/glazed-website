module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      pointerEvents(`auto),
    ]);
  let lightTheme = style([color(hex(Theme.Colors.white))]);
  let darkTheme = style([color(hex(Theme.Colors.darkGreyDarker))]);
  let logoWrapper = style([flex3(~grow=0., ~shrink=0., ~basis=`auto)]);
  let item = style([padding(rem(0.75))]);
};

let items = [|
  ("#case-studies", "case studies"),
  ("#about", "about"),
  ("#team", "team"),
  ("#manifesto", "manifesto"),
|];

[@react.component]
let make = (~className=?, ~useDarkNavBarLinks=false) => {
  let styles =
    switch (className) {
    | None => Styles.wrapper
    | Some(className) => Css.merge([Styles.wrapper, className])
    };
  let contextualStyles = useDarkNavBarLinks ? Styles.darkTheme : Styles.lightTheme;

  <div className=Css.merge([styles, contextualStyles])>
    <div className=Styles.item> {React.string("explore:")} </div>
    {React.array(
       Array.map(
         ((link, label)) => <div className=Styles.item> {React.string("// " ++ label)} </div>,
         items,
       ),
     )}
  </div>;
};

let default = make;