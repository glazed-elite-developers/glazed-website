open Utils.React;

module Styles = {
  open Css;

  let section =
    style([
      padding2(~h=`zero, ~v=rem(2.5)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [padding3(~h=rem(11.25), ~top=rem(6.875), ~bottom=rem(5.))],
      ),
    ]);
  let image = style([boxShadow(Shadow.box(~y=px(50), ~blur=px(60), rgba(0, 0, 0, 0.1)))]);
};

[@react.component]
let make = (~image: option(Gatsby.fluidImage)=?, ~className=?, ~imageClassName=?) => {
  let imageStyle = ReactDOMRe.Style.make(~objectFit="contain", ());

  <CaseStudySection className=?{combineClassNames([Some(Styles.section), className])}>
    <div className=?{combineClassNames([Some(Styles.image), imageClassName])}>
      <Gatsby.Image imgStyle=imageStyle fluid=?image />
    </div>
  </CaseStudySection>;
};

let default = make;
