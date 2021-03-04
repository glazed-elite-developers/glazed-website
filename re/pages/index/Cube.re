open Utils.React;
module Styles = {
  open Css;

  module Variables = {
    let rawCubeSize = 250;
    let cubeSize = `px(rawCubeSize);
    let cubeDimensions = `px(rawCubeSize * 2);
    let cubePerspective = `px(rawCubeSize * 8);
  };

  let wrapper = style([
    perspective(Variables.cubePerspective),
    perspectiveOrigin(Variables.cubeSize, Variables.cubeSize),
    width(Variables.cubeDimensions),
    height(Variables.cubeDimensions),
    filter([`blur(`px(1))])
  ]);

  let cube = style([
    position(`absolute),
    transformStyle(`preserve3d),
    transformOrigin(Variables.cubeSize, Variables.cubeSize),
  ]);

  let cubeFace = style([
    width(Variables.cubeDimensions),
    height(Variables.cubeDimensions),
    opacity(0.8),
    position(`absolute),
    boxShadow(Shadow.box(~x=`zero, ~y=`zero, ~blur=px(5), ~spread=`zero, rgba(83, 211, 255, 1.)))
  ]);


  let front = style([
    transform(`translateZ(Variables.cubeSize)),
    border(px(1), `solid, rgba(83, 211, 255, 1.))
  ]);

  let back = style([
    transforms([`translateZ(`px(Variables.rawCubeSize * -1)), `rotateY(`deg(180.))]),
    border(px(1), `solid, rgba(83, 211, 255, 0.2)),
    transformOrigin(`percent(50.), `percent(50.)),
  ]);

  let right = style([
    transforms([ `translateX(Variables.cubeSize), `rotateY(`deg(-270.))]),
    transformOrigin(`percent(0.), `percent(100.)),
    border(px(1), `solid, rgba(83, 211, 255, 1.)),
    borderLeftStyle(`none)
  ]);

  let left = style([
    transforms([ `translateX(`px(Variables.rawCubeSize * -1)), `rotateY(`deg(270.))]),
    transformOrigin(`percent(50.), `percent(0.)),
    border(px(1), `solid, rgba(83, 211, 255, 1.)),
    borderRightStyle(`none)
  ]);

  let top = style([
    transforms([ `translateY(`px(Variables.rawCubeSize * -1)), `rotateX(`deg(90.))]),
    transformOrigin(`percent(0.), `percent(50.)),
  ]);

  let bottom = style([
    transforms([ `translateY(Variables.cubeSize), `rotateX(`deg(-90.))]),
    transformOrigin(`percent(100.), `percent(50.)),
  ]);
};

[@react.component]
let make =
    (
      ~className=?
    ) => {
    <div className=?{combineClassNames([Some(Styles.wrapper), className])}>
      <div className=Styles.cube>
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.front)])} />
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.back)])} />
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.top)])} />
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.bottom)])} />
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.left)])} />
        <div className=?{combineClassNames([Some(Styles.cubeFace), Some(Styles.right)])} />
      </div>
    </div>
  };

let default = make;
