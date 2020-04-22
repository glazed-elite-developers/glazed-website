open React;

module Styles = {
  open Css;
  open Theme;

  let wrapper = style([backgroundColor(hex(Colors.glazedBlueDark))]);
  let contentWrapper = style([alignItems(`stretch)]);
  let content =
    style([
      position(`relative),
      padding4(
        ~top=rem(4.1875),
        ~bottom=rem(4.1875),
        ~left=rem(1.25),
        ~right=rem(1.25),
      ),
      display(`flex),
      flexDirection(`column),
      justifyContent(`flexEnd),
      flex3(~grow=1., ~shrink=0., ~basis=`auto),
      media(
        Breakpoints.tabletLandscape,
        [
          justifyContent(`flexStart),
          padding4(
            ~top=rem(6.25),
            ~bottom=rem(6.25),
            ~left=rem(4.75),
            ~right=rem(2.5),
          ),
        ],
      ),
    ]);
  let closeButtonWrapper =
    style([
      display(`none),
      media(
        Breakpoints.tabletLandscape,
        [
          display(`flex),
          position(`absolute),
          top(`zero),
          right(`zero),
          textDecoration(`none),
        ],
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
};

[@react.component]
let make = (~modalId, ~onClose, ~_in=true, ~onExited=() => ()) => {
  let close = useCallback0(() => {Js.log("Close")});
  <BaseModal
    modalId
    onClose
    _in
    onExited
    scrollContainerClassName=Styles.wrapper
    contentWrapperClassName=Styles.contentWrapper
    contentClassName=Styles.content>
    <Header componentAtTheRight={React.string("sdasd")} />
  </BaseModal>;
};

let default = make;