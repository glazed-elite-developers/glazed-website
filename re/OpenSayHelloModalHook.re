open React;

let useOpenSayHelloModal = () => {
  let location: Routing.location = Routing.useLocation();
  let currentPath = location.pathname;
  let currentFullPath = Js.Global.encodeURIComponent(Routing.getFullPath(location));
  let sayHelloModalUrl = {j|$(currentPath)?modal=say-hello&backTo=$(currentFullPath)|j};
  let openSayHelloModal =
    useCallback0(event => {
      ReactEvent.Synthetic.preventDefault(event);
      Routing.navigate(sayHelloModalUrl, ~state={"preventDefaultScrollBehavior": true});
    });

  (sayHelloModalUrl, openSayHelloModal);
};
