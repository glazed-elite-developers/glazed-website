module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`grid),
      gridTemplateRows([`auto, `auto, `fr(1.)]),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      padding4(
        ~top=rem(4.1875),
        ~right=`zero,
        ~left=rem(1.25),
        ~bottom=`zero,
      ),
      overflow(`hidden),
      media(
        Breakpoints.tabletLandscape,
        [
          gridTemplateRows([`auto, `fr(1.)]),
          gridTemplateColumns([`fr(1.), `fr(1.)]),
          padding4(
            ~top=rem(6.25),
            ~right=`zero,
            ~bottom=`zero,
            ~left=rem(4.75),
          ),
        ],
      ),
      media(
        Breakpoints.desktop,
        [gridTemplateColumns([`fr(6.), `fr(4.)])],
      ),
    ]);
  let about =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=0., ~shrink=0., ~basis=`auto),
      media(
        Breakpoints.tabletLandscape,
        [
          gridColumn(1, 3),
          padding4(
            ~top=`zero,
            ~right=rem(4.75),
            ~bottom=rem(4.75),
            ~left=`zero,
          ),
        ],
      ),
      media(Breakpoints.desktop, [gridColumn(1, 2)]),
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
          Breakpoints.tabletLandscape,
          [width(`px(258)), height(`px(258))],
        ),
      ]),
      media(
        Breakpoints.tabletLandscape,
        [
          padding4(
            ~top=`rem(5.625),
            ~left=`rem(0.9375),
            ~bottom=`rem(1.875),
            ~right=`zero,
          ),
          width(`auto),
          color(hex(Colors.darkGrey)),
          fontSize(`rem(2.)),
        ],
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
      color(hex(Colors.glazedGreyText)),
      media(
        Breakpoints.tabletLandscape,
        [display(`block), fontSize(`rem(1.5))],
      ),
    ]);
  let contentTextLine =
    style([
      display(`inline),
      media(Breakpoints.tabletLandscape, [display(`block)]),
    ]);
  let dimmedOnDesktop =
    style([media(Breakpoints.tabletLandscape, [opacity(0.6)])]);
  let htmlTextWrapper =
    style([
      media(
        Breakpoints.tabletLandscape,
        [
          padding4(
            ~top=rem(4.75),
            ~right=rem(2.5),
            ~bottom=`zero,
            ~left=`zero,
          ),
        ],
      ),
      media(
        Breakpoints.desktop,
        [
          gridColumn(1, 2),
          padding4(
            ~top=rem(4.75),
            ~right=rem(4.75),
            ~bottom=`zero,
            ~left=rem(2.5),
          ),
          maxWidth(rem(47.5)),
        ],
      ),
    ]);
  let htmlTag =
    style([
      padding4(
        ~top=`rem(0.625),
        ~left=`rem(0.9375),
        ~bottom=`rem(1.25),
        ~right=`rem(0.9375),
      ),
      color(hex(Colors.glazedBabyBlueText)),
      fontSize(rem(1.125)),
      lineHeight(`abs(1.5)),
      width(`rem(21.875)),
      textAlign(`left),
      alignSelf(`flexEnd),
      media(
        Breakpoints.tabletLandscape,
        [width(`auto), fontSize(rem(2.125)), padding(`zero)],
      ),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = (~innerRef=?) => {
  <FullPageSlide className=Styles.wrapper ?innerRef>
    <div className=Styles.about>
      <Heading level=Heading.H1 className=Styles.heading>
        {"// about us" |> ReasonReact.string}
      </Heading>
      <div className=Styles.contentText>
        <p className=Styles.contentTextLine>
          {"Every team member is highly experienced (8y avg), strives for excellency and has access to the colossal combined knowledge of the whole team. "
           |> ReasonReact.string}
        </p>
        <p
          className={Css.merge([
            Styles.contentTextLine,
            Styles.dimmedOnDesktop,
          ])}>
          {"We act as (an extension of) your development team, in very flexible team sizes, and adapting to your processes and with a tight feedback loop."
           |> React.string}
        </p>
      </div>
    </div>
    <div className=Styles.htmlTextWrapper>
      <HTMLText tag=HTMLText.H2 className=Styles.htmlTag>
        {"It's your code, ready to hand off or build a team around at any time, but we care for it as it were ours."
         |> ReasonReact.string}
      </HTMLText>
    </div>
    <AboutSlideProjectList />
  </FullPageSlide>;
};

let default = make;