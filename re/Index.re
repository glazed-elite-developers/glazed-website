let str = React.string;

module Styles = {
  open Css;

  let wrapper =
    style([
      backgroundColor(hex(Theme.Colors.glazedBlue)),
      flex3(~grow=1., ~shrink=1., ~basis=`rem(0.00000001)),
      padding(rem(10.))
    ]);
};

/* For a page of static text like this one, it would be easier to just use plain React
   components since we don't get to take advantage of Reason's type system */
[@react.component]
let make = () => {
  <div className=Styles.wrapper>
    <ColorSamples />
    <h1> {"Gatsby" ++ {js| ❤ |js} ++ "ReasonML" |> str} </h1>
    <p>
      {"Use this starter to create static sites with Gatsby using ReasonML components."
       |> str}
    </p>
    <h2> {"Features" |> str} </h2>
    <ul>
      <li>
        <a href="https://github.com/reasonml/reason-react">
          {"reason-react" |> str}
        </a>
        {" for type-safe React components in ReasonML" |> str}
      </li>
      <li>
        <a href="https://github.com/SentiaAnalytics/bs-css">
          {"bs-css" |> str}
        </a>
        {" for css-in-reason styling" |> str}
      </li>
    </ul>
    <h2> {"Reference" |> str} </h2>
    <ul>
      <li>
        {"see re/Header.re for example component implementation" |> str}
      </li>
      <li>
        {"see re/types/Gatsby.re for example BuckleScript bindings to Gatsby module"
         |> str}
      </li>
    </ul>
    <SocialIconDark icon=SocialIconDark.Twitter />
    <SocialIconDark icon=SocialIconDark.Facebook />
    <SocialIconDark icon=SocialIconDark.Linkedin />
    <SocialIconDark icon=SocialIconDark.Github />
  </div>;
};

let default = make;