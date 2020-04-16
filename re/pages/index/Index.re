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
  let positionsAndRefs =
    Array.init(
      numberOfPages,
      _index => {
        let positionState = useState(() => 0.);
        let ref = useRef(Js.Nullable.null);
        (positionState, ref);
      },
    );
  let getPagePosition = (page: int) => {
    switch (Belt.Array.get(positionsAndRefs, page)) {
    | None => None
    | Some(((position, _), _)) => Some(position)
    };
  };
  let slideRef = (page: int) => {
    switch (Belt.Array.get(positionsAndRefs, page)) {
    | None => None
    | Some((_, ref)) => Some(ref)
    };
  };

  useEffect(() => {
    open Webapi.Dom;
    Array.iter(
      (((_position, setPosition), pageRef)) =>
        switch (pageRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(element) =>
          setPosition(_ =>
            DomRect.top(Element.getBoundingClientRect(element))
          )
        },
      positionsAndRefs,
    );
    None;
  });

  (getPagePosition, slideRef);
};

let useCurrentSlide = numberOfPages => {
  let scrollValues = ScrollConnectors.useRootScrollValues();
  let (getPagePosition, slideRef) = usePagePositionController(5);
  let pagePositions =
    Array.init(numberOfPages, index =>
      switch (getPagePosition(index)) {
      | None => 0.
      | Some(position) => position
      }
    );
  let currentPage =
    Belt.Array.reduceWithIndex(pagePositions, 0, (result, position, index) =>
      scrollValues.position.scrollTop
      -. scrollValues.boundingRect.top > position
        ? index : result
    );

  (currentPage, slideRef);
};

let pagesWithDarkNavBarLinks = Belt.Set.Int.fromArray([|2, 4|]);

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  let (currentPage, slideRef) = useCurrentSlide(5);
  let useDarkNavBarLinks =
    Belt.Set.Int.has(pagesWithDarkNavBarLinks, currentPage);

  <Layout>
    <PageLayout useDarkNavBarLinks>
      <PageContent className=Styles.wrapper>
        <IndexLandingSlide
          innerRef=?{Belt.Option.map(slideRef(0), ReactDOMRe.Ref.domRef)}
        />
        <IndexCaseStudiesSlide
          innerRef=?{Belt.Option.map(slideRef(1), ReactDOMRe.Ref.domRef)}
        />
        <IndexAboutSlide
          innerRef=?{Belt.Option.map(slideRef(2), ReactDOMRe.Ref.domRef)}
        />
        <IndexTeamSlide
          innerRef=?{Belt.Option.map(slideRef(3), ReactDOMRe.Ref.domRef)}
        />
        <IndexManifestoSlide
          innerRef=?{Belt.Option.map(slideRef(4), ReactDOMRe.Ref.domRef)}
        />
      </PageContent>
    </PageLayout>
  </Layout>;
};

let default = make;