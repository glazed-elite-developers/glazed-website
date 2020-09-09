open React;

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
  let scrollContainerRef = useRef(Js.Nullable.null);

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

  React.useEffect1(
    () => {
      // Scroll to top on route pushes.
      if (location.hash === "" && location.action === "PUSH") {
        switch (Js.Nullable.toOption(scrollContainerRef.current)) {
        | None => ()
        | Some(element) => Webapi.Dom.Element.scrollTo(0., 0., element)
        };
      };
      None;
    },
    [|location|],
  );

  <ModalsController>
    <ScrollContainer
      className=Styles.wrapper contentClassName=Styles.content innerRef=scrollContainerRef>
      children
    </ScrollContainer>
  </ModalsController>;
};

let default = make;
