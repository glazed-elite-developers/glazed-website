type emotionCache;

[@bs.module "emotion"] external emotionCache: emotionCache = "cache";

type scrollRestorationProps = {
  ref: React.ref(Js.nullable(Webapi.Dom.Element.t)),
  onScroll: unit => unit,
};

[@bs.module "gatsby"]
external useScrollRestoration: string => scrollRestorationProps = "useScrollRestoration";

module CacheProvider = {
  [@bs.module "@emotion/core"] [@react.component]
  external make: (~children: React.element, ~value: emotionCache) => React.element =
    "CacheProvider";
};

module MediaContextProvider = {
  [@bs.module "src/components/mediaContext"] [@react.component]
  external make: (~children: React.element) => React.element = "MediaContextProvider";
};

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  let url = ReasonReactRouter.useUrl();
  // let scrollRestorationProps: scrollRestorationProps = useScrollRestoration("scrollContainer");

  React.useEffect0(() => {
    if (url.hash !== "") {
      Routing.replace(
        Utils.Routing.getFullPath(url),
        ~state={"preventDefaultScrollBehavior": false},
      );
    };
    None;
  });

  <CacheProvider value=emotionCache>
    <MediaContextProvider>
      <ModalsController>
        <ScrollContainer
          className=Styles.wrapper
          contentClassName=Styles.content>
          // innerRef={scrollRestorationProps.ref}
          // onScroll={scrollRestorationProps.onScroll}>
          children
        </ScrollContainer>
      </ModalsController>
    </MediaContextProvider>
  </CacheProvider>;
};

let default = make;
