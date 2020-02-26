type asset = {
  id: string,
  viewBox: string,
};
[@bs.get] external getId: asset => string = "id";
[@bs.get] external getViewBox: asset => string = "viewBox";

[@react.component]
let make = (~className=?, ~height=?, ~asset: asset) => {
  <svg viewBox={getViewBox(asset)} ?className ?height>
    <use xlinkHref={"#" ++ getId(asset)} />
  </svg>;
};

let default = make;