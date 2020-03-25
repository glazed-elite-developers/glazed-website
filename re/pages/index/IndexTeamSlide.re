// module Styles = {
//   open Css;
// };

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <FullPageSlide backgroundImageUrl="/images/home/slide-1-background.jpg">
    <Team />
  </FullPageSlide>;
};

let default = make;