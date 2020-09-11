module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

let shouldUpdateScroll =
    (
      _previousRouterProps: Js.Nullable.t(Routing.routerProps),
      routerProps: Js.Nullable.t(Routing.routerProps),
    ) => {
  switch (Js.Nullable.toOption(routerProps)) {
  | None => true
  | Some({location}) =>
    if (location.action === "PUSH") {
      switch (Js.Nullable.toOption(location.state)) {
      | None => true
      | Some({state}) =>
        switch (state) {
        | None => true
        | Some(state) => !state.preventDefaultScrollBehavior
        }
      };
    } else {
      true;
    }
  };
};

[@react.component]
let make = (~children) => {
  <ModalsController>
    <Routing.ScrollContainer scrollKey="scrollContainer" shouldUpdateScroll>
      <ScrollContainer className=Styles.wrapper contentClassName=Styles.content>
        children
      </ScrollContainer>
    </Routing.ScrollContainer>
  </ModalsController>;
};

let default = make;
