[@bs.send] external dispatchEvent: (Dom.window, Dom.event) => unit = "dispatchEvent";

[@bs.send]
external pushState: (Dom.history, ~state: Js.t({..}), [@bs.as ""] _, ~href: string) => unit =
  "pushState";

[@bs.send]
external replaceState: (Dom.history, ~state: Js.t({..}), [@bs.as ""] _, ~href: string) => unit =
  "replaceState";

[@bs.val] external event: 'a = "Event";

[@bs.new] external makeEventIE11Compatible: string => Dom.event = "Event";

[@bs.val] [@bs.scope "document"]
external createEventNonIEBrowsers: string => Dom.event = "createEvent";

[@bs.send] external initEventNonIEBrowsers: (Dom.event, string, bool, bool) => unit = "initEvent";

let keyLength = 6;

let createKey = () =>
  Js.Math.random() |> Belt.Float.toString |> Js.String.substrAtMost(~from=2, ~length=keyLength);

let safeMakeEvent = eventName =>
  if (Js.typeof(event) == "function") {
    makeEventIE11Compatible(eventName);
  } else {
    let event = createEventNonIEBrowsers("Event");
    initEventNonIEBrowsers(event, eventName, true, true);
    event;
  };

let push = (~state=?, path) =>
  switch ([%external history], [%external window]) {
  | (None, _)
  | (_, None) => ()
  | (Some((history: Dom.history)), Some((window: Dom.window))) =>
    let nextState =
      switch (state) {
      | None => Js.Obj.empty()
      | Some(state') => {"key": createKey(), "state": state'}
      };
    pushState(history, ~state=nextState, ~href=path);
    dispatchEvent(window, safeMakeEvent("popstate"));
  };

let replace = (~state=?, path) =>
  switch ([%external history], [%external window]) {
  | (None, _)
  | (_, None) => ()
  | (Some((history: Dom.history)), Some((window: Dom.window))) =>
    let nextState =
      switch (state) {
      | None => Js.Obj.empty()
      | Some(state') => {"key": createKey(), "state": state'}
      };
    replaceState(history, ~state=nextState, ~href=path);
    dispatchEvent(window, safeMakeEvent("popstate"));
  };
