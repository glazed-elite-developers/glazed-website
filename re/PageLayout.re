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
  let header =
    style([position(`fixed), top(`zero), right(`zero), left(`zero)]);
  let sayHelloButton = useDarkNavBarLinks =>
    style([
      display(`none),
      padding2(~v=`rem(0.875), ~h=`rem(1.75)),
      color(
        hex(useDarkNavBarLinks ? Colors.darkGreyDarker : Colors.almostWhite),
      ),
      fontSize(`rem(0.75)),
      fontFamily(Fonts.heading),
      pointerEvents(`auto),
      media(Breakpoints.tabletLandscape, [display(`block)]),
    ]);
  let mobileCloseButton =
    style([
      padding(rem(1.25)),
      background(`none),
      color(hex(Colors.almostWhite)),
      fontFamily(Fonts.heading),
      fontSize(rem(0.625)),
    ]);
};

[@react.component]
let make =
  memo(
    (~children, ~className=?, ~useDarkNavBarLinks=false, ~currentPageIndex=0) => {
    open Webapi.Url;
    let openedModalRef = useRef(None);
    let modalsAPI = ModalsController.useContextAPI();
    let url = ReasonReactRouter.useUrl();
    let selectedModal =
      url.search |> URLSearchParams.make |> URLSearchParams.get("modal");
    let currentPath = Utils.Routing.getPath(url);
    let currentFullPath =
      Js.Global.encodeURIComponent(Utils.Routing.getFullPath(url));
    let sayHelloModalUrl = {j|$(currentPath)?modal=say-hello&backTo=$(currentFullPath)|j};
    let openSayHelloModal =
      useCallback0(event => {
        ReactEvent.Synthetic.preventDefault(event);
        ReasonReactRouter.push(sayHelloModalUrl);
      });

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
          <Gatsby.Link _to=sayHelloModalUrl onClick=openSayHelloModal>
            <Button
              _type=Button.Secondary
              className={Styles.sayHelloButton(useDarkNavBarLinks)}>
              {React.string("> say hello")}
            </Button>
          </Gatsby.Link>
        }
      />
      <MobileFooter
        currentPageIndex
        componentAtTheRight={
          <Gatsby.Link _to=sayHelloModalUrl onClick=openSayHelloModal>
            <Button className=Styles.mobileCloseButton>
              {React.string("> say hello")}
            </Button>
          </Gatsby.Link>
        }
      />
    </div>;
  });

let default = make;