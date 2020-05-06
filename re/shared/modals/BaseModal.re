open React;
open Utils.React;

module Styles = {
  open Css;

  let wrapper =
    style([
      position(`absolute),
      top(`zero),
      left(`zero),
      width(pct(100.)),
      height(pct(100.)),
      zIndex(1),
      display(`flex),
      flexDirection(`column),
    ]);
  let scrollContainer =
    style([
      height(pct(100.)),
      display(`flex),
      flexDirection(`column),
      backgroundColor(rgba(74, 74, 74, 0.5)),
    ]);
  let scrollContent =
    style([
      display(`flex),
      flex3(~grow=1., ~shrink=1., ~basis=`auto),
      justifyContent(`center),
      alignItems(`center),
    ]);
  /**
   * Animation styles.
   */
  let wrapperBeforeAppearingAnimation = style([opacity(0.)]);
  let contentBeforeAppearingAnimation =
    style([opacity(0.), transform(translate3d(`zero, rem(1.), `zero))]);
  let wrapperVisible = style([opacity(1.), transition(~duration=300, "opacity")]);
  let contentVisible =
    style([
      opacity(1.),
      transform(translate3d(`zero, `zero, `zero)),
      transitions([
        Transition.shorthand(~duration=300, "transform"),
        Transition.shorthand(~duration=300, "opacity"),
      ]),
    ]);
  let wrapperLeaving = style([opacity(0.), transition(~duration=300, "opacity")]);
  let contentLeaving =
    style([
      opacity(0.),
      transform(translate3d(`zero, rem(1.), `zero)),
      transitions([
        Transition.shorthand(~duration=300, "transform"),
        Transition.shorthand(~duration=300, "opacity"),
      ]),
    ]);
};

let getAnimationClassNames = animationState => {
  switch (animationState) {
  | InOutCSSTransition.BeforeAppearing => (
      Styles.wrapperBeforeAppearingAnimation,
      Styles.contentBeforeAppearingAnimation,
    )
  | InOutCSSTransition.Visible => (Styles.wrapperVisible, Styles.contentVisible)
  | InOutCSSTransition.Leaving => (Styles.wrapperLeaving, Styles.contentLeaving)
  };
};

module Wrapper = {
  [@react.component]
  let make = (~children, ~className=?, ~onClose) => {
    let onClick =
      useCallback1(
        event => {
          ReactEvent.Synthetic.stopPropagation(event);
          onClose();
        },
        [|onClose|],
      );
    <div ?className onClick> children </div>;
  };
};

[@react.component]
module Content = {
  [@react.component]
  let make = (~children, ~className=?) => {
    let onClick = useCallback0(event => ReactEvent.Synthetic.stopPropagation(event));
    <div role="dialog" ?className onClick> children </div>;
  };
};

[@react.component]
let make =
    (
      ~children,
      ~modalId as _,
      ~onClose,
      ~className=?,
      ~scrollContainerClassName=?,
      ~contentWrapperClassName=?,
      ~contentClassName=?,
      ~_in,
      ~onExited,
    ) => {
  <InOutCSSTransition _in onExited>
    {animationState => {
       let (animationWrapperClassName, animationContentClassName) =
         getAnimationClassNames(animationState);

       <Wrapper
         className=?{
           combineClassNames([Some(Styles.wrapper), Some(animationWrapperClassName), className])
         }
         onClose>
         <ScrollContainer
           className=?{
             combineClassNames([Some(Styles.scrollContainer), scrollContainerClassName])
           }
           contentClassName=?{
             combineClassNames([Some(Styles.scrollContent), contentWrapperClassName])
           }>
           <Content
             className=?{combineClassNames([Some(animationContentClassName), contentClassName])}>
             children
           </Content>
         </ScrollContainer>
       </Wrapper>;
     }}
  </InOutCSSTransition>;
};

let default = make;
