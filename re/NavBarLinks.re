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
  ("/#case-studies", "case studies", true),
  ("/#about", "about", true),
  ("/#team", "team", true),
  ("/#manifesto", "manifesto", true),
  ("https://blog.glazedsolutions.com", "blog", false),
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
         (index, (link, label, internal)) => {
           let isDimmed = index !== currentPageIndex - 1;
           let linkStyles =
             isDimmed
               ? Css.merge([Styles.item, Styles.dimmed, contextualStyles])
               : Css.merge([Styles.item, contextualStyles]);
           let onClick =
             switch (onNavBarLinkClick) {
             | None => None
             | Some(handler) => Some(event => handler(event, link))
             };

          let output = internal ?
          <Gatsby.Link
             key={Belt.Int.toString(index)}
             _to=link
             className=linkStyles
             ?onClick
             replace=true>
             {React.string("// " ++ label)}
           </Gatsby.Link> :
           <a href=link className=linkStyles>{React.string("// "++ label)}</a>;

           output;
         },
         items,
       ),
     )}
     
  </div>;
};

let default = make;
