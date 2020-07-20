[@bs.module "static/images/logo-glazed-outline.svg"] external logoOutline: SVG.asset = "default";

open React;

module Styles = {
  open Css;
  open Theme;

  let wrapper = style([backgroundColor(hex(Colors.glazedBlueDark))]);
  let contentWrapper = style([alignItems(`stretch)]);
  let content =
    style([
      position(`relative),
      padding4(~top=rem(4.1875), ~bottom=rem(4.1875), ~left=rem(1.25), ~right=rem(1.25)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`flexEnd),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`flexStart),
          padding4(~top=rem(6.25), ~bottom=rem(6.25), ~left=rem(4.75), ~right=rem(2.5)),
        ],
      ),
    ]);
  let backgroundImage =
    style([
      position(`absolute),
      top(`zero),
      right(`zero),
      bottom(`zero),
      width(pct(100.)),
      maxWidth(pct(90.)),
      zIndex(0),
      media(Theme.Breakpoints.tabletLandscape, [maxWidth(rem(64.)), left(`unset)]),
    ]);
  let developerBackgroundImage = merge([backgroundImage, style([opacity(0.6)])]);
  let overlayImage = merge([backgroundImage, style([opacity(0.1)])]);
  let logoWrapper =
    style([
      position(`absolute),
      top(`zero),
      left(`zero),
      padding2(~v=rem(1.25), ~h=rem(1.25)),
      media(Theme.Breakpoints.tabletLandscape, [display(`none)]),
    ]);
  let logo = style([height(rem(2.1875))]);
  let closeButtonWrapper =
    style([
      display(`none),
      media(
        Breakpoints.tabletLandscape,
        [display(`flex), position(`absolute), top(`zero), right(`zero)],
      ),
    ]);
  let closeButton =
    style([
      padding(`zero),
      flex3(~grow=1., ~shrink=1., ~basis=`auto),
      width(rem(8.5)),
      height(rem(8.5)),
      backgroundColor(hex(Colors.glazedBlueDarker)),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.625)),
      opacity(0.6),
      color(hex(Colors.white)),
    ]);
  let heading =
    style([
      position(`relative),
      padding4(~top=`rem(1.875), ~left=`rem(0.9375), ~bottom=`rem(5.625), ~right=`zero),
      fontSize(`rem(1.125)),
      color(hex(Colors.almostWhite)),
      before([
        contentRule(""),
        display(`block),
        position(`absolute),
        top(`px(0)),
        left(`px(0)),
        width(px(130)),
        height(px(130)),
        border(px(1), `solid, hex(Colors.glazedBabyBlueDarker)),
        opacity(0.1),
        media(Breakpoints.tabletLandscape, [width(`px(258)), height(`px(258))]),
      ]),
      media(
        Breakpoints.tabletLandscape,
        [
          padding4(~top=`rem(5.625), ~left=`rem(0.9375), ~bottom=`rem(1.875), ~right=`zero),
          width(`auto),
          fontSize(`rem(2.)),
        ],
      ),
    ]);
  let descriptions =
    style([
      display(`flex),
      flexDirection(`column),
      padding4(~left=rem(0.9375), ~right=rem(3.125), ~top=`zero, ~bottom=`zero),
      media(
        Theme.Breakpoints.tabletLandscape,
        [maxWidth(rem(37.5)), flex3(~grow=1., ~shrink=0., ~basis=`auto)],
      ),
    ]);
  let shortDescription =
    style([
      lineHeight(`abs(2.)),
      fontSize(rem(0.875)),
      fontFamily(Theme.Fonts.text),
      color(hex(Colors.almostWhite)),
      paddingBottom(rem(0.625)),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          order(2),
          flex3(~grow=1., ~shrink=0., ~basis=`auto),
          display(`flex),
          alignItems(`center),
          justifyContent(`flexEnd),
          paddingLeft(rem(6.25)),
          fontSize(rem(2.)),
          lineHeight(`abs(1.5)),
        ],
      ),
    ]);
  let description =
    style([
      lineHeight(`abs(2.)),
      fontSize(rem(0.75)),
      color(hex(Colors.white)),
      opacity(0.7),
      media(Theme.Breakpoints.tabletLandscape, [order(1), fontSize(rem(1.5))]),
    ]);
  let skillsAndLinkedIn =
    style([
      display(`flex),
      flexDirection(`rowReverse),
      alignItems(`center),
      justifyContent(`spaceBetween),
      padding4(~top=`rem(1.875), ~left=`rem(0.9375), ~bottom=`rem(1.875), ~right=`zero),
      fontSize(rem(0.625)),
      zIndex(0),
      media(Theme.Breakpoints.tabletLandscape, [padding(`zero)]),
    ]);
  let skills =
    style([
      color(hex(Colors.almostWhite)),
      opacity(0.4),
      fontFamily(Theme.Fonts.heading),
      media(Theme.Breakpoints.tabletLandscape, [display(`none)]),
    ]);
  let desktopSkills =
    style([
      display(`none),
      media(
        Theme.Breakpoints.tabletLandscape,
        [
          display(`block),
          position(`absolute),
          top(pct(50.)),
          right(rem(2.5)),
          minWidth(rem(9.375)),
          transform(translateY(pct(-50.))),
          color(hex(Colors.almostWhite)),
          whiteSpace(`preLine),
          fontSize(rem(1.)),
          lineHeight(`abs(2.)),
          opacity(0.6),
        ],
      ),
    ]);
  let linkedinLink =
    style([
      fontFamily(Theme.Fonts.heading),
      color(hex(Colors.glazedBabyBlue)),
      media(Theme.Breakpoints.tabletLandscape, [fontSize(rem(0.75)), minWidth(rem(9.375))]),
    ]);
  let mobileFooter =
    style([
      position(`absolute),
      bottom(`zero),
      left(`zero),
      right(`zero),
      backgroundColor(hex(Colors.glazedBlueDarkestish)),
      display(`flex),
      alignItems(`center),
      media(Breakpoints.tabletLandscape, [display(`none)]),
    ]);
  let mobileCloseButton =
    style([
      padding(rem(1.25)),
      background(`none),
      color(hex(Colors.almostWhite)),
      fontFamily(Theme.Fonts.heading),
      fontSize(rem(0.625)),
    ]);
};

let teamSlideLink = "/#team";

module CloseButton = {
  [@react.component]
  let make = (~close) => {
    <Gatsby.Link className=Styles.closeButtonWrapper _to=teamSlideLink onClick=close>
      <Button className=Styles.closeButton> {React.string("< back team")} </Button>
    </Gatsby.Link>;
  };
};

module MobileFooter = {
  [@react.component]
  let make = (~close) => {
    <MobileFooterLayout className=Styles.mobileFooter>
      <Gatsby.Link _to=teamSlideLink onClick=close>
        <Button className=Styles.mobileCloseButton> {React.string("< back team")} </Button>
      </Gatsby.Link>
    </MobileFooterLayout>;
  };
};

[@react.component]
let make =
    (
      ~modalId,
      ~onClose,
      ~_in=true,
      ~onExited=() => (),
      ~developer: IndexTeamSlideSquares.developer,
    ) => {
  open Webapi.Url;
  let url = ReasonReactRouter.useUrl();
  let exit =
    useCallback2(
      () => {
        onExited();
        switch (url.search |> URLSearchParams.make |> URLSearchParams.get("modal")) {
        | Some("team") =>
          Routing.push(teamSlideLink, ~state={"preventDefaultScrollBehavior": true})
        | _ => ()
        };
      },
      (onExited, url),
    );
  let handleCloseButtonClick =
    useCallback1(
      event => {
        ReactEvent.Synthetic.preventDefault(event);
        onClose();
      },
      [|onClose|],
    );

  <BaseModal
    modalId
    _in
    onClose
    onExited=exit
    scrollContainerClassName=Styles.wrapper
    contentWrapperClassName=Styles.contentWrapper
    contentClassName=Styles.content>
    <DeveloperBackgroundImage
      developerPhotoKey={developer.key}
      className=Styles.developerBackgroundImage
    />
    <DeveloperBackgroundImage developerPhotoKey="overlay" className=Styles.overlayImage />
    <Heading level=Heading.H1 className=Styles.heading>
      {React.array(
         Array.mapi(
           (index, name) => <div key={Belt.Int.toString(index)}> {React.string(name)} </div>,
           Js.String.split(" ", developer.name),
         ),
       )}
    </Heading>
    <div className=Styles.descriptions>
      <Heading level=Heading.H3 className=Styles.shortDescription>
        {React.string(developer.shortDescription)}
      </Heading>
      <p className=Styles.description> {React.string(developer.description)} </p>
    </div>
    <div className=Styles.skillsAndLinkedIn>
      <a className=Styles.linkedinLink href={developer.linkedIn} rel="nofollow" target="_blank">
        {React.string("> LinkedIn")}
      </a>
      <p className=Styles.skills>
        {React.string(
           "{ "
           ++ Array.fold_left((result, skill) => {j|$(result) $(skill)|j}, "", developer.skills)
           ++ " }",
         )}
      </p>
      <p className=Styles.desktopSkills>
        {React.string(
           "{ \n"
           ++ Array.fold_left(
                (result, skill) => {j|$(result) // $(skill)\n|j},
                "",
                developer.skills,
              )
           ++ " }",
         )}
      </p>
    </div>
    <div className=Styles.logoWrapper> <SVG className=Styles.logo asset=logoOutline /> </div>
    <CloseButton close=handleCloseButtonClick />
    <MobileFooter close=handleCloseButtonClick />
  </BaseModal>;
};

let default = make;
