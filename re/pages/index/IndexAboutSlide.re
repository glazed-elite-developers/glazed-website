let str = React.string;

module Styles = {
  open Css;

  let contactFormWrapper =
    style([
      backgroundColor(hex(Theme.Colors.glazedBlueMidnight)),
      marginBottom(rem(3.0)),
      padding(rem(1.0)),
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <FullPageSlide backgroundImageUrl="/images/home/slide-1-background.jpg">
    <div className=Styles.contactFormWrapper> <ContactForm /> </div>
  </FullPageSlide>;
};