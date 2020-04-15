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
        let positionState = useState(() => 0);
        let ref = useRef(Js.Nullable.null);
        (positionState, (ReactDOMRe.Ref.domRef(ref), ref));
      },
    );
  let getPagePosition = (page: int) => {
    switch (Belt.Array.get(positionsAndRefs, page)) {
    | None => None
    | Some((position)) => Some(position);
    };
  };
  let getPageRef = (page: int) => {
    switch (Belt.Array.get(positionsAndRefs, page)) {
    | None => ReactDOMRe.Ref.domRef(Js.Nullable.null)
    | Some((_, (domRef))) => domRef;
    };
  };

  useEffect(() => {
    Array.iter(
      (((position, setPosition), (ref_))) => {
        Js.log(position);
        Js.log(setPosition);
        Js.log(ref_);
      },
      positionsAndRefs,
    );
    None;
  });

  (getPagePosition, getPageRef);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  let (getPagePosition, getPageRef) = usePagePositionController(5);
  let scrollValues = ScrollConnectors.useRootScrollValues();
  Js.log(scrollValues);

  <Layout>
    <PageLayout>
      <PageContent className=Styles.wrapper>
        <IndexLandingSlide ref=?getPageRef(1) />
        <IndexCaseStudiesSlide />
        <IndexAboutSlide />
        <IndexTeamSlide />
        <IndexManifestoSlide />
      </PageContent>
    </PageLayout>
  </Layout>;
};

let default = make;