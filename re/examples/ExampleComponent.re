[@bs.module] external image: string = "assets/examples/bunny.jpg";

let str = React.string;

[@react.component]
let make = () => {
  <div> {React.string("This is a bunny:")} <img src=image /> </div>;
};

let default = make;