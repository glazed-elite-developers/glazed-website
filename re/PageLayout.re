open React;
open Utils.React;

module Styles = {
  open Css;
  open Theme;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      position(`relative),
      backgroundColor(hex(Colors.white)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
    ]);
  let header = style([position(`fixed), top(`zero), right(`zero), left(`zero), zIndex(1)]);
  let sayHelloButton = useDarkNavBarLinks =>
    style([
      display(`none),
      padding2(~v=`rem(0.875), ~h=`rem(1.75)),
      color(hex(useDarkNavBarLinks ? Colors.darkGreyDarker : Colors.almostWhite)),
      fontSize(`rem(0.75)),
      fontFamily(`custom(Fonts.heading)),
      pointerEvents(`auto),
      media(Breakpoints.tabletLandscape, [display(`block)]),
    ]);
  let mobileCloseButtonWrapper = style([flex3(~grow=0., ~shrink=0., ~basis=`auto)]);
  let mobileCloseButton =
    style([
      padding(rem(0.625)),
      margin2(~v=`zero, ~h=rem(0.9375)),
      background(`none),
      color(hex(Colors.almostWhite)),
      fontFamily(`custom(Fonts.heading)),
      fontSize(rem(0.625)),
    ]);
};

[@react.component]
let make =
  memo(
    (
      ~children,
      ~className=?,
      ~headerClassName=?,
      ~headerStyle=?,
      ~useDarkNavBarLinks=false,
      ~currentPageIndex=0,
      ~onHeaderResize=?,
    ) => {
    open Webapi.Url;
    let (sayHelloModalUrl, openSayHelloModal) = OpenSayHelloModalHook.useOpenSayHelloModal();
    let openedModalRef = useRef(None);
    let modalsAPI = ModalsController.useContextAPI();
    let url = ReasonReactRouter.useUrl();
    let selectedModal = url.search |> URLSearchParams.make |> URLSearchParams.get("modal");
    // Need to memoize this to avoid unnecessary header rerenders.
    let headerComponentAtTheRight =
      useMemo3(
        () => {
          <Gatsby.Link _to=sayHelloModalUrl onClick=openSayHelloModal>
            <Button _type=Button.Secondary className={Styles.sayHelloButton(useDarkNavBarLinks)}>
              {React.string("> say hello")}
            </Button>
          </Gatsby.Link>
        },
        (sayHelloModalUrl, openSayHelloModal, useDarkNavBarLinks),
      );

    useEffect1(
      () => {
        // Close other developer modals if any are open.
        switch (openedModalRef.current) {
        | None => ()
        | Some(modal) => modalsAPI.closeModal(modal)
        };

        switch (selectedModal) {
        | Some("say-hello") =>
          let modal =
            modalsAPI.openModal((~id as modalId, ~onClose) => <SayHelloModal modalId onClose />);
          openedModalRef.current = Some(modal);
        | _ => ()
        };
        ();
        None;
      },
      [|selectedModal|],
    );

    <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
      <Header
        className=?{combineClassNames([Some(Styles.header), headerClassName])}
        style=?headerStyle
        useDarkNavBarLinks
        currentPageIndex
        onResize=?onHeaderResize
        componentAtTheRight=headerComponentAtTheRight
      />
      children
      <MobileFooter
        currentPageIndex
        componentAtTheRight={
          <Gatsby.Link
            _to=sayHelloModalUrl
            onClick=openSayHelloModal
            className=Styles.mobileCloseButtonWrapper>
            <Button _type=Button.Secondary className=Styles.mobileCloseButton>
              {React.string("> say hello")}
            </Button>
          </Gatsby.Link>
        }
      />
    </div>;
  });

let default = make;
