[@bs.module] external twitter: string = "static/images/icon_twitter_bright.svg";
[@bs.module] external facebook: string = "static/images/icon_facebook_bright.svg";
[@bs.module] external linkedin: string = "static/images/icon_linkedin_bright.svg";
[@bs.module] external github: string = "static/images/icon_github_bright.svg";

type icon =
  | Twitter
  | Facebook
  | Linkedin
  | Github;

[@react.component]
let make = (~icon: icon) => {
  let iconSource = switch (icon) {
    | Twitter => twitter
    | Facebook => facebook
    | Linkedin => linkedin
    | Github => github
  };
  <img src=iconSource />;
};

let default = make;