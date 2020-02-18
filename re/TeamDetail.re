let str = React.string;

module Styles = {
  open Css;

  let developer =
    style([
      color(hex(Theme.Colors.white)),
      padding(rem(1.)),
      paddingTop(rem(10.9375)),
      position(relative),
      height(pct(100.0)),
      backgroundColor(blue),
      backgroundRepeat(noRepeat),
      before([
        //backgroundSize(pct(250.)),
        backgroundPosition4(
        ~x=`left,
        ~offsetX=pct(40.),
        ~y=`top,
        ~offsetY=rem(0.),
      )
      ]),
      media(Theme.Breakpoints.tabletLandscape, [
        before([
          //backgroundSize(pct(100.)),
        ])
      ]),
    ]);

  let name =
    style([
      fontSize(rem(1.)),
      fontFamily(Theme.Fonts.heading),
      position(relative),
      after([
        contentRule(""),
        position(`absolute),
        top(rem(-4.0)),
        left(rem(-1.0)),
        width(rem(8.125)),
        height(rem(8.125)),
        border(px(1), `solid, hex("69C0FE")),
        opacity(0.5),
      ]),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          fontSize(rem(2.)),
          after([
            contentRule(""),
            position(`absolute),
            width(rem(16.125)),
            height(rem(16.125)),
          ]),
        ],
      ),
    ]);

  let descriptionWrapper = style([display(`flex), flexDirection(`column)]);

  let description =
    style([
      fontSize(rem(0.875)),
      fontFamily(Theme.Fonts.text),
      color(hex(Theme.Colors.grey)),
      order(2),
      paddingTop(rem(1.)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(1),
          maxWidth(rem(31.375)),
          fontSize(rem(1.5)),
          lineHeight(rem(3.)),
          paddingTop(rem(1.0)),
        ],
      ),
    ]);

  let headline =
    style([
      fontSize(rem(1.)),
      fontFamily(Theme.Fonts.text),
      fontWeight(`num(700)),
      paddingTop(rem(6.1875)),
      maxWidth(px(407)),
      order(1),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(2),
          paddingTop(rem(4.5)),
          paddingLeft(rem(6.9375)),
          fontSize(rem(2.)),
          before([contentRule("// ")]),
        ],
      ),
    ]);
};

[@react.component]
let make = (~developer, ~image) => {
  <PageContent> 
    <GatsbyBackgroundImage
      className=Styles.developer
      fluid=image>
      <div className=Styles.name>
        {React.array(
           Array.map(
             name => <div> {React.string(name)} </div>,
             Js.String.split(" ", developer##name),
           ),
         )}
      </div>
      <div className=Styles.descriptionWrapper>
        <div className=Styles.description>
          {developer##description |> str}
        </div>
        <div className=Styles.headline> {developer##headline |> str} </div>
      </div>
    </GatsbyBackgroundImage>
  </PageContent>;
};

let default = make;