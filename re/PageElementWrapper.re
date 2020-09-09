type location = {
  action: string,
  pathname: string,
  hash: string,
};

[@bs.module "@reach/router"] external useLocation: unit => location = "useLocation";

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  let url = ReasonReactRouter.useUrl();
  let location: location = useLocation();
  let scrollerAPI = ScrollConnectors.useRootScrollerAPI();

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
      if (location.hash === "" && location.action === "PUSH") {
        scrollerAPI.scrollTo(Some(0.), Some(0.));
      };
      None;
    },
    (location, scrollerAPI),
  );

  children;
};

let default = make;
