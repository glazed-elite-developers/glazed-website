type scrollRestorationProps = {
  ref: React.ref(Js.nullable(Webapi.Dom.Element.t)),
  onScroll: unit => unit,
};

[@bs.module "gatsby"]
external useScrollRestoration: string => scrollRestorationProps = "useScrollRestoration";

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  let location: Routing.location = Routing.useLocation();
  let scrollRestorationProps: scrollRestorationProps = useScrollRestoration("scrollContainer");

  React.useEffect0(() => {
    // Force navigation after first render to make sure hash links work properly.
    if (location.hash !== "") {
      Routing.navigate(
        Utils.Routing.getFullPath(location),
        ~state={"preventDefaultScrollBehavior": false},
        ~replace=true,
      );
    };
    None;
  });

  React.useEffect2(
    () => {
      // Scroll to top on route pushes.
      let preventDefaultScrollBehavior =
        switch (Js.Nullable.toOption(location.state)) {
        | None => false
        | Some(state) =>
          switch (state.state) {
          | None => false
          | Some(state) => state.preventDefaultScrollBehavior
          }
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
