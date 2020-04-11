// import React, { PureComponent } from 'react';
// import PropTypes from 'prop-types';
// import joinClassNames from 'classnames';
// import {
//     isIOSDevice,
//     scrollElementIfOnLimit,
//     preventRubberBandScroll,
// } from 'shared/util/iOSHackery';

// // Styles.
// import styles from './ScrollContainer.css';
open React;

module Styles = {
  open Css;

  let wrapper = style([]);
  let content = style([]);
  let locked = style([]);
};

// Module mocks.
let isIOSDevice = false;
let preventRubberBandScroll = a => a;
let baseScrollElementIfOnLimit = _element => ();

let defaultScrollingTimeout: int = 100;

type state = {
  arePointerEventsEnabled: bool,
};

type action =
  | TogglePointerEvents(bool)

let initialState = {arePointerEventsEnabled: true};

let reducer = (state: state, action: action) => {
  switch (action) {
  | TogglePointerEvents(nextState) => {
      ...state,
      arePointerEventsEnabled: nextState,
    }
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
  let scrollerAPI = ScrollContext.useScrollerAPI(wrapperRef);
  let needIOSHackery = false;
  let notifySubscribedListeners =
    useCallback(() => List.map(((_component, listener)) => listener()));
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
          | Some(element) => baseScrollElementIfOnLimit(element)
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
        Some(preventRubberBandScroll(handleTouchStart)),
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

  <div
    ref={ReactDOMRe.Ref.domRef(wrapperRef)}
    ?className
    ?style
    ?onClick
    ?onTouchStart
    ?onTouchEnd>
    <div className=?contentClassName style=contentStyle> children </div>
  </div>;
}


// getChildContext() {
//     return {
//         scrollContainers: {
//             ...this.context.scrollContainers,
//             hasRootContainer: true,
//             ...this.getContextApi(),
//         },
//     };
// }

// getContextApi() {
//     const scrollerApi = {
//         registerScrollListener: this.registerScrollListener,
//         unregisterScrollListener: this.unregisterScrollListener,
//         getScrollPosition: this.getScrollPosition,
//         getBoundingRect: this.getBoundingRect,
//         scrollTo: this.scrollTo,
//     };

//     return !this.getHasRootContainer() ? {
//         rootScroller: scrollerApi,
//         closestScroller: scrollerApi,
//     } : { closestScroller: scrollerApi };
// }

// getHasRootContainer() {
//     const { hasRootContainer } = this.context.scrollContainers || {};

//     return hasRootContainer;
// }

// getNeedIOSHackery() {
//     return isIOSDevice() && !this.getHasRootContainer();
// }
