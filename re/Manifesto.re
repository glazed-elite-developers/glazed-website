type manifestoContentType = {title: string, content: string}
let manifestoContent = [|
  {
    title: "love their work",
    content: "They love talking about technology, so they know where it is at and where it is going, and they communicate programming challenges better. They have a comprehensive toolbox, and know there are no silver bullets. And that's why they pick the right tools for specific projects."
  },
  {
    title: "are great people",
    content: "They care about who they work with, and about areas outside their speciality, understanding other's needs and limitations. They anticipate problems and propose solutions. And that's why it takes less time to ship a great product with them."
  },
  {
    title: "built great code",
    content: "Great code is simple: it is the shortest path to a solution. Because it doesn't try to solve the future, it is more adaptable to the unpredictable. Because it is easily understood, it is easy to improve upon. And that's why it takes them less time to add new features."
  }
|];

module Styles = {
  open Css;

  let section = style([
    position(`relative)
  ]);

  let content = style([
    media(
      Theme.Breakpoints.tabletLandscape,
      [display(`flex)]
    )
  ]);

  let displayTitle = style([
    after([
      contentRule(""),
      position(`absolute),
      top(rem(-2.0)),
      left(rem(-1.0)),
      width(rem(8.125)),
      height(rem(8.125)),
      border(px(1), `solid, rgba(159, 168, 179, 0.1))
    ]),
    media(
      Theme.Breakpoints.tabletLandscape,
      [
        after([
          display(`none)
        ]),
        paddingLeft(rem(1.25)),
        paddingBottom(rem(6.25))
      ],
    )
  ]);

  let verticalLine = [
    contentRule(""),
    position(`fixed),
    top(`zero),
    bottom(`zero),
    marginLeft(rem(-1.25)),
    border(px(1), `solid, rgba(159, 168, 179, 0.1))
  ];

  let block = style([
    not_(":last-child", [marginBottom(rem(1.25))]),
    media(
      Theme.Breakpoints.tabletLandscape, [
        position(`relative),
        flex3(~grow=1., ~shrink=0., ~basis=pct(33.)),
        padding2(~v=rem(0.), ~h=rem(1.25)),
        before(verticalLine),
        lastChild([after([
          contentRule(""),
          position(`fixed),
          top(`zero),
          bottom(`zero),
          marginLeft(rem(15.75)),
          border(px(1), `solid, rgba(159, 168, 179, 0.1))
        ])])
      ]
    )
  ]);

  let pre = style([
    display(`none),
    color(hex("2560F2")),
    fontSize(rem(0.75)),
    paddingBottom(rem(1.125)),
    media(
      Theme.Breakpoints.tabletLandscape,
      [display(`block)],
    ),
  ]);

  let title = style([
    color(hex(Theme.Colors.darkGreyDarker)),
    lineHeight(rem(1.5)),
    media(
      Theme.Breakpoints.tabletLandscape,
      [
        color(hex(Theme.Colors.grey)),
        paddingBottom(rem(1.125))
      ],
    )
  ])

  let strong = style([
    media(
      Theme.Breakpoints.tabletLandscape,
      [color(hex(Theme.Colors.darkGreyDarker))],
    )
  ])

  let paragraph = style([
    fontWeight(`num(400)),
    fontSize(rem(0.875)),
    letterSpacing(rem(-0.025)),
    lineHeight(rem(1.5)),
    color(hex(Theme.Colors.darkGrey)),
    media(
      Theme.Breakpoints.tabletLandscape,
      [
        lineHeight(rem(2.125))
      ]
    )
  ])
};

[@react.component]
let make = () => {
  <section>
    <Heading level=Heading.H2 className=Styles.displayTitle>
      {"// manifesto" |> ReasonReact.string}
    </Heading>
    <div className=Styles.content>
    (
      Array.mapi((i, el) => {
        let index = i + 1;

        <div className=Styles.block key=(string_of_int(index))>
          <Heading level=Heading.H5 className=Styles.pre>
            {{j|// 0$index|j} |> ReasonReact.string }
          </Heading>
          <Heading level=Heading.H3 className=Styles.title>
            {"Great developers " |> ReasonReact.string}
            <strong className=Styles.strong>
              {el.title |>  ReasonReact.string}
            </strong>
          </Heading>
          <p className=Styles.paragraph>
            {el.content |> ReasonReact.string}
          </p>
        </div>
      }, manifestoContent) |> ReasonReact.array
    )
    </div>
  </section>;
};

let default = make;