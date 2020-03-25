let str = React.string;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      height(pct(100.)),
      padding4(
        ~top=rem(4.1875),
        ~right=`zero,
        ~left=rem(1.25),
        ~bottom=`zero,
      ),
      overflow(`hidden),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          padding4(
            ~top=rem(6.25),
            ~right=rem(7.25),
            ~bottom=rem(1.875),
            ~left=rem(4.75),
          ),
        ],
      ),
    ]);
  let heading =
    style([
      position(`relative),
      padding4(
        ~top=`rem(1.875),
        ~left=`rem(0.9375),
        ~bottom=`rem(0.625),
        ~right=`zero,
      ),
      fontSize(`rem(1.125)),
      color(hex(Colors.grey)),
      before([
        contentRule(""),
        display(`block),
        position(`absolute),
        top(`px(0)),
        left(`px(0)),
        width(px(130)),
        height(px(130)),
        border(px(1), `solid, hex(Colors.glazedBabyBlueText)),
        opacity(0.1),
        media(
          Theme.Breakpoints.tabletLandscape,
          [width(`px(258)), height(`px(258))],
        ),
      ]),
      media(
        Theme.Breakpoints.tabletLandscape,
        [width(`auto), fontSize(`rem(2.))],
      ),
    ]);
  let contentText =
    style([
      padding4(
        ~top=`zero,
        ~right=`rem(0.9375),
        ~bottom=`zero,
        ~left=`rem(0.9375),
      ),
      opacity(0.6),
      fontSize(`rem(0.75)),
      lineHeight(`abs(2.)),
      color(hex(Theme.Colors.glazedGreyText)),
    ]);
  let htmlTag =
    style([
      padding4(
        ~top=`rem(0.625),
        ~left=`rem(0.9375),
        ~bottom=`rem(1.25),
        ~right=`rem(0.9375),
      ),
      color(hex(Theme.Colors.glazedBabyBlueText)),
      fontSize(rem(1.125)),
      width(`rem(21.875)),
      lineHeight(rem(1.75)),
      textAlign(`left),
      alignSelf(`flexEnd),
    ]);
};

module LineProjectElement = {
  module Styles = {
    open Css;
    open Theme;

    let row =
      style([
        paddingLeft(`rem(0.9375)),
        display(`flex),
        flexDirection(row),
        color(hex(Colors.almostWhite)),
        opacity(0.8),
      ]);
    let rowLeft = style([opacity(0.3), fontSize(`rem(0.625))]);
    let rowRight = style([paddingLeft(px(15)), fontSize(`rem(0.75))]);
  };

  [@react.component]
  let make = (~children) => {
    <div className=Styles.row>
      <div className=Styles.rowLeft> {"<li>" |> ReasonReact.string} </div>
      <div className=Styles.rowRight> children </div>
    </div>;
  };
};

let kindsOfProjects = [|
  "Our kind of projects:",
  "Technically complex",
  "Highly customised and detailed",
  "Innovative and using recent technologies",
  "Critically impact on businesses or people's lives",
|];

module ListProjects = {
  module Styles = {
    open Css;
    open Theme;

    let wrapper =
      style([
        width(`percent(100.0)),
        backgroundColor(hex(Theme.Colors.glazedBlueDarker)),
        Css.float(`right),
        lineHeight(px(30)),
        flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      ]);

    let heading =
      style([
        padding4(
          ~top=`rem(1.25),
          ~left=`rem(3.5),
          ~bottom=`rem(0.625),
          ~right=`zero,
        ),
        fontSize(`rem(0.625)),
        color(hex(Colors.almostWhite)),
        opacity(0.3),
      ]);
  };

  [@react.component]
  let make = () => {
    <div className=Styles.wrapper>
      <Heading level=Heading.H6 className=Styles.heading>
        {"Our kind of projects:" |> ReasonReact.string}
      </Heading>
      {React.array(
         Array.mapi(
           (index, element) =>
             <LineProjectElement key={Belt.Int.toString(index)}>
               {ReasonReact.string(element)}
             </LineProjectElement>,
           kindsOfProjects,
         ),
       )}
    </div>;
  };
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <FullPageSlide className=Styles.wrapper>
    <Heading level=Heading.H1 className=Styles.heading>
      {"// about us" |> ReasonReact.string}
    </Heading>
    <p className=Styles.contentText>
      {"Every team member is highly experienced (8y avg), strives for excellency and has access to the colossal combined knowledge of the whole team. We act as (an extension of) your development team, in very flexible team sizes, and adapting to your processes and with a tight feedback loop."
       |> ReasonReact.string}
    </p>
    <HTMLText tag=HTMLText.H2 className=Styles.htmlTag>
      {"It's your code, ready to hand off or build a team around at any time, but we care for it as it were ours."
       |> ReasonReact.string}
    </HTMLText>
    <ListProjects />
  </FullPageSlide>;
};

let default = make;