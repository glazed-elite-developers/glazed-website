open React;
open Utils.React;

module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      position(`relative),
      height(pct(100.)),
      backgroundColor(hex(Theme.Colors.white)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);
  let header =
    style([position(`fixed), top(`zero), right(`zero), left(`zero)]);
  let sayHelloButton = useDarkNavBarLinks =>
    style([
      display(`none),
      padding2(~v=`rem(0.875), ~h=`rem(1.75)),
      color(
        hex(
          useDarkNavBarLinks
            ? Theme.Colors.darkGreyDarker : Theme.Colors.almostWhite,
        ),
      ),
      fontSize(`rem(0.75)),
      fontFamily(Theme.Fonts.heading),
      pointerEvents(`auto),
      media(Theme.Breakpoints.tabletLandscape, [display(`block)]),
    ]);
  let link = style([textDecoration(`none)]);
};

[@react.component]
let make =
    (~children, ~className=?, ~useDarkNavBarLinks=false, ~currentPageIndex=0) => {
  open Webapi.Url;
  let openedModalRef = useRef(None);
  let modalsAPI = ModalsController.useContextAPI();
  let url = ReasonReactRouter.useUrl();
  let selectedModal =
    url.search |> URLSearchParams.make |> URLSearchParams.get("modal");
  Js.log(url);
  let openSayHelloModal =
    useCallback0(() => {ReasonReactRouter.push("/?modal=say-hello")});

  useEffect1(
    () => {
      // Close other developer modals if any are open.
      switch (Ref.current(openedModalRef)) {
      | None => ()
      | Some(modal) => modalsAPI.closeModal(modal)
      };

      switch (selectedModal) {
      | Some("say-hello") =>
        let modal =
          modalsAPI.openModal((~id as modalId, ~onClose) =>
            <SayHelloModal modalId onClose />
          );
        Ref.setCurrent(openedModalRef, Some(modal));
      | _ => ()
      };
      ();
      None;
    },
    [|selectedModal|],
  );

  <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
    children
    <Header
      className=Styles.header
      useDarkNavBarLinks
      currentPageIndex
      componentAtTheRight={
        <Gatsby.Link
          _to="/?modal=say-hello" className=Styles.link onClick=openSayHelloModal>
          <Button
            _type=Button.Secondary
            className={Styles.sayHelloButton(useDarkNavBarLinks)}>
            {React.string("> say hello")}
          </Button>
        </Gatsby.Link>
      }
    />
    <MobileFooter currentPageIndex />
  </div>;
};

let default = make;