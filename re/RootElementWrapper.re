type emotionCache;

[@bs.module "emotion"] external emotionCache: emotionCache = "cache";

module CacheProvider = {
  [@bs.module "@emotion/core"] [@react.component]
  external make: (~children: React.element, ~value: emotionCache) => React.element =
    "CacheProvider";
};

module MediaContextProvider = {
  [@bs.module "src/components/mediaContext"] [@react.component]
  external make: (~children: React.element) => React.element = "MediaContextProvider";
};

[@react.component]
let make = (~children) => {
  <CacheProvider value=emotionCache>
    <MediaContextProvider>
      children
    </MediaContextProvider>
  </CacheProvider>;
};

let default = make;
