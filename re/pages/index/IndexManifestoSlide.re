type manifestoContentType = {
  title: string,
  content: string,
};
let manifestoContent = [|
  {
    title: "love their work",
    content: "They love talking about technology, so they know where it is at and where it is going, and they communicate programming challenges better. They have a comprehensive toolbox, and know there are no silver bullets. And that's why they pick the right tools for specific projects.",
  },
  {
    title: "are great people",
    content: "They care about who they work with, and about areas outside their speciality, understanding other's needs and limitations. They anticipate problems and propose solutions. And that's why it takes less time to ship a great product with them.",
  },
  {
    title: "build great code",
    content: "Great code is simple: it is the shortest path to a solution. Because it doesn't try to solve the future, it is more adaptable to the unpredictable. Because it is easily understood, it is easy to improve upon. And that's why it takes them less time to add new features.",
  },
|];

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      padding3(~top=rem(4.1875), ~h=rem(2.5), ~bottom=rem(6.)),
      transform(`translateZ(`zero)),
      media(
        Breakpoints.tabletLandscape,
        [padding3(~top=rem(13.5625), ~h=rem(4.75), ~bottom=`zero)],
      ),
    ]);
  let section = style([position(`relative)]);
  let contentWrapper =
    style([
      display(`flex),
      flexDirection(`column),
      media(
        Breakpoints.tabletLandscape,
        [flexDirection(`row), flex3(~grow=1., ~shrink=1., ~basis=`auto)],
      ),
    ]);
  let funPart =
    style([
      display(`flex),
      height(rem(5.5)),
      position(`absolute),
      right(`zero),
      bottom(`zero),
      left(rem(2.5)),
      backgroundColor(hex(Colors.glazedBabyBlueText)),
      media(
        Breakpoints.tabletLandscape,
        [
          position(`static),
          height(`auto),
          margin4(~top=`zero, ~right=rem(-4.75), ~bottom=`zero, ~left=`zero),
          flex3(~grow=0., ~shrink=1., ~basis=pct(40.)),
        ],
      ),
    ]);
  let image =
    style([flex3(~grow=1., ~shrink=1., ~basis=rem(0.0000001)), display(`flex), opacity(0.3)]);
  let content =
    style([
      media(
        Breakpoints.tabletPortrait,
        [display(`flex), flex3(~grow=1., ~shrink=1., ~basis=`auto)],
      ),
    ]);
  let displayTitle =
    style([
      after([
        contentRule(`text("")),
        position(`absolute),
        top(rem(-2.0)),
        left(rem(-1.25)),
        width(rem(8.125)),
        height(rem(8.125)),
        border(px(1), `solid, rgba(159, 168, 179, 0.1)),
      ]),
      paddingBottom(rem(1.25)),
      media(
        Breakpoints.tabletPortrait,
        [after([display(`none)]), paddingLeft(rem(1.25)), paddingBottom(rem(6.25))],
      ),
    ]);
  let verticalLine = [
    contentRule(`text("")),
    position(`fixed),
    top(`zero),
    bottom(`zero),
    marginLeft(rem(-1.25)),
    border(px(1), `solid, rgba(159, 168, 179, 0.1)),
  ];
  let block =
    style([
      not_(":last-child", [marginBottom(rem(1.25))]),
      media(
        Breakpoints.tabletPortrait,
        [
          position(`relative),
          flex3(~grow=1., ~shrink=1., ~basis=pct(33.)),
          padding2(~v=rem(0.), ~h=rem(1.25)),
          before(verticalLine),
          display(`flex),
          flexDirection(`column),
          lastChild([
            after([
              contentRule(`text("")),
              position(`fixed),
              top(`zero),
              bottom(`zero),
              marginLeft(rem(1.25)),
              alignSelf(`flexEnd),
              border(px(1), `solid, rgba(159, 168, 179, 0.1)),
            ]),
          ]),
        ],
      ),
    ]);
  let pre =
    style([
      display(`none),
      color(hex("2560F2")),
      fontSize(rem(0.75)),
      paddingBottom(rem(1.125)),
      media(Breakpoints.tabletPortrait, [display(`block)]),
    ]);
  let title =
    style([
      paddingBottom(rem(0.625)),
      color(hex(Colors.darkGreyDarker)),
      lineHeight(rem(1.5)),
      media(
        Breakpoints.tabletPortrait,
        [color(hex(Colors.grey)), paddingBottom(rem(1.125))],
      ),
    ]);
  let strong =
    style([media(Breakpoints.tabletPortrait, [color(hex(Colors.darkGreyDarker))])]);
  let paragraph =
    style([
      fontWeight(`num(400)),
      fontSize(rem(0.75)),
      letterSpacing(rem(-0.025)),
      lineHeight(rem(1.5)),
      color(hex(Colors.darkGrey)),
      opacity(0.8),
      media(Breakpoints.tabletPortrait, [fontSize(rem(0.875)), lineHeight(rem(2.125))]),
    ]);
};

[@react.component]
let make =
  React.memo((~innerRef=?, ~id=?, ~onResize) => {
    <FullPageSlide className=Styles.wrapper ?id ?innerRef onResize>
      <Heading level=Heading.H2 className=Styles.displayTitle>
        {"// manifesto" |> ReasonReact.string}
      </Heading>
      <div className=Styles.contentWrapper>
        <div className=Styles.content>
          {Array.mapi(
             (index, element) => {
               let index = index + 1;

               <div className=Styles.block key={Belt.Int.toString(index)}>
                 <Heading level=Heading.H5 className=Styles.pre>
                   {{j|// 0$index|j} |> ReasonReact.string}
                 </Heading>
                 <Heading level=Heading.H3 className=Styles.title>
                   {"Great developers " |> ReasonReact.string}
                   <strong className=Styles.strong> {element.title |> ReasonReact.string} </strong>
                 </Heading>
                 <p className=Styles.paragraph> {element.content |> ReasonReact.string} </p>
               </div>;
             },
             manifestoContent,
           )
           |> ReasonReact.array}
        </div>
        <div className=Styles.funPart>
          <DeveloperBackgroundImage className=Styles.image developerPhotoKey="overlay" />
        </div>
      </div>
    </FullPageSlide>
  });

let default = make;
