let str = React.string;

module Styles = {
  open Css;

  let page = style([
    padding(`zero)
  ])

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
      alignSelf(`flexEnd),
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

  let listProjects =
    style([
      width(`percent(100.0)),
      backgroundColor(hex(Theme.Colors.glazedBlueDarker)),
      Css.float(`right),
      lineHeight(px(30)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);

  let row = style([flexDirection(row), color(white), display(`flex)]);

  let rowLeft = style([paddingLeft(px(15)), color(hex("FEFFFE"))]);

  let rowRight = style([paddingLeft(px(15))]);

};

module LineProjectElement = {
  [@react.component]
  let make = (~children) => {
    <div className=Styles.row>
      <div className=Styles.rowLeft> {"<li>" |> ReasonReact.string} </div>
      <div className=Styles.rowRight> children </div>
    </div>;
  };
};

module ListProjects = {
  [@react.component]
  let make = () => {
    <div className=Styles.listProjects>
      <div> {"Our kind of projects:" |> ReasonReact.string} </div>
      <LineProjectElement>
        {"Technically complex" |> ReasonReact.string}
      </LineProjectElement>
      <LineProjectElement>
        {"Highly customised and detailed" |> ReasonReact.string}
      </LineProjectElement>
      <LineProjectElement>
        {"Innovative and using recent technologies" |> ReasonReact.string}
      </LineProjectElement>
      <LineProjectElement>
        {"Critically impact on businesses or people's lives" |> ReasonReact.string}
      </LineProjectElement>
      <LineProjectElement>
        {"Scalable prototypes" |> ReasonReact.string}
      </LineProjectElement>
    </div>;
  };
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <PageContent className=Styles.page>
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
    <ListProjects />
  </PageContent>;
};

let default = make;