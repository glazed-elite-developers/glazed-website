open React;

[@react.component]
let make =
    (
      ~children,
      ~className: option(string)=?,
      ~backgroundImageUrl: option(string)=?,
    ) => {
  let wrapperRef = useRef(Js.Nullable.null);

  useEffect(() => {
    Js.log(wrapperRef);
    None;
  });

  <FullPageSlide
    ref={ReactDOMRe.Ref.domRef(wrapperRef)} ?className ?backgroundImageUrl>
    children
  </FullPageSlide>;
};

let default = make;