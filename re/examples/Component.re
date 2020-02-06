let str = React.string;

[@react.component]
let make = () => {
  <div> {"hey" |> str} </div>;
};

let default = make;