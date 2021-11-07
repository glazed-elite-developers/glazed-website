open React;

module Styles = {
  open Css;
  open Theme;

  let pageLayout =
    style([
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.whiteTurquoise)),
    ]);
  let pageContent = style([position(`relative), zIndex(0), transform(`translateZ(`zero))]);
  let header =
    style([
      position(`fixed),
      backgroundColor(hex(Colors.whiteTurquoise)),
      transition(~duration=200, ~delay=0, ~timingFunction=`easeOut, "all"),
      transform(translateY(pct(-100.)))
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


[@react.component]
let make = (~content, ~pageTitle, ~pageDescription) => {
  <Layout title=pageTitle description=pageDescription>
    <PageLayout
      className=Styles.pageLayout
      useDarkNavBarLinks=true
      useFloatingNavBar=true
      currentPageIndex=1>
      <div className=Styles.pageContent>
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
      </div>
    </PageLayout>
  </Layout>;
};

let default = make;
