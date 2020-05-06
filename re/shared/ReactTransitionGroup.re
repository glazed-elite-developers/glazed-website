module TransitionGroup = {
  [@bs.module "react-transition-group"] [@react.component]
  external make: (~children: React.element) => React.element = "TransitionGroup";
};

module Transition = {
  [@bs.module "react-transition-group"] [@react.component]
  external make:
    (
      ~children: React.element,
      ~onEnter: option(unit => unit)=?,
      ~onEntering: option(unit => unit)=?,
      ~onExit: option(unit => unit)=?,
      ~onExiting: option(unit => unit)=?,
      ~onExited: option(unit => unit)=?,
      ~timeout: int,
      ~_in: bool
    ) =>
    React.element =
    "Transition";
};
