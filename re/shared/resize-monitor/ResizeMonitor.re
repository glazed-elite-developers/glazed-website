open React;

module Styles = {
  open Css;

  let wrapper =
    style([
      position(`absolute),
      top(`zero),
      left(`zero),
      width(pct(100.)),
      height(pct(100.)),
      zIndex(-1),
      overflow(`hidden),
      display(`block),
      visibility(`hidden),
      pointerEvents(`none),
    ]);
};

[@react.component]
let make =
    (
      ~className=?,
      ~onResize: option(Utils.Dom.Measurements.boundingRect) => unit,
    ) => {
  open Utils.React;

  // open Utils.React;
  let placeholderObjectRef = useRef(Js.Nullable.null);
  let objectDefaultViewRef = useRef(Js.Nullable.null);
  let (withData, setWithData) = useState(() => false);
  let dispatchResizeEvent =
    useCallback1(
      Utils.Timing.throttle(() => {
        let boundingClientRect =
          switch (placeholderObjectRef |> Ref.current |> Js.Nullable.toOption) {
          | None => None
          | Some(element) =>
            Some(Utils.Dom.Measurements.getBoundingClientRect(element))
          };
        onResize(boundingClientRect);
      }),
      [|onResize|],
    );
  let handleContentResize =
    useCallback1(_event => dispatchResizeEvent(), [|dispatchResizeEvent|]);
  let handleLoad =
    useCallback1(
      _event =>
        switch (placeholderObjectRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(element) =>
          let jsElement = Utils.Dom.Types.webApiElementToJsObject(element);
          let objectDefaultView = jsElement##contentDocument##defaultView;
          Ref.setCurrent(objectDefaultViewRef, objectDefaultView);
          Webapi.Dom.Element.addEventListener(
            "resize",
            handleContentResize,
            objectDefaultView,
          );
          dispatchResizeEvent();
        },
      [|handleContentResize|],
    );
  let data = withData ? Some("about:blank") : None;

  useEffect0(() => {
    // For some reason, IE doesn't fire the load event when the object 'data' attribute
    // is assigned before the object element is mounted. That's what we are triggering here.
    // Also, on Chrome, only the first <object> mounted gets onLoad called. Go figure. This
    // fixes that too.
    setWithData(_state => true);
    Some(
      () =>
        switch (objectDefaultViewRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(element) =>
          Webapi.Dom.Element.removeEventListener(
            "resize",
            handleContentResize,
            Ref.current(element),
          )
        },
    );
  });

  <object
    ref={ReactDOMRe.Ref.domRef(placeholderObjectRef)}
    className=?{combineClassNames([Some(Styles.wrapper), className])}
    onLoad=handleLoad
    ?data
    type_="text/html"
    role="presentation"
    ariaLabel="resize monitor placeholder"
  />;
};