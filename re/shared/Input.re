type tint =
  | Dark
  | Light;

let tints = {"Dark": 0, "Light": 1};

module Styles = {
  open Css;

  let wrapper = style([]);
  let label = style([color(hex("9FA8B3"))]);
  let labelInner = tint =>
    switch (tint) {
    | Dark => style([color(hex("fff"))])
    | Light => style([color(hex("000"))])
    };

  let focusStyle =
    style([borderColor(hex("2962F6")), borderBottomWidth(px(1))]);

  let nonFocusStyle = style([]);

  let inputNormal =
    style([
      backgroundColor(hex("F4F6FB")),
      transition(~duration=1, "borderWidth"),
      borderWidth(px(0)),
      color(hex("9FA8B3")),
      display(`block),
      fontFamily(Theme.Fonts.primary),
      fontSize(rem(0.69)),
      lineHeight(rem(1.44)),
      marginTop(rem(0.625)),
      width(px(327)),
      padding2(~h=rem(1.25), ~v=rem(0.93)),
      fontSize(rem(0.93)),
    ]);

  let inputTint = tint =>
    switch (tint) {
    | Dark => style([backgroundColor(hex("020A26"))])
    | Light => style([backgroundColor(hex("F4F6FB"))])
    };

  let input = (tint, focus) =>
    merge([
      inputNormal,
      inputTint(tint),
      focus ? focusStyle : nonFocusStyle,
    ]);
};

[@react.component]
let make =
    (
      ~label,
      ~placeholder,
      ~disabled=false,
      ~error="",
      ~value,
      ~onChange,
      ~tint,
      ~textArea=false,
    ) => {
  let (hasFocus, setHasFocus) = React.useState(() => false);

  let onFocus = _ => setHasFocus(_ => true);
  let onBlur = _ => setHasFocus(_ => false);

  let handleChange = event => onChange(ReactEvent.Form.target(event)##value);

  <div className=Styles.wrapper>
    <label className=Styles.label>
      {"<input \"" |> ReasonReact.string}
      <span className={Styles.labelInner(tint)}> label </span>
      {"\">" |> ReasonReact.string}
    </label>
    {textArea
       ? <textarea
           placeholder
           className={Styles.input(tint, hasFocus)}
           onChange=handleChange
           value
           onFocus
           onBlur
         />
       : <input
           placeholder
           className={Styles.input(tint, hasFocus)}
           onChange=handleChange
           value
           onFocus
           onBlur
         />}
  </div>;
};

let default = make;