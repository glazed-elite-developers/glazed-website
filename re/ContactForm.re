let str = React.string;

type mode =
  | Normal
  | Wide;

let modes = {"Normal": 0, "Wide": 1};

module Styles = {
  open Css;
  let labelInner = tint =>
    switch (tint) {
    | Normal => style([color(hex("fff"))])
    | Wide => style([color(hex("000"))])
    };
  let container = style([display(`flex), flexDirection(`column)]);
  let title =
    style([
      color(hex("ffffff")),
      fontSize(rem(1.125)),
      marginBottom(rem(2.0)),
    ]);
  let subtitle =
    style([
      color(hex("feffef")),
      fontSize(rem(0.75)),
      opacity(0.5),
      marginBottom(rem(1.)),
    ]);
  let anchor = style([color(hex("2560F2"))]);
  let field = style([display(`flex), margin2(~v=rem(0.1), ~h=`zero)]);
  let fields =
    style([
      display(`flex),
      flexDirection(`column),
      width(`percent(50.0)),
    ]);
  let adaptiveFieldsContainer = mode =>
    switch (mode) {
    | Normal => style([display(`flex), flexDirection(`column)])
    | Wide => style([display(`flex), flexDirection(`row)])
    };
  let button =
    style([
      width(rem(5.0)),
      marginTop(rem(1.25)),
      backgroundColor(hex("2962F6")),
      width(rem(7.5)),
      height(rem(2.5)),
      color(hex("FFFFFF")),
      borderColor(`transparent),
    ]);
};

[@react.component]
let make = (~mode=Normal) => {
  let (name, baseSetName) = React.useState(() => "");
  let (email, baseSetEmail) = React.useState(() => "");
  let (message, baseSetMessage) = React.useState(() => "");

  let setName = value => {
    baseSetName(_ => value);
  };
  let setEmail = value => {
    baseSetEmail(_ => value);
  };
  let setMessage = value => {
    baseSetMessage(_ => value);
  };

  let handleSubmit = _value => {
    Js.log("submitting");
  };

  <div className=Styles.container>
    <div className={Styles.adaptiveFieldsContainer(mode)}>
      <div className=Styles.fields>
        <div className=Styles.field>
          <Input
            label={"your name" |> str}
            value=name
            onChange=setName
            placeholder="Name"
            tint=Input.Light
          />
        </div>
        <div className=Styles.field>
          <Input
            label={"your email" |> str}
            value=email
            onChange=setEmail
            placeholder="Email"
            tint=Input.Light
          />
        </div>
      </div>
      <div className=Styles.fields>
        <div className=Styles.field>
          <Input
            label={"your subject" |> str}
            value=message
            onChange=setMessage
            placeholder="Subject"
            textArea=true
            tint=Input.Light
          />
        </div>
      </div>
    </div>
    <button className=Styles.button onClick=handleSubmit>
      {"submit" |> str}
    </button>
  </div>;
};

let default = make;