let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      padding(rem(10.)),
    ]);

  let htmlTag =
    style([
      color(hex(Theme.Colors.glazedBabyBlueText)),
      fontSize(rem(1.125)),
      width(px(241)),
      lineHeight(rem(1.75)),
      textAlign(`left),
      paddingRight(px(25)),
      paddingTop(px(10)),
      float(`right)
    ]);

  let headerText =
    style([
      border(px(1), `solid, rgba(159, 168, 179, 0.1)),
      textAlign(center),
      width(px(130)),
      paddingTop(px(31)),
      paddingBottom(px(71)),
    ]);

  let contentText =
    style([
      marginTop(px(-61)),
      paddingLeft(px(33)),
      paddingRight(px(11)),
      color(hex(Theme.Colors.glazedGreyText)),
      opacity(0.8),
      fontWeight(normal),
      lineHeight(px(24)),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <section>
    <Heading level=Heading.H2 className=Styles.headerText>
      {"// about us" |> ReasonReact.string}
    </Heading>
    <div className=Styles.contentText>
      {"Every team member is highly experienced (8y avg), strives for excellency and has access to the colossal combined knowledge of the whole team. We act as (an extension of) your development team, in very flexible team sizes, and adapting to your processes and with a tight feedback loop."
       |> ReasonReact.string}
    </div>
    <HTMLText tag=HTMLText.H2 className=Styles.htmlTag>
      {"It's your code, ready to hand off or build a team around at any time, but we care for it as it were ours."
       |> ReasonReact.string}
    </HTMLText>
  </section>;
};

let default = make;