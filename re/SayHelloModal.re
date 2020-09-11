open React;

[@bs.module "static/images/icon_back_arrow.svg"] external backArrowIcon: SVG.asset = "default";
[@bs.module "static/images/logo-glazed-small.svg"] external glazedMapPin: SVG.asset = "default";

// Social icons.
[@bs.module "static/images/icon_twitter.svg"] external twitterIcon: SVG.asset = "default";
[@bs.module "static/images/icon_facebook.svg"] external facebookIcon: SVG.asset = "default";
[@bs.module "static/images/icon_linkedin.svg"] external linkedInIcon: SVG.asset = "default";
[@bs.module "static/images/icon_github.svg"] external githubIcon: SVG.asset = "default";

let emailSubject = "Glazed Mail";

module Styles = {
  open Css;
  open Theme;

  let wrapper = style([backgroundColor(hex(Colors.almostAlmostWhite))]);
  let contentWrapper = style([alignItems(`stretch)]);
  let content =
    style([display(`flex), flexDirection(`column), flex3(~grow=1., ~shrink=0., ~basis=`auto)]);
  let header = style([position(`absolute), top(`zero), right(`zero), left(`zero)]);
  let closeButtonWrapper =
    style([
      display(`none),
      media(Breakpoints.tabletLandscape, [display(`flex), pointerEvents(`auto)]),
    ]);
  let closeButton =
    style([
      opacity(0.3),
      padding(`zero),
      Css.SVG.fill(hex(Colors.darkGrey)),
      Css.SVG.stroke(hex(Colors.darkGrey)),
    ]);
  let contacts =
    style([
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=1., ~basis=`auto),
      media(
        Breakpoints.tabletLandscape,
        [flexDirection(`row), paddingTop(Header.Styles.Variables.height)],
      ),
    ]);
  let map =
    style([
      position(`relative),
      display(`flex),
      flex3(~grow=0., ~shrink=0., ~basis=rem(12.5)),
      backgroundColor(hex("dddddd")),
      media(
        Breakpoints.tabletLandscape,
        [
          flex3(~grow=1., ~shrink=1., ~basis=rem(0.000000001)),
          paddingTop(Header.Styles.Variables.height),
        ],
      ),
    ]);
  let mapImage =
    style([position(`absolute), top(`zero), right(`zero), bottom(`zero), left(`zero)]);
  let mapPin =
    style([
      position(`absolute),
      bottom(rem(5.)),
      left(pct(23.)),
      height(px(30)),
      media(
        Breakpoints.tabletLandscape,
        [bottom(pct(30.)), left(pct(51.)), height(px(50))],
      ),
    ]);
  let form =
    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      padding3(~top=rem(2.8125), ~bottom=rem(5.625), ~h=rem(1.25)),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`center),
          padding4(~top=rem(3.75), ~left=rem(5.), ~bottom=rem(3.75), ~right=rem(3.75)),
          flex3(~grow=0., ~shrink=1., ~basis=pct(50.)),
        ],
      ),
      media(Breakpoints.desktop, [flex3(~grow=0., ~shrink=1., ~basis=pct(40.))]),
    ]);
  let heading =
    style([
      fontSize(`rem(1.125)),
      color(hex(Colors.darkGreyDarker)),
      opacity(0.9),
      before([contentRule(`text("// "))]),
      media(Breakpoints.tabletLandscape, [fontSize(`rem(2.)), before([display(`none)])]),
    ]);
  let hidden =
    style([
      opacity(0.),
      visibility(`hidden),
      transitions([
        Transition.shorthand(~duration=0, ~delay=500, "visibility"),
        Transition.shorthand(~duration=500, "opacity"),
      ]),
    ]);
  let visible =
    style([
      visibility(`visible),
      transitions([Transition.shorthand(~duration=100, "opacity")]),
    ]);
  let formMessage =
    merge([
      style([
        display(`inline),
        padding3(~top=rem(0.3125), ~bottom=rem(0.625), ~h=`zero),
        fontSize(rem(0.75)),
        lineHeight(`abs(2.)),
        color(hex(Colors.darkGrey)),
        opacity(0.6),
        media(
          Breakpoints.tabletLandscape,
          [
            display(`flex),
            flexDirection(`column),
            padding3(~top=rem(1.5625), ~bottom=rem(2.8126), ~h=`zero),
            fontSize(rem(0.875)),
            opacity(1.),
          ],
        ),
      ]),
      visible,
    ]);
  let formMessageHidden =
    merge([formMessage, hidden, style([media(Breakpoints.tabletLandscape, [opacity(0.)])])]);
  let fillFormMessage = style([display(`inline), paddingRight(rem(0.3125))]);
  let sendEmailParagraph = style([display(`inline), color(hex(Colors.grey))]);
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
  let socialIconLink = style([display(`flex), margin(rem(0.9375))]);
  let socialIcon = style([opacity(0.4), Css.SVG.fill(hex(Theme.Colors.darkGrey))]);
  let addressDetails =
    style([
      position(`absolute),
      top(rem(1.25)),
      right(rem(1.25)),
      width(rem(12.875)),
      height(rem(12.875)),
      padding4(~top=rem(1.5625), ~left=rem(1.25), ~bottom=rem(1.5625), ~right=rem(2.5)),
      backgroundColor(hex(Colors.white)),
      fontSize(rem(0.75)),
      fontFamily(`custom(Fonts.heading)),
      lineHeight(`abs(1.75)),
      media(
        Breakpoints.tabletLandscape,
        [
          top(rem(3.125)),
          right(rem(3.125)),
          width(rem(18.125)),
          height(rem(18.125)),
          padding4(~top=rem(3.125), ~left=rem(2.5), ~bottom=rem(3.4375), ~right=rem(2.5)),
          fontSize(rem(0.84375)),
        ],
      ),
    ]);
  let address = style([whiteSpace(`preLine), color(hex(Colors.darkGrey))]);
  let postalCode =
    style([
      padding3(~top=rem(1.5625), ~bottom=rem(0.9375), ~h=`zero),
      color(hex(Colors.grey)),
      media(
        Breakpoints.tabletLandscape,
        [padding3(~top=rem(1.875), ~bottom=rem(2.5), ~h=`zero)],
      ),
    ]);
  let openInMapsLink = merge([link, style([fontSize(rem(0.75))])]);
  let contactForm =
    merge([visible, style([media(Breakpoints.desktop, [maxWidth(rem(28.125))])])]);
  let mobileCloseButton =
    style([
      padding(rem(1.25)),
      background(`none),
      color(hex(Colors.almostWhite)),
      fontFamily(`custom(Theme.Fonts.heading)),
      fontSize(rem(0.625)),
    ]);
};

let backgroundImageQuery = [%raw
  {|Gatsby.graphql`
    query {
      map_mobile: file(relativePath: { eq: "map_mobile.png" }) {
        childImageSharp {
          fluid(maxWidth: 1024) {
            ...GatsbyImageSharpFluid
          }
        }
      }
      map_desktop: file(relativePath: { eq: "map.png" }) {
        childImageSharp {
          fluid(maxWidth: 2000) {
            ...GatsbyImageSharpFluid
          }
        }
      }
    }
  `|}
];

module CloseButton = {
  [@react.component]
  let make = (~backToUrl, ~close) => {
    <Gatsby.Link className=Styles.closeButtonWrapper _to=backToUrl onClick=close>
      <Button className=Styles.closeButton> <SVG asset=backArrowIcon height="12" /> </Button>
    </Gatsby.Link>;
  };
};

[@react.component]
let make = (~modalId, ~onClose, ~_in=true, ~onExited=() => ()) => {
  open Webapi.Url;
  let location: Routing.location = Routing.useLocation();
  let backToUrl =
    switch (location.search |> URLSearchParams.make |> URLSearchParams.get("backTo")) {
    | None => "/"
    | Some(path) => path
    };
  let onExited =
    useCallback3(
      () => {
        onExited();
        switch (location.search |> URLSearchParams.make |> URLSearchParams.get("modal")) {
        | Some("say-hello") =>
          Routing.navigate(backToUrl, ~state={"preventDefaultScrollBehavior": true})
        | _ => ()
        };
      },
      (onExited, backToUrl, location),
    );
  let handleCloseButtonClick =
    useCallback1(
      event => {
        ReactEvent.Synthetic.preventDefault(event);
        onClose();
      },
      [|onClose|],
    );
  let onNavBarLinkClick = useCallback0((_event, link) => {Routing.navigate(link)});
  let (submissionStatus, setSubmissionStatus) = useState(() => ContactForm.Pristine);
  let onSubmit =
    useCallback1(
      (values: FormValidations.values(string)) => {
        setSubmissionStatus(_status => ContactForm.Pending);
        let valuesArray = FormValidations.Values.toArray(values);
        let payload =
          valuesArray
          ->Belt.List.fromArray
          ->Belt.List.add(("subject", emailSubject))
          ->Belt.List.map(((key, value)) => (key, Js.Json.string(value)))
          ->Js.Dict.fromList;
        let _promise =
          Js.Promise.(
            Fetch.fetchWithInit(
              "/.netlify/functions/sendEmail",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
                (),
              ),
            )
            |> then_(response =>
                 if (Fetch.Response.status(response) < 200
                     || Fetch.Response.status(response) >= 300) {
                   reject(Js.Exn.raiseError(Fetch.Response.statusText(response)));
                 } else {
                   resolve(response);
                 }
               )
            |> then_(Fetch.Response.json)
            |> then_(_response => {resolve(setSubmissionStatus(_status => Success))})
            |> catch(_error => {resolve(setSubmissionStatus(_status => Failed(Unexpected)))})
          );
        ();
      },
      [|setSubmissionStatus|],
    );
  let onChange =
    useCallback2(
      (_values, _eventMetadata) => {
        switch (submissionStatus) {
        | ContactForm.Failed(_) => setSubmissionStatus(_status => ContactForm.Pristine)
        | _ => ()
        }
      },
      (submissionStatus, setSubmissionStatus),
    );
  let (formMessageClassName, formClassName, headingMessage) =
    submissionStatus === Success
      ? (
        Styles.formMessageHidden,
        Css.merge([Styles.contactForm, Styles.hidden]),
        "we'll get in touch soon!",
      )
      : (Styles.formMessage, Styles.contactForm, "say hello");
  let queryResult = Gatsby.useStaticQuery(backgroundImageQuery);
  let fluidMapImage =
    Gatsby.getResponsiveImageFluid(
      queryResult,
      [|("map_mobile", None), ("map_desktop", Some("(min-width: 1024px)"))|],
    );

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
          <Gatsby.BackgroundImage
            className=Styles.mapImage
            fluid=fluidMapImage
            style={ReactDOMRe.Style.make(~position="absolute", ())}
          />
          <SVG className=Styles.mapPin asset=glazedMapPin />
          <div className=Styles.addressDetails>
            <p className=Styles.address>
              {React.string({j|Rua Mouzinho de Albuquerque\n nº 744, 3º andar|j})}
            </p>
            <p className=Styles.postalCode> {React.string("4450-203  Matosinhos, PT")} </p>
            <a
              href="https://goo.gl/maps/V6Q8fQyzHStX6wGx7"
              className=Styles.openInMapsLink
              target="_blank"
              rel="nofollow">
              {React.string("> open in google maps")}
            </a>
          </div>
        </div>
        <div className=Styles.form>
          <div className=Styles.socialNetworks>
            <a
              href="https://twitter.com/glazedSolutions"
              className=Styles.socialIconLink
              target="_blank"
              rel="nofollow">
              <SVG className=Styles.socialIcon asset=twitterIcon height="14" />
            </a>
            <a
              href="https://www.facebook.com/glazedEliteDevelopers/"
              className=Styles.socialIconLink
              target="_blank"
              rel="nofollow">
              <SVG className=Styles.socialIcon asset=facebookIcon height="14" />
            </a>
            <a
              href="https://www.linkedin.com/company/glazed-solutions/"
              className=Styles.socialIconLink
              target="_blank"
              rel="nofollow">
              <SVG className=Styles.socialIcon asset=linkedInIcon height="14" />
            </a>
            <a
              href="https://github.com/glazed-elite-developers"
              className=Styles.socialIconLink
              target="_blank"
              rel="nofollow">
              <SVG className=Styles.socialIcon asset=githubIcon height="14" />
            </a>
          </div>
          <Heading level=Heading.H1 className=Styles.heading>
            {React.string(headingMessage)}
          </Heading>
          <div className=formMessageClassName>
            <p className=Styles.fillFormMessage>
              {React.string("Fill the form, or, if you prefer,")}
            </p>
            <p className=Styles.sendEmailParagraph>
              {React.string("<a>")}
              <a href="mailto:info@glazedsolutions.com" className=Styles.link>
                {React.string("send us an email")}
              </a>
              {React.string("</a>")}
            </p>
          </div>
          <ContactForm className=formClassName onSubmit onChange submissionStatus />
        </div>
      </div>
    </ScrollContainer>
    <Header
      className=Styles.header
      useDarkNavBarLinks=true
      componentAtTheRight={<CloseButton backToUrl close=handleCloseButtonClick />}
      onNavBarLinkClick
    />
    <MobileFooter
      componentAtTheRight={
        <Gatsby.Link _to=backToUrl onClick=handleCloseButtonClick>
          <Button className=Styles.mobileCloseButton> {React.string("< back team")} </Button>
        </Gatsby.Link>
      }
    />
  </BaseModal>;
};

let default = make;
