module Styles = {
  open Css;

  let wrapper = style([display(`flex), pointerEvents(`auto)]);
  let lightTheme = style([color(hex(Theme.Colors.white))]);
  let darkTheme = style([color(hex(Theme.Colors.darkGreyDarker))]);
  let logoWrapper = style([flex3(~grow=0., ~shrink=0., ~basis=`auto)]);
  let item = style([padding(rem(0.75))]);
  let dimmed = style([opacity(0.6)]);
  let link = style([textDecoration(`none)]);
};

let items = [|
  ("#case-studies", "case studies"),
  ("#about", "about"),
  ("#team", "team"),
  ("#manifesto", "manifesto"),
|];

[@react.component]
let make = (~className=?, ~useDarkNavBarLinks=false, ~currentPageIndex: int) => {
  let styles =
    switch (className) {
    | None => Styles.wrapper
    | Some(className) => Css.merge([Styles.wrapper, className])
    };
  let contextualStyles =
    useDarkNavBarLinks ? Styles.darkTheme : Styles.lightTheme;

  <div className={Css.merge([styles, contextualStyles])}>
    <div className={Css.merge([Styles.dimmed, Styles.item])}>
      {React.string("explore:")}
    </div>
    {React.array(
       Array.mapi(
         (index, (link, label)) => {
           let isDimmed = index > currentPageIndex;
           let linkStyles =
             isDimmed
               ? Css.merge([
                   Styles.item,
                   Styles.link,
                   Styles.dimmed,
                   contextualStyles,
                 ])
               : Css.merge([Styles.item, Styles.link, contextualStyles]);

           <Gatsby.Link _to={"/" ++ link} className=linkStyles replace=true>
             {React.string("// " ++ label)}
           </Gatsby.Link>;
         },
         items,
       ),
     )}
  </div>;
};

let default = make;