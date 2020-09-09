open React;

module Styles = {
  open Css;
  open Theme;

  let pageLayout =
    style([
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.whiteTurquoise)),
    ]);
  let header =
    style([
      position(`sticky),
      transform(`translateZ(`zero)),
      backgroundColor(hex(Colors.whiteTurquoise)),
    ]);
  let headerWithShadow =
    style([boxShadow(Shadow.box(~y=px(7), ~blur=px(15), rgba(0, 0, 0, 0.04)))]);
};

let techs: array(CaseStudyBrief.tech) = [|
  {name: "react", icon: TechIcons.twitter},
  {name: "angular", icon: TechIcons.twitter},
  {name: "ios", icon: TechIcons.twitter},
|];

type dynamicContentComponents =
  | BigImage(option(Gatsby.fluidImage))
  | TextAndImage(string, option(Gatsby.fluidImage))
  | QuoteCard(string, CaseStudyQuoteCard.author)
  | BigVideo(string)
  | TextAndVideo(string, string)
  | Custom(React.element);

type hero = {
  image: option(Gatsby.fluidImage),
  title: string,
  area: string,
  text: string,
};

type brief = {
  techs: array(CaseStudyBrief.tech),
  year: string,
  brief: string,
};

type nextCase = {
  image: option(Gatsby.fluidImage),
  title: string,
  area: string,
  link: string,
};

type content = {
  hero,
  brief,
  content: array(dynamicContentComponents),
  nextCase,
};

type scrollDirection =
  | Up
  | Down;

type headerPosition =
  | Static(float)
  | Fixed;

let useHeaderPosition = () => {
  let scrollValues = ScrollConnectors.useClosestScrollValues();
  let scrollTop = scrollValues.position.scrollTop;
  let lastPositionRef = useRef(Static(scrollTop));
  let (headerHeight, setHeaderHeight) = useState(() => 0.);
  let lastScrollDataRef = useRef((scrollTop, Down));
  let (lastScrollTop, lastScrollDirection) = lastScrollDataRef.current;
  let scrollDirection =
    scrollTop > lastScrollTop ? Down : lastScrollTop === scrollTop ? lastScrollDirection : Up;
  let shouldHaveBackground = scrollTop > 0.;
  lastScrollDataRef.current = (scrollTop, scrollDirection);
  let onHeaderResize =
    useCallback1(
      (nextBoundingRect: option(Utils.Dom.Measurements.boundingRect)) => {
        switch (nextBoundingRect) {
        | Some(boundingRect) => setHeaderHeight(_state => boundingRect.height)
        | None => ()
        }
      },
      [|setHeaderHeight|],
    );
  let position =
    useMemo4(
      () => {
        switch (scrollDirection, lastPositionRef.current) {
        | (Down, Fixed) => Static(Js.Math.max_float(scrollTop, 0.))
        | (Up, Static(offset)) =>
          if (offset +. headerHeight < scrollTop) {
            Static(Js.Math.max_float(scrollTop -. headerHeight, 0.));
          } else if (offset >= scrollTop) {
            Fixed;
          } else {
            lastPositionRef.current;
          }
        | _ => lastPositionRef.current
        }
      },
      (scrollDirection, lastPositionRef.current, headerHeight, scrollTop),
    );
  lastPositionRef.current = position;

  (position, shouldHaveBackground, onHeaderResize);
};

[@react.component]
let make = (~content) => {
  let (headerPosition, shouldHaveBackground, onHeaderResize) = useHeaderPosition();
  let headerStyle =
    useMemo1(
      () => {
        switch (headerPosition) {
        | Static(offsetTop) =>
          Some(
            ReactDOMRe.Style.make(
              ~position="relative",
              ~transform={j|translateY($(offsetTop)px)|j},
              (),
            ),
          )
        | Fixed => None
        }
      },
      [|headerPosition|],
    );
  let headerClassName =
    shouldHaveBackground ? Css.merge([Styles.header, Styles.headerWithShadow]) : Styles.header;

  <Layout>
    <PageLayout
      className=Styles.pageLayout
      headerClassName
      ?headerStyle
      onHeaderResize
      useDarkNavBarLinks=true
      currentPageIndex=1>
      <CaseStudyHeader
        image=?{content.hero.image}
        title={content.hero.title}
        area={content.hero.area}
        text={content.hero.text}
      />
      <CaseStudyBrief
        techs={content.brief.techs}
        year={content.brief.year}
        brief={content.brief.brief}
      />
      {React.array(
         Belt.Array.mapWithIndex(
           content.content,
           (index, contentComponent) => {
             let key = Belt.Int.toString(index);

             switch (contentComponent) {
             | BigImage(image) => <CaseStudyBigImage key ?image />
             | TextAndImage(text, image) => <CaseStudyTextAndImage key text ?image />
             | QuoteCard(quote, author) => <CaseStudyQuoteCard key quote author />
             | BigVideo(src) => <CaseStudyBigVideo key src />
             | TextAndVideo(text, videoSrc) => <CaseStudyTextAndVideo key text videoSrc />
             | Custom(component) => cloneElement(component, ReactDOMRe.props(~key, ()))
             };
           },
         ),
       )}
      <CaseStudyNextCase
        image=?{content.nextCase.image}
        title={content.nextCase.title}
        area={content.nextCase.area}
        link={content.nextCase.link}
      />
    </PageLayout>
  </Layout>;
};

let default = make;
