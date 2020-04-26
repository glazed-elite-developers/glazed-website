open React;

module Styles = {
  open Css;

  let pageLayout = style([
    maxHeight(pct(100.)),
  ]);
  let wrapper =
    style([
      maxHeight(pct(100.)),
      padding(`zero),
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      media(Theme.Breakpoints.tabletLandscape, [padding(`zero)]),
    ]);
};

let usePagePositionController = (numberOfSlides: int) => {
  let positionsState = useState(() => Array.make(numberOfSlides, 0.));
  let (positions, setPositions) = positionsState;
  let refs: Ref.t(array(Ref.t(Js.Nullable.t('a)))) =
    useRef(Array.init(numberOfSlides, _index => createRef()));
  let scrollerAPI = ScrollConnectors.useClosestScrollerAPI();
  let domSlideRefs = Array.map(ReactDOMRe.Ref.domRef, Ref.current(refs));
  let updatePositions =
    useCallback3(
      () =>
        Webapi.Dom.(
          Array.iteri(
            (index, slideRef) =>
              switch (slideRef |> Ref.current |> Js.Nullable.toOption) {
              | None => ()
              | Some(element) =>
                setPositions(state => {
                  // We add the scrollTop value to the element's top offset when reading the value so
                  // that we always store the element's position relative to the scroll container.
                  let nextPosition =
                    DomRect.top(Element.getBoundingClientRect(element))
                    +. scrollerAPI.getScrollPosition().scrollTop;
                  Array.mapi(
                    (positionIndex, position) =>
                      index === positionIndex ? nextPosition : position,
                    state,
                  );
                })
              },
            Ref.current(refs),
          )
        ),
      (setPositions, refs, scrollerAPI),
    );
  let handleResize =
    useCallback1(
      (_nextBoundingRect: option(Utils.Dom.Measurements.boundingRect)) =>
        updatePositions(),
      [|updatePositions|],
    );

  useEffect0(() => {
    updatePositions();
    None;
  });

  (positions, domSlideRefs, handleResize);
};

let useCurrentSlideIndex = (positions: array(float), offsetY: float): int => {
  let scrollValues = ScrollConnectors.useClosestScrollValues();
  useMemo2(
    () =>
      Belt.Array.reduceWithIndex(positions, 0, (currentPage, position, index) => {
        scrollValues.position.scrollTop
        +. scrollValues.boundingRect.top >= position
        +. offsetY
          ? index : currentPage
      }),
    (scrollValues, positions),
  );
};

let pagesWithDarkNavBarLinks = Belt.Set.Int.fromArray([|2, 4|]);
let numberOfSlides = 5;
let headerStyleTransitionOffsetY = (-65.);

[@react.component]
let make = () => {
  let (positions, domSlideRefs, onResize) =
    usePagePositionController(numberOfSlides);
  let currentPageIndex =
    useCurrentSlideIndex(positions, headerStyleTransitionOffsetY);
  let useDarkNavBarLinks =
    Belt.Set.Int.has(pagesWithDarkNavBarLinks, currentPageIndex);

  <Layout>
    <PageLayout className=Styles.pageLayout useDarkNavBarLinks currentPageIndex>
      <PageContent className=Styles.wrapper>
        <IndexLandingSlide
          id="hey"
          innerRef={Array.get(domSlideRefs, 0)}
          onResize
        />
        <IndexCaseStudiesSlide
          id="case-studies"
          innerRef={Array.get(domSlideRefs, 1)}
          onResize
        />
        <IndexAboutSlide
          id="about"
          innerRef={Array.get(domSlideRefs, 2)}
          onResize
        />
        <IndexTeamSlide
          id="team"
          innerRef={Array.get(domSlideRefs, 3)}
          onResize
        />
        <IndexManifestoSlide
          id="manifesto"
          innerRef={Array.get(domSlideRefs, 4)}
          onResize
        />
      </PageContent>
    </PageLayout>
  </Layout>;
};

let default = make;