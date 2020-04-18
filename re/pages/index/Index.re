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

let usePagePositionController = numberOfPages => {
  let (positions, setPositions) =
    useState(() => Array.make(numberOfPages, 0.));
  let refs: Ref.t(array(option(Webapi.Dom.eventPhase))) = useRef(Array.make(numberOfPages, None));
  let updateSlideRef = useCallback1((index, element) => {
    let nextRefs = Array.mapi(
      (slideIndex, slide) => index === slideIndex ? element : slide,
      Ref.current(refs)
    );
    Ref.setCurrent(refs, nextRefs);
  }, [|refs|]);

  useEffect(() => {
    open Webapi.Dom;
    Array.iteri(
      (index, slideRef) =>
        switch (slideRef) {
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
    );
    None;
  });

  (positions, updateSlideRef);
};

let useCurrentSlide: int => (int, array(ReactDOMRe.Ref.t)) =
  numberOfPages => {
    let scrollValues = ScrollConnectors.useRootScrollValues();
    let (positions, refs) = usePagePositionController(numberOfPages);
    useMemo2(
      () =>
        Belt.Array.reduceReverse2(
          positions,
          refs,
          (0, [||]),
          ((currentPage, slideRefs), position, slideRef) =>
            position > scrollValues.boundingRect.top ? index : currentPage,
            Array.append(slideRefs, [|ReactDOMRe.Ref.domRef(slideRef)|])
        ),
        // Belt.Array.reduceWithIndex(
        //   positions,
        //   (0, [||]),
        //   ((currentPage, slideRefs), position, index) =>
        //   (
        //     position > scrollValues.boundingRect.top ? index : currentPage,
        //     Array.append(slideRefs, [|ReactDOMRe.Ref.domRef(slideRef)|]),
        //   )
        // ),
      (scrollValues, positionsAndRefs),
    );
  };

let pagesWithDarkNavBarLinks = Belt.Set.Int.fromArray([|2, 4|]);

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  let (currentPage, slideRefs) = useCurrentSlide(5);
  let useDarkNavBarLinks =
    Belt.Set.Int.has(pagesWithDarkNavBarLinks, currentPage);

  <Layout>
    <PageLayout useDarkNavBarLinks>
      <PageContent className=Styles.wrapper>
        <IndexLandingSlide innerRef={Array.get(slideRefs, 0)} />
        <IndexCaseStudiesSlide innerRef={Array.get(slideRefs, 1)} />
        <IndexAboutSlide innerRef={Array.get(slideRefs, 2)} />
        <IndexTeamSlide innerRef={Array.get(slideRefs, 3)} />
        <IndexManifestoSlide innerRef={Array.get(slideRefs, 4)} />
      </PageContent>
    </PageLayout>
  </Layout>;
};

let default = make;