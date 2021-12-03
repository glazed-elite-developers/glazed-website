open React;

open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let header =
    style([
      position(`fixed),
      backgroundColor(hex(Colors.whiteTurquoise)),
      transition(~duration=200, ~delay=0, ~timingFunction=`easeOut, "all"),
    ]);
  let headerWithShadow =
    style([boxShadow(Shadow.box(~y=px(7), ~blur=px(15), rgba(0, 0, 0, 0.04)))]);
};

type scrollDirection =
  | Up
  | Down;

type headerPosition =
  | Static(float)
  | Fixed;

// Micro mousewheel movements may prompt the header animation without need so
// we offset the travel by 10 to clearly indicate up/downwards scroll
let scrollDirectionOffset = 15.;

let useHeaderPosition = () => {
  let scrollValues = ScrollConnectors.useClosestScrollValues();
  let scrollTop = scrollValues.position.scrollTop;
  let lastScrollDataRef = useRef((scrollTop, Up));
  let (lastScrollTop, lastScrollDirection) = lastScrollDataRef.current;
  let scrollDirection =
    scrollTop > (lastScrollTop +. scrollDirectionOffset)
      ? Down
      : lastScrollTop <= scrollTop
        ? lastScrollDirection
        : Up;
  let shouldHaveBackground = scrollTop > scrollDirectionOffset;
  lastScrollDataRef.current = (scrollTop, scrollDirection);

  (scrollDirection, shouldHaveBackground);
};

[@react.component]
let make = (
  ~innerRef=?,
  ~className=?,
  ~componentAtTheRight=?,
  ~onNavBarLinkClick: option((ReactEvent.Synthetic.t, string) => unit)=?,
  ~useDarkNavBarLinks: bool=false,
  ~currentPageIndex=?,
) => {
  let (scrollDirection, shouldHaveBackground) = useHeaderPosition();
  let headerStyle =
    useMemo1(
      () => {
        switch (scrollDirection) {
        | Up =>  None
        | Down => Some(
            ReactDOMRe.Style.make(
              ~transform={j|translateY(-100%)|j},
              (),
            ),
          )
        }
      },
      [|scrollDirection|],
    );
  let headerClassName =
    shouldHaveBackground ? Css.merge([Styles.header, Styles.headerWithShadow]) : Styles.header;

  <Header
    style=?headerStyle
    innerRef=?innerRef
    className=?{combineClassNames([Some(headerClassName), className])}
    componentAtTheRight=?componentAtTheRight
    onNavBarLinkClick=?onNavBarLinkClick
    useDarkNavBarLinks=useDarkNavBarLinks
    currentPageIndex=?currentPageIndex
  />;
};

let default = make;
let useHeaderPosition = useHeaderPosition;
