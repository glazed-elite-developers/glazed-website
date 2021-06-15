open React;

module Styles = {
  open Css;
  open Theme;


  let fillFormMessage = style([display(`inline), paddingRight(rem(0.3125)), paddingBottom(rem(1.))]);
  let sendEmailParagraph = style([display(`inline), color(hex(Colors.grey)), marginBottom(rem(2.))]);
  let link = style([color(hex(Colors.glazedBlueDarkish))]);

  let content =
    style([
      position(`relative),
      padding4(~top=rem(4.1875), ~bottom=rem(8.1875), ~left=rem(1.25), ~right=rem(1.25)),
      display(`flex),
      flexDirection(`column),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      backgroundColor(hex(Colors.almostAlmostWhite)),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`flexStart),
          padding4(~top=rem(12.25), ~bottom=rem(6.25), ~left=rem(4.75), ~right=rem(2.5)),
        ],
      ),
    ]);
  let heading =
    style([
      position(`relative),
      padding4(~top=`rem(1.875), ~left=`rem(0.9375), ~bottom=`rem(5.625), ~right=`zero),
      fontSize(`rem(4.125)),
      color(hex(Colors.glazedBabyBlueText)),
      before([
        contentRule(`text("")),
        display(`block),
        position(`absolute),
        top(`px(0)),
        left(`px(0)),
        width(px(130)),
        height(px(130)),
        border(px(1), `solid, hex(Colors.glazedBabyBlueDarker)),
        opacity(0.8),
        media(Breakpoints.tabletLandscape, [width(`px(258)), height(`px(258))]),
      ]),
      media(
        Breakpoints.tabletLandscape,
        [
          padding4(~top=`rem(5.625), ~left=`rem(0.9375), ~bottom=`rem(6.875), ~right=`zero),
          width(`auto),
          fontSize(rem(9.)),
          before([
            top(`px(-30)),
          ]),
        ],
      ),
    ]);
  let pageContent =
    style([
      media(
        Breakpoints.tabletLandscape,
        [
          maxWidth(rem(50.))
        ],
      ),
    ]);
};

let emailSubject = "Glazed Application";

[@react.component]
let make = () => {
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

  <Layout>
    <PageLayout className=Styles.content useDarkNavBarLinks=true>
      <Heading level=Heading.H1 className=Styles.heading>
        {React.string("Next")}
      </Heading>
      <div className=Styles.pageContent>
        <p className=Styles.fillFormMessage>
          {React.string("At Glazed we're committed to taking software development to next level. Many of our developers started by doing an internship or developing their thesis at Glazed, and you could be next! We will provide the support you need to help your project bloom.")}
        </p>
        <br/>
        <br/>
        <p className=Styles.fillFormMessage>
          {React.string("Send your application by filling the form below, or, if you prefer,")}
        </p>
        <p className=Styles.sendEmailParagraph>
          {React.string("<a>")}
          <a href="mailto:info@glazedsolutions.com" className=Styles.link>
            {React.string("send us an email")}
          </a>
          {React.string("</a>")}
        </p>
        <br/>
        <br/>
        <ContactForm onSubmit onChange submissionStatus hackyOverride={true} />
      </div>
    </PageLayout>
  </Layout>;
};

let default = make;
