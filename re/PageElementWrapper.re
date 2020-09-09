type routeStatePayload = {preventDefaultScrollBehavior: bool};

type routeState = {
  key: string,
  state: option(routeStatePayload),
};

type location = {
  action: string,
  pathname: string,
  hash: string,
  state: routeState,
};

type scrollRestorationProps = {
  ref: React.ref(Js.nullable(Webapi.Dom.Element.t)),
  onScroll: unit => unit,
};

[@bs.module "@reach/router"] external useLocation: unit => location = "useLocation";

[@bs.module "gatsby"]
external useScrollRestoration: string => scrollRestorationProps = "useScrollRestoration";

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  let url = ReasonReactRouter.useUrl();
  let location: location = useLocation();
  let scrollRestorationProps: scrollRestorationProps = useScrollRestoration("scrollContainer");

  React.useEffect0(() => {
    // Force navigation after first render to make sure hash links work properly.
    if (url.hash !== "") {
      Routing.replace(
        Utils.Routing.getFullPath(url),
        ~state={"preventDefaultScrollBehavior": false},
      );
    };
    None;
  });

  React.useEffect2(
    () => {
      // Scroll to top on route pushes.
      let preventDefaultScrollBehavior =
        switch (location.state.state) {
        | None => false
        | Some(state) => state.preventDefaultScrollBehavior
        };
      if (!preventDefaultScrollBehavior && location.hash === "" && location.action === "PUSH") {
        switch (Js.Nullable.toOption(scrollRestorationProps.ref.current)) {
        | None => ()
        | Some(element) => Webapi.Dom.Element.scrollTo(0., 0., element)
        };
      };
      None;
    },
    (location, scrollRestorationProps.ref),
  );

  <ScrollContainer
    className=Styles.wrapper
    contentClassName=Styles.content
    innerRef={scrollRestorationProps.ref}
    onScroll={scrollRestorationProps.onScroll}>
    children
  </ScrollContainer>;
};

let default = make;
