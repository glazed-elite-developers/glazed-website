open React;

type scrollPosition = Utils.Dom.Measurements.scrollPosition;

type boundingRect = Utils.Dom.Measurements.boundingRect;

let initialScrollPosition: scrollPosition = {
  scrollTop: 0.,
  scrollLeft: 0.,
  scrollWidth: 0,
  scrollHeight: 0,
};

let initialBoundingRect: boundingRect = {
  top: 0.,
  right: 0.,
  bottom: 0.,
  left: 0.,
  width: 0.,
  height: 0.,
};

type scrollListenerSubjectID = Ref.t(unit);

type scrollListener = unit => unit;

type scrollerAPI = {
  registerScrollListener: (scrollListenerSubjectID, scrollListener) => unit,
  unregisterScrollListener: scrollListenerSubjectID => unit,
  getScrollPosition: unit => scrollPosition,
  getBoundingRect: unit => boundingRect,
  scrollTo: (option(float), option(float)) => unit,
};

type context = {
  // Scroll container instances highest in the component tree set this flag to true,
  // which we then use to prevent the rubber band scroll animations in iOS.
  hasRootContainer: bool,
  closestScroller: scrollerAPI,
  rootScroller: scrollerAPI,
};

let defaultScrollerAPI = {
  registerScrollListener: (_component, _handler) => (),
  unregisterScrollListener: _component => (),
  getScrollPosition: () => initialScrollPosition,
  getBoundingRect: () => initialBoundingRect,
  scrollTo: (_top, _left) => (),
};

let defaultContextValue = {
  // Scroll container instances highest in the component tree set this flag to true,
  // which we then use to prevent the rubber band scroll animations in iOS.
  hasRootContainer: false,
  closestScroller: defaultScrollerAPI,
  rootScroller: defaultScrollerAPI,
};

let context = createContext(defaultContextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = Context.provider(context);
};

let useScrollerAPI = wrapperRef => {
  let scrollListeners = useRef([]);
  let registerScrollListener =
    useCallback1(
      (component, handler) => {
        Ref.setCurrent(
          scrollListeners,
          [(component, handler), ...Ref.current(scrollListeners)],
        );
        ();
      },
      [|scrollListeners|],
    );
  let unregisterScrollListener =
    useCallback1(
      component => {
        Ref.setCurrent(
          scrollListeners,
          Belt.List.keep(
            Ref.current(scrollListeners), ((component', _listener)) =>
            component' !== component
          ),
        );
        ();
      },
      [|scrollListeners|],
    );
  let notifySubscribedListeners =
    useCallback1(
      () => {
        List.iter(
          ((_component, listener)) => listener(),
          Ref.current(scrollListeners),
        );
        ();
      },
      [|scrollListeners|],
    );
  let getScrollPosition =
    useCallback1(
      (): scrollPosition =>
        switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
        | None => initialScrollPosition
        | Some(element) => Utils.Dom.Measurements.getScrollPosition(element)
        },
      [|wrapperRef|],
    );
  let getBoundingRect =
    useCallback1(
      (): boundingRect =>
        switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
        | None => initialBoundingRect
        | Some(element) =>
          Utils.Dom.Measurements.getBoundingClientRect(element)
        },
      [|wrapperRef|],
    );
  let scrollTo =
    useCallback((top, left) =>
      switch (wrapperRef |> Ref.current |> Js.Nullable.toOption) {
      | None => ()
      | Some(element) =>
        switch (top) {
        | None => ()
        | Some(value) => Webapi.Dom.Element.setScrollTop(element, value)
        };
        switch (left) {
        | None => ()
        | Some(value) => Webapi.Dom.Element.setScrollLeft(element, value)
        };
      }
    );
  let scrollerAPI =
    useMemo5(
      () =>
        {
          registerScrollListener,
          unregisterScrollListener,
          getScrollPosition,
          getBoundingRect,
          scrollTo,
        },
      (
        registerScrollListener,
        unregisterScrollListener,
        getScrollPosition,
        getBoundingRect,
        scrollTo,
      ),
    );

  (scrollerAPI, notifySubscribedListeners);
};