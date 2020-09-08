type scrollRestorationProps = {
  ref: React.ref(Js.nullable(Webapi.Dom.Element.t)),
  onScroll: unit => unit,
};

type location = {action: string};

[@bs.module "gatsby"]
external useScrollRestoration: string => scrollRestorationProps = "useScrollRestoration";

[@bs.module "@reach/router"] external useLocation: unit => location = "useLocation";

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  let url = ReasonReactRouter.useUrl();
  let scrollRestorationProps: scrollRestorationProps = useScrollRestoration("scrollContainer");
  let location: location = useLocation();

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
      if (location.action === "PUSH") {
        switch (Js.Nullable.toOption(scrollRestorationProps.ref.current)) {
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
      className=Styles.wrapper
      contentClassName=Styles.content
      innerRef={scrollRestorationProps.ref}
      onScroll={scrollRestorationProps.onScroll}>
      children
    </ScrollContainer>
  </ModalsController>;
};

let default = make;
