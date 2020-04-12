open React;

module Styles = {
  open Css;

  let wrapper =
    style([
      /* Hints the browser to isolate the content in a new layer without creating
         a new stacking context. 'will-change: transform;' of other transform based
         hints would create new contexts. */
      overflow(`auto),
      display(`flex),
      flex3(~grow=1., ~shrink=0., ~basis=`rem(0.000000001)),
      flexDirection(`column),
      unsafe("will-change", "opacity"),
      unsafe("-webkit-overflow-scrolling", "touch"),
      unsafe("-ms-overflow-style", "-ms-autohiding-scrollbar"),
    ]);
  let content =
    style([
      display(`flex),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      flexDirection(`column),
      unsafe("will-change", "opacity"),
    ]);
  let locked =
    style([
      overflow(`hidden),
      unsafe("-webkit-overflow-scrolling", "auto"),
    ]);
  let iOSScrollFix =
    style([
      flex3(~grow=1., ~shrink=0., ~basis=Calc.(+)(pct(100.), px(2))),
    ]);
};

// Module mocks.
let isIOSDevice = false;

let defaultScrollingTimeout: int = 100;

type state = {arePointerEventsEnabled: bool};

type action =
  | TogglePointerEvents(bool);

let initialState = {arePointerEventsEnabled: true};

let reducer = (_state: state, action: action) => {
  switch (action) {
  | TogglePointerEvents(nextState) => {arePointerEventsEnabled: nextState}
  };
};

[@react.component]
let make =
    (
      ~lock: bool,
      ~disablePointerEventsOnScroll: bool=false,
      ~scrollingTimeout: int=defaultScrollingTimeout,
      // https://github.com/reasonml/reason-react/issues/497
      // ~innerRef=?,
      ~children,
      ~className=?,
      ~contentClassName=?,
      ~style=?,
      ~contentStyle=?,
      ~onClick=?,
    ) => {
  open Utils.React;

  let wrapperRef = useRef(Js.Nullable.null);
  let didTouchEnd = useRef(false);
  let scrollingTimeoutId = useRef(None);
  let (state, dispatch) = useReducer(reducer, initialState);
  // let needIOSHackery = useMemo2(() => false, (isIOSDevice, ));
  let scrollContext = useContext(ScrollContext.scrollContext);
  let (scrollerAPI, notifySubscribedListeners) =
    ScrollContext.useScrollerAPI(wrapperRef);
  let scrollContextToPassDown =
    scrollContext.hasRootContainer
      ? {...scrollContext, closestScroller: scrollerAPI}
      : {
        hasRootContainer: true,
        closestScroller: scrollerAPI,
        rootScroller: scrollerAPI,
      };
  let needIOSHackery = isIOSDevice && scrollContext.hasRootContainer;
  let handleTouchStart =
    useCallback(_event =>
      if (Ref.current(didTouchEnd)) {
        Ref.setCurrent(didTouchEnd, false);
      }
    );
  let handleTouchEnd =
    useCallback(_event => Ref.setCurrent(didTouchEnd, true));
  let scrollElementIfOnLimit =
    useCallback1(
      () =>
        if (needIOSHackery) {
          switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
          | None => ()
          | Some(element) =>
            ScrollContainerUtils.scrollElementIfOnLimit(element)
          };
        },
      [|needIOSHackery|],
    );
  let handleScrollEnd =
    useCallback3(
      () => {
        if (disablePointerEventsOnScroll) {
          dispatch(TogglePointerEvents(true));
        };

        if (Ref.current(didTouchEnd)) {
          scrollElementIfOnLimit();
        };
      },
      (disablePointerEventsOnScroll, dispatch, scrollElementIfOnLimit),
    );
  let handleScroll =
    useCallback3(
      _event => {
        notifySubscribedListeners();

        if (disablePointerEventsOnScroll || needIOSHackery) {
          switch (Ref.current(scrollingTimeoutId)) {
          | None => ()
          | Some(id) => Js.Global.clearTimeout(id)
          };

          Ref.setCurrent(
            scrollingTimeoutId,
            Some(Js.Global.setTimeout(handleScrollEnd, scrollingTimeout)),
          );

          if (disablePointerEventsOnScroll) {
            dispatch(TogglePointerEvents(false));
          };
        };

        ();
      },
      (notifySubscribedListeners, disablePointerEventsOnScroll, dispatch),
    );
  let attachScrollListener =
    useCallback(() =>
      switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
      | None => ()
      | Some(element) =>
        Webapi.Dom.Element.addEventListenerWithOptions(
          "scroll",
          handleScroll,
          {"passive": true, "once": false, "capture": false},
          element,
        )
      }
    );
  let detachScrollListener =
    useCallback(() =>
      switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
      | None => ()
      | Some(element) =>
        Webapi.Dom.Element.removeEventListener(
          "scroll",
          handleScroll,
          element,
        )
      }
    );

  let (onTouchStart, onTouchEnd) =
    needIOSHackery
      ? (
        Some(ScrollContainerUtils.preventRubberBandScroll(handleTouchStart)),
        Some(handleTouchEnd),
      )
      : (None, None);
  let pointerEventsStyle =
    ReactDOMRe.Style.make(
      ~pointerEvents=?state.arePointerEventsEnabled ? None : Some("none"),
      (),
    );
  let className =
    combineClassNames([
      Some(Styles.wrapper),
      className,
      lock ? Some(Styles.locked) : None,
    ]);
  let contentClassName =
    combineClassNames([Some(Styles.content), contentClassName]);
  let contentStyle =
    switch (contentStyle) {
    | None => pointerEventsStyle
    | Some(style) => ReactDOMRe.Style.combine(style, pointerEventsStyle)
    };

  useEffect(() => {
    attachScrollListener();
    Some(detachScrollListener);
  });

  <ScrollContext value=scrollContextToPassDown>
    <div
      ref={ReactDOMRe.Ref.domRef(wrapperRef)}
      ?className
      ?style
      ?onClick
      ?onTouchStart
      ?onTouchEnd>
      <div className=?contentClassName style=contentStyle> children </div>
    </div>
  </ScrollContext>;
};

let default = make;