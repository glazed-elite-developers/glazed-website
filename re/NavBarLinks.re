module Styles = {
  open Css;

  let wrapper = style([display(`flex), pointerEvents(`auto)]);
  let lightTheme = style([color(hex(Theme.Colors.almostWhite))]);
  let darkTheme = style([color(hex(Theme.Colors.darkGreyDarker))]);
  let logoWrapper = style([flex3(~grow=0., ~shrink=0., ~basis=`auto)]);
  let item =
    style([
      padding(rem(0.25)),
      media(Theme.Breakpoints.tabletLandscape, [padding(rem(0.75))]),
    ]);
  let dimmed = style([opacity(0.6)]);
  let explore =
    style([display(`none), media(Theme.Breakpoints.tabletLandscape, [display(`flex)])]);
};

let items = [|
  ("/#case-studies", "case studies"),
  ("/#about", "about"),
  ("/#team", "team"),
  ("/#manifesto", "manifesto"),
|];

[@react.component]
let make = (~className=?, ~useDarkNavBarLinks=false, ~currentPageIndex: int, ~onNavBarLinkClick=?) => {
  let contextualStyles = useDarkNavBarLinks ? Styles.darkTheme : Styles.lightTheme;
  let wrapperStyles =
    Utils.React.combineClassNames([Some(Styles.wrapper), className, Some(contextualStyles)]);

  <div className=?wrapperStyles>
    <div className={Css.merge([Styles.dimmed, Styles.item, Styles.explore])}>
      {React.string("explore:")}
    </div>
    {React.array(
       Array.mapi(
         (index, (link, label)) => {
           let isDimmed = index >= currentPageIndex;
           let linkStyles =
             isDimmed
               ? Css.merge([Styles.item, Styles.dimmed, contextualStyles])
               : Css.merge([Styles.item, contextualStyles]);
           let onClick =
             switch (onNavBarLinkClick) {
             | None => None
             | Some(handler) => Some(event => handler(event, link))
             };

           <Gatsby.Link
             key={Belt.Int.toString(index)}
             _to=link
             className=linkStyles
             ?onClick
             // @TODO: Use "replace" conditionally depending on if we're linking for the same page or a different one.
             replace=true>
             {React.string("// " ++ label)}
           </Gatsby.Link>;
         },
         items,
       ),
     )}
  </div>;
};

let default = make;
