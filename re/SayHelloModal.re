open React;

[@bs.module "static/images/icon_back_arrow.svg"]
external backArrowIcon: SVG.asset = "default";

// Social icons.
[@bs.module "static/images/icon_twitter.svg"]
external twitterIcon: SVG.asset = "default";
[@bs.module "static/images/icon_facebook.svg"]
external facebookIcon: SVG.asset = "default";
[@bs.module "static/images/icon_linkedin.svg"]
external linkedInIcon: SVG.asset = "default";
[@bs.module "static/images/icon_github.svg"]
external githubIcon: SVG.asset = "default";

module Styles = {
  open Css;
  open Theme;

  let wrapper = style([backgroundColor(hex(Colors.almostAlmostWhite))]);
  let contentWrapper = style([alignItems(`stretch)]);
  let content =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
    ]);
  let header =
    style([position(`absolute), top(`zero), right(`zero), left(`zero)]);
  let closeButtonWrapper =
    style([
      display(`none),
      media(
        Breakpoints.tabletLandscape,
        [display(`flex), pointerEvents(`auto)],
      ),
    ]);
  let closeButton = style([opacity(0.6), padding(`zero)]);
  let contacts =
    style([
      display(`flex),
      flexDirection(`column),
      paddingTop(Header.Styles.Variables.height),
      flex3(~grow=1., ~shrink=1., ~basis=`auto),
      media(Breakpoints.tabletLandscape, [flexDirection(`row)]),
    ]);
  let map =
    style([
      position(`relative),
      display(`flex),
      flex3(~grow=1., ~shrink=1., ~basis=rem(0.000000001)),
      backgroundColor(hex("dddddd")),
    ]);
  let form =
    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`center),
          padding4(
            ~top=rem(3.75),
            ~left=rem(5.),
            ~bottom=rem(3.75),
            ~right=rem(3.75),
          ),
          flex3(~grow=0., ~shrink=1., ~basis=pct(50.)),
        ],
      ),
      media(
        Breakpoints.desktop,
        [flex3(~grow=0., ~shrink=1., ~basis=pct(40.))],
      ),
    ]);
  let heading =
    style([
      fontSize(`rem(1.125)),
      color(hex(Colors.darkGreyDarker)),
      opacity(0.9),
      media(Breakpoints.tabletLandscape, [fontSize(`rem(2.))]),
    ]);
  let formMessage =
    style([
      padding3(~top=rem(1.5625), ~bottom=rem(2.8126), ~h=`zero),
      fontSize(rem(0.875)),
      color(hex(Colors.darkGrey)),
    ]);
  let sendEmailParagraph = style([color(hex(Colors.grey))]);
  let link = style([color(hex(Colors.glazedBlueDarkish))]);
  let socialNetworks =
    style([
      display(`none),
      media(
        Breakpoints.tabletLandscape,
        [
          position(`absolute),
          top(`zero),
          right(rem(4.6875)),
          margin(rem(-0.9375)),
          display(`flex),
        ],
      ),
    ]);
  let socialIcon =
    style([
      margin(rem(0.9375)),
      opacity(0.4),
      Css.SVG.fill(hex(Theme.Colors.darkGrey)),
    ]);
  let addressDetails =
    style([
      position(`absolute),
      top(rem(3.125)),
      right(rem(3.125)),
      width(rem(18.125)),
      height(rem(18.125)),
      padding4(
        ~top=rem(3.125),
        ~left=rem(2.5),
        ~bottom=rem(3.4375),
        ~right=rem(2.5),
      ),
      backgroundColor(hex(Colors.white)),
      fontSize(rem(0.84375)),
      fontFamily(Fonts.heading),
      lineHeight(`abs(1.75)),
    ]);
  let address = style([whiteSpace(`preLine), color(hex(Colors.darkGrey))]);
  let postalCode =
    style([
      padding3(~top=rem(1.875), ~bottom=rem(2.5), ~h=`zero),
      color(hex(Colors.grey)),
    ]);
  let openInMapsLink = merge([link, style([fontSize(rem(0.75))])]);
  let contactForm =
    style([media(Breakpoints.desktop, [maxWidth(rem(28.125))])]);
};

module CloseButton = {
  [@react.component]
  let make = (~backToUrl, ~close) => {
    <Gatsby.Link
      className=Styles.closeButtonWrapper _to=backToUrl onClick=close>
      <Button className=Styles.closeButton>
        <SVG asset=backArrowIcon height="12" />
      </Button>
    </Gatsby.Link>;
  };
};

[@react.component]
let make = (~modalId, ~onClose, ~_in=true, ~onExited=() => ()) => {
  open Webapi.Url;
  let url = ReasonReactRouter.useUrl();
  let backToUrl =
    switch (
      url.search |> URLSearchParams.make |> URLSearchParams.get("backTo")
    ) {
    | None => "/"
    | Some(path) => path
    };
  let close =
    useCallback1(
      event => {
        ReactEvent.Synthetic.preventDefault(event);
        Routing.push(
          backToUrl,
          ~state={"preventDefaultScrollBehavior": true},
        );
      },
      [|backToUrl|],
    );
  let onNavBarLinkClick =
    useCallback0((_event, link) => {Routing.push(link)});

  <BaseModal
    modalId
    onClose
    _in
    onExited
    scrollContainerClassName=Styles.wrapper
    contentWrapperClassName=Styles.contentWrapper
    contentClassName=Styles.content>
    <ScrollContainer>
      <div className=Styles.contacts>
        <div className=Styles.map>
          <div className=Styles.addressDetails>
            <p className=Styles.address>
              {React.string(
                 {j|Rua Mouzinho de Albuquerque\n nº 744, 3º andar|j},
               )}
            </p>
            <p className=Styles.postalCode>
              {React.string("4450-203  Matosinhos, PT")}
            </p>
            <a href="" className=Styles.openInMapsLink>
              {React.string("> open in google maps")}
            </a>
          </div>
        </div>
        <div className=Styles.form>
          <div className=Styles.socialNetworks>
            <SVG className=Styles.socialIcon asset=twitterIcon height="14" />
            <SVG className=Styles.socialIcon asset=facebookIcon height="14" />
            <SVG className=Styles.socialIcon asset=linkedInIcon height="14" />
            <SVG className=Styles.socialIcon asset=githubIcon height="14" />
          </div>
          <Heading level=Heading.H1 className=Styles.heading>
            {React.string("// say hello")}
          </Heading>
          <div className=Styles.formMessage>
            <p> {React.string("Fill the form, or, if you prefer,")} </p>
            <p className=Styles.sendEmailParagraph>
              {React.string("<a>")}
              <a href="mailto:info@glazedsolutions.com" className=Styles.link>
                {React.string("send us an email")}
              </a>
              {React.string("</a>")}
            </p>
          </div>
          <ContactForm className=Styles.contactForm />
        </div>
      </div>
    </ScrollContainer>
    <Header
      className=Styles.header
      useDarkNavBarLinks=true
      componentAtTheRight={<CloseButton backToUrl close />}
      onNavBarLinkClick
    />
  </BaseModal>;
};

let default = make;