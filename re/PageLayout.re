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
  let header = style([position(`fixed), top(`zero), right(`px(14)), left(`zero), zIndex(1)]);
  let padFloatingNav =
    style([
     paddingTop(px(75)),
     media(Breakpoints.tabletLandscape, [paddingTop(px(117))]),

    ]);
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
      ~useFloatingNavBar=false,
      ~currentPageIndex=0,
      ~onHeaderResize=?
    ) => {
    open Webapi.Url;
    let (sayHelloModalUrl, openSayHelloModal) = OpenSayHelloModalHook.useOpenSayHelloModal();
    let openedModalRef = useRef(None);
    let modalsAPI = ModalsController.useContextAPI();
    let location: Routing.location = Routing.useLocation();
    let selectedModal = location.search |> URLSearchParams.make |> URLSearchParams.get("modal");
    // Need to memoize this to avoid unnecessary header rerenders.
    let careersUrl = "https://www.careers-page.com/glazed-solutions"; // Replace with your actual URL
    let headerComponentAtTheRight =
  useMemo3(
    () => {
      <>
        <Gatsby.Link _to=careersUrl>
          <Button _type=Button.Secondary className={Styles.sayHelloButton(useDarkNavBarLinks)}>
            {React.string("> Careers")}
          </Button>
        </Gatsby.Link>
        <Gatsby.Link
          _to=sayHelloModalUrl
          onClick=openSayHelloModal
          state={
            "state": {
              "preventDefaultScrollBehavior": true,
            },
          }>
          <Button _type=Button.Secondary className={Styles.sayHelloButton(useDarkNavBarLinks)}>
            {React.string("> say hello")}
          </Button>
        </Gatsby.Link>
      </>
    },
    (sayHelloModalUrl, openSayHelloModal, useDarkNavBarLinks),
  );
    let footerComponentAtTheRight =
  useMemo2(
    () => {
      <>
        <Gatsby.Link _to=careersUrl>
          <Button _type=Button.Secondary className={Styles.mobileCloseButton}>
            {React.string("Careers")}
          </Button>
        </Gatsby.Link>
        <Gatsby.Link
          _to=sayHelloModalUrl
          onClick=openSayHelloModal
          className=Styles.mobileCloseButtonWrapper>
          <Button _type=Button.Secondary className={Styles.mobileCloseButton}>
            {React.string("> say hello")}
          </Button>
        </Gatsby.Link>
      </>
    },
    (sayHelloModalUrl, openSayHelloModal),
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
        | Some("job-offer") =>
          let modal =
            modalsAPI.openModal((~id as modalId, ~onClose) => <JobOfferModal modalId onClose />);
          openedModalRef.current = Some(modal);
        |_ => ()
        };
        ();
        None;
      },
      [|selectedModal|],
    );



    <div className=?{combineClassNames([
      Some(Styles.wrapper),
      className,
      Some(useFloatingNavBar ? Styles.padFloatingNav : "")])}>
      {
        useFloatingNavBar ?
        <FloatingHeader
            className=?{combineClassNames([Some(Styles.header), headerClassName])}
            useDarkNavBarLinks
            currentPageIndex
            componentAtTheRight=headerComponentAtTheRight
          />
        : <Header
          className=?{combineClassNames([Some(Styles.header), headerClassName])}
          style=?headerStyle
          useDarkNavBarLinks
          currentPageIndex
          onResize=?onHeaderResize
          componentAtTheRight=headerComponentAtTheRight
        />
      }
      children
      <MobileFooter currentPageIndex componentAtTheRight=footerComponentAtTheRight />
    </div>;
  });

let default = make;
