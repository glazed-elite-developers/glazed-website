open React;

type scroller =
  | Root
  | Closest;

let createUseScrollerAPI = (scrollerType: scroller, ()) => {
  let scrollContext = useContext(ScrollContext.context);
  switch (scrollerType) {
  | Root => scrollContext.rootScroller
  | Closest => scrollContext.closestScroller
  };
};

let useRootScrollerAPI: unit => ScrollContext.scrollerAPI = createUseScrollerAPI(Root);
let useClosestScrollerAPI: unit => ScrollContext.scrollerAPI = createUseScrollerAPI(Closest);

type scrollValues = {
  position: ScrollContext.scrollPosition,
  boundingRect: ScrollContext.boundingRect,
};

let createUseScrollValues = (scrollerType: scroller) => {
  let useScrollerAPI = createUseScrollerAPI(scrollerType);

  // ~scrollValuesToInclude=PositionAndBoundingRect,
  // ~scrollEventThrottler=?,
  () => (
    {
      let listenerRef = useRef();
      let scrollerAPI = useScrollerAPI();
      let getScrollValues =
        useCallback1(
          () =>
            {
              position: scrollerAPI.getScrollPosition(),
              boundingRect: scrollerAPI.getBoundingRect(),
            },
          [|scrollerAPI|],
        );
      let (state, setState) = useState(getScrollValues);
      let handleScroll =
        useCallback2(() => setState(_state => getScrollValues()), (getScrollValues, setState));

      useEffect(() => {
        scrollerAPI.registerScrollListener(listenerRef, handleScroll);
        Some(() => scrollerAPI.unregisterScrollListener(listenerRef));
      });

      state;
    }: scrollValues
  );
};

let useRootScrollValues: unit => scrollValues = createUseScrollValues(Root);
let useClosestScrollValues: unit => scrollValues = createUseScrollValues(Closest);
