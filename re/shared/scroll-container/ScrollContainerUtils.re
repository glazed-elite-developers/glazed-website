let isIOSDevice = false;

let scrollElementIfOnLimit = element => {
  open Webapi.Dom;
  let top = Element.scrollTop(element);

  if (top <= 0.) {
    Element.setScrollTop(element, 1.);
  } else {
    switch (Element.asHtmlElement(element)) {
    | None => ()
    | Some(htmlElement) =>
      if (Belt.Int.fromFloat(top) >= Element.scrollHeight(element)
          - HtmlElement.offsetHeight(htmlElement)) {
        Element.setScrollTop(element, top -. 1.);
      }
    };
  };
};

let preventRubberBandScroll = (handler, event: ReactEvent.Touch.t) => {
//   if (isIOSDevice) {
//     Webapi.Dom.(
//       scrollElementIfOnLimit(
//         event
//         |> ReactEvent.Touch.nativeEvent
//         |> Event.t
//         |> EventTarget.unsafeAsElement,
//       )
//     );
//   };

  handler(event);
};