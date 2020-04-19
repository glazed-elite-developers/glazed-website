open React;

module Styles = {
  open Css;

  let wrapper =
    style([
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
  let domSlideRefs = Array.map(ReactDOMRe.Ref.domRef, Ref.current(refs));
  let updatePositions =
    useCallback2(
      () =>
        Webapi.Dom.(
          Array.iteri(
            (index, slideRef) =>
              switch (slideRef |> Ref.current |> Js.Nullable.toOption) {
              | None => ()
              | Some(element) =>
                setPositions(state => {
                  let nextPosition =
                    DomRect.top(Element.getBoundingClientRect(element));
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
      (positionsState, refs),
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
  let scrollValues = ScrollConnectors.useRootScrollValues();
  useMemo2(
    () =>
      Belt.Array.reduceWithIndex(positions, 0, (currentPage, position, index) =>
        scrollValues.position.scrollTop
        +. scrollValues.boundingRect.top >= position
        +. offsetY
          ? index : currentPage
      ),
    (scrollValues, positions),
  );
};

let pagesWithDarkNavBarLinks = Belt.Set.Int.fromArray([|2, 4|]);
let numberOfSlides = 5;
let headerStyleTransitionOffsetY = (-65.);

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  // @TODO: Update slide positions on content resize.
  let (positions, domSlideRefs, onResize) =
    usePagePositionController(numberOfSlides);
  let currentPageIndex =
    useCurrentSlideIndex(positions, headerStyleTransitionOffsetY);
  let useDarkNavBarLinks =
    Belt.Set.Int.has(pagesWithDarkNavBarLinks, currentPageIndex);

  <Layout>
    <PageLayout useDarkNavBarLinks currentPageIndex>
      <PageContent className=Styles.wrapper>
        <IndexLandingSlide innerRef={Array.get(domSlideRefs, 0)} onResize />
        <IndexCaseStudiesSlide
          innerRef={Array.get(domSlideRefs, 1)}
          onResize
        />
        <IndexAboutSlide innerRef={Array.get(domSlideRefs, 2)} onResize />
        <IndexTeamSlide innerRef={Array.get(domSlideRefs, 3)} onResize />
        <IndexManifestoSlide innerRef={Array.get(domSlideRefs, 4)} onResize />
      </PageContent>
    </PageLayout>
  </Layout>;
};

let default = make;