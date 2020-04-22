type emotionCache;

[@bs.module "emotion"] external emotionCache: emotionCache = "cache";

module CacheProvider = {
  [@bs.module "@emotion/core"] [@react.component]
  external make:
    (~children: React.element, ~value: emotionCache) => React.element =
    "CacheProvider";
};

module MediaContextProvider = {
  [@bs.module "src/components/mediaContext"] [@react.component]
  external make: (~children: React.element) => React.element =
    "MediaContextProvider";
};

module Styles = {
  open Css;

  let wrapper = style([height(pct(100.))]);
  let content = style([height(pct(100.))]);
};

[@react.component]
let make = (~children) => {
  <CacheProvider value=emotionCache>
    <MediaContextProvider>
      <ModalsController>
        <ScrollContainer
          className=Styles.wrapper contentClassName=Styles.content>
          children
        </ScrollContainer>
      </ModalsController>
    </MediaContextProvider>
  </CacheProvider>;
};

let default = make;